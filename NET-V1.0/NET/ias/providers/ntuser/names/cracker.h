///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) Microsoft Corp. All rights reserved.
//
// FILE
//
//    Cracker.h
//
// SYNOPSIS
//
//    This file declares the class NameCracker.
//
// MODIFICATION HISTORY
//
//    04/13/1998    Original version.
//    08/10/1998    Remove NT4 support.
//    08/21/1998    Removed initialization/shutdown routines.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef  CRACKER_H_
#define  CRACKER_H_
#if _MSC_VER >= 1000
#pragma once
#endif

#include "guard.h"
#include "nocopy.h"

#include <ntdsapi.h>

// Forward declaration of helper class used by NameCracker.
class DsHandle;

///////////////////////////////////////////////////////////////////////////////
//
// CLASS
//
//    NameCracker
//
// DESCRIPTION
//
//    This class wraps the DsCrackNames API. It adds functionality for
//    connection caching and transparent retry of failed queries.
//
///////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE NameCracker
   : Guardable, NonCopyable
{
public:
   NameCracker() throw ();
   ~NameCracker() throw ();

   // Non-connection oriented version of DsCrackNames.
   DWORD crackNames(
             DS_NAME_FLAGS flags,
             DS_NAME_FORMAT formatOffered,
             DS_NAME_FORMAT formatDesired,
             PCWSTR name,
             PCWSTR upnSuffix,
             PDS_NAME_RESULTW *ppResult
             ) throw ();

   // Wrapper around the DsFreeNameResultW.
   void freeNameResult(DS_NAME_RESULTW *pResult) throw ()
   { DsFreeNameResultW(pResult); }

protected:

   // Discards the cached GC handle.  Used to shutdown a bad connection.
   void disable(DsHandle* h) throw ();

   // Get a handle to the Global Catalog.
   DWORD getGC(DsHandle** h) throw ();

   // Current connection to the Global Catalog.
   DsHandle* gc;

private:
   DWORD processSID(
                     PCWSTR name, 
                     PCWSTR upnSuffix, 
                     DS_NAME_FORMAT& newFormatOffered, 
                     wchar_t** ppUpnString) throw();

   bool convertSid2Puid(PCWSTR sidString, LARGE_INTEGER& puid) throw();
   
   DWORD convertPuid2String(
                        const LARGE_INTEGER& puid, 
                        wchar_t* upnString, 
                        DWORD upnStringCch,
                        const wchar_t* suffix
                     ) throw();
   
};

#endif  // CRACKER_H_
