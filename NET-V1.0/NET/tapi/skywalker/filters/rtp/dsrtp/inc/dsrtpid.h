/**********************************************************************
 *
 *  Copyright (C) Microsoft Corporation, 1999
 *
 *  File name:
 *
 *    dsrtpid.h
 *
 *  Abstract:
 *
 *    CLSIDs, IIDs and GUIDs
 *
 *  Author:
 *
 *    Andres Vega-Garcia (andresvg)
 *
 *  Revision:
 *
 *    1999/05/17 created
 *
 **********************************************************************/

#ifndef _dsrtpid_h_
#define _dsrtpid_h_

#include <olectl.h>

/**********************************************************************
 * Media types GUIDs
 **********************************************************************/

#if 0 // remove later

/* {14099BC0-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIATYPE_RTP_Single_Stream, 
0x14099bc0, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BC1-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIATYPE_RTP_Multiple_Stream, 
0x14099bc1, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BC2-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_Mixed, 
0x14099bc2, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);



/* {14099BC3-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_G711U, 
0x14099bc3, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BC4-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_G711A, 
0x14099bc4, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BC5-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_G723, 
0x14099bc5, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BC6-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_H261, 
0x14099bc6, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BC7-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_H263, 
0x14099bc7, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {14099BCA-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_RTP_Payload_ANY, 
0x14099bc8, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

/* {33363248-0000-0010-8000-00AA00389B71} */
DEFINE_GUID(MEDIASUBTYPE_H263, 
0x33363248, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

/* {14099BC8-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_H263EX, 
0x14099bc8, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

#if 0
/* {31363248-0000-0010-8000-00AA00389B71} */
DEFINE_GUID(MEDIASUBTYPE_H261, 
0x31363248, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
#endif
/* {14099BC9-787B-11d0-9CD3-00A0C9081C19} */
DEFINE_GUID(MEDIASUBTYPE_H261EX, 
0x14099bc9, 0x787b, 0x11d0, 0x9c, 0xd3, 0x0, 0xa0, 0xc9, 0x8, 0x1c, 0x19);

#endif

#endif /* _dsrtpid_h_ */
