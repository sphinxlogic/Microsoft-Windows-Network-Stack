///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) Microsoft Corp. All rights reserved.
//
// FILE
//
//    iasnap.cpp
//
// SYNOPSIS
//
//    Implementation of DLL exports for an ATL in proc server.
//
///////////////////////////////////////////////////////////////////////////////

#include <ias.h>
#include <iasutil.h>
#include <newop.cpp>

#include <enforcer.h>
#include <match.h>
#include <ntgroups.h>
#include <posteap.h>
#include <timeofday.h>
#include <userr.h>

CComModule _Module;
#include <atlimpl.cpp>

BEGIN_OBJECT_MAP(ObjectMap)
   OBJECT_ENTRY(__uuidof(AttributeMatch), AttributeMatch)
   OBJECT_ENTRY(__uuidof(NTGroups), NTGroups)
   OBJECT_ENTRY(__uuidof(TimeOfDay), TimeOfDay)
   OBJECT_ENTRY(__uuidof(PolicyEnforcer),
                IASTL::IASRequestHandlerObject<PolicyEnforcer> )
   OBJECT_ENTRY(__uuidof(ProxyPolicyEnforcer),
                IASTL::IASRequestHandlerObject<ProxyPolicyEnforcer> )
   OBJECT_ENTRY(__uuidof(URHandler),
                IASTL::IASRequestHandlerObject<UserRestrictions> )
   OBJECT_ENTRY(__uuidof(PostEapRestrictions),
                IASTL::IASRequestHandlerObject<PostEapRestrictions> )
END_OBJECT_MAP()


//////////
// DLL Entry Point
//////////
BOOL
WINAPI
DllMain(
    HINSTANCE hInstance,
    DWORD dwReason,
    LPVOID /*lpReserved*/
    )
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {
     _Module.Init(ObjectMap, hInstance);

     DisableThreadLibraryCalls(hInstance);
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
     _Module.Term();
   }

   return TRUE;
}


//////////
// Used to determine whether the DLL can be unloaded by OLE
//////////
STDAPI DllCanUnloadNow(void)
{
   return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}


//////////
// Returns a class factory to create an object of the requested type.
//////////
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
   return _Module.GetClassObject(rclsid, riid, ppv);
}


//////////
// DllRegisterServer - Adds entries to the system registry
//////////
STDAPI DllRegisterServer(void)
{
   return  _Module.RegisterServer(TRUE);
}


//////////
// DllUnregisterServer - Removes entries from the system registry
//////////
STDAPI DllUnregisterServer(void)
{
   HRESULT hr = _Module.UnregisterServer();

   if (FAILED(hr)) return hr;

   hr = UnRegisterTypeLib(__uuidof(NetworkPolicy),
                          1,
                          0,
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                          SYS_WIN32);

   return hr;
}

#include <BuildTree.h>
#include <xprparse.h>
#include <xprparse.cpp>
