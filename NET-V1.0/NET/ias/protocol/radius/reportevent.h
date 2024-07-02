//#--------------------------------------------------------------
//        
//  File:       reportevent.h
//        
//  Synopsis:   This file holds the declarations of the 
//				CReportEvent class
//                  
//
//  History:     1/29/98  MKarki Created
//
//    Copyright (C) 1997-98 Microsoft Corporation
//    All rights reserved.
//
//#--------------------------------------------------------------
#ifndef _REPORTEVENT_H_
#define _REPORTEVENT_H_


//
//  here the audit log types generated by the RADIUS
//  protocol component
//
typedef enum _radiuslogtype_
{
    RADIUS_DROPPED_PACKET = 0,
    RADIUS_MALFORMED_PACKET = RADIUS_DROPPED_PACKET +1,
    RADIUS_INVALID_CLIENT = RADIUS_MALFORMED_PACKET +1,
    RADIUS_LOG_PACKET = RADIUS_INVALID_CLIENT +1,
    RADIUS_BAD_AUTHENTICATOR = RADIUS_LOG_PACKET +1,
    RADIUS_UNKNOWN_TYPE = RADIUS_BAD_AUTHENTICATOR +1,
    RADIUS_NO_RECORD = RADIUS_UNKNOWN_TYPE +1

}   RADIUSLOGTYPE, *PRADIUSLOGTYPE;

//
// this the maximum value the the log types have 
//
#define MAX_RADIUSLOGTYPE  RADIUS_NO_RECORD

class CReportEvent
{

public:

    VOID SetLogType  (
            /*[in]*/    DWORD   dwLogType,
            /*[in]*/    BOOL    bLogValue
            );

    VOID Process (
            /*[in]*/    RADIUSLOGTYPE   radLogType,
            /*[in]*/    PACKETTYPE      radPacketType,
            /*[in]*/    DWORD           dwDataSize,
            /*[in]*/    DWORD           dwIPAddress,
            /*[in]*/    LPCWSTR         szString,
            /*[in]*/    LPVOID          pRawData
            );
        
    CReportEvent ();
    
    ~CReportEvent ();

private:
    
    BOOL        m_bLogMalformed;
    BOOL        m_bLogAcct;
    BOOL        m_bLogAuth;
    BOOL        m_bLogAll;

};

#endif //   _REPORTEVENT_H_
