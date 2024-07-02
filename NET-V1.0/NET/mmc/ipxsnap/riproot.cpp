/**********************************************************************/
/**                       Microsoft Windows/NT                       **/
/**                Copyright(c) Microsoft Corporation, 1997 - 1999 **/
/**********************************************************************/

/*
	root.cpp
		Root node information (the root node is not displayed
		in the MMC framework but contains information such as 
		all of the subnodes in this snapin).
		
    FILE HISTORY:
        
*/

#include "stdafx.h"
#include "util.h"
#include "riproot.h"
#include "reg.h"
#include "ripview.h"	// RIP handlers
#include "ripstats.h"
#include "routprot.h"	// IP_BOOTP


/*---------------------------------------------------------------------------
	RipRootHandler implementation
 ---------------------------------------------------------------------------*/

DEBUG_DECLARE_INSTANCE_COUNTER(RipRootHandler)

extern const ContainerColumnInfo s_rgRIPParamsStatsColumnInfo[];

struct _ViewInfoColumnEntry
{
	UINT	m_ulId;
	UINT	m_cColumns;
	const ContainerColumnInfo *m_prgColumn;
};

static const struct _ViewInfoColumnEntry	s_rgViewColumnInfo[] =
{
	{ RIPSTRM_STATS_RIPPARAMS, MVR_RIPPARAMS_COUNT, s_rgRIPParamsStatsColumnInfo },
};

RipRootHandler::RipRootHandler(ITFSComponentData *pCompData)
	: RootHandler(pCompData)
{
	DEBUG_INCREMENT_INSTANCE_COUNTER(RipRootHandler)
			
	m_ConfigStream.Init(DimensionOf(s_rgViewColumnInfo));
	
    // This will initialize the view information for the statistics
    // dialogs.  (which is why the fConfigurableColumns is set to TRUE).
	for (int i=0; i<DimensionOf(s_rgViewColumnInfo); i++)
	{
		m_ConfigStream.InitViewInfo(s_rgViewColumnInfo[i].m_ulId,
                                    TRUE /*fConfigurableColumns*/,
									s_rgViewColumnInfo[i].m_cColumns,
									TRUE,
									s_rgViewColumnInfo[i].m_prgColumn);
	}
}


STDMETHODIMP RipRootHandler::QueryInterface(REFIID riid, LPVOID *ppv)
{
    // Is the pointer bad?
    if (ppv == NULL)
		return E_INVALIDARG;

    //  Place NULL in *ppv in case of failure
    *ppv = NULL;

    //  This is the non-delegating IUnknown implementation
    if (riid == IID_IUnknown)
		*ppv = (LPVOID) this;
	else if (riid == IID_IRtrAdviseSink)
		*ppv = &m_IRtrAdviseSink;
	else
		return RootHandler::QueryInterface(riid, ppv);

    //  If we're going to return an interface, AddRef it first
    if (*ppv)
	{
	((LPUNKNOWN) *ppv)->AddRef();
		return hrOK;
	}
    else
		return E_NOINTERFACE;	
}


///////////////////////////////////////////////////////////////////////////////
//// IPersistStream interface members

STDMETHODIMP RipRootHandler::GetClassID
(
	CLSID *pClassID
)
{
    ASSERT(pClassID != NULL);

    // Copy the CLSID for this snapin
    *pClassID = CLSID_IPXRipExtension;

    return hrOK;
}

/*!--------------------------------------------------------------------------
	RipRootHandler::OnExpand
		-
	Author: KennT
 ---------------------------------------------------------------------------*/
HRESULT RipRootHandler::OnExpand(ITFSNode *pNode,
								 LPDATAOBJECT pDataObject,
								 DWORD dwType,
								 LPARAM arg,
								 LPARAM lParam)
{
	HRESULT	                hr = hrOK;
	SPITFSNode			    spNode;
	SPIRtrMgrProtocolInfo	spRmProt;
    SPIRtrMgrInfo           spRm;
    SPIRouterInfo           spRouterInfo;
    LONG_PTR               ulConnId;

	// Grab the router info from the dataobject
	spRm.Query(pDataObject);
	Assert(spRm);

	spRm->GetParentRouterInfo(&spRouterInfo);

	// Setup the advise on the RtrMgr (to see when BootP is added/removed)
	spRm->RtrAdvise(&m_IRtrAdviseSink, &ulConnId, 0);

    // add things to our map for later
    AddRtrObj(ulConnId, IID_IRtrMgrInfo, spRm);
    AddScopeItem(spRm->GetMachineName(), (HSCOPEITEM) lParam);

    hr = spRm->FindRtrMgrProtocol(IPX_PROTOCOL_RIP, &spRmProt);
	if (!FHrOK(hr))
	{
		// Treat this as an already expanded node, we depend on
		// the notification mechanism to let us know if something
		// changes
		goto Error;
	}

	CORg( AddProtocolNode(pNode, spRouterInfo) );

    SetProtocolAdded(ulConnId, TRUE);
	
Error:
	return hr;
}

/*!--------------------------------------------------------------------------
	RipRootHandler::OnCreateDataObject
		Implementation of ITFSNodeHandler::OnCreateDataObject
	Author: KennT
 ---------------------------------------------------------------------------*/
STDMETHODIMP RipRootHandler::OnCreateDataObject(MMC_COOKIE cookie, DATA_OBJECT_TYPES type, IDataObject **ppDataObject)
{
	HRESULT		    hr = hrOK;
    SPIRouterInfo   spRouterInfo;

    COM_PROTECT_TRY
	{
		// this will always be NULL
        if (spRouterInfo == NULL)
		{
			// If we haven't created the sub nodes yet, we still have to
			// create a dataobject.
			CDataObject *	pObject = NULL;
			SPIDataObject	spDataObject;
			SPITFSNode		spNode;
			SPITFSNodeHandler	spHandler;
			
			pObject = new CDataObject;
			spDataObject = pObject;	// do this so that it gets released correctly
			Assert(pObject != NULL);
			
			// Save cookie and type for delayed rendering
			pObject->SetType(type);
			pObject->SetCookie(cookie);
			
			// Store the coclass with the data object
			pObject->SetClsid(*(m_spTFSCompData->GetCoClassID()));
			
			pObject->SetTFSComponentData(m_spTFSCompData);
			
			hr = pObject->QueryInterface(IID_IDataObject, 
									 reinterpret_cast<void**>(ppDataObject));
			
		}
		else
			hr = CreateDataObjectFromRouterInfo(spRouterInfo,
												type, cookie, m_spTFSCompData,
												ppDataObject);
	}
	COM_PROTECT_CATCH;
	return hr;
}



ImplementEmbeddedUnknown(RipRootHandler, IRtrAdviseSink)

STDMETHODIMP RipRootHandler::EIRtrAdviseSink::OnChange(LONG_PTR ulConn,
	DWORD dwChangeType, DWORD dwObjectType, LPARAM lUserParam, LPARAM lParam)
{
 	InitPThis(RipRootHandler, IRtrAdviseSink);
	HRESULT		    hr = hrOK;
	SPITFSNode	    spNode;
    SPIRtrMgrInfo   spRm;
    SPIRouterInfo   spRouterInfo;

	if (dwObjectType != ROUTER_OBJ_RmProt)
		return hr;

	COM_PROTECT_TRY
	{
        CORg (pThis->GetRtrObj(ulConn, (IUnknown **) &spRm));

		if (dwChangeType == ROUTER_CHILD_ADD)
		{
			// check to see if BootP is in the current list
			if (spRm->FindRtrMgrProtocol(IPX_PROTOCOL_RIP, NULL) == hrOK)
			{
				// We found Bootp, add our child node if we
				// don't have a child node
				if (!pThis->IsProtocolAdded(ulConn))
				{
                	spRm->GetParentRouterInfo(&spRouterInfo);
					pThis->m_spNodeMgr->GetRootNode(&spNode);
					pThis->AddProtocolNode(spNode, spRouterInfo);
					pThis->SetProtocolAdded(ulConn, TRUE);
				}
			}
		}
		else if (dwChangeType == ROUTER_CHILD_DELETE)
		{
			if (spRm->FindRtrMgrProtocol(IPX_PROTOCOL_RIP, NULL) == hrFalse)
			{
				// couldn't find Bootp, delete all of our child nodes
				pThis->m_spNodeMgr->GetRootNode(&spNode);
				pThis->RemoveNode(spNode, spRm->GetMachineName());
			    pThis->SetProtocolAdded(ulConn, FALSE);
			}
		}
		
        COM_PROTECT_ERROR_LABEL;
	}
	COM_PROTECT_CATCH;
	
	return hr;
}

/*!--------------------------------------------------------------------------
	RipRootHandler::DestroyHandler
		-
	Author: KennT
 ---------------------------------------------------------------------------*/
STDMETHODIMP RipRootHandler::DestroyHandler(ITFSNode *pNode)
{
    RemoveAllNodes(pNode);
    RemoveAllRtrObj();
	return hrOK;
}

/*!--------------------------------------------------------------------------
	RipRootHandler::AddProtocolNode
		-
	Author: KennT
 ---------------------------------------------------------------------------*/
HRESULT RipRootHandler::AddProtocolNode(ITFSNode *pNode, IRouterInfo * pRouterInfo)
{
	SPITFSNodeHandler	spHandler;
	RipNodeHandler *    pHandler = NULL;
	HRESULT				hr = hrOK;
	SPITFSNode			spNode;
    HSCOPEITEM          hScopeItem, hOldScopeItem;
    
    // Windows NT Bug : 246822
    // Due to the server list programming model, we need to setup
    // the proper scopeitem (so that MMC adds this to the proper
    // node).

    
    // Get the proper scope item for this node.
    // ----------------------------------------------------------------
    Verify( GetScopeItem(pRouterInfo->GetMachineName(), &hScopeItem) == hrOK);

    
    // Get the old one and save it.  place the new one in the node.
    // ----------------------------------------------------------------
    hOldScopeItem = pNode->GetData(TFS_DATA_SCOPEID);
    pNode->SetData(TFS_DATA_SCOPEID, hScopeItem);

	pHandler = new RipNodeHandler(m_spTFSCompData);
	spHandler = pHandler;
	CORg( pHandler->Init(pRouterInfo, &m_ConfigStream) );

	CreateContainerTFSNode(&spNode,
						   &GUID_IPXRipNodeType,
						   static_cast<ITFSNodeHandler *>(pHandler),
						   static_cast<ITFSResultHandler *>(pHandler),
						   m_spNodeMgr);

	// Call to the node handler to init the node data
	pHandler->ConstructNode(spNode);
				
	// Make the node immediately visible
	spNode->SetVisibilityState(TFS_VIS_SHOW);
	pNode->AddChild(spNode);

Error:
    // Restore the scope item
    pNode->SetData(TFS_DATA_SCOPEID, hOldScopeItem);
	return hr;
}


/*!--------------------------------------------------------------------------
	RipRootHandler::CompareNodeToMachineName
		This function is used by the RemoveNode() function.

        Returns hrOK if this node is a DHCP relay node and corresponds
        to the pszMachineName.
        Returns hrFalse if this is not the indicated node.
        Returns errors otherwise.
	Author: KennT
 ---------------------------------------------------------------------------*/
HRESULT RipRootHandler::CompareNodeToMachineName(ITFSNode *pNode,
    LPCTSTR pszMachineName)
{
    HRESULT     hr = hrFalse;

    // Should check that this is a RIP node
    if (*(pNode->GetNodeType()) != GUID_IPXRipNodeType)
        hr = hrFalse;
    else
    {
        IPXConnection *  pIPXConn;
        
        pIPXConn = GET_RIP_NODEDATA(pNode);
        if (StriCmp(pszMachineName, pIPXConn->GetMachineName()) == 0)
            hr = hrOK;
    }

    return hr;
}


