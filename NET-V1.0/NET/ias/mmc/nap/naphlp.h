//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       naphlp.h
//
//--------------------------------------------------------------------------
//
// Created by Melissa Simmons
// Used by napmmc.rc

#define  IDH_BUTTON_ADD_CONDITION   800020001
#define  IDH_BUTTON_ADD_GROUP 800020026
#define  IDH_BUTTON_CONDITION_ADD   800020352
#define  IDH_BUTTON_CONDITION_EDIT  800020354
#define  IDH_BUTTON_CONDITION_REMOVE   800020353
#define  IDH_BUTTON_EDITPROFILE  800020357
#define  IDH_BUTTON_ENUMCOND_ADD 800020051
#define  IDH_BUTTON_ENUMCOND_DELETE 800020052
#define  IDH_BUTTON_REMOVE_GROUP 800020027
#define  IDH_EDIT_COND_TEXT   800020075
#define  IDH_EDIT_POLICYNAME  800020350
#define  IDH_EDIT_VENDORID 800020229
#define  IDH_IAS_BUTTON_ADD_VALUE   800020181
#define  IDH_IAS_BUTTON_CONFIGURE   800020232
#define  IDH_IAS_BUTTON_EDIT  800020183
#define  IDH_IAS_BUTTON_MOVE_DOWN   800020180
#define  IDH_IAS_BUTTON_MOVE_UP  800020179
#define  IDH_IAS_BUTTON_REMOVE   800020182
#define  IDH_IAS_COMBO_ENUM_VALUES  800020128
#define  IDH_IAS_COMBO_VENDORID  800020227
#define  IDH_IAS_COMBO_VENDORSPEC_FORMAT  800020276
#define  IDH_IAS_EDIT_ATTRVALUE  800020205
#define  IDH_IAS_EDIT_IPADDR  800020153
#define  IDH_IAS_EDIT_MULTI_ATTR_FORMAT   800020177
#define  IDH_IAS_EDIT_MULTI_ATTR_NAME  800020175
#define  IDH_IAS_EDIT_MULTI_ATTR_NUMBER   800020176
#define  IDH_IAS_EDIT_VENDORSPEC_TYPE  800020275
#define  IDH_IAS_EDIT_VENDORSPEC_VALUE 800020250
#define  IDH_IAS_LIST_MULTI_ATTRS   800020178
#define  IDH_IAS_NO_RADIO_HEX 800020231
#define  IDH_IAS_RADIO_HEX 800020204
#define  IDH_IAS_RADIO_RADIUS 800020230
#define  IDH_IAS_RADIO_STRING 800020203
#define  IDH_IAS_STATIC_ATTRFORMAT  800020127
#define  IDH_IAS_STATIC_ATTRNAME 800020125
#define  IDH_IAS_STATIC_ATTRTYPE 800020126
#define  IDH_LIST_COND_SELATTR   800020000
#define  IDH_LIST_CONDITIONS  800020351
#define  IDH_LIST_ENUMCOND_CHOICE   800020050
#define  IDH_LIST_ENUMCOND_SELECTION   800020053
#define  IDH_LIST_GROUPS   800020025
#define  IDH_RADIO_DENY_DIALIN   800020356
#define  IDH_RADIO_ENTERVERDORID 800020228
#define  IDH_RADIO_GRANT_DIALIN  800020355
#define  IDH_RADIO_SELECTFROMLIST   800020226
#define  IDH_RADIO_STORE_ACTIVEDS   800020100
#define  IDH_RADIO_STORE_LOCAL   800020101
#define  IDH_IAS_STATIC_ATTR_VALUE    800020233

#define  IDH_BUTTON_LOCAL_FILE_LOGGING_PAGE2__BROWSE  800010134
#define  IDH_CHECK_LOCAL_FILE_LOGING_PAGE1__ACCOUNTING   800010100
#define  IDH_CHECK_LOCAL_FILE_LOGING_PAGE1__AUTHENTICATION  800010101
#define  IDH_CHECK_LOCAL_FILE_LOGING_PAGE1__INTERIM_ACCT 800010102
#define  IDH_EDIT_LOCAL_FILE_LOGGING_PAGE2__DIRECTORY 800010133
#define  IDH_EDIT_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_SIZE   800010132
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__DAILY 800010127
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__FORMAT_IAS1 800010126
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__FORMAT_ODBC 800010125
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__LOG_LIMIT   800010131
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__MONTHLY  800010129
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__UNLIMITED   800010130
#define  IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__WEEKLY   800010128
#define  IDH_CHECK_DELETE_IF_FULL 800010135

#define  IDH_STATIC_SPECIFY_NAS_VENDOR 900000000
#define  IDH_STATIC_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_NAME 900000001
#define  IDH_TXT_ATTRIBUTEVALUE     900000002
#define  IDH_TXT_CHOOSEFORMAT    900000003

// help IDs for IDD_NEWRAPWIZ_NAME
#define IDH_NEWRAPWIZ_NAME_POLICYNAME  900000004
#define IDH_NEWRAPWIZ_NAME_SCENARIO    900000005
#define IDH_NEWRAPWIZ_NAME_MANUAL      900000006

// help IDs for IDD_NEWRAPWIZ_GROUP
#define IDH_NEWRAPWIZ_GROUP_REMOVEGROUP 900001020
#define IDH_NEWRAPWIZ_GROUP_USER        900001021
#define IDH_NEWRAPWIZ_GROUP_GROUP       900001022
#define IDH_NEWRAPWIZ_GROUP_ADDGROUP    900001023
#define IDH_NEWRAPWIZ_GROUP_GROUPS      900001024

// help IDs for IDD_NEWRAPWIZ_AUTHENTICATION
#define IDH_NEWRAPWIZ_AUTH_EAP          900001040
#define IDH_NEWRAPWIZ_AUTH_EAP_COMBO    900001041
#define IDH_NEWRAPWIZ_AUTH_CONFIGEAP    900001042
#define IDH_NEWRAPWIZ_AUTH_MSCHAP2      900001043
#define IDH_NEWRAPWIZ_AUTH_MSCHAP       900001044

// help IDs for IDD_NEWRAPWIZ_ENCRYPTION
#define IDH_NEWRAPWIZ_ENCRY_NO          900001061
#define IDH_NEWRAPWIZ_ENCRY_BASIC       900001062
#define IDH_NEWRAPWIZ_ENCRY_STRONG      900001063
#define IDH_NEWRAPWIZ_ENCRY_STRONGEST   900001064
#define  IDH_NEWRAPWIZ_ENCRY_NO_STATIC 900001065

// help IDs for IDD_NEWRAPWIZ_SCENARIO
#define IDH_NEWRAPWIZ_SCENARIO_DIALUP   900001080
#define IDH_NEWRAPWIZ_SCENARIO_VPN      900001081
#define IDH_NEWRAPWIZ_SCENARIO_WIRELESS 900001082
#define IDH_NEWRAPWIZ_SCENARIO_SWITCH   900001083

// help IDs for IDD_IAS_BOOLEAN_ATTR
#define IDH_TXT_PROF_ATTR_SELECT_VALUE 800020090
#define IDH_RADIO_PROF_ATTR_TRUE       800020091
#define IDH_RADIO_PROF_ATTR_FALSE      800020092

// help IDs for IDD_IAS_IP_FILTER_ATTR
#define IDH_BUTTON_FROMCLIENT           800020300
#define IDH_BUTTON_TOCLIENT             800020301
#define IDH_TXT_PROF_ATTR_INPUT_FILTER  800020302
#define IDH_TXT_PROF_ATTR_OUTPUT_FILTER 800020303

const DWORD g_aHelpIDs_IDD_COND_SELECT_ATTRIBUTE[]=
{
   IDC_LIST_COND_SELATTR,IDH_LIST_COND_SELATTR,
   IDC_BUTTON_ADD_CONDITION,IDH_BUTTON_ADD_CONDITION,
   0,0
};

const DWORD g_aHelpIDs_IDD_DIALOG_DISPLAY_GROUPS[]=
{
   IDC_LIST_GROUPS,IDH_LIST_GROUPS,
   IDC_BUTTON_ADD_GROUP,IDH_BUTTON_ADD_GROUP,
   IDC_BUTTON_REMOVE_GROUP,IDH_BUTTON_REMOVE_GROUP,
   0,0
};

const DWORD g_aHelpIDs_IDD_DIALOG_ENUM_COND[]=
{
   IDC_LIST_ENUMCOND_CHOICE,IDH_LIST_ENUMCOND_CHOICE,
   IDC_BUTTON_ENUMCOND_ADD,IDH_BUTTON_ENUMCOND_ADD,
   IDC_BUTTON_ENUMCOND_DELETE,IDH_BUTTON_ENUMCOND_DELETE,
   IDC_LIST_ENUMCOND_SELECTION,IDH_LIST_ENUMCOND_SELECTION,
   0,0
};

const DWORD g_aHelpIDs_IDD_DIALOG_MATCH_COND[]=
{
   IDC_EDIT_COND_TEXT,IDH_EDIT_COND_TEXT,
   0,0
};

const DWORD g_aHelpIDs_IDD_DIALOG_POLICY_LOCATION[]=
{
   IDC_RADIO_STORE_ACTIVEDS,IDH_RADIO_STORE_ACTIVEDS,
   IDC_RADIO_STORE_LOCAL,IDH_RADIO_STORE_LOCAL,
   0,0
};


const DWORD g_aHelpIDs_IDD_IAS_ENUM_ATTR[]=
{
   IDC_IAS_STATIC_ATTRNAME,IDH_IAS_STATIC_ATTRNAME,
   IDC_IAS_STATIC_ATTRTYPE,IDH_IAS_STATIC_ATTRTYPE,
   IDC_IAS_STATIC_ATTRFORMAT,IDH_IAS_STATIC_ATTRFORMAT,
   IDC_IAS_COMBO_ENUM_VALUES,IDH_IAS_COMBO_ENUM_VALUES,
   0,0
};


const DWORD g_aHelpIDs_IDD_IAS_IPADDR_ATTR[]=
{
   IDC_IAS_STATIC_ATTRNAME,IDH_IAS_STATIC_ATTRNAME,
   IDC_IAS_STATIC_ATTRTYPE,IDH_IAS_STATIC_ATTRTYPE,
   IDC_IAS_STATIC_ATTRFORMAT,IDH_IAS_STATIC_ATTRFORMAT,
   IDC_IAS_EDIT_IPADDR,IDH_IAS_EDIT_IPADDR,
   0,0
};

const DWORD g_aHelpIDs_IDD_IAS_MULTIVALUED_EDITOR[]=
{
   IDC_IAS_EDIT_MULTI_ATTR_NAME,IDH_IAS_EDIT_MULTI_ATTR_NAME,
   IDC_IAS_EDIT_MULTI_ATTR_NUMBER,IDH_IAS_EDIT_MULTI_ATTR_NUMBER,
   IDC_IAS_EDIT_MULTI_ATTR_FORMAT,IDH_IAS_EDIT_MULTI_ATTR_FORMAT,
   IDC_IAS_LIST_MULTI_ATTRS,IDH_IAS_LIST_MULTI_ATTRS,
   IDC_IAS_BUTTON_MOVE_UP,IDH_IAS_BUTTON_MOVE_UP,
   IDC_IAS_BUTTON_MOVE_DOWN,IDH_IAS_BUTTON_MOVE_DOWN,
   IDC_IAS_BUTTON_ADD_VALUE,IDH_IAS_BUTTON_ADD_VALUE,
   IDC_IAS_BUTTON_REMOVE,IDH_IAS_BUTTON_REMOVE,
   IDC_IAS_BUTTON_EDIT,IDH_IAS_BUTTON_EDIT,
   0,0
};

const DWORD g_aHelpIDs_IDD_IAS_SINGLE_ATTR[]=
{
   IDC_TXT_ATTRIBUTEVALUE, IDH_TXT_ATTRIBUTEVALUE,
   IDC_TXT_CHOOSEFORMAT, IDH_TXT_CHOOSEFORMAT,
   IDC_IAS_STATIC_ATTRNAME,IDH_IAS_STATIC_ATTRNAME,
   IDC_IAS_STATIC_ATTRTYPE,IDH_IAS_STATIC_ATTRTYPE,
   IDC_IAS_STATIC_ATTRFORMAT,IDH_IAS_STATIC_ATTRFORMAT,
   IDC_RADIO_STRING,IDH_IAS_RADIO_STRING,
   IDC_RADIO_HEX,IDH_IAS_RADIO_HEX,
   IDC_IAS_EDIT_ATTRVALUE,IDH_IAS_EDIT_ATTRVALUE,
   0,0
};

const DWORD g_aHelpIDs_IDD_IAS_BOOLEAN_ATTR[]=
{
   IDC_TXT_ATTRIBUTEVALUE, IDH_TXT_ATTRIBUTEVALUE,
   IDC_IAS_STATIC_ATTRNAME,IDH_IAS_STATIC_ATTRNAME,
   IDC_IAS_STATIC_ATTRTYPE,IDH_IAS_STATIC_ATTRTYPE,
   IDC_IAS_STATIC_ATTRFORMAT,IDH_IAS_STATIC_ATTRFORMAT,
   IDC_TXT_SELECT_VALUE,IDH_TXT_PROF_ATTR_SELECT_VALUE,
   IDC_RADIO_TRUE,IDH_RADIO_PROF_ATTR_TRUE,
   IDC_RADIO_FALSE,IDH_RADIO_PROF_ATTR_FALSE,
   0,0
};

const DWORD g_aHelpIDs_IDD_IAS_IP_FILTER_ATTR[]=
{
   IDC_IAS_STATIC_ATTRNAME, IDH_IAS_STATIC_ATTRNAME,
   IDC_IAS_STATIC_ATTRTYPE, IDH_IAS_STATIC_ATTRTYPE,
   IDC_BUTTON_FROMCLIENT, IDH_BUTTON_FROMCLIENT,
   IDC_BUTTON_TOCLIENT, IDH_BUTTON_TOCLIENT,
   IDC_TXT_PROF_ATTR_INPUT_FILTER, IDH_TXT_PROF_ATTR_INPUT_FILTER,
   IDC_TXT_PROF_ATTR_OUTPUT_FILTER, IDH_TXT_PROF_ATTR_OUTPUT_FILTER,
   0,0
};

const DWORD g_aHelpIDs_IDD_IAS_VENDORSPEC_ATTR[]=
{
   IDC_IAS_STATIC_ATTRNAME,IDH_IAS_STATIC_ATTRNAME,
   IDC_RADIO_SELECTFROMLIST,IDH_RADIO_SELECTFROMLIST,
   IDC_IAS_COMBO_VENDORID,IDH_IAS_COMBO_VENDORID,
   IDC_RADIO_ENTERVERDORID,IDH_RADIO_ENTERVERDORID,
   IDC_EDIT_VENDORID,IDH_EDIT_VENDORID,
   IDC_STATIC_SPECIFY_NAS_VENDOR, IDH_STATIC_SPECIFY_NAS_VENDOR,
   IDC_IAS_RADIO_RADIUS,IDH_IAS_RADIO_RADIUS,
   IDC_IAS_RADIO_HEX,IDH_IAS_NO_RADIO_HEX,
   IDC_IAS_BUTTON_CONFIGURE,IDH_IAS_BUTTON_CONFIGURE,
   IDC_IAS_STATIC_ATTR_VALUE, IDH_IAS_STATIC_ATTR_VALUE,
   0,0
};


const DWORD g_aHelpIDs_IDD_IAS_VENDORSPEC_ATTR_CONFORMS_NO[]=
{
   IDC_IAS_EDIT_VENDORSPEC_VALUE,IDH_IAS_EDIT_VENDORSPEC_VALUE,
   0,0
};

const DWORD g_aHelpIDs_IDD_IAS_VENDORSPEC_ATTR_CONFORMS_YES[]=
{
   IDC_IAS_EDIT_VENDORSPEC_TYPE,IDH_IAS_EDIT_VENDORSPEC_TYPE,
   IDC_IAS_COMBO_VENDORSPEC_FORMAT,IDH_IAS_COMBO_VENDORSPEC_FORMAT,
   IDC_IAS_EDIT_VENDORSPEC_VALUE,IDH_IAS_EDIT_VENDORSPEC_VALUE,
   0,0
};

const DWORD g_aHelpIDs_IDD_PROPPAGE_POLICY1[]=
{
   IDC_LIST_CONDITIONS,IDH_LIST_CONDITIONS,
   IDC_BUTTON_CONDITION_ADD,IDH_BUTTON_CONDITION_ADD,
   IDC_BUTTON_CONDITION_REMOVE,IDH_BUTTON_CONDITION_REMOVE,
   IDC_BUTTON_CONDITION_EDIT,IDH_BUTTON_CONDITION_EDIT,
   IDC_RADIO_GRANT_DIALIN,IDH_RADIO_GRANT_DIALIN,
   IDC_RADIO_DENY_DIALIN,IDH_RADIO_DENY_DIALIN,
   IDC_BUTTON_EDITPROFILE,IDH_BUTTON_EDITPROFILE,
   0,0
};


const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_WELCOME[]=
{
   0,0
};

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_COMPLETION[]=
{
   0,0
};

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_NAME[]=
{
   IDC_NEWRAPWIZ_NAME_POLICYNAME,   IDH_NEWRAPWIZ_NAME_POLICYNAME,
   IDC_NEWRAPWIZ_NAME_SCENARIO,     IDH_NEWRAPWIZ_NAME_SCENARIO  ,
   IDC_NEWRAPWIZ_NAME_MANUAL,       IDH_NEWRAPWIZ_NAME_MANUAL   ,
   0,0
};

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_SCENARIO[]=
{
   IDC_NEWRAPWIZ_SCENARIO_DIALUP,      IDH_NEWRAPWIZ_SCENARIO_DIALUP,
   IDC_NEWRAPWIZ_SCENARIO_VPN,        IDH_NEWRAPWIZ_SCENARIO_VPN,
   IDC_NEWRAPWIZ_SCENARIO_WIRELESS, IDH_NEWRAPWIZ_SCENARIO_WIRELESS,
   IDC_NEWRAPWIZ_SCENARIO_SWITCH,     IDH_NEWRAPWIZ_SCENARIO_SWITCH,
   0,0
};

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_GROUP[]=
{
   IDC_NEWRAPWIZ_GROUP_REMOVEGROUP,    IDH_NEWRAPWIZ_GROUP_REMOVEGROUP,
   IDC_NEWRAPWIZ_GROUP_USER,         IDH_NEWRAPWIZ_GROUP_USER,
   IDC_NEWRAPWIZ_GROUP_GROUP,       IDH_NEWRAPWIZ_GROUP_GROUP,
   IDC_NEWRAPWIZ_GROUP_ADDGROUP,    IDH_NEWRAPWIZ_GROUP_ADDGROUP,
   IDC_NEWRAPWIZ_GROUP_GROUPS,        IDH_NEWRAPWIZ_GROUP_GROUPS,
   0,0
};

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_AUTHENTICATION[]=
{
   IDC_NEWRAPWIZ_AUTH_EAP        ,IDH_NEWRAPWIZ_AUTH_EAP        ,
   IDC_NEWRAPWIZ_AUTH_EAP_COMBO  ,IDH_NEWRAPWIZ_AUTH_EAP_COMBO  ,
   IDC_NEWRAPWIZ_AUTH_CONFIGEAP  ,IDH_NEWRAPWIZ_AUTH_CONFIGEAP  ,
   IDC_NEWRAPWIZ_AUTH_MSCHAP2    ,IDH_NEWRAPWIZ_AUTH_MSCHAP2    ,
   IDC_NEWRAPWIZ_AUTH_MSCHAP     ,IDH_NEWRAPWIZ_AUTH_MSCHAP     ,
   0,0
};

const DWORD* g_aHelpIDs_IDD_NEWRAPWIZ_EAP = g_aHelpIDs_IDD_NEWRAPWIZ_AUTHENTICATION;

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_ENCRYPTION[]=
{
   IDC_NEWRAPWIZ_ENCRY_NO       ,IDH_NEWRAPWIZ_ENCRY_NO       ,
   IDC_NEWRAPWIZ_ENCRY_BASIC    ,IDH_NEWRAPWIZ_ENCRY_BASIC    ,
   IDC_NEWRAPWIZ_ENCRY_STRONG   ,IDH_NEWRAPWIZ_ENCRY_STRONG   ,
   IDC_NEWRAPWIZ_ENCRY_STRONGEST,IDH_NEWRAPWIZ_ENCRY_STRONGEST,
   0,0
};


const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_CONDITION[]=
{
   IDC_LIST_CONDITIONS,IDH_LIST_CONDITIONS,
   IDC_BUTTON_CONDITION_ADD,IDH_BUTTON_CONDITION_ADD,
   IDC_BUTTON_CONDITION_REMOVE,IDH_BUTTON_CONDITION_REMOVE,
   IDC_BUTTON_CONDITION_EDIT,IDH_BUTTON_CONDITION_EDIT,
   0,0
};

const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_ALLOWDENY[]=
{
   IDC_RADIO_GRANT_DIALIN,IDH_RADIO_GRANT_DIALIN,
   IDC_RADIO_DENY_DIALIN,IDH_RADIO_DENY_DIALIN,
   0,0
};


const DWORD g_aHelpIDs_IDD_NEWRAPWIZ_EDITPROFILE[]=
{
   IDC_BUTTON_EDITPROFILE,IDH_BUTTON_EDITPROFILE,
   0,0
};

//These are the same as IAShlp.h

const DWORD g_aHelpIDs_IDD_PROPPAGE_LOCAL_FILE_LOGGING1[]=
{
   IDC_CHECK_LOCAL_FILE_LOGING_PAGE1__LOG_ACCOUNTING_PACKETS,IDH_CHECK_LOCAL_FILE_LOGING_PAGE1__ACCOUNTING,
   IDC_CHECK_LOCAL_FILE_LOGING_PAGE1__LOG_AUTHENTICATION_PACKETS,IDH_CHECK_LOCAL_FILE_LOGING_PAGE1__AUTHENTICATION,
   IDC_CHECK_LOCAL_FILE_LOGING_PAGE1__LOG_INTERIM_ACCOUNTING_PACKETS,IDH_CHECK_LOCAL_FILE_LOGING_PAGE1__INTERIM_ACCT,
   0,0
};

const DWORD g_aHelpIDs_IDD_PROPPAGE_LOCAL_FILE_LOGGING2[]=
{
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__FORMAT_ODBC,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__FORMAT_ODBC,
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__FORMAT_IAS1,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__FORMAT_IAS1,
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__DAILY,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__DAILY,
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__WEEKLY,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__WEEKLY,
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__MONTHLY,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__MONTHLY,
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__UNLIMITED,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__UNLIMITED,
   IDC_RADIO_LOCAL_FILE_LOGGING_PAGE2__WHEN_LOG_FILE_REACHES,IDH_RADIO_LOCAL_FILE_LOGGING_PAGE2__LOG_LIMIT,
   IDC_EDIT_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_SIZE,IDH_EDIT_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_SIZE,
   IDC_STATIC_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_SIZE_UNITS,IDH_EDIT_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_SIZE,
   IDC_EDIT_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_DIRECTORY,IDH_EDIT_LOCAL_FILE_LOGGING_PAGE2__DIRECTORY,
   IDC_BUTTON_LOCAL_FILE_LOGGING_PAGE2__BROWSE,IDH_BUTTON_LOCAL_FILE_LOGGING_PAGE2__BROWSE,
   IDC_STATIC_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_NAME , IDH_STATIC_LOCAL_FILE_LOGGING_PAGE2__LOG_FILE_NAME  ,
   IDC_CHECK_DELETE_IF_FULL, IDH_CHECK_DELETE_IF_FULL,
   0,0
};

///////////////////////////////////////////////////////////////////////////////
// Now for the Proxy pages
///////////////////////////////////////////////////////////////////////////////
//#define IDH_BUTTON_ADD_CLIENT__CONFIGURE_CLIENT   800010052
//#define IDH_BUTTON_CLIENT_PAGE1__FIND 800010077
//#define IDH_CHECK_CLIENT_PAGE1__CLIENT_ALWAYS  800010079
//#define IDH_COMBO_ADD_CLIENT__PROTOCOL   800010051
//#define IDH_COMBO_CLIENT_PAGE1__MANUFACTURER   800010078
//#define IDH_EDIT_ADD_CLIENT__NAME  800010050
//#define IDH_EDIT_CLIENT_PAGE1__ADDRESS   800010076
//#define IDH_EDIT_CLIENT_PAGE1__NAME   800010075
//#define IDH_EDIT_CLIENT_PAGE1__SHARED_SECRET   800010080
//#define IDH_EDIT_CLIENT_PAGE1__SHARED_SECRET_CONFIRM 800010081

//#define IDH_BUTTON_RESOLVE_DNS_NAME__USE_THIS_IP 900000000

//#define IDH_BUTTON_REALMS_ADD   800010003
//#define IDH_BUTTON_REALMS_EDIT  800010005
//#define IDH_BUTTON_REALMS_MOVE_DOWN   800010002
//#define IDH_BUTTON_REALMS_MOVE_UP  800010001
//#define IDH_BUTTON_REALMS_REMOVE   800010004
//#define IDH_LIST_REALMS_REPLACEMENTS  800010000

//#define IDH_CHECK_SERVER_PAGE1__CAPTURE_DEBUG_PACKETS   800010152
//#define IDH_CHECK_SERVER_PAGE1__CAPTURE_MALFORMED_PACKETS  800010151
//#define IDH_EDIT_SERVER_PAGE1__NAME   800010150
//#define IDH_EDIT_SERVER_PAGE2_ACCOUNTING_PORT  800010176
//#define IDH_EDIT_SERVER_PAGE2_AUTHENTICATION_PORT 800010175

//#define IDH_EDIT_STARTUP_WIZARD_CONNECT__COMPUTER_NAME  800010277
//#define IDH_RADIO_STARTUP_WIZARD_CONNECT__ANOTHER_COMPUTER 800010276
//#define IDH_RADIO_STARTUP_WIZARD_CONNECT__LOCAL_COMPUTER   800010275

/////////
// Attribute manipulation rule
/////////
// Adv tab.
#define IDH_LIST_PROF_ATTR_ADVLIST  800020022
#define IDH_BUTTON_PROF_ADV_ADD     800020023
#define IDH_BUTTON_PROF_ADV_EDIT    800020024
#define IDH_BUTTON_PROF_ADV_REMOVE  800020046


///////////////////////////////////////////////////////////////////////////////
// RADIUS Server Group properties
///////////////////////////////////////////////////////////////////////////////
#define IDH_EDIT_RSG_PROP_GROUPNAME 800020047
#define IDH_LIST_RSG_PROP_GROUPMEM  800020048
#define IDH_BUTTON_RSG_PROP_ADD     800020028
#define IDH_BUTTON_RSG_PROP_REMOVE  800020029
#define IDH_BUTTON_RSG_PROP_PROP    800020030

const  DWORD g_aHelpIDs_IDD_SERVER_GROUP[]=
{
   IDC_EDIT_NAME,     IDH_EDIT_RSG_PROP_GROUPNAME,
   IDC_LIST_SERVERS,  IDH_LIST_RSG_PROP_GROUPMEM,
   IDC_BUTTON_ADD,    IDH_BUTTON_RSG_PROP_ADD,
   IDC_BUTTON_REMOVE, IDH_BUTTON_RSG_PROP_REMOVE,
   IDC_BUTTON_EDIT,   IDH_BUTTON_RSG_PROP_PROP,
   0,0
};


///////////////////////////////////////////////////////////////////////////////
// Remote RADIUS server properties
///////////////////////////////////////////////////////////////////////////////

//////////
// Address tab
//////////
#define IDH_EDIT_RSG_MEMBER_ADDR_NAME     800020031
#define IDH_BUTTON_RSG_MEMBER_ADDR_VERIFY 800020032

const  DWORD g_aHelpIDs_IDD_SERVER_NAME[]=
{
   IDC_EDIT_NAME,     IDH_EDIT_RSG_MEMBER_ADDR_NAME,
   IDC_BUTTON_VERIFY, IDH_BUTTON_RSG_MEMBER_ADDR_VERIFY,
   0,0
};

//////////
// Authentication / Accounting tab
//////////
#define IDH_EDIT_RSG_MEMBER_AUTHACCT_AUTHPORT     800020033
#define IDH_EDIT_RSG_MEMBER_AUTHACCT_AUTHSECRET   800020034
#define IDH_EDIT_RSG_MEMBER_AUTHACCT_AUTHSECRET2  800020035
#define IDH_EDIT_RSG_MEMBER_AUTHACCT_ACCTPORT     800020036
#define IDH_CHECK_RSG_MEMBER_AUTHACCT_SAMESECRET  800020037
#define IDH_EDIT_RSG_MEMBER_AUTHACCT_ACCTSECRET   800020038
#define IDH_EDIT_RSG_MEMBER_AUTHACCT_ACCTSECRET2  800020039
#define IDH_CHECK_RSG_MEMBER_AUTHACCT_FWDNOTIFIES 800020040

const  DWORD g_aHelpIDs_IDD_SERVER_AUTH[]=
{
   IDC_EDIT_AUTH_PORT,    IDH_EDIT_RSG_MEMBER_AUTHACCT_AUTHPORT,
   IDC_EDIT_AUTH_SECRET1, IDH_EDIT_RSG_MEMBER_AUTHACCT_AUTHSECRET,
   IDC_EDIT_AUTH_SECRET2, IDH_EDIT_RSG_MEMBER_AUTHACCT_AUTHSECRET2,
   IDC_EDIT_ACCT_PORT,    IDH_EDIT_RSG_MEMBER_AUTHACCT_ACCTPORT,
   IDC_CHECK_SAME_SECRET, IDH_CHECK_RSG_MEMBER_AUTHACCT_SAMESECRET,
   IDC_EDIT_ACCT_SECRET1, IDH_EDIT_RSG_MEMBER_AUTHACCT_ACCTSECRET,
   IDC_EDIT_ACCT_SECRET2, IDH_EDIT_RSG_MEMBER_AUTHACCT_ACCTSECRET2,
   IDC_CHECK_ACCT_ONOFF,  IDH_CHECK_RSG_MEMBER_AUTHACCT_FWDNOTIFIES,
   0,0
};

//////////
// Load-balancing tab
//////////
#define IDH_EDIT_RSG_MEMBER_LB_PRIORITY 800020041
#define IDH_EDIT_RSG_MEMBER_LB_WEIGHT   800020042
#define IDH_EDIT_RSG_MEMBER_LB_ADV1     800020043
#define IDH_EDIT_RSG_MEMBER_LB_ADV2     800020044
#define IDH_EDIT_RSG_MEMBER_LB_ADV3     800020045

const  DWORD g_aHelpIDs_IDD_SERVER_FTLB[]=
{
   IDC_EDIT_PRIORITY, IDH_EDIT_RSG_MEMBER_LB_PRIORITY,
   IDC_EDIT_WEIGHT,   IDH_EDIT_RSG_MEMBER_LB_WEIGHT,
   IDC_EDIT_TIMEOUT,  IDH_EDIT_RSG_MEMBER_LB_ADV1,
   IDC_EDIT_MAX_LOST, IDH_EDIT_RSG_MEMBER_LB_ADV2,
   IDC_EDIT_BLACKOUT, IDH_EDIT_RSG_MEMBER_LB_ADV3,
   0,0
};

//////////
// Verify server address dialog.
//////////

#define IDH_EDIT_RSG_VRFYSRV_NAME      800020057
#define IDH_BUTTON_RSG_VRFYSRV_RESOLVE 800020058
#define IDH_LIST_RSG_VRFYSRV_IPADDRS   800020059

const  DWORD g_aHelpIDs_IDD_RESOLVE_SERVER_ADDRESS[]=
{
   IDC_EDIT_NAME,      IDH_EDIT_RSG_VRFYSRV_NAME,
   IDC_BUTTON_RESOLVE, IDH_BUTTON_RSG_VRFYSRV_RESOLVE,
   IDC_LIST_IPADDRS,   IDH_LIST_RSG_VRFYSRV_IPADDRS,
   0,0
};

//////////
// Verify client address dialog.
//////////

#define IDH_EDIT_RSG_VRFYCLNT_NAME      800020060
#define IDH_BUTTON_RSG_VRFYCLNT_RESOLVE 800020061
#define IDH_LIST_RSG_VRFYCLNT_IPADDRS   800020062

const  DWORD g_aHelpIDs_IDD_RESOLVE_CLIENT_ADDRESS[]=
{
   IDC_EDIT_NAME,      IDH_EDIT_RSG_VRFYCLNT_NAME,
   IDC_BUTTON_RESOLVE, IDH_BUTTON_RSG_VRFYCLNT_RESOLVE,
   IDC_LIST_IPADDRS,   IDH_LIST_RSG_VRFYCLNT_IPADDRS,
   0,0
};

///////////////////////////////////////////////////////////////////////////////
// Proxy Policy Properties
///////////////////////////////////////////////////////////////////////////////

//////////
// Policy page
//////////
#define IDH_EDIT_CRP_POLNAME   800020007
#define IDH_LIST_CRP_POLCOND   800020002
#define IDH_BUTTON_CRP_ADD     800020003
#define IDH_BUTTON_CRP_EDIT    800020004
#define IDH_BUTTON_CRP_REMOVE  800020005
#define IDH_BUTTON_CRP_PROFILE 800020006

const  DWORD g_aHelpIDs_IDD_PROXY_POLICY[]=
{
   IDC_EDIT_NAME,                   IDH_EDIT_CRP_POLNAME,
   IDC_LIST_POLICYPAGE1_CONDITIONS, IDH_LIST_CRP_POLCOND,
   IDC_BUTTON_CONDITION_ADD,        IDH_BUTTON_CRP_ADD,
   IDC_BUTTON_CONDITION_EDIT,       IDH_BUTTON_CRP_EDIT,
   IDC_BUTTON_CONDITION_REMOVE,     IDH_BUTTON_CRP_REMOVE,
   IDC_BUTTON_EDITPROFILE,          IDH_BUTTON_CRP_PROFILE,
   0,0
};


///////////////////////////////////////////////////////////////////////////////
// Proxy Profile Properties
///////////////////////////////////////////////////////////////////////////////

//////////
// Authentication tab
//////////
#define IDH_RADIO_PROF_AUTH_LOCAL   800020009
#define IDH_RADIO_PROF_AUTH_REMOTE  800020010
#define IDH_COMBO_PROF_AUTH_GROUPS  800020011
#define IDH_RADIO_PROF_AUTH_UNAUTH  800020012

const  DWORD g_aHelpIDs_IDD_PROXY_PROFILE_AUTH[]=
{
   IDC_RADIO_NONE,    IDH_RADIO_PROF_AUTH_UNAUTH,
   IDC_RADIO_WINDOWS, IDH_RADIO_PROF_AUTH_LOCAL,
   IDC_RADIO_RADIUS,  IDH_RADIO_PROF_AUTH_REMOTE,
   IDC_COMBO_GROUP,   IDH_COMBO_PROF_AUTH_GROUPS,
   0,0
};

//////////
// Accounting tab
//////////
#define IDH_CHECK_PROF_ACCT_REMOTE  800020013
#define IDH_COMBO_PROF_ACCT_GROUPS  800020014

const  DWORD g_aHelpIDs_IDD_PROXY_PROFILE_ACCT[]=
{
   IDC_CHECK_RECORD_ACCT, IDH_CHECK_PROF_ACCT_REMOTE,
   IDC_COMBO_GROUP, IDH_COMBO_PROF_ACCT_GROUPS,
   0,0
};

//////////
// Attribute manipulation tab
//////////
#define IDH_COMBO_PROF_ATTR_ATTRNAME   800020015
#define IDH_LIST_PROF_ATTR_RULELIST 800020016
#define IDH_BUTTON_PROF_ATTR_MOVEUP 800020017
#define IDH_BUTTON_PROF_ATTR_MOVEDOWN  800020018
#define IDH_BUTTON_PROF_ATTR_ADD 800020019
#define IDH_BUTTON_PROF_ATTR_EDIT   800020020
#define IDH_BUTTON_PROF_ATTR_REMOVE 800020021

const  DWORD g_aHelpIDs_IDD_PROXY_PROFILE_ATTR[]=
{
   IDC_COMBO_TARGET,     IDH_COMBO_PROF_ATTR_ATTRNAME,
   IDC_LIST_RULES,       IDH_LIST_PROF_ATTR_RULELIST,
   IDC_BUTTON_MOVE_UP,   IDH_BUTTON_PROF_ATTR_MOVEUP,
   IDC_BUTTON_MOVE_DOWN, IDH_BUTTON_PROF_ATTR_MOVEDOWN,
   IDC_BUTTON_ADD,       IDH_BUTTON_PROF_ATTR_ADD,
   IDC_BUTTON_REMOVE,    IDH_BUTTON_PROF_ATTR_REMOVE,
   IDC_BUTTON_EDIT,      IDH_BUTTON_PROF_ATTR_EDIT,
   0,0
};

//////////
// Edit attribute manipulation rule
//////////
#define IDH_EDIT_PROF_ATTR_RULE_FIND      800020055
#define IDH_EDIT_PROF_ATTR_RULE_REPLACE   800020056

const  DWORD g_aHelpIDs_IDD_EDIT_RULE[]=
{
   IDC_EDIT_RULE_FIND,    IDH_EDIT_PROF_ATTR_RULE_FIND,
   IDC_EDIT_RULE_REPLACE, IDH_EDIT_PROF_ATTR_RULE_REPLACE,
   0,0
};


/////////
// SQL Server property page.
//////////
#define IDH_DB_CHECK_ACCT         800020401
#define IDH_DB_CHECK_AUTH         800020402
#define IDH_DB_CHECK_INTERIM      800020403
#define IDH_DB_EDIT_MAX_SESSIONS  800020404
#define IDH_DB_EDIT_DATA_SOURCE   800020405
#define IDH_DB_BUTTON_CONFIGURE   800020406
#define IDH_DB_BUTTON_CLEAR       800020407

const DWORD g_aHelpIDs_IDD_DB_PROPPAGE[] =
{
   IDC_DB_CHECK_ACCT, IDH_DB_CHECK_ACCT,
   IDC_DB_CHECK_AUTH, IDH_DB_CHECK_AUTH,
   IDC_DB_CHECK_INTERIM, IDH_DB_CHECK_INTERIM,
   IDC_DB_EDIT_MAX_SESSIONS, IDH_DB_EDIT_MAX_SESSIONS,
   IDC_DB_EDIT_DATA_SOURCE, IDH_DB_EDIT_DATA_SOURCE,
   IDC_DB_BUTTON_CONFIGURE, IDH_DB_BUTTON_CONFIGURE,
   IDC_DB_BUTTON_CLEAR, IDH_DB_BUTTON_CLEAR,
   0, 0
};
