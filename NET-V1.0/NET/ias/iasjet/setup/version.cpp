//////////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2000 Microsoft Corporation all rights reserved.
//
// Module:      Version.cpp
//
// Project:     Windows 2000 IAS
//
// Description: Implementation of the CProperties class
//      works only with m_StdSession (database being upgraded)
//
// Author:      tperraut
//
// Revision     02/24/2000 created
//
//////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "version.h"


//////////////////////////////////////////////////////////////////////////////
// CVersionGet::GetVersion
//////////////////////////////////////////////////////////////////////////////
LONG CVersionGet::GetVersion()
{
    HRESULT hr = BaseExecute();
    if ( FAILED(hr) )
    {
        /////////////////////////////////////
        // The Version table does not exist.
        // return zero as the version # 
        /////////////////////////////////////
        
        ///////////////////////////
        // Set Zero as the version
        ///////////////////////////
        m_Version = 0;
    }
    Close();
    return m_Version;
}


//////////////////////////////////////////////////////////////////////////////
// CVersion::GetVersion
//////////////////////////////////////////////////////////////////////////////
LONG CVersion::GetVersion()
{
    CVersionGet  GetVer(m_Session);
    return GetVer.GetVersion();
}
