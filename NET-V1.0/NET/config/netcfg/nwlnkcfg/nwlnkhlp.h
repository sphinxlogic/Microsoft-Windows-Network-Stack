// Copyright (c) 1999, Microsoft Corporation, all rights reserved.
//
// Ipxcfg.h is used by nwlnkcfg.rc
// Help context IDs and Help map
//
// Created in Dev Studio
// 4-22-99 Melissa Simmons


#define IDH_BTN_IPXAS_ADD           17000030
#define IDH_BTN_IPXAS_AUTO          17000027
#define IDH_BTN_IPXAS_EDIT          17000031
#define IDH_BTN_IPXAS_MANUAL        17000028
#define IDH_BTN_IPXAS_REMOVE        17000032
#define IDH_CMB_IPXAS_DEST          17000050
#define IDH_CMB_IPXPP_FRAMETYPE     17000001
#define IDH_EDT_IPXAS_INTERNAL      17000000
#define IDH_EDT_IPXPP_NETWORKNUMBER 17000002
#define IDH_LVC_IPXAS_DEST          17000029

#define IDH_DISABLE_HELP            (DWORD(-1))

const DWORD g_aHelpIDs_DLG_IPX_CONFIG[]=
{
    IDC_STATIC, IDH_DISABLE_HELP,
    EDT_IPXAS_INTERNAL,IDH_EDT_IPXAS_INTERNAL,
    GB_IPXPP_ADAPTER, IDH_DISABLE_HELP,
    IDC_IPXPP_ADAPTER_TEXT, IDH_DISABLE_HELP,
    IDC_STATIC_FRAMETYPE, IDH_CMB_IPXPP_FRAMETYPE,
    CMB_IPXPP_FRAMETYPE,IDH_CMB_IPXPP_FRAMETYPE,
    IDC_STATIC_NETNUM, IDH_EDT_IPXPP_NETWORKNUMBER,
    EDT_IPXPP_NETWORKNUMBER,IDH_EDT_IPXPP_NETWORKNUMBER,
    IDC_IPXPP_TEXT,IDH_DISABLE_HELP,
    0,0
};

const DWORD g_aHelpIDs_DLG_IPXAS_CONFIG[]=
{
    IDC_STATIC, IDH_DISABLE_HELP,
    EDT_IPXAS_INTERNAL,IDH_EDT_IPXAS_INTERNAL,
    IDC_IPXAS_GROUP, IDH_DISABLE_HELP,
    BTN_IPXAS_AUTO,IDH_BTN_IPXAS_AUTO,
    BTN_IPXAS_MANUAL,IDH_BTN_IPXAS_MANUAL,
    LVC_IPXAS_DEST,IDH_LVC_IPXAS_DEST,
    BTN_IPXAS_ADD,IDH_BTN_IPXAS_ADD,
    BTN_IPXAS_EDIT,IDH_BTN_IPXAS_EDIT,
    BTN_IPXAS_REMOVE,IDH_BTN_IPXAS_REMOVE,
    IDC_IPXPP_TEXT,IDH_DISABLE_HELP,
    0,0
};

const DWORD g_aHelpIDs_DLG_IPXAS_FRAME_ADD[]=
{
    IDC_STATIC, IDH_DISABLE_HELP,
    CMB_IPXAS_DEST,IDH_CMB_IPXAS_DEST,
    EDT_IPXAS_NETNUM, IDH_EDT_IPXPP_NETWORKNUMBER,
    0,0
};

const DWORD g_aHelpIDs_DLG_IPXAS_FRAME_EDIT[]=
{
    EDT_IPXAS_NETNUM, IDH_EDT_IPXPP_NETWORKNUMBER,
    0,0
};