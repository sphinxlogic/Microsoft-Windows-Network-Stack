#define IDH_ARPS_MUL_LOWER_IP	30000001
#define IDH_ARPS_MUL_UPPER_IP	30000003
#define IDH_LVW_ARPS_REG_ADDR	30000051
#define IDH_PSH_ARPS_REG_ADD	30000052
#define IDH_PSH_ARPS_REG_EDT	30000053
#define IDH_PSH_ARPS_REG_RMV	30000054
#define IDH_LVW_ARPS_MUL_ADDR	30000057
#define IDH_PSH_ARPS_MUL_ADD	30000058
#define IDH_PSH_ARPS_MUL_EDT	30000059
#define IDH_PSH_ARPS_MUL_RMV	30000060
#define IDH_EDT_ARPS_REG_Address	30000101
#define IDH_CMB_PVC_Layer2	30000153
#define IDH_EDT_PVC_User_Layer2	30000155
#define IDH_CMB_PVC_Layer3	30000157
#define IDH_EDT_PVC_User_Layer3	30000159
#define IDH_EDT_PVC_Layer3_IPI	30000161
#define IDH_EDT_PVC_SNAP_ID	30000163
#define IDH_CMB_PVC_High_Type	30000166
#define IDH_CMB_PVC_High_Value	30000168
#define IDH_CMB_PVC_Layer2_2	30000203
#define IDH_CMB_PVC_Layer3_2	30000207
#define IDH_CMB_PVC_High_Type_2	30000216
#define IDH_EDT_PVC_Name	30000252
#define IDH_EDT_PVC_VPI	30000254
#define IDH_EDT_PVC_VCI	30000256
#define IDH_CMB_PVC_AAL	30000258
#define IDH_CMB_PVC_Type	30000261
#define IDH_CHK_PVC_CallAddr	30000262
#define IDH_EDT_PVC_CallAddr	30000263
#define IDH_CHK_PVC_AnswerAddr	30000264
#define IDH_EDT_PVC_AnswerAddr	30000265
#define IDH_PBN_PVC_Advanced	30000266
#define IDH_EDT_PVC_TRANS_PEAK	30000302
#define IDH_EDT_PVC_TRANS_AVG	30000304
#define IDH_EDT_PVC_TRANS_BURST	30000306
#define IDH_EDT_PVC_TRANS_MAX_SIZE	30000308
#define IDH_CMB_PVC_TRANS_SERVICE	30000310
#define IDH_EDT_PVC_RECEIVE_PEAK	30000313
#define IDH_EDT_PVC_RECEIVE_AVG	30000315
#define IDH_EDT_PVC_RECEIVE_BURST	30000317
#define IDH_EDT_PVC_RECEIVE_MAX_SIZE	30000319
#define IDH_CMB_PVC_RECEIVE_SERVICE	30000321
#define IDH_LVW_PVC_LIST	30000351
#define IDH_PBN_PVC_Add	30000352
#define IDH_PBN_PVC_Remove	30000353
#define IDH_PBN_PVC_Properties	30000354


const DWORD g_aHelpIDs_IDD_ARPS_MUL_ADDR[]=
{
	IDC_ARPS_MUL_LOWER_IP, IDH_ARPS_MUL_LOWER_IP,
	IDC_ARPS_MUL_UPPER_IP, IDH_ARPS_MUL_UPPER_IP,
	0, 0
};

const DWORD g_aHelpIDs_IDD_ARPS_PROP[]=
{
	IDC_LVW_ARPS_REG_ADDR, IDH_LVW_ARPS_REG_ADDR,
	IDC_PSH_ARPS_REG_ADD, IDH_PSH_ARPS_REG_ADD,
	IDC_PSH_ARPS_REG_EDT, IDH_PSH_ARPS_REG_EDT,
	IDC_PSH_ARPS_REG_RMV, IDH_PSH_ARPS_REG_RMV,
	IDC_LVW_ARPS_MUL_ADDR, IDH_LVW_ARPS_MUL_ADDR,
	IDC_PSH_ARPS_MUL_ADD, IDH_PSH_ARPS_MUL_ADD,
	IDC_PSH_ARPS_MUL_EDT, IDH_PSH_ARPS_MUL_EDT,
	IDC_PSH_ARPS_MUL_RMV, IDH_PSH_ARPS_MUL_RMV,
	0, 0
};

const DWORD g_aHelpIDs_IDD_ARPS_REG_ADDR[]=
{
	IDC_EDT_ARPS_REG_Address, IDH_EDT_ARPS_REG_Address,
	0,0
};

const DWORD g_aHelpIDs_IDD_PVC_Dest[]=
{
	IDC_CMB_PVC_Layer2, IDH_CMB_PVC_Layer2,
	IDC_EDT_PVC_User_Layer2, IDH_EDT_PVC_User_Layer2,
	IDC_CMB_PVC_Layer3, IDH_CMB_PVC_Layer3,
	IDC_EDT_PVC_User_Layer3, IDH_EDT_PVC_User_Layer3,
	IDC_EDT_PVC_Layer3_IPI, IDH_EDT_PVC_Layer3_IPI,
	IDC_EDT_PVC_SNAP_ID, IDH_EDT_PVC_SNAP_ID,
	IDC_CMB_PVC_High_Type, IDH_CMB_PVC_High_Type,
	IDC_CMB_PVC_High_Value, IDH_CMB_PVC_High_Value,
	0,0
};

const DWORD g_aHelpIDs_IDD_PVC_Local[]=
{
	IDC_CMB_PVC_Layer2, IDH_CMB_PVC_Layer2_2,
	IDC_EDT_PVC_User_Layer2, IDH_EDT_PVC_User_Layer2,
	IDC_CMB_PVC_Layer3, IDH_CMB_PVC_Layer3_2,
	IDC_EDT_PVC_User_Layer3, IDH_EDT_PVC_User_Layer3,
	IDC_EDT_PVC_Layer3_IPI, IDH_EDT_PVC_Layer3_IPI,
	IDC_EDT_PVC_SNAP_ID, IDH_EDT_PVC_SNAP_ID,
	IDC_CMB_PVC_High_Type, IDH_CMB_PVC_High_Type_2,
	IDC_CMB_PVC_High_Value, IDH_CMB_PVC_High_Value,
	0,0
};

const DWORD g_aHelpIDs_IDD_PVC_Main[]=
{
	IDC_EDT_PVC_Name, IDH_EDT_PVC_Name,
	IDC_EDT_PVC_VPI, IDH_EDT_PVC_VPI,
	IDC_EDT_PVC_VCI, IDH_EDT_PVC_VCI,
	IDC_CMB_PVC_AAL, IDH_CMB_PVC_AAL,
	IDC_CMB_PVC_Type, IDH_CMB_PVC_Type,
	IDC_CHK_PVC_CallAddr, IDH_CHK_PVC_CallAddr,
	IDC_EDT_PVC_CallAddr, IDH_EDT_PVC_CallAddr,
	IDC_CHK_PVC_AnswerAddr, IDH_CHK_PVC_AnswerAddr,
	IDC_EDT_PVC_AnswerAddr, IDH_EDT_PVC_AnswerAddr,
	IDC_PBN_PVC_Advanced, IDH_PBN_PVC_Advanced,
	0,0
};

const DWORD g_aHelpIDs_IDD_PVC_Traffic[]=
{
	IDC_EDT_PVC_TRANS_PEAK, IDH_EDT_PVC_TRANS_PEAK,
	IDC_EDT_PVC_TRANS_AVG, IDH_EDT_PVC_TRANS_AVG,
	IDC_EDT_PVC_TRANS_BURST, IDH_EDT_PVC_TRANS_BURST,
	IDC_EDT_PVC_TRANS_MAX_SIZE, IDH_EDT_PVC_TRANS_MAX_SIZE,
	IDC_CMB_PVC_TRANS_SERVICE, IDH_CMB_PVC_TRANS_SERVICE,
	IDC_EDT_PVC_RECEIVE_PEAK, IDH_EDT_PVC_RECEIVE_PEAK,
	IDC_EDT_PVC_RECEIVE_AVG, IDH_EDT_PVC_RECEIVE_AVG,
	IDC_EDT_PVC_RECEIVE_BURST, IDH_EDT_PVC_RECEIVE_BURST,
	IDC_EDT_PVC_RECEIVE_MAX_SIZE, IDH_EDT_PVC_RECEIVE_MAX_SIZE,
	IDC_CMB_PVC_RECEIVE_SERVICE, IDH_CMB_PVC_RECEIVE_SERVICE,
	0,0
};

const DWORD g_aHelpIDs_IDD_UNI_PROP[]=
{
	IDC_LVW_PVC_LIST, IDH_LVW_PVC_LIST,
	IDC_PBN_PVC_Add, IDH_PBN_PVC_Add,
	IDC_PBN_PVC_Remove, IDH_PBN_PVC_Remove,
	IDH_PBN_PVC_Properties, IDH_PBN_PVC_Properties,
	0,0
};
