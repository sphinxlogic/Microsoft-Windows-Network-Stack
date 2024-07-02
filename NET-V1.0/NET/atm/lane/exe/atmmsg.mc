;/*++
;
;Copyright (c) 1994  Microsoft Corporation
;
;Module Name:
;
;    atmmsg.mc
;
;Abstract:
;
;    Contains internationalizable message text for ATMLANE
;
;Author:
;
;    v-lcleet		21-Oct-1997
;
;Revision History:
;
;    21-Oct-1997		v-lcleet
;        Created based on atmadm's .mc file
;
;--*/

MessageId=10000 Severity=Error SymbolicName=MSG_ATMLANE_BANNER
Language=English

Windows ATM LAN Emulation Client Information

.

MessageId=10001 SymbolicName=MSG_ERROR_OPENING_DEVICE
Language=English
Could not access ATM LAN Emulation Client
.

MessageId=10002 SymbolicName=MSG_ERROR_GETTING_VERSION_INFO
Language=English
Could not get version from ATM LAN Emulation Client
.

MessageId=10003 SymbolicName=MSG_ERROR_INVALID_INFO_VERSION
Language=English
This utility does not match the version of the ATM LAN Emulation Client driver
.

MessageId=10004 SymbolicName=MSG_ERROR_GETTING_ADAPTER_LIST
Language=English
Could not get the adapter list from ATM LAN Emulation Client
.

MessageId=10005 SymbolicName=MSG_ERROR_GETTING_ELAN_LIST
Language=English
Could not get the ELAN list from ATM LAN Emulation Client
.

MessageId=10006 SymbolicName=MSG_ERROR_GETTING_ELAN_INFO
Language=English
Could not get the ELAN information from ATM LAN Emulation Client
.

MessageId=10007 SymbolicName=MSG_ERROR_GETTING_ELAN_ARP_TABLE
Language=English
Could not get the ELAN ARP Table information from ATM LAN Emulation Client
.

MessageId=10008 SymbolicName=MSG_ERROR_GETTING_ELAN_CONN_TABLE
Language=English
Could not get the ELAN Connection Table information from ATM LAN Emulation Client
.

MessageId=10009 SymbolicName=MSG_NONE
Language=English
None%0
.

MessageId=10010 SymbolicName=MSG_OFF
Language=English
Off%0
.

MessageId=10011 SymbolicName=MSG_ON
Language=English
On%0
.

MessageId=10012 SymbolicName=MSG_UNSPECIFIED
Language=English
Unspecified%0
.

MessageId=10013 SymbolicName=MSG_CONNTYPE_PEER
Language=English
PEER%0
.

MessageId=10014 SymbolicName=MSG_CONNTYPE_BUS
Language=English
BUS %0
.

MessageId=10015 SymbolicName=MSG_CONNTYPE_LES
Language=English
LES %0
.

MessageId=10016 SymbolicName=MSG_CONNTYPE_LECS
Language=English
LECS%0
.

MessageId=10017 SymbolicName=MSG_NOCONNECT
Language=English
<no connection>%0
.


MessageId=10020 SymbolicName=MSG_ELAN_STATE_UNKNOWN
Language=English
 ? %0
.

MessageId=10021 SymbolicName=MSG_ELAN_STATE_INIT
Language=English
INITIAL%0
.

MessageId=10022 SymbolicName=MSG_ELAN_STATE_LECS_CONNECT_ILMI
Language=English
LECS CONNECT ILMI%0
.

MessageId=10023 SymbolicName=MSG_ELAN_STATE_LECS_CONNECT_WKA
Language=English
LECS CONNECT WKA%0
.

MessageId=10024 SymbolicName=MSG_ELAN_STATE_LECS_CONNECT_PVC
Language=English
LECS CONNECT PVC%0
.

MessageId=10025 SymbolicName=MSG_ELAN_STATE_LECS_CONNECT_CFG
Language=English
LECS CONNECT CFG%0
.

MessageId=10026 SymbolicName=MSG_ELAN_STATE_CONFIGURE
Language=English
CONFIGURE%0
.

MessageId=10027 SymbolicName=MSG_ELAN_STATE_LES_CONNECT
Language=English
LES CONNECT%0
.

MessageId=10028 SymbolicName=MSG_ELAN_STATE_JOIN
Language=English
JOIN%0
.

MessageId=10029 SymbolicName=MSG_ELAN_STATE_BUS_CONNECT
Language=English
BUS CONNECT%0
.

MessageId=10030 SymbolicName=MSG_ELAN_STATE_OPERATIONAL
Language=English
OPERATIONAL%0
.

MessageId=10031 SymbolicName=MSG_ELAN_STATE_SHUTDOWN
Language=English
SHUTDOWN%0
.

MessageId=10032 SymbolicName=MSG_LANTYPE_UNKNOWN
Language=English
 ? %0
.

MessageId=10033 SymbolicName=MSG_LANTYPE_UNSPECIFIED
Language=English
Unspecified%0
.

MessageId=10034 SymbolicName=MSG_LANTYPE_ETHERNET
Language=English
Ethernet/802.3%0
.

MessageId=10035 SymbolicName=MSG_LANTYPE_TOKENRING
Language=English
Token Ring/802.5%0
.

MessageId=10036 SymbolicName=MSG_VCTYPE_UNKNOWN
Language=English
 ? %0
.

MessageId=10037 SymbolicName=MSG_VCTYPE_CONFIG_DIRECT
Language=English
ConfigDirect%0
.

MessageId=10038 SymbolicName=MSG_VCTYPE_CONTROL_DIRECT
Language=English
CtrlDirect%0
.

MessageId=10039 SymbolicName=MSG_VCTYPE_CONTROL_DISTRIBUTE
Language=English
+ CtrlDistr%0
.

MessageId=10040 SymbolicName=MSG_VCTYPE_DATA_DIRECT
Language=English
DataDirect%0
.

MessageId=10041 SymbolicName=MSG_VCTYPE_MULTI_SEND
Language=English
MultiSend%0
.

MessageId=10042 SymbolicName=MSG_VCTYPE_MULTI_FORWARD
Language=English
+ MultiFwd%0
.

MessageId=10043 SymbolicName=MSG_ADAPTER
Language=English
Adapter: %1!ws!

.

MessageId=10044 SymbolicName=MSG_ELAN
Language=English
ELAN: %1!ws!

.

MessageId=10045 SymbolicName=MSG_ELAN_NUMBER
Language=English
    ELAN Number:        %1!d!
.

MessageId=10046 SymbolicName=MSG_ELAN_STATE
Language=English
    ELAN State:         %1
.

MessageId=10047 SymbolicName=MSG_C1
Language=English
C1  ATM Address:        %1
.

MessageId=10048 SymbolicName=MSG_C2
Language=English
C2  LAN Type:           %1
.

MessageId=10049 SymbolicName=MSG_C3
Language=English
C3  MaxFrameSize:       %1
.

MessageId=10050 SymbolicName=MSG_C4
Language=English
C4  Proxy:              %1
.

MessageId=10051 SymbolicName=MSG_C5
Language=English
C5  ELAN Name:          %1
.

MessageId=10052 SymbolicName=MSG_C6
Language=English
C6  MAC Address:        %1
.

MessageId=10053 SymbolicName=MSG_C7
Language=English
C7  ControlTimeout:     %1!d! sec
.

MessageId=10054 SymbolicName=MSG_C8
Language=English
C8  RouteDescriptors:   %1
.

MessageId=10055 SymbolicName=MSG_LECS_ADDR
Language=English
    LECS Address:       %1
.

MessageId=10056 SymbolicName=MSG_C9
Language=English
C9  LES Address:        %1
.

MessageId=10057 SymbolicName=MSG_BUS_ADDR
Language=English
    BUS Address:        %1
.

MessageId=10058 SymbolicName=MSG_C10
Language=English
C10 MaxUnkFrameCount:   %1!d!
.

MessageId=10059 SymbolicName=MSG_C11
Language=English
C11 MaxUnkFrameTime:    %1!d! sec
.

MessageId=10060 SymbolicName=MSG_C12
Language=English
C12 VccTimeout:         %1!d! sec
.

MessageId=10061 SymbolicName=MSG_C13
Language=English
C13 MaxRetryCount:      %1!d!
.

MessageId=10062 SymbolicName=MSG_C14
Language=English
C14 LEC ID:             %1!d!
.

MessageId=10063 SymbolicName=MSG_C15
Language=English
C15 MulticastMacAddrs:  Broadcast,All_Multicast
.

MessageId=10064 SymbolicName=MSG_C16
Language=English
C16 LE_ARP Cache:       See below
.

MessageId=10065 SymbolicName=MSG_C17
Language=English
C17 AgingTime:          %1!d! sec
.

MessageId=10066 SymbolicName=MSG_C18
Language=English
C18 ForwardDelayTime:   %1!d! sec
.

MessageId=10067 SymbolicName=MSG_C19
Language=English
C19 TopologyChange:     %1
.

MessageId=10068 SymbolicName=MSG_C20
Language=English
C20 ArpResponseTime:    %1!d! sec
.

MessageId=10069 SymbolicName=MSG_C21
Language=English
C21 FlushTimeout:       %1!d! sec
.

MessageId=10070 SymbolicName=MSG_C22
Language=English
C22 PathSwitchingDelay: %1!d! sec
.

MessageId=10071 SymbolicName=MSG_C23
Language=English
C23 LocalSegmentId:     %1!d!
.

MessageId=10072 SymbolicName=MSG_C24
Language=English
C24 McastSendVcType:    %1
.

MessageId=10073 SymbolicName=MSG_C25
Language=English
C25 McastSendVcRate:    %1!d! cps
.

MessageId=10074 SymbolicName=MSG_C26
Language=English
C26 McastSendPeakRate:  %1!d! cps
.

MessageId=10075 SymbolicName=MSG_C27
Language=English
C27 RemoteMacAddrs:     %1
.

MessageId=10076 SymbolicName=MSG_C28
Language=English
C28 ConnComplTimer:     %1!d! sec
.

MessageId=10077 SymbolicName=MSG_MCAST_VCTYPE_BESTEFFORT
Language=English
Best Effort%0
.

MessageId=10078 SymbolicName=MSG_MCAST_VCTYPE_VARIABLE
Language=English
Variable%0
.

MessageId=10079 SymbolicName=MSG_MCAST_VCTYPE_CONSTANT
Language=English
Constant%0
.

MessageId=10080 SymbolicName=MSG_MCAST_VCTYPE_UNKNOWN
Language=English
 ? %0
.

MessageId=10081 SymbolicName=MSG_C16_LE_ARP_CACHE
Language=English

C16 LE_ARP Cache

.

MessageId=10082 SymbolicName=MSG_CONN_CACHE
Language=English

Connection Cache

.

MessageId=10083 SymbolicName=MSG_ARP_ENTRY
Language=English
%1 -> %2
.

MessageId=10084 SymbolicName=MSG_CONN_ENTRY
Language=English
%1 %2 %3 %4
.
