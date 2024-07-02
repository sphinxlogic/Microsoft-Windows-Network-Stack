/*++

Copyright (c) 1990-1995  Microsoft Corporation

Module Name:

    Tapi.c

Abstract:


Author:

    Tony Bell   (TonyBe) June 06, 1995

Environment:

    Kernel Mode

Revision History:

    TonyBe      06/06/95        Created

--*/

//
// We want to initialize all of the global variables now!
//
#include "wan.h"

#define __FILE_SIG__    TAPI_FILESIG

ULONG gulNdistapiMissedCount = 0;

EXPORT
VOID
NdisTapiCompleteRequest(
    IN  NDIS_HANDLE Handle,
    IN  PVOID       NdisRequest,
    IN  NDIS_STATUS Status
    );

EXPORT
VOID
NdisTapiIndicateStatus(
    IN  NDIS_HANDLE Handle,
    IN  PVOID       StatusBuffer,
    IN  UINT        StatusBufferSize
    );

NDIS_STATUS
NdisWanTapiRequestProc(
    HANDLE NdisTapiKey,
    PNDIS_REQUEST   NdisRequest
    )
/*++

Routine Name:

    NdisWanTapiRequestProc

Routine Description:

    Procedure is called by the NdisTapi.sys driver to send
    requests to the WanMiniport driver.  We intercept this
    just to moderate.  NdisTapi could call the miniport directly
    if we wanted but we don't.

Arguments:

Return Values:

--*/
{
    NDIS_STATUS     Status;
    PWAN_REQUEST    WanRequest;
    PNDIS_REQUEST   MyNdisRequest;
    POPENCB         OpenCB = NULL;
    OPENCB *pOpenCBTemp;
    LIST_ENTRY *pEntry;
    

    NdisWanDbgOut(DBG_TRACE, DBG_TAPI, ("NdisWanTapiRequestProc - Enter"));
    NdisWanDbgOut(DBG_INFO, DBG_TAPI, ("NdisRequest: Type: 0x%x OID: 0x%x",
    NdisRequest->RequestType,NdisRequest->DATA.QUERY_INFORMATION.Oid));

    //
    // Map the NdisTapiKey to OpenCB
    //
    NdisAcquireSpinLock(&OpenCBList.Lock);

    for(pEntry = OpenCBList.List.Flink;
        pEntry != &OpenCBList.List;
        pEntry = pEntry->Flink)
    {
        pOpenCBTemp = CONTAINING_RECORD(pEntry, OPENCB, Linkage);
        
        if(     (NULL != pOpenCBTemp->NdisTapiKey)
            &&  (pOpenCBTemp->NdisTapiKey == NdisTapiKey))
        {
            OpenCB = pOpenCBTemp;
            break;
        }
    }

    if(OpenCB == NULL)
    {
        //
        // Miniport is already removed from the list.
        //
        NdisReleaseSpinLock(&OpenCBList.Lock);
        NdisWanInterlockedInc(&gulNdistapiMissedCount);
        return NDIS_STATUS_FAILURE;
    }

    //
    // Take a ref on the opencb and release locks.
    //
    NdisAcquireSpinLock(&OpenCB->Lock);

    if (OpenCB->Flags & OPEN_CLOSING) {

        NdisReleaseSpinLock(&OpenCB->Lock);
        NdisReleaseSpinLock(&OpenCBList.Lock);
        return (NDIS_STATUS_FAILURE);
    }

    REF_OPENCB(OpenCB);

    NdisReleaseSpinLock(&OpenCB->Lock);
    NdisReleaseSpinLock(&OpenCBList.Lock);
    
    WanRequest =
        NdisAllocateFromNPagedLookasideList(&WanRequestList);

    if (WanRequest == NULL) {
        DEREF_OPENCB(OpenCB);
        return (NDIS_STATUS_RESOURCES);
    }

    WanRequest->Type = ASYNC;
    WanRequest->Origin = NDISTAPI;
    WanRequest->OpenCB = OpenCB;
    WanRequest->OriginalRequest = NdisRequest;

    NdisWanInitializeNotificationEvent(&WanRequest->NotificationEvent);

    MyNdisRequest = &WanRequest->NdisRequest;
    MyNdisRequest->RequestType =
        NdisRequest->RequestType;
    if (NdisRequest->RequestType == NdisRequestQueryInformation) {
        MyNdisRequest->DATA.QUERY_INFORMATION.Oid =
            NdisRequest->DATA.QUERY_INFORMATION.Oid;
        MyNdisRequest->DATA.QUERY_INFORMATION.InformationBuffer =
            NdisRequest->DATA.QUERY_INFORMATION.InformationBuffer;
        MyNdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength =
            NdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength;
        MyNdisRequest->DATA.QUERY_INFORMATION.BytesWritten =
            NdisRequest->DATA.QUERY_INFORMATION.BytesWritten;
    } else if (NdisRequest->RequestType == NdisRequestSetInformation) {
        MyNdisRequest->DATA.SET_INFORMATION.Oid =
            NdisRequest->DATA.SET_INFORMATION.Oid;
        MyNdisRequest->DATA.SET_INFORMATION.InformationBuffer =
            NdisRequest->DATA.SET_INFORMATION.InformationBuffer;
        MyNdisRequest->DATA.SET_INFORMATION.InformationBufferLength =
            NdisRequest->DATA.SET_INFORMATION.InformationBufferLength;
        MyNdisRequest->DATA.SET_INFORMATION.BytesRead =
            NdisRequest->DATA.SET_INFORMATION.BytesRead;
    }
        
    Status = NdisWanSubmitNdisRequest(OpenCB, WanRequest);

    NdisWanDbgOut(DBG_INFO, DBG_TAPI, ("Status: 0x%x", Status));
    NdisWanDbgOut(DBG_TRACE, DBG_TAPI, ("NdisWanTapiRequestProc - Exit"));

    DEREF_OPENCB(OpenCB);

    return (Status);
}

VOID
NdisWanTapiRequestComplete(
    POPENCB OpenCB,
    PWAN_REQUEST    WanRequest
    )
{
    PNDIS_REQUEST   NdisRequest, MyNdisRequest;

    NdisWanDbgOut(DBG_TRACE, DBG_TAPI,
        ("NdisWanTapiRequestComplete - Enter"));

    NdisRequest = WanRequest->OriginalRequest;

    MyNdisRequest = &WanRequest->NdisRequest;
    if (NdisRequest->RequestType == NdisRequestQueryInformation) {
        NdisRequest->DATA.QUERY_INFORMATION.BytesWritten =
            MyNdisRequest->DATA.QUERY_INFORMATION.BytesWritten;
    } else if (NdisRequest->RequestType == NdisRequestSetInformation) {
        NdisRequest->DATA.SET_INFORMATION.BytesRead =
            MyNdisRequest->DATA.SET_INFORMATION.BytesRead;
    }

    NdisWanDbgOut(DBG_INFO, DBG_TAPI,
        ("NdisRequest: Type: 0x%x OID: 0x%x",
        NdisRequest->RequestType,
        NdisRequest->DATA.QUERY_INFORMATION.Oid));

    NdisWanDbgOut(DBG_INFO, DBG_TAPI,
        ("Status: 0x%x", WanRequest->NotificationStatus));

    NdisTapiCompleteRequest(OpenCB->NdisTapiKey,
                            NdisRequest,
                            WanRequest->NotificationStatus);

    NdisFreeToNPagedLookasideList(&WanRequestList, WanRequest);
}

VOID
NdisWanTapiIndication(
    POPENCB OpenCB,
    PUCHAR          StatusBuffer,
    ULONG           StatusBufferSize
    )
/*++

Routine Name:

Routine Description:

Arguments:

Return Values:

--*/
{
    NdisWanDbgOut(DBG_TRACE, DBG_TAPI, ("NdisWanTapiIndication - Enter"));

    //
    // If tapi is present and this miniport has registered for
    // connectionwrapper services give this to tapi
    //
    if (OpenCB->WanInfo.FramingBits & TAPI_PROVIDER) {

        NdisTapiIndicateStatus(OpenCB,
                               StatusBuffer,
                               StatusBufferSize);
    }

    NdisWanDbgOut(DBG_TRACE, DBG_TAPI, ("NdisWanTapiIndication - Exit"));
}
