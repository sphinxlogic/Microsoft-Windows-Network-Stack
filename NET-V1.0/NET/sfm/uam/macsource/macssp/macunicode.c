/* *  macunicode.cpp *  MSUAM * *  Created by mconrad on Fri Nov 16 2001. *  Copyright (c) 2001 Microsoft Corp. All rights reserved. * */#include "macunicode.h"// ---------------------------------------------------------------------------//		� MacSspCStringToUnicode()// ---------------------------------------------------------------------------// Convert a c-string (null terminated mbcs) into a unicode string.//OSStatusMacSspCStringToUnicode(	IN	PCSTR				cString,	OUT	UInt16*				unicodeLen,	OUT	UniCharArrayPtr*	unicodeString	){	UnicodeMapping		unicodeMapping;	TextToUnicodeInfo	textInfo;	OSStatus			Status					= noErr;	ByteCount			unicodeBufferSize		= CALC_UNICODE_CSTRING_LENGTH(cString);	ByteCount			unicodeActualLen		= 0;	UniCharArrayPtr		unicodeResult			= NULL;    ByteCount			actualCharsConverted	= 0;    OptionBits			controlFlags			= 0;		//	//Just in case the caller didn't initialize the return	//parameters, we'll do it for them for safety.	//	*unicodeString 	= NULL;	*unicodeLen		= 0;		//	//Create the test encoding that we'll use to convert Mac	//characters to unicode chars.	//	unicodeMapping.unicodeEncoding 	= CreateTextEncoding(											kTextEncodingUnicodeV2_0,											kUnicodeNoSubset,											kUnicode16BitFormat											);        //    //Call our homegrown routine that will set the proper encoding    //for the current script system.    //    Status = MacSspGetCurrentTextEncoding(&unicodeMapping.otherEncoding);        if (NT_SUCCESS(Status))    {        unicodeMapping.mappingVersion	= kUnicodeUseLatestMapping;                Status = CreateTextToUnicodeInfo(&unicodeMapping, &textInfo);                        if (NT_SUCCESS(Status))        {        	//        	//Allocate memory for the unicode string. Note that the buffer        	//should be big enough to hold the new unicode string.        	//            unicodeResult = (UniCharArrayPtr)NewPtrClear(unicodeBufferSize);                        if (unicodeResult != nil)            {	            //	            //Set the control flags for this conversion.	            //	            //controlFlags = kUnicodeForceASCIIRangeMask;	            	            Status = ConvertFromTextToUnicode(	                            textInfo,	                            strlen(cString),	                            cString,	                            controlFlags,	                            0,	                            NULL,	                            NULL,	                            NULL,	                            unicodeBufferSize,	                            &actualCharsConverted,	                            &unicodeActualLen,	                            unicodeResult	                            );	                            	            SspDebugPrint((DBUF, "ConvertFromTextToUnicode() returned = %d", Status));	            	            if (NT_SUCCESS(Status))	            {	                SspDebugPrintHex(unicodeResult, unicodeActualLen);	                	                *unicodeString 	= unicodeResult;	                *unicodeLen		= unicodeActualLen;	            }	        }	        else	        {	        	Status = memFullErr;	        }                        //            //Dispose of the opaque info structure used for the conversion.            //            DisposeTextToUnicodeInfo(&textInfo);        }	}    	return(Status);}// ---------------------------------------------------------------------------//		� MacSspUnicodeToWindowsCString()// ---------------------------------------------------------------------------// Converts a unicode string to a single byte CString using the Windows ASCII// mapping table.//OSStatusMacSspUnicodeToWindowsCString(	IN	UniCharArrayPtr		unicodeString,	IN	UInt32				unicodeLen,	IN	UInt32				cStringBufferLen,	OUT	PCHAR				cString	){	OSStatus			Status	= noErr;	UnicodeMapping		unicodeMapping;	UnicodeToTextInfo	textInfo;	ByteCount			inputRead 	= 0;	ByteCount			outputLen 	= 0;	OptionBits			options		= 0;		unicodeMapping.unicodeEncoding 	= CreateTextEncoding(                                            kTextEncodingUnicodeV2_0,                                            kUnicodeNoSubset,                                            kUnicode16BitFormat                                            );        unicodeMapping.otherEncoding	= CreateTextEncoding(											kTextEncodingWindowsLatin1,											kTextEncodingDefaultVariant,											kTextEncodingDefaultFormat											);                                            	unicodeMapping.mappingVersion	= kUnicodeUseLatestMapping;		Status = CreateUnicodeToTextInfo(				&unicodeMapping,				&textInfo				);					if (NT_SUCCESS(Status))	{		//		//Set the options bits. If we don't set the fallback bit, then		//conversion from unicode to Windows will fail if extended		//characters are in the string.		//		options	= kUnicodeUseFallbacksMask;				Status = ConvertFromUnicodeToText(						textInfo,						unicodeLen,						unicodeString,						options,						0,						NULL,						NULL,						NULL,						cStringBufferLen,						&inputRead,						&outputLen,						cString						);                                SspDebugPrint((DBUF, "ConvertFromUnicodeToText() returned: %d", Status));								DisposeUnicodeToTextInfo(&textInfo);	}		return(Status);}// ---------------------------------------------------------------------------//		� MacSspPStringToUnicode()// ---------------------------------------------------------------------------// Convert a PString into a unicode string.//OSStatusMacSspPStringToUnicode(	IN	Str255				PString,	OUT	UInt16*				unicodeLen,	OUT	UniCharArrayPtr*	unicodeString	){	UnicodeMapping		unicodeMapping;	TextToUnicodeInfo	textInfo;	OSStatus			Status				= noErr;	ByteCount			unicodeBufferSize	= CALC_UNICODE_PSTRING_LENGTH(PString);	ByteCount			unicodeActualLen	= 0;	UniCharArrayPtr		unicodeResult		= NULL;		unicodeMapping.unicodeEncoding 	= CreateTextEncoding(											kTextEncodingUnicodeV2_0,											kUnicodeNoSubset,											kUnicode16BitFormat											);    //    //Call our homegrown routine that will set the proper encoding    //for the current script system.    //    Status = MacSspGetCurrentTextEncoding(&unicodeMapping.otherEncoding);        if (NT_SUCCESS(Status))    {        unicodeMapping.mappingVersion	= kUnicodeUseLatestMapping;                Status = CreateTextToUnicodeInfo(&unicodeMapping, &textInfo);                        if (NT_SUCCESS(Status))        {            unicodeResult = (UniCharArrayPtr)NewPtrClear(unicodeBufferSize);                        if (unicodeResult != nil)            {	            Status = ConvertFromPStringToUnicode(	                            textInfo,	                            PString,	                            unicodeBufferSize,	                            &unicodeActualLen,	                            unicodeResult	                            );	            	            SspDebugPrint((DBUF, "ConvertFromPStringToUnicode() returned = %d", Status));	            	            if (NT_SUCCESS(Status))	            {	                SspDebugPrintHex(unicodeResult, unicodeActualLen);	                	                *unicodeString 	= unicodeResult;	                *unicodeLen		= unicodeActualLen;	            }	        }	        else	        {	        	Status = memFullErr;	        }                        //            //Dispose of the opaque info structure used for the conversion.            //            DisposeTextToUnicodeInfo(&textInfo);        }	}    	return(Status);}// ---------------------------------------------------------------------------//		� MacSspGetCurrentTextEncoding()// ---------------------------------------------------------------------------// Returns a text encoding of the current system script.//OSStatusMacSspGetCurrentTextEncoding(    OUT	TextEncoding* currentEncoding    ){    OSStatus	Status = noErr;    LangCode	currentLang;        //    //Unfortuanately, we cannot test for failure here since a value of    //0 actual means its a US system. I guess it should never fail??    //    currentLang = (LangCode)GetScriptVariable(smCurrentScript, smScriptLang);        //    //Call the API that converts Scrip Manager information into an encoding    //we can use in the conversion routines.    //    Status = UpgradeScriptInfoToTextEncoding(                    smCurrentScript,                    currentLang,                    kTextRegionDontCare,                    NULL,                    currentEncoding                    );        return(Status);}