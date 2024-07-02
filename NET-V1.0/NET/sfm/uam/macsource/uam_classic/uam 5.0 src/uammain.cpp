// ===========================================================================//	UAMMain.cp 				� 1997-2001 Microsoft Corp. All rights reserved.// ===========================================================================//	Main unit for Microsoft User Authentication Method.////	Notes://	--------------------------------------------------------------------------////// 	Version History:// 	===========================================================================//	04.22.97	MJC - Begin coding version 5.0.//	05.22.97	MJC - Completed version 5.0d5, getting close.//	02.21.98	MJC	- Begin updating for AppleShare 3.8 and AFP/TCP.//	03.02.98	MJC - First working version (5.0d12) with AS Client v3.8a1lawJ//	03.26.98	MJC - Implemented change password. It works, but not when the//					  password has expired on the server. I suspect a bug in//					  in AppleShare Client 3.8a1LawL which doesn't open a session//					  when the error code returned is not noErr. //	03.31.98	MJC	- First checkin into VSS database.////	Version 5.0d15://	04.13.98	MJC	- Changed the way supported UAM's are recorded (bitmap vice//					  a struct of booleans).//					- Change some error code determination code in UAM_OpenSession()//					  and UAM_MSUAMContLogin().//					- Added version string at bottom of dialog window.////	Version 5.0d16://	04.30.98	MJC	- Fixed bug in UAMDSNetwork.c where the AFP login command block//					  would not always end on an even boundary.//					- Added some additional asserts to UAM_DSLoginMSUAM().//					- Changed instances of astring[0] to PSTR_LENGTH(astring).////	Version 5.0d17://	05.19.98	MJC	- Updated for new ClientUAM.h from Apple. Now the main//					  entry returns OSStatus vice OSErr.////	Version 5.0b2://	06.08.98	MJC	- Added new event callback routine for AS and the Chooser//					  in the login dialog filter.//	Version 5.0b3://	09.01.98	MJC	- Fixed bug where null passwords weren't allowed.//	10.23.98	MJC	- Fixed bug where you could use cmd-g to select Guest//					  radio even though it was disabled.//					- Can now use cut, copy and paste in User Name field.//					- Changed 'OK' button to 'Connect' to match Apple's UAM//					- Clicking on 'Registered User' when it is already//					  doesn't cause a flash anymore or select the user name.//	11.13.98	MJC - Added support for passing the actual encrypted password//					  over the wire for cleartxt storage updating when//					  changing password.//				MJC - Added support for notifying the user that their password//					  is about to expire.//	12.01.98	MJC	- Fixed bug were I wasn't reversing the byte order of the//					  returned password expiration time.//	01.22.99	MJC - CheckGatedControls() would step 1 too far in the array.//					- Could not use escape key if username len maxed out.//	Version 5.0.1://	07.12.99	MJC - More problems with UAM_CheckGatedControls(), hopefully all//					  fixed this time.//					  Made small change in MS_VersionUserItem() so we compile//					  under CW Pro 5.//	Version 5.0.2://	10.21.99	MJC - Fixed bug on double byte character OS's (CHX, JPN, etc)//					  where first char in password was getting dropped.//					- Now select all the password text after a login failure.//	Version 5.0.3://	10.29.99	MJC - Fixed bug on international systems where hitting//					  backspace would yield incorrect results (got rid of one//					  char instead of the double byte char).//					- Related to fix above, change password field entry diaplay//					  character to '*' instead of '�'.//	Version 5.0.4://	11.17.99	MJC - Fixed bug in encrypt.c, wasn't locking resource handle,//					  so password OWF was incorrectly generated.//					- SetupUAMEncrypt() was not returning a fail code//					  if loading the data table failed.//	Version 5.0.5://	11.22.99	MJC - Put 2 0x00 bytes at the end of the initial login call for//					  NT4 SP6.//	12.01.99	MJC - Finished keychain support.//					- NOTE: You must now compile the MS UAM with Universal//					  headers v3.3 or later.//					- Can finally build PPC! The MS UAM is now a safe FAT//					  binary. So, it'll run natively on 68K and PPC.//					- Complete rewrite of password edit field handling. Now kicks//					  butt! You can type just like any other text and should work//					  better with foreign languages.//					- Made some changes to the dialog code in preparation//					  for Carbon.//	01.10.00	MJC - Now check for cmd key down when opening UAM so user can//					  bypass keychain.//	03.13.00	MJC - Removed about dialog.//	03.15.00	MJC - Now check for MacOS 9 or > to see if keychain is available.//					- Now week load the Keychain.lib for compatibility with//					  older systems.//	03.20.00	MJC - Fixed bug: When changing password, wasn't checking for existance//					  of keychain manager (caused -2802 error).//	Version 5.0.6://	06.11.00	MJC	- Now give the option to replace keychains items that//					  already exist. This caused problems when the user changed//					  their password on another machine, there was no way to//					  update the keychain item without doing it manually from the//					  KeychainAccess control panel.//	Version 5.0.7://	09.06.00	MJC - Bug fix: keychain item shouldn't appear when guest selected//					- Bug fix: Don't allow white space as first char in user name, this//					  involved redoing the gating logic in UAMDlogUtils.c.//	09.28.00		- Bug fix: Allow null user name and password entries when//					  guest login is enabled on server.//	01.29.01		- Set PPC struct alignment to 68K for fix change password//					  bug.//	Version 5.0.8://	04.26.01	MJC	- Code cleanup. Combined UAMNetwork and UAMDSNetwork into//					  one file (UAMNetwork.c & UAMNetwork.h)//					- UAM_ChangePasswordV2(): Now check for zero length old//					  and new passwords before upper casing.//					- Now use common NTLM des code for login and changepassword v2.//					- Zero password buffers when done with them (security fix).//					- Now clear password field when login error occurs.//	05.01.01		- Fixed bug where over-long user names could be pasted//					  into username field.//					- Can now tab out of user name field when name is max length.//					- Now clear password when failure occurs in UAM_LoginMSUAM().//	07.02.01		- Fixed bug where password was getting cleared before I was//					  adding it to the keychain.////	Version 5.0.9://	10.23.01		- Added support for NTLMv2 authentication//					- Don't support blank passwords for MS2.0 auth//					- Added new MS3.0 encryption protocol (support NTLMv2)////	Version 5.0.10	- Now properly close session after bad password error case.//	Version 5.0.11	- Security review//						- Added max length parameter to string copy routine//						- Found bug where couldn't save passwords more than//						  8 bytes long in keychain. Could lead to AV.//						- Now use strsafe routines.// ===========================================================================#if !GENERATINGCFM#include <A4Stuff.h>#include <SetupA4.h>#else#define EnterCodeResource()#define PrepareCallback()#define ExitCodeResource()#define EnterCallback()#define ExitCallback()#endif#include "UAMMain.h"#include "UAMDebug.h"#include "UAMUtils.h"#include "UAMDialogs.h"#include "UAMNetwork.h"#include "UAMDLOGUtils.h"#include "UAMKeychain.h"#include "UAMPswdField.h"#include "UAMPrefs.h"////Global variables are declared here//Str32				gServerName;Str32				gUserName;Boolean				gContextInited;Boolean				gGuestLogon;Boolean				gSupportsChngPwd;Boolean				gDoingIPConnection;DialogPtr			gDialog;Str32				gAFPVersion;long				gSupportedUAMs;ModalFilterUPP		gDialogFilter;ModalFilterUPP		gPwdDialogFilter;UserItemUPP			gLineItem;UserItemUPP			gVersionItem;Str32				gUAMVersionString;Str32				gZoneName;UInt32				gExpirationTime		= 0;OTAddress*			gServerAddress 		= NULL;EventCallbackPtr	gEventCallbackUPP 	= NULL;Boolean				gTriedKeychain		= false;extern UAM_PREFERENCES	gUAMPreferences;#if GENERATINGCFM//We need to define __procinfo for Metrowerks' linker. This basically//defines main. Without it, we'll get a link error.ProcInfoType __procinfo = kPascalStackBased | RESULT_SIZE(SIZE_CODE(sizeof(OSStatus)))											| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(UAMArgs*)));#endif// ---------------------------------------------------------------------------//		� main()// ---------------------------------------------------------------------------//	This is the main entry point for our UAM. This function is passed a//	pointer to a UAMArgs struct. This struct contains the function selector,//	call-backs, and many other things we need to do our stuff.pascal OSStatus main(UAMArgs *inUAMArgs){	OSStatus theResult = noErr;		EnterCodeResource();	PrepareCallback();				switch(inUAMArgs->command)	{		case kUAMOpen:			theResult = MS_UAMOpen(inUAMArgs);			break;					case kUAMClose:			MS_UAMClose();			break;					case kUAMPWDlog:			theResult = MS_UAMPwdDialog(inUAMArgs);			break;					case kUAMLogin:			theResult = UAM_UAMLogin(inUAMArgs);			break;					case kUAMVSDlog:			break;				case kUAMChgPass:		case kUAMChgPassDlg:			DbgPrint_((DBGBUFF, "Change password dialog must be implemented"));			theResult = kNotForUs;			break;						default:			//			//If we get here then we were asked to handle a routine that			//we don't support. Return the appropriate error code.			//									DbgPrint_((DBGBUFF, "Unsupported function selector in MSUAM main() (%d)", inUAMArgs->command));			theResult = kNotForUs;			break;	}		ExitCodeResource();		return(theResult);}// ---------------------------------------------------------------------------//		� MS_UAMOpen()// ---------------------------------------------------------------------------//	This is called by the device package. It is not a required function but//	we use it to initialize our UAM code. Note that when we encounter an//	error we don't make an effort to clean up. Instead we return userCanceledErr//	in which case our UAMClose function will be called by AppleShare Client.OSStatus MS_UAMOpen(UAMArgs *inUAMArgs){	short 	theUAMConfig = 0;	SInt32	theResponse;			//	//Get the name of the server we want to log into.	//	UAM_PStrCopy(inUAMArgs->Opt.open.objectName, gServerName, sizeof(gServerName));		//	//Copy the zone name for. If it's NULL, then we	//don't have a zone name.	//	if (inUAMArgs->Opt.open.zoneName != NULL)	{		//		//01.16.02: Pass maximum length to string copy routine.		//		UAM_PStrCopy(inUAMArgs->Opt.open.zoneName, gZoneName, sizeof(gZoneName));	}	else		gZoneName[0] = 0;								gContextInited 		= false;		//Been through PwdDialog before?		gGuestLogon 		= false;		//Is guest our logon choice?	gDoingIPConnection	= false;		//Default to AppleTalk support.	gDialog				= NULL;			//So we can see if we really got it.	gDialogFilter		= NULL;		gPwdDialogFilter	= NULL;	gLineItem			= NULL;	gVersionItem		= NULL;	gAFPVersion[0]		= 0;	gUserName[0]		= 0;	gServerAddress		= inUAMArgs->Opt.open.srvrAddress;	gEventCallbackUPP	= inUAMArgs->callbacks->EventCallbackUPP;			gTriedKeychain		= false;		ZeroMemory(&gUAMPreferences, sizeof(UAM_PREFERENCES));	UAM_RetrieveUAMPreferenceData(&gUAMPreferences);			UAM_KCInitialize(inUAMArgs);						//	//Under PowerPC this is a pointer allocated. Under 68K, it just	//points to the function.	//	gDialogFilter = NewModalFilterProc(&UAM_DialogFilter);	if (gDialogFilter == NULL)	{		//		//We check for ptr validity. Note that we don't bother to 		//clean up since we'll get a kUAMClose message next.		//				DbgPrint_((DBGBUFF, "Failed to allocate gDialogFilter"));		return(userCanceledErr);	}		gPwdDialogFilter = NewModalFilterProc(&MS_PwdDialogFilter);	if (gPwdDialogFilter == NULL)	{		DbgPrint_((DBGBUFF, "Failed to allocate gPwdDialogFilter"));		return(userCanceledErr);	}		gLineItem = NewUserItemProc(&UAM_FrameItem);	if (gLineItem == NULL)	{		DbgPrint_((DBGBUFF, "Failed to allocate gLineItem"));		return(userCanceledErr);	}		gVersionItem = NewUserItemProc(&MS_VersionUserItem);	if (gVersionItem == NULL)	{		DbgPrint_((DBGBUFF, "Failed to allocate gVersionItem"));		return(userCanceledErr);	}	//	//Get the AFP version and the default user name. This function finds	//a match which is the highest AFP version supported by both the client	//and server.	//	UAM_GetAFPVersionString(				inUAMArgs->Opt.open.srvrInfo,			inUAMArgs->callbacks,			gAFPVersion,			gUserName 			);		//	//gUserName can be null, we just capture here during debugging to	//ensure we're getting the name properly.	//	Assert_(PSTR_LENGTH(gUserName) != 0);	Assert_(PSTR_LENGTH(gAFPVersion) != 0);		if (PSTR_LENGTH(gAFPVersion) == 0)	{		//		//No AFPVersion, no logon...		//				UAM_ReportError(uamErr_NoAFPVersion);		return(userCanceledErr);	}						gSupportsChngPwd = ((inUAMArgs->Opt.open.srvrInfo->fFlags & kSupportsChngPswd) != 0);		//	//Determine what connection method we are using, IP or AppleTalk. Basically,	//if the client supports IP and the address type is IP, then we have	//a TCP connection.	//	if (inUAMArgs->Opt.open.srvrInfo->fFlags & kSupportsTCPIP)	{		if (inUAMArgs->Opt.open.srvrAddress->fAddressType == AF_INET)		{			gDoingIPConnection = TRUE;		}	}													//	//Get the list of supported UAMs from a utility routine. This data	//is necessary in the password dialog code.	//								UAM_GetSupportedUAMS(			inUAMArgs,			(StringPtr)gAFPVersion,			&gSupportedUAMs		);			//	//We should never get here if the following is false, but we	//check just to be on the safe side.	//	if (	((gSupportedUAMs & kMSUAMSupported) 	== 0)	&&			((gSupportedUAMs & kMSUAM_V2_Supported) == 0)	) 	{		Assert_((gSupportedUAMs & kMSUAMSupported) != 0);				UAM_ReportError(afpBadUAM);		return(userCanceledErr);	}		UAM_VersionString(gUAMVersionString);	UAM_SetMaximumPasswordLength(false);	//	//This is how we tell AppleShare what our UAM supports. We have	//our own password dialog, we support change password, and we	//use our own change password dialog.	//		theUAMConfig |= BIT_0;	//Custom login dialog	theUAMConfig |= BIT_2;	//We support change password	theUAMConfig |= BIT_3;	//Custom change password dialog		inUAMArgs->result = theUAMConfig;			return(noErr);}// ---------------------------------------------------------------------------//		� MS_UAMClose()// ---------------------------------------------------------------------------//	Like UAMOpen, UAMClose has no specific purpose as defined by the device//	manager. We use it to clean up our allocated storage and globals.void MS_UAMClose(void){		if (gDialog != NULL)	{		//		//If we put up our login dialog, get rid of it.		//		UAM_DisposeDialog(gDialog);	}		if (gDialogFilter != NULL)		DisposeRoutineDescriptor(gDialogFilter);	if (gLineItem != NULL)			DisposeRoutineDescriptor(gLineItem);	if (gPwdDialogFilter != NULL)	DisposeRoutineDescriptor(gPwdDialogFilter);	if (gVersionItem != NULL)		DisposeRoutineDescriptor(gVersionItem);}// ---------------------------------------------------------------------------//		� MS_VersionUserItem()// ---------------------------------------------------------------------------//	Custom user item routine to display UAM version number and connection//	type (ATalk or TCP/IP).pascal void MS_VersionUserItem(DialogPtr inDialog, DialogItemIndex inItem){	short	theFont, theSize;	Rect	theItemRect;		EnterCallback();				theFont = inDialog->txFont;	theSize	= inDialog->txSize;		TextFont(kFontIDGeneva);	TextSize(9);		theItemRect = UAM_GetItemRect(inDialog, inItem);		switch(inItem)	{		case DITEM_Version:			//			//Display the version of the MS UAM in the lower right corner.			//			TETextBox(						&gUAMVersionString[1],					PSTR_LENGTH(gUAMVersionString),					&theItemRect,					teJustRight	);			break;				case DITEM_Method:			//			//Let the client know what connection method is being used to			//connect to the server.			//			if (gDoingIPConnection)			{				TETextBox(					&STR_TCPConnection,					strlen(STR_TCPConnection),					&theItemRect,					teJustLeft);			}			else			{				TETextBox(					STR_AppleTalkConnection,					strlen(STR_AppleTalkConnection),					&theItemRect,					teJustLeft);			}			break;					default:			Assert_(0);			break;	}				TextFont(theFont);	TextSize(theSize);		ExitCallback();}// ---------------------------------------------------------------------------//		� MS_TestTextEntryLength()// ---------------------------------------------------------------------------//	We don't allow entries in the login dialog to be of any length. This//	function tests the length of the entered text in an edit field. It will//	modify the event record appropriately to inhibit processing of the//	keystroke if it will take the field over the limit.Boolean MS_TestTextEntryLength(	DialogPtr 		inDialog,	EventRecord*	inEvent,	short 			inItem,	short			inMaxLengthAllowed){	Str255	theString;	Boolean	theResult 	= false;			if ((((DialogPeek)inDialog)->editField + 1) == inItem)	{		UAM_GetText(inDialog, inItem, (Str255 *)&theString);				if (PSTR_LENGTH(theString) >= inMaxLengthAllowed)		{			SysBeep(1);					inEvent->what 		= nullEvent;			inEvent->message	= 0;			theResult 	  		= true;						//			//If the string length is currently too long, then			//we have to chop off the end of the string to the			//proper length.			//			if (PSTR_LENGTH(theString) > inMaxLengthAllowed)			{				//				//Easy way out, pascal style strings have length				//byte in front. Just adjust it.				//				theString[0] = inMaxLengthAllowed;								//				//Now set the text in the edit field with the new string.				//				UAM_SetText(inDialog, inItem, theString);			}		}	}		return(theResult);}// ---------------------------------------------------------------------------//		� MS_PwdDialogFilter()// ---------------------------------------------------------------------------//	Filter function for the password dialog. We have this so we can capture//	command keys and keep length requirements for the user name in the login //	dialog.pascal Boolean MS_PwdDialogFilter(DialogPtr inDialog, EventRecord *inEvent, short *inItem){	short	theCode;	Str255	theString;	Boolean	theResult = false;	SInt16	theMaxUsernameLen;		EnterCallback();				if ((inEvent->what == keyDown) || (inEvent->what == autoKey))	{		theMaxUsernameLen = (gSupportedUAMs & (kMSUAM_V2_Supported | kMSUAM_V3_Supported)) ?								UAM_USERNAMELEN_V3 : UAM_USERNAMELEN;						theCode = (inEvent->message & charCodeMask);				//		//04.30.01: Don't allow cmd selections when autoKey'ing.		//		if ((inEvent->modifiers & cmdKey) && (inEvent->what != autoKey))		{			switch(theCode)			{				case 'g':				case 'G':					*inItem   = DITEM_GuestRadio;					theResult = true;					break;								case 'r':				case 'R':					*inItem   = DITEM_RegRadio;					theResult = true;					break;									case 's':				case 'S':					*inItem	  = DITEM_ChangePwd;					theResult = true;					break;													case 'a':				case 'A':					*inItem   = DITEM_Keychain;					theResult = true;					break;								//				//Handle edit commands from the user. We don't allow any				//editing commands in the password field. This mimicks				//Apple's own UAM's.				//									case 'c':				case 'C':					if ((((DialogPeek)inDialog)->editField + 1) != DITEM_Password) {						DialogCopy(inDialog);					}					break;									case 'v':				case 'V':					if ((((DialogPeek)inDialog)->editField + 1) != DITEM_Password)					{						DialogPaste(inDialog);												//						//For pastes, we have to do a lot more work to ensure the						//user name field doesn't get too big.						//						theResult = MS_TestTextEntryLength(											inDialog,											inEvent,											DITEM_UserName,											theMaxUsernameLen);					}					break;				case 'x':				case 'X':					if ((((DialogPeek)inDialog)->editField + 1) != DITEM_Password) {						DialogCut(inDialog);					}					break;									default:					break;			}		}		else		{			//			//Don't allow more than UAM_USERNAMELEN maximum characters in edit field.			//						if ((((DialogPeek)inDialog)->editField + 1) == DITEM_UserName)			{				UAM_GetText(inDialog, DITEM_UserName, (Str255 *)&theString);								switch(theCode)				{					case UAMKey_BackDel:					case UAMKey_Left:					case UAMKey_Right:					case UAMKey_Return:					case UAMKey_Enter:					case UAMKey_Escape:					case UAMKey_Tab:						break;											default:						if (PSTR_LENGTH(theString) >= theMaxUsernameLen)						{							SysBeep(1);													inEvent->what = nullEvent;							theResult 	  = true;						}						break;				}			}		}	}	else	{		if (gEventCallbackUPP)		{			//			//If we're not handling the event ourselves, then call the			//event callback which gives AS and the Chooser a chance			//to update it's windows, etc.			//						#if GENERATING68K						gEventCallbackUPP(inEvent);						#else						CallUniversalProc(gEventCallbackUPP, kEventCallbackProcInfo, inEvent);						#endif			}	}		ExitCallback();		return(theResult);}// ---------------------------------------------------------------------------//		� MS_UAMPwdDialog()// ---------------------------------------------------------------------------//	This is where we put up our password dialog. The buffers pointed to by//	'inUserName' and 'inPassword' end up getting passed directly to the//	UAMLogin function.////	The buffer passed for the user name and password is 64 bytes long. Don't//	use more than that! OSStatus MS_UAMPwdDialog(UAMArgs *inUAMArgs){	short			theItem, x;	Str255			theStr;	OSStatus		theError	= noErr;	Boolean			theLoop 	= true;		Assert_(gDialogFilter 		!= NULL);	Assert_(gPwdDialogFilter 	!= NULL);	Assert_(gLineItem 			!= NULL);			//	//Determine which user name to use, the default or the	//one supplied by the client (if any). gUserName is filled	//in originally during the UAMOpen call.	//	if (PSTR_LENGTH(inUAMArgs->Opt.pwDlg.userName) != 0)	{		//		//01.16.02: Pass maximum length to string copy routine.		//		UAM_PStrCopy(inUAMArgs->Opt.pwDlg.userName, gUserName, sizeof(gUserName));	}		//	//If we already tried the keychain and failed, we don't want	//to try again or we'll loop forever. Give the user a chance	//to enter the correct name and password.	//	//NOTE: We check to see if the cmd key is down, if it is, then	//we bypass the keychain stuff alltogether. Maybe the user wants	//to change his password!?!?!	//	if ((gTriedKeychain == false) && (UAM_KCAvailable()) && (!UAM_KeyDown(KEY_Command)))	{		gTriedKeychain = true;				if ( (PSTR_LENGTH(inUAMArgs->Opt.pwDlg.userName))	&&			 (PSTR_LENGTH(inUAMArgs->Opt.pwDlg.password))	)		{			//			//We were supplied a username and password by the AFP			//client. This means the user clicked a keychain entry.			//			goto exit;		}		else 		{			theError = UAM_KCFindAppleSharePassword(							gUserName,							inUAMArgs->Opt.pwDlg.password,							gServerName,							NULL			);						if (theError == noErr)			{				DbgPrint_((DBGBUFF, "Pswd found via MSUAM keychain calls;g"));								//				//Fill in the user name for the UAMArgs.				//				if (PSTR_LENGTH(inUAMArgs->Opt.pwDlg.userName) == 0)				{					UAM_PStrCopy(gUserName, inUAMArgs->Opt.pwDlg.userName);				}				//				//A password was found so try to logon.				//				goto exit;			}			else if (	(theError != errKCItemNotFound)		&&						(theError != userCanceledErr)		)			{				//				//Only report "real" errors.				//				UAM_ReportError(theError);			}		}	}	else if ((UAM_KCAvailable()) && (UAM_KeyDown(KEY_Command)))	{		//		//If the user is holding the cmd key down, then we don't want to		//try the keychain the next time through either.		//		gTriedKeychain = true;	}				//	//Display the server name in the dialog title text	//which is located at the top of the dialog. This must be	//done even if we've been here before.	//		ParamText(gServerName, NULL, NULL, NULL);		//	//If we haven't been through here before, then we need to do	//all the prep work.	//			if (!gContextInited)	{		gDialog = UAM_NewDialog(DLOG_Login, true);		if (gDialog == NULL)		{			//			//If we couldn't get the dialog, then we're either out			//of memory or the resource couldn't be found.			//						theError = MemError();			if (theError == noErr)				theError = ResError();			if (theError == noErr)				theError = resNotFound;						UAM_ReportError(theError);			return(userCanceledErr);		}				//		//Setup our custom user items that display things like the UAM		//version number and the connection method.		//			UAM_SetupDialogUserItem(gDialog, DITEM_Line, gLineItem, userItem);		UAM_SetupDialogUserItem(gDialog, DITEM_Version, gVersionItem, userItem);		UAM_SetupDialogUserItem(gDialog, DITEM_Method, gVersionItem, userItem);				//		//Set up the default user name and password (if any). If a user name		//exists, then make the password field the active field ready for input.		//								//		//If we've not been here before, then we want to use the user name		//entered in the Sharing Setup Control Panel (or Chooser).		//				if (PSTR_LENGTH(gUserName) != 0)		{			UAM_SetText(gDialog, DITEM_UserName, gUserName);			SelectDialogItemText(gDialog, DITEM_Password, 0, 64);		}		else		{			UAM_HiliteItem(gDialog, 1, 255);		}				//		//Now we set up the guest and registered user radio buttons and the		//change password button as determined by UAM_GetServerInfo().		//				if (!gSupportsChngPwd) {			UAM_HiliteItem(gDialog, DITEM_ChangePwd, 255);		}		else {			UAM_GateControl(gDialog, DITEM_ChangePwd, DITEM_UserName);		}				if (!(gSupportedUAMs & kGuestSupported))		{			//			//No guest support, we don't need the guest radio button.			//			UAM_HiliteItem(gDialog, DITEM_GuestRadio, 255);						//			//If guest is not supported, then we gate the connect			//button to the username text field.			//			UAM_GateControl(gDialog, DITEM_Connect, DITEM_UserName);		}				//		//Set the initial radio for the default/current login method.		//				if (gGuestLogon)		{			UAM_SetCValue(gDialog, DITEM_GuestRadio, 1);			UAM_SetCValue(gDialog, DITEM_RegRadio, 	 0);						UAM_HiliteItem(gDialog, DITEM_ChangePwd, 255);						for (x = DITEM_FirstHideItem; x <= DITEM_LastHideItem; x++) {				HideDialogItem(gDialog, x);			}						UAM_HiliteItem(gDialog, 1, 0);		}		else {			UAM_SetCValue(gDialog, DITEM_RegRadio, 1);		}						UAM_SetBulletItem(				gDialog,				DITEM_Password,				(gSupportedUAMs & (kMSUAM_V2_Supported | kMSUAM_V3_Supported)) ?					UAM_MAX_LMv2_PASSWORD : UAM_CLRTXTPWDLEN				);				UAM_SupportCmdKeys(gDialog, false);						//		//Set our custom filter function so we can handle command keys and		//manage user name maximum string length.		//		UAM_SetCustomFilterProc(gDialog, gPwdDialogFilter);				//		//If the client is not allowed to save password for this server,		//then we gray out the keychain checkbox.		//		if (UAM_KCAvailable() == false)		{			UAM_HiliteItem(gDialog, DITEM_Keychain, 255);		}		else if (gTriedKeychain)		{			UAM_SetBulletText(gDialog, DITEM_Password, inUAMArgs->Opt.pwDlg.password);			SelectDialogItemText(gDialog, DITEM_Password, 0, 64);		}				//		//Set the encryption type checkbox to the proper value.		//		if (gUAMPreferences.flags & UAM_PREFS_REQUIRE_STRONG_ENCRYPTION)		{			UAM_SetCValue(gDialog, DITEM_StrongEncryption, 1);		}				//		//This flag lets up know that we've initialized our login dialog		//and that we don't need to do it again when/if we come here again.		//				gContextInited	= true;	}	else {		UAM_SetText(gDialog, DITEM_UserName, inUAMArgs->Opt.pwDlg.userName);		UAM_SetBulletText(gDialog, DITEM_Password, inUAMArgs->Opt.pwDlg.password);				//		//Hilite the password selection.		//		SelectDialogItemText(gDialog, DITEM_Password, 0, 64);				InvalRect(&gDialog->portRect);	}		do	{		ModalDialog(gDialogFilter, &theItem);				//		//Check gated controls, disable them if their text item		//counterpart has no text.		//					UAM_CheckGatedControls(gDialog);		switch(theItem)		{			case DITEM_OK:								gGuestLogon 	= (UAM_GetCValue(gDialog, DITEM_GuestRadio) != 0);				theError		= noErr;				theLoop 		= false;								if (gGuestLogon)				{					inUAMArgs->Opt.pwDlg.userName[0] = 0;					inUAMArgs->Opt.pwDlg.password[0] = 0;				}				else				{										UAM_GetBulletBuffer(	gDialog,											DITEM_Password,											inUAMArgs->Opt.pwDlg.password	);										UAM_GetText(			gDialog,											DITEM_UserName,											(Str255 *)inUAMArgs->Opt.pwDlg.userName	);                    //                    //Don't allow blank passwords for 2 reasons:                    //                    //	1. It is not secure and user can use Apple UAM for this.                    //	2. This covers a security hole that is generated after changing                     //	   passwords on these servers using Apple's clear text UAM.                    //                    if (PSTR_LENGTH(inUAMArgs->Opt.pwDlg.password) == 0)                    {                        UAM_StandardAlert(                                uamErr_PasswordMessage,                                uamErr_NoBlankPasswordsAllowed,                                NULL                                );                                                        //                        //Continue the login dialog loop so the user can make changes.                        //                        theLoop = true;                    }				}								//				//Only save the preferences if the user hits "Connect".				//				UAM_SaveUAMPreferenceData(&gUAMPreferences);				break;							case DITEM_Cancel:				//				//VERSION 5.0: To force cancellation, we pass userCanceledError(-128)				//back to the Chooser. The old UAM would pass back dsForcedQuit which				//is the wrong value. This would cause an error dialog when cancelling.				//								theError	= userCanceledError;				theLoop 	= false;				break;						case DITEM_GuestRadio:				//				//Set up the controls in the dialog for guest login. We don't				//need the user name and password items, so hide them from				//the user. We must explicitly enable the 'OK' button since				//it may have been disabled by the gate stuff.				//								if (UAM_IsActive(gDialog, DITEM_GuestRadio))				{					UAM_SetCValue(gDialog, DITEM_GuestRadio, 1);					UAM_SetCValue(gDialog, DITEM_RegRadio, 	 0);										//UAM_HiliteItem(gDialog, DITEM_ChangePwd, 255);										for (x = DITEM_FirstHideItem; x <= DITEM_LastHideItem; x++) {						HideDialogItem(gDialog, x);					}										//					//Now hide the keychain checkbox					//					UAM_SetCValue(gDialog, DITEM_Keychain, 0);					HideDialogItem(gDialog, DITEM_Keychain);										HideDialogItem(gDialog, DITEM_StrongEncryption);										UAM_StopGate(gDialog, DITEM_Connect);				}				break;						case DITEM_RegRadio:				//				//Now we need all the items back that were hidden above, make				//them visible.				//				if (UAM_GetCValue(gDialog, DITEM_RegRadio) <= 0)				{					UAM_SetCValue(gDialog, DITEM_GuestRadio, 0);					UAM_SetCValue(gDialog, DITEM_RegRadio, 	 1);										for (x = DITEM_FirstHideItem; x <= DITEM_LastHideItem; x++) {						ShowDialogItem(gDialog, x);					}										//					//Make the keychain and encryption items reaappear.					//					ShowDialogItem(gDialog, DITEM_Keychain);					ShowDialogItem(gDialog, DITEM_StrongEncryption);													UAM_GetText(gDialog, DITEM_UserName, &theStr);					SelectDialogItemText(gDialog, DITEM_UserName, 0, 32767);										if ((gSupportsChngPwd) && (theStr[0] != 0)) {						UAM_HiliteItem(gDialog, DITEM_ChangePwd, 0);					}										//					//Check to see if guest is supported or not so we know if					//we need to gate the connect button.					//					if (!(gSupportedUAMs & kGuestSupported))					{						UAM_GateControl(gDialog, DITEM_Connect, DITEM_UserName);						UAM_CheckGatedControls(gDialog);					}				}				break;							case DITEM_ChangePwd:				UAM_GetBulletBuffer(	gDialog,										DITEM_Password,										inUAMArgs->Opt.pwDlg.password	);				UAM_GetText(			gDialog,										DITEM_UserName,										(Str255 *)inUAMArgs->Opt.pwDlg.userName	);								theError = UAM_ChangePwd(inUAMArgs);				switch(theError)				{					case CHNGPSWD_USER_CANCELED:						break;										case CHNGPSWD_UPDATE_KEYCHAIN:						//						//We need to re-add the keychain item with the						//correct password. Flag it by checking the box.						//						UAM_SetCValue(gDialog, DITEM_Keychain, 1);												//						//Just fall on through and handle the normal case.						//											case CHNGPSWD_NOERR:						//						//Set the password field and buffer with the new password in case						//we end back here later.						//												UAM_SetBulletText(gDialog, DITEM_Password, inUAMArgs->Opt.pwDlg.password);												theError = noErr;						theLoop  = false;						break;											default:						UAM_ReportError(theError);												//						//Make sure in debug that the password field is cleared in						//an error condition.						//						Assert_(PSTR_LENGTH(inUAMArgs->Opt.pwDlg.password) == 0);												//						//We do this here so we clear the password field like we should						//do whenever there is a failure.						//						UAM_SetBulletText(gDialog, DITEM_Password, "\p");												//						//Because we use ParamText() we must manually force an update						//of the dialog or things won't redraw properly.						//						InvalRect(&gDialog->portRect);						break;				}							//				//Must reset our user's name since UAM_ChangePwd() uses ParamText()				//to set some strings of it's own.				//								ParamText(gServerName, NULL, NULL, NULL);				break;										case DITEM_Keychain:				UAM_ToggleControl(gDialog, DITEM_Keychain);				break;							case DITEM_StrongEncryption:				//				//Update the required encryption dynamically.				//				UAM_ToggleControl(gDialog, DITEM_StrongEncryption);								if (UAM_GetCValue(gDialog, DITEM_StrongEncryption) > 0)				{					gUAMPreferences.flags |= UAM_PREFS_REQUIRE_STRONG_ENCRYPTION;				}				else				{					gUAMPreferences.flags &= ~UAM_PREFS_REQUIRE_STRONG_ENCRYPTION;										UAM_StandardAlert(						uamErr_WARNINGMessage,						uamErr_UsingWeakAuthentication,						NULL						);				}				break;						default:				break;		}			}while(theLoop);exit:	return(theError);}