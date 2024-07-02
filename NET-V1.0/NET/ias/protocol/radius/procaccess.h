//#--------------------------------------------------------------
//        
//  File:       procaccess.h
//        
//  Synopsis:   This file holds the declarations of the 
//				CProcAccess class
//              
//
//  History:     10/20/97  MKarki Created
//
//    Copyright (C) 1997-98 Microsoft Corporation
//    All rights reserved.
//
//----------------------------------------------------------------
#ifndef _PROCACCESS_H_ 
#define _PROCACCESS_H_

#include "packetradius.h"
#include "hashmd5.h"
#include "sendtopipe.h"

class CPreValidator;

class CProcAccess  
{

public:

    //
    //  initialize the CProcAccess class object
    //
    BOOL Init (
            /*[in]*/ CPreValidator  *pCPreValidator,
            /*[in]*/ CHashMD5       *pCHashMD5,
            /*[in]*/ CSendToPipe       *pCSendToPipe
            );
    //
    //  process out bound RADUS packet
    //
	HRESULT ProcessOutPacket (
                /*[in]*/    CPacketRadius *pCPacketRadius
                );

    //
    //  process in bound RADUS packet
    //
	HRESULT ProcessInPacket (
                /*[in]*/    CPacketRadius *pCPacketRadius
                );

    //
    //  constructor
    //
	CProcAccess();

    //
    //  destructor
    //
	virtual ~CProcAccess();

private:

    CPreValidator   *m_pCPreValidator;

    CHashMD5        *m_pCHashMD5;

    CSendToPipe     *m_pCSendToPipe;

};

#endif // ifndef _PROCACCESS_H_
