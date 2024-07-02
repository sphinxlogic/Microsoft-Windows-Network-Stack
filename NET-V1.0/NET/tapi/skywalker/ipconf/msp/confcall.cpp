/*++

Copyright (c) 1997  Microsoft Corporation

Module Name:

    confcall.cpp 

Abstract:

    This module contains implementation of CIPConfMSPCall.

Author:
    
    Mu Han (muhan)   5-September-1998

--*/
#include "stdafx.h"
#include <confpdu.h>

CIPConfMSPCall::CIPConfMSPCall()
    : m_fLocalInfoRetrieved(FALSE),
    m_fShutDown(FALSE),
    m_dwIPInterface(INADDR_ANY),
    m_LoopbackMode(MM_NO_LOOPBACK),
    m_hAudioRTPSession(NULL),
    m_hVideoRTPSession(NULL),
    m_pIAudioDuplexController(NULL),
    m_fCallStarted(FALSE),
    m_pApplicationID(NULL),
    m_pApplicationGUID(NULL),
    m_pSubIDs(NULL),
    m_pCallQCRelay(NULL)
{
    ZeroMemory(m_InfoItems, sizeof(m_InfoItems));
}

CIPConfMSPCall::~CIPConfMSPCall()
{
    if (m_pApplicationID)
    {
        SysFreeString(m_pApplicationID);
    }

    if (m_pApplicationGUID)
    {
        SysFreeString(m_pApplicationGUID);
    }

    if (m_pSubIDs)
    {
        SysFreeString(m_pSubIDs);
    }

    if (m_pCallQCRelay)
    {
        delete m_pCallQCRelay;
    }
}

STDMETHODIMP CIPConfMSPCall::CreateStream(
    IN      long                lMediaType,
    IN      TERMINAL_DIRECTION  Direction,
    IN OUT  ITStream **         ppStream
    )
{
    // This MSP doesn't support creating new streams on the fly.
    return TAPI_E_NOTSUPPORTED;
}

STDMETHODIMP CIPConfMSPCall::RemoveStream(
    IN      ITStream *          pStream
    )
{
    // This MSP doesn't support removing streams either.
    return TAPI_E_NOTSUPPORTED;
}

HRESULT CIPConfMSPCall::InitializeLocalParticipant()
/*++

Routine Description:

    This function uses the RTP filter to find out the local information that
    will be used in the call. The infomation is stored in a local participant 
    object.

Arguments:
    
Return Value:

    HRESULT.

--*/
{
    m_fLocalInfoRetrieved = FALSE;

    // Create the RTP fitler.
    IRtpSession *pIRtpSession;

    HRESULT hr = CoCreateInstance(
            __uuidof(MSRTPSourceFilter),
            NULL,
            CLSCTX_INPROC_SERVER | CLSCTX_NO_CODE_DOWNLOAD,
            __uuidof(IRtpSession),
            (void **) &pIRtpSession
            );
    
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "can't create RTP filter for local info. %x", hr));
        return hr;
    }

    // Get the available local SDES info from the filter.
    WCHAR Buffer[MAX_PARTICIPANT_TYPED_INFO_LENGTH + 1];

    for (int i = 0; i < NUM_SDES_ITEMS; i ++)
    {
        DWORD dwLen = MAX_PARTICIPANT_TYPED_INFO_LENGTH;
        
        hr = pIRtpSession->GetSdesInfo(
            RTPSDES_CNAME + i,
            Buffer,
            &dwLen,
            0           // local participant
            );
        
        if (SUCCEEDED(hr) && dwLen > 0)
        {
            _ASSERT(dwLen <= MAX_PARTICIPANT_TYPED_INFO_LENGTH);

            // allocate memory to store the string.
            m_InfoItems[i] = (WCHAR *)malloc((dwLen) * sizeof(WCHAR));
            if (m_InfoItems[i] == NULL)
            {
                LOG((MSP_ERROR, "out of mem for local info"));

                pIRtpSession->Release();
                return E_OUTOFMEMORY;
            }
    
            lstrcpynW(m_InfoItems[i], Buffer, dwLen);
        }
    }

    pIRtpSession->Release();

    m_fLocalInfoRetrieved = TRUE;

    return S_OK;
}


HRESULT CIPConfMSPCall::Init(
    IN      CMSPAddress *       pMSPAddress,
    IN      MSP_HANDLE          htCall,
    IN      DWORD               dwReserved,
    IN      DWORD               dwMediaType
    )
/*++

Routine Description:

    This method is called when the call is first created. It sets
    up the streams based on the mediatype specified.

Arguments:
    
    pMSPAddress - The pointer to the address object.

    htCall      - The handle to the Call in TAPI's space. 
                    Used in sending events.

    dwReserved  - Reserved.

    dwMediaType - The media type of this call.

Return Value:

    HRESULT.

--*/
{
    LOG((MSP_TRACE, 
        "IPConfMSP call %x initialize entered,"
        " pMSPAddress:%x, htCall %x, dwMediaType %x",
        this, pMSPAddress, htCall, dwMediaType
        ));

#ifdef DEBUG_REFCOUNT
    if (g_lStreamObjects != 0)
    {
        LOG((MSP_ERROR, "Number of Streams alive: %d", g_lStreamObjects));
//        DebugBreak();
    }
#endif

    // initialize the participant array so that the array is not NULL.
    if (!m_Participants.Grow())
    {
        LOG((MSP_ERROR, "out of mem for participant list"));
        return E_OUTOFMEMORY;
    }

    // Call the base class's init.
    HRESULT hr= CMSPCallMultiGraph::Init(
        pMSPAddress, 
        htCall, 
        dwReserved, 
        dwMediaType
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "MSPCallMultiGraph init failed:%x", hr));
        return hr;
    }

    // create the quality control relay for this call.
    m_pCallQCRelay = new CCallQualityControlRelay ();
    if (NULL == m_pCallQCRelay)
    {
        LOG((MSP_ERROR, "call init: failed to create call quality control relay:%x", hr));
        return E_OUTOFMEMORY;
    }

    // initialize qc relay, a thread will be started
    if (FAILED (hr = m_pCallQCRelay->Initialize (this)))
    {
        LOG ((MSP_ERROR, "call init: failed to initialize qc relay. %x", hr));
        return hr;
    }

    // create streams based on the media types.
    if (dwMediaType & TAPIMEDIATYPE_AUDIO)
    {
        ITStream * pStream;

        // create a stream object.
        hr = InternalCreateStream(TAPIMEDIATYPE_AUDIO, TD_RENDER, &pStream);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "create audio render stream failed:%x", hr));
            return hr;
        }

        // The stream is already in our array, we don't need this pointer.
        pStream->Release();

        // create a stream object.
        hr = InternalCreateStream(TAPIMEDIATYPE_AUDIO, TD_CAPTURE, &pStream);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "create audio capture stream failed:%x", hr));
            return hr;
        }

        // The stream is already in our array, we don't need this pointer.
        pStream->Release();
    }

    if (dwMediaType & TAPIMEDIATYPE_VIDEO)
    {
        ITStream * pStream;

        // create a stream object.
        hr = InternalCreateStream(TAPIMEDIATYPE_VIDEO, TD_RENDER, &pStream);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "create video render stream failed:%x", hr));
            return hr;
        }

        // The stream is already in our array, we don't need this pointer.
        pStream->Release();

        // create a stream object.
        hr = InternalCreateStream(TAPIMEDIATYPE_VIDEO, TD_CAPTURE, &pStream);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "create video capture stream failed:%x", hr));
            return hr;
        }

        // The stream is already in our array, we don't need this pointer.
        pStream->Release();
    }
    
    DWORD dwLoopback = 0;
    if (TRUE == ::GetRegValue(gszMSPLoopback, &dwLoopback) && dwLoopback != 0)
    {
        m_LoopbackMode = MULTICAST_LOOPBACK_MODE(dwLoopback);
    }

    m_fShutDown = FALSE;
    
    return S_OK;
}

HRESULT CIPConfMSPCall::ShutDown()
/*++

Routine Description:

    Shutdown the call. 

Arguments:
    
Return Value:

    HRESULT.

--*/
{
    InternalShutDown();

    // acquire the lock on call.
    m_lock.Lock();

    for (int i = 0; i < NUM_SDES_ITEMS; i ++)
    {
        if (m_InfoItems[i])
        {
            free(m_InfoItems[i]);
            m_InfoItems[i] = NULL;
        }
    }

    m_lock.Unlock();

    return S_OK;
}

HRESULT CIPConfMSPCall::InternalShutDown()
/*++

Routine Description:

    First call the base class's shutdown and then release all the participant
    objects.

Arguments:
    
Return Value:

    HRESULT.

--*/
{
    LOG((MSP_TRACE, "ConfMSPCall.InternalShutdown, entered"));

    // acquire the lock on the call.
    m_lock.Lock();

    if (m_fShutDown)
    {
        LOG((MSP_TRACE, "ConfMSPCall::InterShutdown, already shutdown"));
        m_lock.Unlock ();
        return S_OK;
    }

    m_fShutDown = TRUE;

    if (m_pCallQCRelay)    
    {
        m_pCallQCRelay->Shutdown ();
    }

	int i;

    // Shutdown all the streams
    for (i = m_Streams.GetSize() - 1; i >= 0; i --)
    {
        UnregisterWaitEvent(i);
        ((CMSPStream*)m_Streams[i])->ShutDown();
    }
    m_ThreadPoolWaitBlocks.RemoveAll();

    // release all the streams
    for (i = m_Streams.GetSize() - 1; i >= 0; i --)
    {
        m_Streams[i]->Release();
    }
    m_Streams.RemoveAll();

    if (m_pIAudioDuplexController)
    {
        m_pIAudioDuplexController->Release();
        m_pIAudioDuplexController = NULL;	
    }

    m_lock.Unlock();

    // release all the participants
    m_ParticipantLock.Lock();

    for (i = 0; i < m_Participants.GetSize(); i ++)
    {
        m_Participants[i]->Release();
    }
    m_Participants.RemoveAll();

    m_ParticipantLock.Unlock();

    return S_OK;
}

template <class T>
HRESULT CreateStreamHelper(
    IN      T *                     pT,
    IN      HANDLE                  hAddress,
    IN      CIPConfMSPCall*         pMSPCall,
    IN      IMediaEvent *           pGraph,
    IN      DWORD                   dwMediaType,
    IN      TERMINAL_DIRECTION      Direction,
    OUT     ITStream **             ppITStream
    )
/*++

Routine Description:

    Create a stream object and initialize it. This method is called internally
    to create a stream object of different class.

Arguments:
    
    hAddress    - the handle to the address object.

    pCall       - the call object.

    pGraph      - the filter graph for this stream.

    dwMediaType - the media type of the stream. 

    Direction   - the direction of the steam.
    
    ppITStream  - the interface on this stream object.

Return Value:

    HRESULT.

--*/
{
    ENTER_FUNCTION ("CreateStreamHelper");

    CComObject<T> * pCOMMSPStream;

    HRESULT hr;

    hr = ::CreateCComObjectInstance(&pCOMMSPStream);

    if (NULL == pCOMMSPStream)
    {
        LOG((MSP_ERROR, "CreateMSPStream:could not create stream:%x", hr));
        return hr;
    }

    // get the interface pointer.
    hr = pCOMMSPStream->_InternalQueryInterface(
        __uuidof(ITStream), 
        (void **)ppITStream
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "CreateMSPStream:QueryInterface failed: %x", hr));
        delete pCOMMSPStream;
        return hr;
    }

    // Initialize the object.
    hr = pCOMMSPStream->Init(
        hAddress,
        pMSPCall, 
        pGraph,
        dwMediaType,
        Direction
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "CreateMSPStream:call init failed: %x", hr));
        (*ppITStream)->Release();
        return hr;
    }

    // retrieve inner call quality control
    IInnerCallQualityControl * pIInnerCallQC;

    if (FAILED (hr = pMSPCall->_InternalQueryInterface (
        __uuidof (IInnerCallQualityControl),
        (void **)&pIInnerCallQC
        )))
    {
        LOG ((MSP_ERROR, "%s failed to retrieve inner call qc relay: %x", __fxName, hr));
        (*ppITStream)->Release ();
        return hr;
    }

    // retrieve inner stream quality control
    IInnerStreamQualityControl *pIInnerStreamQC;

    if (FAILED (hr = (*ppITStream)->QueryInterface (
        __uuidof (IInnerStreamQualityControl),
        (void **)&pIInnerStreamQC
        )))
    {
        LOG ((MSP_ERROR, "%s failed to retrieve inner stream qc relay: %x", __fxName, hr));
        pIInnerCallQC->Release ();
        (*ppITStream)->Release ();
        return hr;
    }

    // store inner call qc
    if (FAILED (hr = pIInnerStreamQC->LinkInnerCallQC (pIInnerCallQC)))
    {
        LOG ((MSP_ERROR, "%s failed to setup inner call qc on stream, %x", __fxName, hr));

        pIInnerCallQC->Release ();
        pIInnerStreamQC->Release ();
        (*ppITStream)->Release ();
        return hr;
    }

    // register inner stream qc on the call
    hr = pIInnerCallQC->RegisterInnerStreamQC (pIInnerStreamQC);
    pIInnerStreamQC->Release ();
    pIInnerCallQC->Release ();
    if (FAILED (hr))
    {
        LOG ((MSP_ERROR, "%s failed to register inner stream qc relay: %x", __fxName, hr));
        (*ppITStream)->Release ();
        return hr;
    }

    return S_OK;
}


HRESULT CIPConfMSPCall::CreateStreamObject(
    IN      DWORD               dwMediaType,
    IN      TERMINAL_DIRECTION  Direction,
    IN      IMediaEvent *       pGraph,
    IN      ITStream **         ppStream
    )
/*++

Routine Description:

    Create a media stream object based on the mediatype and direction.

Arguments:
    
    pMediaType  - TAPI3 media type.

    Direction   - direction of this stream.

    IMediaEvent - The filter graph used in this stream.

    ppStream    - the return pointer of the stream interface

Return Value:

    HRESULT.

--*/
{
    LOG((MSP_TRACE, "CreateStreamObject, entered"));

    HRESULT      hr = S_OK;
    ITStream   * pIMSPStream = NULL;

    // Create a stream object based on the media type.
    if (dwMediaType == TAPIMEDIATYPE_AUDIO)
    {
        if (Direction == TD_RENDER)
        {
            CStreamAudioRecv *pAudioRecv = NULL;
            hr = ::CreateStreamHelper(
                pAudioRecv,
                m_pMSPAddress,
                this, 
                pGraph,
                TAPIMEDIATYPE_AUDIO,
                TD_RENDER,
                &pIMSPStream
                );
            LOG((MSP_TRACE, "create audio receive:%x, hr:%x", pIMSPStream,hr));

            if (FAILED(hr))
            {
                LOG((MSP_ERROR, "create stream failed. %x", hr));
                return hr;
            }
            
            if (FAILED(hr = InitFullDuplexControler()))
            {
                LOG((MSP_ERROR, "Create full duplex controller failed. %x", hr));
            }
            else
            {
                ((CStreamAudioRecv *)pIMSPStream)->
                    SetFullDuplexController(m_pIAudioDuplexController);
            }
        }
        else if (Direction == TD_CAPTURE)
        {
            CStreamAudioSend *pAudioSend = NULL;
            hr = ::CreateStreamHelper(
                pAudioSend,
                m_pMSPAddress,
                this, 
                pGraph,
                TAPIMEDIATYPE_AUDIO,
                TD_CAPTURE,
                &pIMSPStream
                );
            LOG((MSP_TRACE, "create audio send:%x, hr:%x", pIMSPStream,hr));

            if (FAILED(hr))
            {
                LOG((MSP_ERROR, "create stream failed. %x", hr));
                return hr;
            }

            if (FAILED(hr = InitFullDuplexControler()))
            {
                LOG((MSP_ERROR, "Create full duplex controller failed. %x", hr));
            }
            else
            {
                ((CStreamAudioSend *)pIMSPStream)->
                    SetFullDuplexController(m_pIAudioDuplexController);
            }
        }
        else
        {
            return TAPI_E_INVALIDDIRECTION;
        }
    }
    else if (dwMediaType == TAPIMEDIATYPE_VIDEO)
    {
        if (Direction == TD_RENDER)
        {
            CStreamVideoRecv *pVideoRecv = NULL;
            hr = ::CreateStreamHelper(
                pVideoRecv,
                m_pMSPAddress,
                this, 
                pGraph,
                TAPIMEDIATYPE_VIDEO,
                TD_RENDER,
                &pIMSPStream
                );
            LOG((MSP_TRACE, "create video Recv:%x, hr:%x", pIMSPStream,hr));

            if (FAILED(hr))
            {
                LOG((MSP_ERROR, "create stream failed. %x", hr));
                return hr;
            }
        }
        else if (Direction == TD_CAPTURE)
        {
            CStreamVideoSend *pVideoSend = NULL;
            hr = ::CreateStreamHelper(
                pVideoSend,
                m_pMSPAddress,
                this, 
                pGraph,
                TAPIMEDIATYPE_VIDEO,
                TD_CAPTURE,
                &pIMSPStream
                );
            LOG((MSP_TRACE, "create video send:%x, hr:%x", pIMSPStream,hr));

            if (FAILED(hr))
            {
                LOG((MSP_ERROR, "create stream failed. %x", hr));
                return hr;
            }
        }
        else
        {
            return TAPI_E_INVALIDDIRECTION;
        }
    }
    else
    {
        return TAPI_E_INVALIDMEDIATYPE;
    }

    *ppStream = pIMSPStream;

    return S_OK;
}

DWORD CIPConfMSPCall::FindInterfaceByName(IN WCHAR *pMachineName)
/*++

Routine Description:

    Given the machine name of the originator, find out which local interface
    can be used to reach that machine.

Arguments:
    
    pMachineName - The machine name of the originator.
    
Return Value:

    INADDR_NONE - nothing can be found.
    valid IP - succeeded.

--*/
{
    char buffer[MAXIPADDRLEN + 1];

    if (WideCharToMultiByte(
        GetACP(),
        0,
        pMachineName,
        -1,
        buffer,
        MAXIPADDRLEN,
        NULL,
        NULL
        ) == 0)
    {
        LOG((MSP_ERROR, "can't convert originator's address:%ws", pMachineName));

        return INADDR_NONE;
    }

    DWORD dwAddr;
    if ((dwAddr = inet_addr(buffer)) != INADDR_NONE)
    {
        dwAddr = ntohl(dwAddr);

        LOG((MSP_INFO, "originator's IP:%x", dwAddr));
        
        return ((CIPConfMSP *)m_pMSPAddress)->FindLocalInterface(dwAddr);
    }

    struct hostent * pHost;

    // attempt to lookup hostname
    pHost = gethostbyname(buffer);

    // validate pointer
    if (pHost == NULL) 
    {
        LOG((MSP_WARN, "can't resolve address:%s", buffer));
        return INADDR_NONE;

    }

    // for each of the addresses returned, find the local interface.
    for (DWORD i = 0; TRUE; i ++)
    {
        if (pHost->h_addr_list[i] == NULL)
        {
            break;
        }

        // retrieve host address from structure
        dwAddr = ntohl(*(unsigned long *)pHost->h_addr_list[i]);

        LOG((MSP_INFO, "originator's IP:%x", dwAddr));
        
        DWORD dwInterface = 
            ((CIPConfMSP *)m_pMSPAddress)->FindLocalInterface(dwAddr);

        if (dwInterface != INADDR_NONE)
        {
            return dwInterface;
        }
    }

    return INADDR_NONE;
}

HRESULT CIPConfMSPCall::CheckOrigin(
    IN      ITSdp *     pITSdp, 
    OUT     BOOL *      pFlag,
    OUT     DWORD *     pdwIP
    )
/*++

Routine Description:

    Check to see if the current user is the originator of the conference.
    If he is, he can send to a receive only conference.

Arguments:
    
    pITSdp  - a pointer to the ITSdp interface.

    pFlag   - The result.

    pdwIP   - The local IP interface that should be used to reach the originator.
    
Return Value:

    HRESULT.

--*/
{
    const DWORD MAXUSERNAMELEN = 127;
    DWORD dwUserNameLen = MAXUSERNAMELEN;
    WCHAR szUserName[MAXUSERNAMELEN+1];

    // determine the name of the current user
    if (!GetUserNameW(szUserName, &dwUserNameLen))
    {
        LOG((MSP_ERROR, "cant' get user name. %x", GetLastError()));
        return E_UNEXPECTED;
    }

    LOG((MSP_INFO, "current user: %ws", szUserName));

    // find out if the current user is the originator of the conference.
    BSTR Originator = NULL;
    HRESULT hr = pITSdp->get_Originator(&Originator);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "cant' get originator. %x", hr));
        return hr;
    }

    LOG((MSP_INFO, "originator: %ws", Originator));

    *pFlag = (_wcsnicmp(szUserName, Originator, lstrlenW(szUserName)) == 0);
    
    SysFreeString(Originator);
    
    // Get the machine IP address of the originator.
    BSTR MachineAddress = NULL;
    hr = pITSdp->get_MachineAddress(&MachineAddress);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "cant' get MachineAddress. %x", hr));
        return hr;
    }

    LOG((MSP_INFO, "MachineAddress: %ws", MachineAddress));

    DWORD dwIP = FindInterfaceByName(MachineAddress);

    SysFreeString(MachineAddress);

    *pdwIP = dwIP;

    LOG((MSP_INFO, "Interface to use:%x", *pdwIP));
    
    return S_OK;
}


HRESULT GetAddress(
    IN      IUnknown *          pIUnknown, 
    OUT     DWORD *             pdwAddress, 
    OUT     DWORD *             pdwTTL,
    OUT     BSTR *              ppKey,
    OUT     LONG *              plBandwidth,
    OUT     LONG *              plConfBandwidth = NULL
    )
/*++

Routine Description:

    Get the IP address and TTL value from a connection. It is a "c=" line
    in the SDP blob.

Arguments:
    
    pIUnknow    - an object that might contain connection information.

    pdwAddress  - the mem address to store the IP address.

    pdwTTL      - the mem address to store the TTL value.

    plBandwidth - maximum bandwidth
Return Value:

    HRESULT.

--*/
{
    // query for the ITConnection i/f
    CComPtr<ITConnection> pITConnection;
    HRESULT hr = pIUnknown->QueryInterface(__uuidof(ITConnection), (void **)&pITConnection);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get connection interface. %x", hr));
        return hr;
    }

    // clear 
    if (plConfBandwidth != NULL) *plConfBandwidth = QCDEFAULT_QUALITY_UNSET;

    // get bandwidth
    const WCHAR * const AS = L"AS";
    const WCHAR * const CT = L"CT";
    BSTR pModifier = NULL;
    DOUBLE bandwidth;

    if (FAILED (hr = pITConnection->get_BandwidthModifier (&pModifier)))
    {
        *plBandwidth = QCDEFAULT_QUALITY_UNSET;
        // bandwidth modifier may not be presented
        // LOG ((MSP_TRACE, "get bandwidth modifiler. %x", hr));
    }
    else if (_wcsnicmp (AS, pModifier, lstrlenW (AS)) != 0)
    {
        // if not application specific
        *plBandwidth = QCDEFAULT_QUALITY_UNSET;

        // check conference-wide bandwidth limit
        if (_wcsnicmp (CT, pModifier, lstrlenW (CT)) == 0)
        {
            if (plConfBandwidth)
            {
                if (FAILED (hr = pITConnection->get_Bandwidth (&bandwidth)))
                {
                    *plConfBandwidth = QCDEFAULT_QUALITY_UNSET;
                    LOG ((MSP_ERROR, "get conf bandwidth. %x", hr));
                }
                else
                    *plConfBandwidth = (LONG)(bandwidth * 1000);
            }
        }

    }
    else if (FAILED (hr = pITConnection->get_Bandwidth (&bandwidth)))
    {
        *plBandwidth = QCDEFAULT_QUALITY_UNSET;
        LOG ((MSP_ERROR, "get bandwidth. %x", hr));
    }
    else
        *plBandwidth = (LONG)(bandwidth * 1000);

    if (pModifier)
    {
        SysFreeString (pModifier);
        pModifier = NULL;
    }

    // get the start address,
    BSTR StartAddress = NULL;
    hr = pITConnection->get_StartAddress(&StartAddress);
    if (FAILED(hr))
    {
        LOG((MSP_WARN, "get start address. %x", hr));
        return hr;
    }
    
    // Get the IP address from the string.
    const DWORD MAXIPADDRLEN = 20;
    char Buffer[MAXIPADDRLEN+1];

    // first convert the string to ascii.
    Buffer[0] = '\0';
    if (!WideCharToMultiByte(
        CP_ACP, 
        0, 
        StartAddress, 
        -1, 
        Buffer, 
        MAXIPADDRLEN, 
        NULL, 
        NULL
        ))
    {
        LOG((MSP_ERROR, "converting address. %ws", StartAddress));
        SysFreeString(StartAddress);
        return E_UNEXPECTED;
    }

    SysFreeString(StartAddress);

    // convert the string to DWORD IP address.
    DWORD dwIP = ntohl(inet_addr(Buffer));
    if (dwIP == INADDR_NONE)
    {
        LOG((MSP_ERROR, "invalid IP address. %s", Buffer));
        return E_UNEXPECTED;
    }

    // get the TTL value.
    BYTE Ttl;
    hr = pITConnection->get_Ttl(&Ttl);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "can't get TTL."));
        return hr;
    }

    // get the Encryption key.
    const WCHAR * const CLEAR = L"clear";
    VARIANT_BOOL fKeyValid;
    BSTR bstrKeyType = NULL;

    if (*ppKey)
        SysFreeString (*ppKey);

    *ppKey = NULL;

    if (FAILED (hr = pITConnection->GetEncryptionKey (&bstrKeyType, &fKeyValid, ppKey)))
    {
        LOG((MSP_WARN, "can't get EncryptionKey. %x", hr));
    }
    else if (_wcsnicmp (CLEAR, bstrKeyType, lstrlenW (CLEAR)) != 0)
    {
        if (*ppKey)
        {
            SysFreeString (*ppKey);
            *ppKey = NULL;
        }
    }

    if (bstrKeyType)
        SysFreeString (bstrKeyType);

    *pdwAddress = dwIP;
    *pdwTTL     = Ttl;

    return S_OK;
}

HRESULT CheckAttributes(
    IN      IUnknown *  pIUnknown,
    OUT     BOOL *      pbSendOnly,
    OUT     BOOL *      pbRecvOnly,
    OUT     DWORD *     pdwMSPerPacket,
    OUT     BOOL *      pbCIF
    )
/*++

Routine Description:

    Check the direction of the media, find out if it is send only or 
    receive only.

Arguments:
    
    pIUnknow    - an object that might have a attribute list.

    pbSendOnly   - the mem address to store the returned BOOL.

    pbRecvOnly   - the mem address to store the returned BOOL.

    pbCIF        - if CIF is used for video. 
    
Return Value:

    HRESULT.

--*/
{
    // query for the ITAttributeList i/f
    CComPtr<ITAttributeList> pIAttList;
    HRESULT hr = pIUnknown->QueryInterface(__uuidof(ITAttributeList), (void **)&pIAttList);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get attribute interface. %x", hr));
        return hr;
    }

    // get the number of attributes
    long lCount;
    hr = pIAttList->get_Count(&lCount);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get attribute count. %x", hr));
        return hr;
    }

    *pbRecvOnly = FALSE;
    *pbSendOnly = FALSE;
    *pdwMSPerPacket = 0;
    *pbCIF      = FALSE;

    const WCHAR * const SENDONLY = L"sendonly";
    const WCHAR * const RECVONLY = L"recvonly";
    const WCHAR * const FORMAT  = L"fmtp";
    const WCHAR * const PTIME  = L"ptime:";
    const WCHAR * const CIF  = L" CIF=";

    for (long i = 1; i <= lCount; i ++)
    {

        // get the attributes and check if sendonly of recvonly is specified.
        BSTR Attribute = NULL;
        hr = pIAttList->get_Item(i, &Attribute);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "get attribute item. %x", hr));
            return hr;
        }
        
        if (_wcsnicmp(SENDONLY, Attribute, lstrlen(SENDONLY)) == 0)
        {
            *pbSendOnly = TRUE;
        }
        else if (_wcsnicmp(RECVONLY, Attribute, lstrlen(RECVONLY)) == 0)
        {
            *pbRecvOnly = TRUE;
        }
        else if (_wcsnicmp(PTIME, Attribute, lstrlen(PTIME)) == 0)
        {
            // read the number of milliseconds per packet.
            *pdwMSPerPacket = (DWORD)_wtol(Attribute + lstrlen(PTIME));

            // RFC 1890 only requires an app to support 200ms packets.
            if (*pdwMSPerPacket > 200)
            {
                // invalid tag, we just use our default.
                *pdwMSPerPacket = 0;
            }

        }
        else if (_wcsnicmp(FORMAT, Attribute, lstrlen(FORMAT)) == 0)
        {
            if (wcsstr(Attribute, CIF))
            {
                *pbCIF = TRUE;
            }
        }

        SysFreeString(Attribute);
    }
    
    return S_OK;
}

HRESULT CIPConfMSPCall::ProcessMediaItem(
    IN      ITMedia *           pITMedia,
    IN      DWORD               dwMediaTypeMask,
    OUT     DWORD *             pdwMediaType,
    OUT     WORD *              pwPort,
    OUT     DWORD *             pdwPayloadTypes,
    IN OUT  DWORD *             pdwNumPayLoadType
    )
/*++

Routine Description:

    Process a "m=" line, find out the media type, port, and payload type.

Arguments:

    dwMediaTypeMask - the media type of this call.

    pdwMediaType    - return the media type of this media item.

    pwPort          - return the port number used for this media.

    pdwPayloadType  - an array to store the RTP payload types. 
    
    pdwNumPayLoadType -  The size of the above array. When return, it is the
        number of payload types read.

Return Value:

    HRESULT.

    S_FALSE - everything is all right but the media type is not needed.

--*/
{
    // get the name of the media.
    BSTR MediaName = NULL;
    HRESULT hr = pITMedia->get_MediaName(&MediaName);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get media name. %x", hr));
        return hr;
    }

    LOG((MSP_INFO, "media name: %ws", MediaName));

    // check if the media is audio or video.
    const WCHAR * const AUDIO = L"audio";
    const WCHAR * const VIDEO = L"video";
    const DWORD NAMELEN = 5;

    DWORD dwMediaType = 0;
    if (_wcsnicmp(AUDIO, MediaName, NAMELEN) == 0)
    {
        dwMediaType = TAPIMEDIATYPE_AUDIO;
    }
    else if (_wcsnicmp(VIDEO, MediaName, NAMELEN) == 0)
    {
        dwMediaType = TAPIMEDIATYPE_VIDEO;
    }

    SysFreeString(MediaName);

    // check if the call wants this media type.
    if ((dwMediaType & dwMediaTypeMask) == 0)
    {
        // We don't need this media type in this call.
        LOG((MSP_INFO, "media skipped."));
        return S_FALSE;
    }

    // get start port
    long  lStartPort;
    hr = pITMedia->get_StartPort(&lStartPort);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get start port. %x", hr));
        return hr;
    }

    // get the transport Protocol
    BSTR TransportProtocol = NULL;
    hr = pITMedia->get_TransportProtocol(&TransportProtocol);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get transport Protocol. %x", hr));
        return hr;
    }

    // varify that the protocol is RTP.
    const WCHAR * const RTP = L"RTP";
    const DWORD PROTOCOLLEN = 3;

    if (_wcsnicmp(RTP, TransportProtocol, PROTOCOLLEN) != 0)
    {
        LOG((MSP_ERROR, "wrong transport Protocol:%ws", TransportProtocol));
        SysFreeString(TransportProtocol);
        return S_FALSE;
    }

    SysFreeString(TransportProtocol);

    // get the format code list
    VARIANT Variant;
    VariantInit(&Variant);

    hr = pITMedia->get_FormatCodes(&Variant);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get format codes. %x", hr));
        return hr;
    }

    // Verify that the SafeArray is in proper shape.
    if(SafeArrayGetDim(V_ARRAY(&Variant)) != 1)
    {
        LOG((MSP_ERROR, "wrong dimension for the format code. %x", hr));
	    VariantClear(&Variant);
        return E_UNEXPECTED;
    }

    long lLowerBound;
    long lUpperBound;
    if (FAILED(hr = SafeArrayGetLBound(V_ARRAY(&Variant), 1, &lLowerBound))
     || FAILED(hr = SafeArrayGetUBound(V_ARRAY(&Variant), 1, &lUpperBound)))
    {
        LOG((MSP_ERROR, "Can't get the array bounds. %x", hr));
	    VariantClear(&Variant);
        return E_UNEXPECTED;
    }

    DWORD dwNumFormats = 0;
    for (long l = lLowerBound; l <= lUpperBound && dwNumFormats < *pdwNumPayLoadType; l ++)
    {
        BSTR Format = NULL;
        hr = SafeArrayGetElement(V_ARRAY(&Variant), &l, &Format);

        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "get format code. %x", hr));
            continue;
        }

        LOG((MSP_INFO, "format code: %ws", Format));
        
        pdwPayloadTypes[dwNumFormats] = (DWORD)_wtoi(Format);

        // ignore unsupported codec, including G723
        if (IsPayloadSupported(pdwPayloadTypes[dwNumFormats]))
        {
            dwNumFormats ++;
        }

        SysFreeString(Format);
    }

    // clear the variant because we don't need it any more
    VariantClear(&Variant);


    *pdwMediaType   = dwMediaType;
    *pwPort         = (WORD)lStartPort;
    *pdwNumPayLoadType = dwNumFormats;

    return S_OK;
}

HRESULT CIPConfMSPCall::ConfigStreamsBasedOnSDP(
    IN  ITSdp *     pITSdp,
    IN  DWORD       dwAudioQOSLevel,
    IN  DWORD       dwVideoQOSLevel
    )
/*++

Routine Description:

    Configure the streams based on the information in the SDP blob.

Arguments:

    pITSdp  - the SDP object. It contains parsed information.

Return Value:

    HRESULT.

--*/
{
    // find out if the current user is the originator of the conference.
    BOOL fIsOriginator;
    DWORD dwLocalInterface = INADDR_NONE;

    HRESULT hr = CheckOrigin(pITSdp, &fIsOriginator, &dwLocalInterface);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "check origin. %x", hr));
        return hr;
    }
    
    LOG((MSP_INFO, "Local interface: %x", dwLocalInterface));

    // get the start IP address and TTL value from the connection.
    DWORD dwIPGlobal, dwTTLGlobal;
    BSTR bstrKeyGlobal = NULL;
    LONG lbandwidth, lConfBandwidth;
    hr = GetAddress(pITSdp, &dwIPGlobal, &dwTTLGlobal, &bstrKeyGlobal, &lbandwidth, &lConfBandwidth);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get global address. %x", hr));
        return hr;
    }

    CLock lock(m_lock);

    // store conference bandwidth
    if (FAILED (m_pCallQCRelay->SetConfBitrate (lConfBandwidth)))
    {
        LOG ((MSP_ERROR, "bandwidth is out of range %d", lConfBandwidth));
    }

    // find out if this conference is sendonly or recvonly.
    BOOL fSendOnlyGlobal = FALSE, fRecvOnlyGlobal = FALSE, fCIF = FALSE;
    DWORD dwMSPerPacket;
    hr = CheckAttributes(
        pITSdp, &fSendOnlyGlobal, &fRecvOnlyGlobal, &dwMSPerPacket, &fCIF);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "check global attributes. %x", hr));
        return hr;
    }

    // get the media information
    CComPtr<ITMediaCollection> pICollection;
    hr = pITSdp->get_MediaCollection(&pICollection);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get the media collection. %x", hr));
        return hr;
    }

    // find out how many media sessions are in the blobl.
    long lCount;
    hr = pICollection->get_Count(&lCount);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "get number of media items. %x", hr));
        return hr;
    }

    if (lCount > 0)
    {
        // change the call into connected state since the SDP is OK.
        // We are going to set up each every streams next.
        SendTSPMessage(CALL_CONNECTED, 0);
    }

    DWORD dwNumSucceeded = 0;

    // for each media session, get info configure a stream.
    for(long i=1; i <= lCount; i++)
    {
        // get the media item first.
        ITMedia *pITMedia;
        hr = pICollection->get_Item(i, &pITMedia);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "get media item. %x", hr));
            continue;
        }

        DWORD dwMediaType;
        STREAMSETTINGS Setting;

        ZeroMemory(&Setting, sizeof(STREAMSETTINGS));

        // find out the information about the media. Here we pass in the media
        // type of call so that we won't wasting time reading the attributes
        // for a media type we don't need.
        DWORD dwNumPayloadTypes = sizeof(Setting.PayloadTypes) 
            / sizeof(Setting.PayloadTypes[0]);

        hr = ProcessMediaItem(
            pITMedia,
            m_dwMediaType,
            &dwMediaType,
            &Setting.wRTPPortRemote,
            Setting.PayloadTypes,
            &dwNumPayloadTypes
            );

        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "process media. %x", hr));
            continue;
        }
        
        Setting.dwNumPayloadTypes = dwNumPayloadTypes;

        // if the return value is S_FALSE from the previous call, this media
        // type is not needed for the call.
        if (hr != S_OK || dwNumPayloadTypes == 0)
        {
            // the media is not needed.
            continue;
        }
        
        if (dwMediaType == TAPIMEDIATYPE_AUDIO)
        {
            Setting.dwQOSLevel = dwAudioQOSLevel;
            Setting.phRTPSession = &m_hAudioRTPSession;
        }
        else
        {
            Setting.dwQOSLevel = dwVideoQOSLevel;
            Setting.phRTPSession = &m_hVideoRTPSession;
        }

        // Get the local connect information.
        DWORD dwIP, dwTTL;
        BSTR bstrKey = NULL;

        hr = GetAddress(pITMedia, &dwIP, &dwTTL, &bstrKey, &lbandwidth);
        if (FAILED(hr))
        {
            LOG((MSP_WARN, "no local address, use global one", hr));
            Setting.dwIPRemote  = dwIPGlobal;
            Setting.dwTTL       = dwTTLGlobal;
            Setting.lBandwidth = QCDEFAULT_QUALITY_UNSET;
        }
        else
        {
            Setting.dwIPRemote  = dwIP;
            Setting.dwTTL       = dwTTL;
            Setting.lBandwidth = lbandwidth;
        }

        // find out if this media is sendonly or recvonly.
        BOOL fSendOnly = FALSE, fRecvOnly = FALSE, fCIF = FALSE;
        hr = CheckAttributes(
            pITMedia, &fSendOnly, &fRecvOnly, &dwMSPerPacket, &fCIF);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "check local attributes. %x", hr));
        }
        
        fSendOnly = fSendOnly || fSendOnlyGlobal;
        fRecvOnly = (fRecvOnly || fRecvOnlyGlobal) && (!fIsOriginator);
        Setting.dwMSPerPacket = dwMSPerPacket;
        Setting.fCIF = fCIF;

        // The media item is not needed after this point.
        pITMedia->Release();

        // Go through the existing streams and find out if any stream
        // can be configured.

        // Note: we are not creating any new streams now. We might want to 
        // do it in the future if we want to support two sessions of the
        // same media type.

        m_fCallStarted = TRUE;

        for (long j = 0; j < m_Streams.GetSize(); j ++)
        {
            CIPConfMSPStream* pStream = (CIPConfMSPStream*)m_Streams[j];
        
            if ((pStream->MediaType() != dwMediaType)
                || pStream->IsConfigured()
                || (fSendOnly && pStream->Direction() == TD_RENDER)
                || (fRecvOnly && pStream->Direction() == TD_CAPTURE)
                )
            {
                // this stream should not be configured.
                continue;
            }

            // set the local interface that the call should bind to.
            Setting.dwIPLocal = m_dwIPInterface;

            if ((m_dwIPInterface == INADDR_ANY)
                && (dwLocalInterface != INADDR_NONE))
            {
                Setting.dwIPLocal = dwLocalInterface;
            }

            // set the loopback mode of the stream.
            Setting.LoopbackMode = m_LoopbackMode;

            // set the qos application IDS.
            Setting.pApplicationID = m_pApplicationID;
            Setting.pApplicationGUID = m_pApplicationGUID;
            Setting.pSubIDs = m_pSubIDs;

            // configure the stream, it will not be started.
            hr = pStream->Configure(Setting, (bstrKey) ? bstrKey : bstrKeyGlobal);
            if (FAILED(hr))
            {
               LOG((MSP_ERROR, "configure stream failed. %x", hr));
            }
        }

        SysFreeString(bstrKey);
    }

    SysFreeString(bstrKeyGlobal);

    // after configuring the streams, start them.
    for (int j = 0; j < m_Streams.GetSize(); j ++)
    {
        CIPConfMSPStream* pStream = (CIPConfMSPStream*)m_Streams[j];

        // start the stream.
        hr = pStream->FinishConfigure();
        if (SUCCEEDED(hr))
        {
            dwNumSucceeded ++;
        }
    }

    if (dwNumSucceeded == 0)
    {
        LOG((MSP_ERROR, "No media succeeded."));
        return E_FAIL;
    }

    return S_OK;        
}

HRESULT CIPConfMSPCall::ParseSDP(
    IN  WCHAR * pSDP,
    IN  DWORD dwAudioQOSLevel,
    IN  DWORD dwVideoQOSLevel
    )
/*++

Routine Description:

    Parse the SDP string. The function uses the SdpConferenceBlob object
    to parse the string.

Arguments:

    pSDP  - the SDP string.
    dwAudioQOSLevel - the QOS requirement for audio.
    dwVideoQOSLevel - the QOS requirement for video.

Return Value:

    HRESULT.

--*/
{
    // co-create an sdp conference blob component
    // query for the ITConferenceBlob interface
    CComPtr<ITConferenceBlob>   pIConfBlob;   

    HRESULT hr = ::CoCreateInstance(
        CLSID_SdpConferenceBlob,
        NULL,
        CLSCTX_INPROC_SERVER | CLSCTX_NO_CODE_DOWNLOAD,
        __uuidof(ITConferenceBlob),
        (void **)&pIConfBlob
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "creating a SDPBlob object. %x", hr));
        return hr;
    }
    
    // conver the sdp into a BSTR to use the interface.
    BSTR bstrSDP = SysAllocString(pSDP);
    if (bstrSDP == NULL)
    {
        LOG((MSP_ERROR, "out of mem converting SDP to a BSTR."));
        return E_OUTOFMEMORY;
    }

    // Parse the SDP string.
    hr = pIConfBlob->Init(NULL, BCS_ASCII, bstrSDP);
    
    // the string is not needed any more.
    SysFreeString(bstrSDP);

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "parse the SDPBlob object. %x", hr));
        return hr;
    }
    
    // Get the ITSdp interface.
    CComPtr<ITSdp>  pITSdp;
    hr = pIConfBlob->QueryInterface(__uuidof(ITSdp), (void **)&pITSdp);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "can't get the ITSdp interface. %x", hr));
        return hr;
    }

    // check main sdp validity
    VARIANT_BOOL IsValid;
    hr = pITSdp->get_IsValid(&IsValid);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "can't get the valid flag on the SDP %x", hr));
        return hr;
    }

    if (!IsValid)
    {
        LOG((MSP_ERROR, "the SDP is not valid %x", hr));
        return E_FAIL;
    }

    return ConfigStreamsBasedOnSDP(
        pITSdp,
        dwAudioQOSLevel,
        dwVideoQOSLevel
        );
}

HRESULT CIPConfMSPCall::SendTSPMessage(
    IN  TSP_MSP_COMMAND command,
    IN  DWORD           dwParam1,
    IN  DWORD           dwParam2
    ) const
/*++

Routine Description:

    Send the TSP a message from the MSP. 

Arguments:

    command     - the command to be sent.

    dwParam1    - the first DWORD used in the command.

    dwParam2    - the second DWORD used in the command.

Return Value:

    HRESULT.

--*/
{
    LOG((MSP_TRACE, "SendTSPMessage, command %d, dwParam1 %d, dwParam2", 
        command, dwParam1, dwParam2));

    // first allocate the memory.

    MSPEVENTITEM* pEventItem = AllocateEventItem(sizeof(MSG_TSPMSPDATA));

    if (pEventItem == NULL)
    {
        LOG((MSP_ERROR, "No memory for the TSPMSP data"));
        return E_OUTOFMEMORY;
    }
    
    // Fill in the necessary fields for the event structure.
    pEventItem->MSPEventInfo.dwSize = 
        sizeof(MSP_EVENT_INFO) + sizeof(MSG_TSPMSPDATA);
    pEventItem->MSPEventInfo.Event  = ME_TSP_DATA;
    pEventItem->MSPEventInfo.hCall  = m_htCall;

    // Fill in the data for the TSP.
    pEventItem->MSPEventInfo.MSP_TSP_DATA.dwBufferSize = sizeof(MSG_TSPMSPDATA);

    MSG_TSPMSPDATA *pData = (MSG_TSPMSPDATA *)
        pEventItem->MSPEventInfo.MSP_TSP_DATA.pBuffer;

    pData->command = command;
    switch (command)
    {

    case CALL_DISCONNECTED:
        pData->CallDisconnected.dwReason = dwParam1;
        break;

    case CALL_QOS_EVENT:
        pData->QosEvent.dwEvent = dwParam1;
        pData->QosEvent.dwMediaMode = dwParam2;
        break;

    case CALL_CONNECTED:
        break;

	default:
		
		LOG((MSP_ERROR, "Wrong command type for TSP"));

        FreeEventItem(pEventItem);
		return E_UNEXPECTED;
    }

    HRESULT hr = m_pMSPAddress->PostEvent(pEventItem);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "Post event failed %x", hr));

        FreeEventItem(pEventItem);

        return hr;
    }
    return S_OK;
}

HRESULT CIPConfMSPCall::CheckUnusedStreams()
/*++

Routine Description:

    Find out which streams are not used and send tapi events about them.

Arguments:

Return Value:

    HRESULT.

--*/
{
    LOG((MSP_TRACE, "CheckUnusedStreams"));

    CLock lock(m_lock);
    for (long j = 0; j < m_Streams.GetSize(); j ++)
    {
        CIPConfMSPStream* pStream = (CIPConfMSPStream*)m_Streams[j];
    
        if (pStream->IsConfigured())
        {
            // find the next.
            continue;
        }
        
        MSPEVENTITEM* pEventItem = AllocateEventItem();

        if (pEventItem == NULL)
        {
            LOG((MSP_ERROR, "No memory for the TSPMSP data"));

            return E_OUTOFMEMORY;
        }
    
        // Fill in the necessary fields for the event structure.
        pEventItem->MSPEventInfo.dwSize = sizeof(MSP_EVENT_INFO);;
        pEventItem->MSPEventInfo.Event  = ME_CALL_EVENT;
        pEventItem->MSPEventInfo.hCall  = m_htCall;
    
        pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.Type = CALL_STREAM_NOT_USED;
        pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.Cause = CALL_CAUSE_REMOTE_REQUEST;
        pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.pStream = m_Streams[j];
        
        // Addref to prevent it from going away.
        m_Streams[j]->AddRef();

        pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.pTerminal = NULL;
        pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.hrError= 0;

        // send the event to tapi.
        HRESULT hr = m_pMSPAddress->PostEvent(pEventItem);
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "Post event failed %x", hr));
        
            FreeEventItem(pEventItem);
            return hr;
        }
    }
    return S_OK;
}

DWORD WINAPI CIPConfMSPCall::WorkerCallbackDispatcher(VOID *pContext)
/*++

Routine Description:

    Because Parsing the SDP and configure the streams uses a lot of COM
    stuff, we can't rely on the RPC thread the calls into the MSP to 
    receive the TSP data. So, we let our own working thread do the work.
    This method is the callback function for the queued work item. It 
    just gets the call object from the context structure and calls a method
    on the call object to handle the work item.

Arguments:

    pContext - A pointer to a CALLWORKITEM structure.

Return Value:

    HRESULT.

--*/
{
    _ASSERTE(!IsBadReadPtr(pContext, sizeof CALLWORKITEM));

    CALLWORKITEM *pItem = (CALLWORKITEM *)pContext;
    
    pItem->pCall->ProcessWorkerCallBack(pItem->Buffer, pItem->dwLen);
    pItem->pCall->MSPCallRelease();

    free(pItem);

    return NOERROR;
}

DWORD CIPConfMSPCall::ProcessWorkerCallBack(
    IN      PBYTE               pBuffer,
    IN      DWORD               dwSize
    )
/*++

Routine Description:

    This function handles the work item given by the TSP. 

Arguments:

    pBuffer - a buffer that contains a TSP_MSP command block.

    dwSize  - the size of the buffer.

Return Value:

    NOERROR.

--*/
{
    LOG((MSP_TRACE, "PreocessWorkerCallBAck"));

    _ASSERTE(!IsBadReadPtr(pBuffer, dwSize));

    MSG_TSPMSPDATA * pData = (MSG_TSPMSPDATA *)pBuffer;

    HRESULT hr;

    switch (pData->command)
    {
    case CALL_START:

        // Parse the SDP contained in the command block.
        hr = ParseSDP(pData->CallStart.szSDP, 
            pData->CallStart.dwAudioQOSLevel,
            pData->CallStart.dwVideoQOSLevel
            );

        if (FAILED(hr))
        {
            // disconnect the call if someting terrible happend.
            SendTSPMessage(CALL_DISCONNECTED, 0);

            LOG((MSP_ERROR, "parsing theSDPBlob object. %x", hr));
            return NOERROR;
        }

        // go through the streams and send events if they are not used.
        hr = CheckUnusedStreams();
        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "start the streams failed. %x", hr));
        }
        break;

    case CALL_STOP:
        InternalShutDown();
        break;
    }

    return NOERROR;
}

HRESULT CIPConfMSPCall::ReceiveTSPCallData(
    IN      PBYTE               pBuffer,
    IN      DWORD               dwSize
    )
/*++

Routine Description:

    This function handles the work item given by the TSP. 

Arguments:

    pBuffer - a buffer that contains a TSP_MSP command block.

    dwSize  - the size of the buffer.

Return Value:

    NOERROR.

--*/
{
    LOG((MSP_TRACE, 
        "ReceiveTSPCallData, pBuffer %x, dwSize %d", pBuffer, dwSize));

    MSG_TSPMSPDATA * pData = (MSG_TSPMSPDATA *)pBuffer;
    switch (pData->command)
    {
    case CALL_START:

        // make sure the string is valid.
        if ((IsBadReadPtr(pData->CallStart.szSDP, 
            (pData->CallStart.dwSDPLen + 1) * sizeof (WCHAR)))
            || (pData->CallStart.szSDP[pData->CallStart.dwSDPLen] != 0))
        {
            LOG((MSP_ERROR, "the TSP data is invalid."));
            return E_UNEXPECTED;
        }

        LOG((MSP_INFO, "SDP string\n%ws", pData->CallStart.szSDP));

        break;

    case CALL_STOP:
        break;

    default:
        LOG((MSP_ERROR, 
            "wrong command received from the TSP:%x", pData->command));
        return E_UNEXPECTED; 
    }

    // allocate a work item structure for our worker thread.
    CALLWORKITEM *pItem = (CALLWORKITEM *)malloc(sizeof(CALLWORKITEM) + dwSize);

    if (pItem == NULL)
    {
        // Disconnect the call because of out of memory.
        SendTSPMessage(CALL_DISCONNECTED, 0);

        LOG((MSP_ERROR, "out of memory for work item."));
        return E_OUTOFMEMORY;
    }

    this->MSPCallAddRef();
    pItem->pCall = this;
    pItem->dwLen = dwSize;
    CopyMemory(pItem->Buffer, pBuffer, dwSize);
    
    // post a work item to our worker thread.
    HRESULT hr = g_Thread.QueueWorkItem(
        WorkerCallbackDispatcher,           // the callback
        pItem,                              // the context.
        FALSE                               // sync (FALSE means asyn)
        );

    if (FAILED(hr))
    {
        if (pData->command == CALL_START)
        {
            // Disconnect the call because we can't handle the work.
            SendTSPMessage(CALL_DISCONNECTED, 0);
        }

        this->MSPCallRelease();
        free(pItem);

        LOG((MSP_ERROR, "queue work item failed."));
    }

    return hr;
}


STDMETHODIMP CIPConfMSPCall::EnumerateParticipants(
    OUT     IEnumParticipant **      ppEnumParticipant
    )
/*++

Routine Description:

    This method returns an enumerator to the participants. 

Arguments:
    ppEnumParticipant - the memory location to store the returned pointer.
  
Return Value:

S_OK
E_POINTER
E_OUTOFMEMORY

--*/
{
    LOG((MSP_TRACE, 
        "EnumerateParticipants entered. ppEnumParticipant:%p", ppEnumParticipant));

    //
    // Check parameters.
    //

    if (IsBadWritePtr(ppEnumParticipant, sizeof(VOID *)))
    {
        LOG((MSP_ERROR, "CIPConfMSPCall::EnumerateParticipants - "
            "bad pointer argument - exit E_POINTER"));

        return E_POINTER;
    }

    //
    // First see if this call has been shut down.
    // acquire the lock before accessing the Participant object list.
    //

    CLock lock(m_ParticipantLock);

    if (m_Participants.GetData() == NULL)
    {
        LOG((MSP_ERROR, "CIPConfMSPCall::EnumerateParticipants - "
            "call appears to have been shut down - exit E_UNEXPECTED"));

        // This call has been shut down.
        return E_UNEXPECTED;
    }

    //
    // Create an enumerator object.
    //
    HRESULT hr = CreateParticipantEnumerator(
        m_Participants.GetData(),                        // the begin itor
        m_Participants.GetData() + m_Participants.GetSize(),  // the end itor,
        ppEnumParticipant
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "CIPConfMSPCall::EnumerateParticipants - "
            "create enumerator object failed, %x", hr));

        return hr;
    }

    LOG((MSP_TRACE, "CIPConfMSPCall::EnumerateParticipants - exit S_OK"));

    return hr;
}

STDMETHODIMP CIPConfMSPCall::get_Participants(
    OUT     VARIANT *              pVariant
    )
{
    LOG((MSP_TRACE, "CIPConfMSPCall::get_Participants - enter"));

    //
    // Check parameters.
    //

    if ( IsBadWritePtr(pVariant, sizeof(VARIANT) ) )
    {
        LOG((MSP_ERROR, "CIPConfMSPCall::get_Participants - "
            "bad pointer argument - exit E_POINTER"));

        return E_POINTER;
    }

    //
    // See if this call has been shut down. Acquire the lock before accessing
    // the Participant object list.
    //

    CLock lock(m_ParticipantLock);

    if (m_Participants.GetData() == NULL)
    {
        LOG((MSP_ERROR, "CIPConfMSPCall::get_Participants - "
            "call appears to have been shut down - exit E_UNEXPECTED"));

        // This call has been shut down.
        return E_UNEXPECTED;
    }

    //
    // create the collection object - see mspcoll.h
    //
    HRESULT hr = CreateParticipantCollection(
        m_Participants.GetData(),                        // the begin itor
        m_Participants.GetData() + m_Participants.GetSize(),  // the end itor,
        m_Participants.GetSize(),                        // the size
        pVariant
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "CIPConfMSPCall::get_Participants - "
            "create collection failed - exit 0x%08x", hr));
        
        return hr;
    }

    LOG((MSP_TRACE, "CIPConfMSPCall::get_Participants - exit S_OK"));
 
    return S_OK;
}

// IMulticastControl methods
STDMETHODIMP CIPConfMSPCall::get_LoopbackMode (
    OUT MULTICAST_LOOPBACK_MODE * pMode
    )
{
    if (pMode == NULL)
    {
        return E_INVALIDARG;
    }

    *pMode = m_LoopbackMode;

    return S_OK;
}
    
STDMETHODIMP CIPConfMSPCall::put_LoopbackMode (
    IN MULTICAST_LOOPBACK_MODE mode
    )
{
    if (mode < MM_NO_LOOPBACK || mode > MM_SELECTIVE_LOOPBACK)
    {
        return E_INVALIDARG;
    }

    m_LoopbackMode = mode;

    return S_OK;
}

// ITLocalParticipant methods, called by the app.
STDMETHODIMP CIPConfMSPCall::get_LocalParticipantTypedInfo(
    IN  PARTICIPANT_TYPED_INFO  InfoType,
    OUT BSTR *                  ppInfo
    )
/*++

Routine Description:

    Get a information item for the local participant. This information is
    sent out to other participants in the conference.

Arguments:
    
    InfoType - The type of the information asked.

    ppInfo  - the mem address to store a BSTR.

Return Value:

    S_OK,
    E_INVALIDARG,
    E_POINTER,
    E_OUTOFMEMORY,
    TAPI_E_NOITEMS
*/
{
    LOG((MSP_TRACE, "CParticipant get info, type:%d", InfoType));
    
    if (InfoType > PTI_PRIVATE || InfoType < PTI_CANONICALNAME)
    {
        LOG((MSP_ERROR, "CParticipant get info - invalid type:%d", InfoType));
        return E_INVALIDARG;
    }

    if (IsBadWritePtr(ppInfo, sizeof(BSTR)))
    {
        LOG((MSP_ERROR, "CParticipant get info - exit E_POINTER"));
        return E_POINTER;
    }

    // check if we have that info.
    CLock lock(m_lock);
    
    if (!m_fLocalInfoRetrieved)
    {
        HRESULT hr = InitializeLocalParticipant();
        if (FAILED(hr))
        {
            return hr;
        }
    }

    int index = (int)InfoType; 
    if (m_InfoItems[index] == NULL)
    {
        LOG((MSP_INFO, "no local participant info item for %d", InfoType));
        return TAPI_E_NOITEMS;
    }

    // make a BSTR out of it.
    BSTR pName = SysAllocString(m_InfoItems[index]);

    if (pName == NULL)
    {
        LOG((MSP_ERROR, "CParticipant get info - exit out of mem"));
        return E_POINTER;
    }

    // return the BSTR.
    *ppInfo = pName;

    return S_OK; 
}

// ITLocalParticipant methods, called by the app.
STDMETHODIMP CIPConfMSPCall::put_LocalParticipantTypedInfo(
    IN  PARTICIPANT_TYPED_INFO  InfoType,
    IN  BSTR                    pInfo
    )
/*++

Routine Description:

    Set a information item for the local participant. This information is
    sent out to other participants in the conference.

Arguments:
    
    InfoType - The type of the information item.

    pInfo  - the information item.

Return Value:

    S_OK,
    E_INVALIDARG,
    E_POINTER,
    E_OUTOFMEMORY,
    TAPI_E_NOITEMS
*/
{
    LOG((MSP_TRACE, "set local info, type:%d", InfoType));
    
    if (InfoType > PTI_PRIVATE || InfoType < PTI_CANONICALNAME)
    {
        LOG((MSP_ERROR, "set local info - invalid type:%d", InfoType));
        return E_INVALIDARG;
    }

    if (IsBadStringPtr(pInfo, MAX_PARTICIPANT_TYPED_INFO_LENGTH))
    {
        LOG((MSP_ERROR, "set local info, bad ptr:%p", pInfo));
        return E_POINTER;
    }

    DWORD dwStringLen = lstrlenW(pInfo);
    if (dwStringLen > MAX_PARTICIPANT_TYPED_INFO_LENGTH)
    {
        LOG((MSP_ERROR, "local info too long"));
        return E_INVALIDARG;
    }

    // check if we have that info.
    CLock lock(m_lock);

    if (m_fCallStarted)
    {
        return TAPI_E_INVALCALLSTATE;
    }
    
    if (!m_fLocalInfoRetrieved)
    {
        HRESULT hr = InitializeLocalParticipant();
        if (FAILED(hr))
        {
            return hr;
        }
    }

    int index = (int)InfoType; 
    if (m_InfoItems[index] != NULL)
    {
        if (lstrcmpW(m_InfoItems[index], pInfo) == 0)
        {
            // The info is the same as what we are using.
            return S_OK;
        }

		// the infomation is different, release the old info.
		free(m_InfoItems[index]);
		m_InfoItems[index] = NULL;
    }

	// save the info.
    m_InfoItems[index] = (WCHAR *)malloc((dwStringLen + 1)* sizeof(WCHAR));
    if (m_InfoItems[index] == NULL)
    {
        LOG((MSP_ERROR, "out of mem for local info"));

        return E_OUTOFMEMORY;
    }

    lstrcpynW(m_InfoItems[index], pInfo, dwStringLen + 1);

    //
    // The info is new, we need to set it on the streams.
    //

    for (int i = 0; i < m_Streams.GetSize(); i ++)
    {
        ((CIPConfMSPStream*)m_Streams[i])->SetLocalParticipantInfo(
            InfoType,
            m_InfoItems[index],
            dwStringLen
            );
    }

    return S_OK; 
}

STDMETHODIMP CIPConfMSPCall::SetQOSApplicationID (
    IN  BSTR pApplicationID,
    IN  BSTR pApplicationGUID,
    IN  BSTR pSubIDs
    )
/*++

Routine Description:
    
    This method is called by the App to set the QOS specific application ID.
    It can only be called before the call is connected.

Arguments:

    pApplicationID - the Application ID.

    pSubIDs - the SubIDs that will be appended to the end of policy locator.

Return Value:

S_OK
E_OUTOFMEMORY

--*/
{
    CLock lock(m_lock);

    if (m_fCallStarted)
    {
        return TAPI_E_INVALCALLSTATE;
    }

    if (pSubIDs!=NULL && lstrlenW(pSubIDs)>MAX_QOS_ID_LEN)
    {
        return E_INVALIDARG;
    }

    if (pApplicationID!=NULL && lstrlenW(pApplicationID)>MAX_QOS_ID_LEN)
    {
        return E_INVALIDARG;
    }

    try
    {
        if (m_pApplicationID) SysFreeString(m_pApplicationID);
        m_pApplicationID = SysAllocString(pApplicationID);
    }
    catch(...)
    {
        return E_POINTER;
    }
    
    if (m_pApplicationID == NULL)
    {
        return E_OUTOFMEMORY;
    }

    try
    {
        if (m_pApplicationGUID)
        {
            SysFreeString(m_pApplicationGUID);
            m_pApplicationGUID = NULL;
        }

        if (m_pSubIDs)
        {
            SysFreeString(m_pSubIDs);
            m_pSubIDs = NULL;
        }

        if (pApplicationGUID)
        {
            m_pApplicationGUID = SysAllocString(pApplicationGUID);
        }

        if (pSubIDs)
        {
            m_pSubIDs = SysAllocString(pSubIDs);
        }
    }
    catch(...)
    {
        SysFreeString(m_pApplicationID);
        m_pApplicationID = NULL;

        if (m_pApplicationGUID)
        {
            SysFreeString(m_pApplicationGUID);
        }
        m_pApplicationGUID = NULL;

        if (m_pSubIDs)
        {
            SysFreeString(m_pSubIDs);
        }
        m_pSubIDs = NULL;

        return E_POINTER;
    }

    if ((pApplicationGUID!=NULL && m_pApplicationGUID==NULL) ||
        (pSubIDs!=NULL && m_pSubIDs==NULL))
    {
        return E_OUTOFMEMORY;
    }

    return S_OK;
}

HRESULT CIPConfMSPCall::NewParticipant(
    IN  ITStream *          pITStream,
    IN  DWORD               dwSSRC,
    IN  DWORD               dwSendRecv,
    IN  DWORD               dwMediaType,
    IN  WCHAR *              szCName,
    OUT ITParticipant **    ppITParticipant
    )
/*++

Routine Description:
    
    This method is called by a stream object when a new participant appears.
    It looks throught the call's participant list, if the partcipant is 
    already in the list, it returns the pointer to the object. If it is not
    found, a new object will be created and added into the list.

Arguments:

    pITStream - the stream object.

    dwSSRC - the SSRC of the participant in the stream.

    dwSendRecv - a sender or a receiver.
    
    dwMediaType - the media type of the stream.

    szCName - the canonical name of the participant.

    ppITParticipant - the address to store the returned pointer.

Return Value:

S_OK
E_OUTOFMEMORY

--*/
{
    CLock lock(m_ParticipantLock);

    HRESULT hr;

    // First check to see if the participant is in our list. If he is already
    // in the list, just return the object.
    int index;
    if (m_Participants.FindByCName(szCName, &index))
    {
        hr = ((CParticipant *)m_Participants[index])->
                AddStream(pITStream, dwSSRC, dwSendRecv, dwMediaType);

        if (FAILED(hr))
        {
            LOG((MSP_ERROR, "can not add a stream to a participant:%x", hr));
            return hr;
        }

        *ppITParticipant = m_Participants[index];
        (*ppITParticipant)->AddRef();

        return S_OK;
    }

    // create a new participant object.
    CComObject<CParticipant> * pCOMParticipant;

    hr = ::CreateCComObjectInstance(&pCOMParticipant);

    if (NULL == pCOMParticipant)
    {
        LOG((MSP_ERROR, "can not create a new participant:%x", hr));
        return hr;
    }

    ITParticipant* pITParticipant;

    // get the interface pointer.
    hr = pCOMParticipant->_InternalQueryInterface(
        __uuidof(ITParticipant), 
        (void **)&pITParticipant
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "Participant QueryInterface failed: %x", hr));
        delete pCOMParticipant;
        return hr;
    }

    // Initialize the object.
    hr = pCOMParticipant->Init(
        szCName, pITStream, dwSSRC, dwSendRecv, dwMediaType
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "Create participant:call init failed: %x", hr));
        pITParticipant->Release();

        return hr;
    }

    // Add the Participant into our list of Participants.
    if (!m_Participants.InsertAt(index, pITParticipant))
    {
        pITParticipant->Release();

        LOG((MSP_ERROR, "out of memory in adding a Participant."));
        return E_OUTOFMEMORY;
    }

    // AddRef the interface pointer and return it.
    pITParticipant->AddRef(); 
    *ppITParticipant = pITParticipant;

    SendParticipantEvent(PE_NEW_PARTICIPANT, pITParticipant);

    return S_OK;
}

HRESULT CIPConfMSPCall::ParticipantLeft(
    IN  ITParticipant *     pITParticipant
    )
/*++

Routine Description:
    
    This method is called by a stream object when a participant left the
    conference.

Arguments:

    pITParticipant - the participant that left.

Return Value:

S_OK

--*/
{
    m_ParticipantLock.Lock();

    BOOL fRemoved = m_Participants.Remove(pITParticipant);

    m_ParticipantLock.Unlock();
    
    if (fRemoved)
    {
        SendParticipantEvent(PE_PARTICIPANT_LEAVE, pITParticipant);
        pITParticipant->Release();
    }
    else
    {
        LOG((MSP_ERROR, "can't remove Participant %p", pITParticipant));
    }

    return S_OK;
}

void CIPConfMSPCall::SendParticipantEvent(
    IN  PARTICIPANT_EVENT   Event,
    IN  ITParticipant *     pITParticipant,
    IN  ITSubStream *       pITSubStream
    ) const
/*++

Routine Description:
    
    This method is called by a stream object to send a participant related
    event to the app.

Arguments:

    Event - the event code.

    pITParticipant - the participant object.

    pITSubStream - the substream object, if any.

Return Value:

nothing.

--*/
{
    if (pITParticipant)
    {
        LOG((MSP_TRACE, "SendParticipantEvent, event %s, participant:%ws",
            ParticipantEventString[Event], 
            ((CParticipant*)pITParticipant)->Name()
            ));
    }
    else
    {
        LOG((MSP_TRACE, "SendParticipantEvent, event %s, participant: null (local)",
            ParticipantEventString[Event]
            ));
    }

    // Create a private event object.
    CComPtr<IDispatch> pEvent;
    HRESULT hr = CreateParticipantEvent(
        Event, 
        pITParticipant, 
        pITSubStream, 
        &pEvent
        );

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "create event returned: %x", hr));
        return;
    }


    MSPEVENTITEM* pEventItem = AllocateEventItem();

    if (pEventItem == NULL)
    {
        LOG((MSP_ERROR, "No memory for the TSPMSP data"));

        return;
    }

    // Fill in the necessary fields for the event structure.
    pEventItem->MSPEventInfo.dwSize = sizeof(MSP_EVENT_INFO);;
    pEventItem->MSPEventInfo.Event  = ME_PRIVATE_EVENT;
    pEventItem->MSPEventInfo.hCall  = m_htCall;
    
    pEventItem->MSPEventInfo.MSP_PRIVATE_EVENT_INFO.pEvent = pEvent;
    pEventItem->MSPEventInfo.MSP_PRIVATE_EVENT_INFO.lEventCode = Event;
    pEvent.p->AddRef();

    // send the event to tapi.
    hr = m_pMSPAddress->PostEvent(pEventItem);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "Post event failed %x", hr));
    
        pEvent.Release();
        FreeEventItem(pEventItem);
    }
}

VOID CIPConfMSPCall::HandleGraphEvent(
    IN  MSPSTREAMCONTEXT * pContext
    )
{
    long     lEventCode;
    LONG_PTR lParam1, lParam2; // win64 fix

    HRESULT hr = pContext->pIMediaEvent->GetEvent(&lEventCode, &lParam1, &lParam2, 0);
    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "Can not get the actual event. %x", hr));
        return;
    }

    LOG((MSP_EVENT, "ProcessGraphEvent, code:%d param1:%x param2:%x",
        lEventCode, lParam1, lParam2));

    if (lEventCode == EC_PALETTE_CHANGED 
        || lEventCode == EC_VIDEO_SIZE_CHANGED)
    {
        LOG((MSP_EVENT, "event %d ignored", lEventCode));
        return;
    }

    //
    // Create an event data structure that we will pass to the worker thread.
    //

    MULTI_GRAPH_EVENT_DATA * pData;
    pData = new MULTI_GRAPH_EVENT_DATA;
    
    if (pData == NULL)
    {
        LOG((MSP_ERROR, "Out of memory for event data."));
        return;
    }
    
    pData->pCall      = this;
    pData->pITStream  = pContext->pITStream;
    pData->lEventCode = lEventCode;
    pData->lParam1    = lParam1;
    pData->lParam2    = lParam2;
 
     //
    // also pass an addref'ed pointer to IMediaEvent, so that whoever processes
    // the message has the opportunity to free event parameters
    //

    pData->pIMediaEvent = pContext->pIMediaEvent;
    pData->pIMediaEvent->AddRef();

   //
    // Make sure the call and stream don't go away while we handle the event.
    // but use our special inner object addref for the call
    //

    pData->pCall->MSPCallAddRef();
    pData->pITStream->AddRef();

    //
    // Queue an async work item to call ProcessGraphEvent.
    //

    hr = g_Thread.QueueWorkItem(AsyncMultiGraphEvent,
                                (void *) pData,
                                FALSE);  // asynchronous

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "QueueWorkItem failed, return code:%x", hr));

        pData->pCall->MSPCallRelease();
        pData->pITStream->Release();


        //
        // no one is going to free event params and release the IMediaEvent
        // pointer, so do it here
        //

        pContext->pIMediaEvent->FreeEventParams(lEventCode, lParam1, lParam2);
        pData->pIMediaEvent->Release();

        delete pData;
    }
}


HRESULT CIPConfMSPCall::InitFullDuplexControler()
/*++

Routine Description:

    This method creates the full-duplex controller object used to control
    audio devices.

Arguments:
    
    NONE

Return Value:

    HRESULT.

--*/
{
    ENTER_FUNCTION("CIPConfMSPCall::InitFullDuplexControler");
    LOG((MSP_TRACE, "%s entered", __fxName));

    CLock lock(m_lock);

    if (m_pIAudioDuplexController != NULL)
    {
        return S_OK;
    }

    HRESULT hr;
    IAudioDuplexController *pIAudioDuplexController;

    if (FAILED(hr = CoCreateInstance(
            __uuidof(TAPIAudioDuplexController),
            NULL,
            CLSCTX_INPROC_SERVER | CLSCTX_NO_CODE_DOWNLOAD,
            __uuidof(IAudioDuplexController),
            (void **) &pIAudioDuplexController
            )))
    {
        LOG((MSP_ERROR, "%s, create AudioDuplexController failed. hr=%x", 
            __fxName, hr));
        return hr;
    }
    
    m_pIAudioDuplexController = pIAudioDuplexController;

    return S_OK;
}

/*++

Routine Description:

    ITCallQualityControl method. Delegated to quality control relay

--*/
STDMETHODIMP
CIPConfMSPCall::GetRange (
    IN CallQualityProperty Property, 
    OUT long *plMin, 
    OUT long *plMax, 
    OUT long *plSteppingDelta, 
    OUT long *plDefault, 
    OUT TAPIControlFlags *plFlags
    )
{
    return m_pCallQCRelay->GetRange (Property, plMin, plMax, plSteppingDelta, plDefault, plFlags);
}

/*++

Routine Description:

    ITCallQualityControl method. Delegated to quality control relay

--*/
STDMETHODIMP
CIPConfMSPCall::Get (
    IN CallQualityProperty Property, 
    OUT long *plValue, 
    OUT TAPIControlFlags *plFlags
    )
{
    return m_pCallQCRelay->Get (Property, plValue, plFlags);
}

/*++

Routine Description:

    ITCallQualityControl method. Delegated to quality control relay

--*/
STDMETHODIMP
CIPConfMSPCall::Set (
    IN CallQualityProperty Property, 
    IN long lValue, 
    IN TAPIControlFlags lFlags
    )
{
    return m_pCallQCRelay->Set (Property, lValue, lFlags);
}

/*++

Routine Description:

    IInnerCallQualityControl method. Delegated to quality control relay

--*/
STDMETHODIMP_(ULONG)
CIPConfMSPCall::InnerCallAddRef (VOID)
{
    return this->MSPCallAddRef ();
}

STDMETHODIMP_(ULONG)
CIPConfMSPCall::InnerCallRelease (VOID)
{
    return this->MSPCallRelease ();
}

STDMETHODIMP
CIPConfMSPCall::RegisterInnerStreamQC (
    IN  IInnerStreamQualityControl *pIInnerStreamQC
    )
{
    return m_pCallQCRelay->RegisterInnerStreamQC (
        pIInnerStreamQC
        );
}

/*++

Routine Description:

    IInnerCallQualityControl method. Delegated to quality control relay

--*/
STDMETHODIMP
CIPConfMSPCall::DeRegisterInnerStreamQC (
    IN  IInnerStreamQualityControl *pIInnerStreamQC
    )
{
    return m_pCallQCRelay->DeRegisterInnerStreamQC (
        pIInnerStreamQC
        );
}

/*++

Routine Description:

    IInnerCallQualityControl method. Delegated to quality control relay

--*/
STDMETHODIMP
CIPConfMSPCall::ProcessQCEvent (
    IN  QCEvent event,
    IN  DWORD dwParam
    )
{
    return m_pCallQCRelay->ProcessQCEvent (event, dwParam);
}
