// ===========================================================================//	UAMPrefs.h 			� 1998-2002 Microsoft Corp. All rights reserved.// ===========================================================================#pragma once////The name of the preferences file.//#define UAM_PREFERENCE_FILE_NAME	"\pMSUAM Preferences"////These flags are currently defined for preferences.//enum{	UAM_PREFS_REQUIRE_STRONG_ENCRYPTION	= 0x02};////This is the data structure of the UAM preferences file.//typedef struct{	SInt32	flags;	SInt32	reserved1;	SInt32	reserved2;}UAM_PREFERENCES, *PUAM_PREFERENCES;SInt16 UAM_OpenOrCreateFile(		FSSpec*		inSpec,		OSType		inCreator,		OSType		inFileType);SInt16 UAM_OpenPreferenceFile();OSErr UAM_RetrieveUAMPreferenceData(		PUAM_PREFERENCES	ioUAMPrefs);OSErr UAM_SaveUAMPreferenceData(		PUAM_PREFERENCES	inUAMPrefs);