#pragma once

#define WZC_ACCESS_SET      0x00000001
#define WZC_ACCESS_QUERY    0x00000002
#define WZC_READ        (STANDARD_RIGHTS_READ    | WZC_ACCESS_QUERY)
#define WZC_WRITE       (STANDARD_RIGHTS_WRITE   | WZC_ACCESS_QUERY | WZC_ACCESS_SET)
#define WZC_EXECUTE     (STANDARD_RIGHTS_EXECUTE | WZC_ACCESS_QUERY)
#define WZC_ALL_ACCESS  (STANDARD_RIGHTS_REQUIRED| WZC_ACCESS_QUERY | WZC_ACCESS_SET)

DWORD
WZCSvcCheckConfig(PWZC_WLAN_CONFIG pwzcConfig, UINT nBytes);

DWORD
WZCSvcStartRPCServer();

DWORD
WZCSvcStopRPCServer();
