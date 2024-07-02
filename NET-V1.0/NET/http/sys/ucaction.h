/*++

Copyright (c) 1998-2002 Microsoft Corporation

Module Name:

    ucaction.h

Abstract:

    Action codes for reftracing http.sys. The !httpkd.uc debugger extension
    uses this file with a different definition of UC_ACTION() to
    print out symbolic information.

Author:

    Rajesh Sundaram (rajeshsu) - 17th July 2001.

--*/
//
// Action codes.
//

#ifndef BEGIN_UC_ACTION
# define BEGIN_UC_ACTION()     enum UC_ACTION {
# define END_UC_ACTION()       };
# define UC_ACTION(x)          UC_ACTION_##x ,
#endif // !BEGIN_UC_ACTION

BEGIN_UC_ACTION()
    UC_ACTION( NO_OP )  // == 0
    

    UC_ACTION( NEW_RESPONSE )

    UC_ACTION( REQUEST_NEW )
    UC_ACTION( REQUEST_COMPLETE_IRP )
    UC_ACTION( REQUEST_COMPLETE_EARLY )
    UC_ACTION( REQUEST_CANCELLED )
    UC_ACTION( REQUEST_SEND_COMPLETE )
    UC_ACTION( REQUEST_SET_CANCEL_ROUTINE )
    UC_ACTION( REQUEST_BUFFERED )
    UC_ACTION( REQUEST_SENT )
    UC_ACTION( REQUEST_MORE_ENTITY_NEEDED )
    UC_ACTION( REQUEST_QUEUED )
    UC_ACTION( REQUEST_FAILED )
    UC_ACTION( REQUEST_PARSE_DONE )
    UC_ACTION( REQUEST_CLEAN_PENDED)
    UC_ACTION( REQUEST_CLEAN_RESUMED)

    UC_ACTION( ENTITY_NEW )
    UC_ACTION( ENTITY_CANCELLED )
    UC_ACTION( ENTITY_LAST )
    UC_ACTION( ENTITY_SENT )
    UC_ACTION( ENTITY_BUFFERED )
    UC_ACTION( ENTITY_READY_TO_SEND )
    UC_ACTION( ENTITY_QUEUED )

    UC_ACTION( RESPONSE_CANCELLED )

    UC_ACTION( CONNECTION_STATE_ENTER )
    UC_ACTION( CONNECTION_STATE_LEAVE )

    UC_ACTION( CONNECTION_CLOSE )
    UC_ACTION( CONNECTION_RAW_CLOSE )
    UC_ACTION( CONNECTION_RAW_FILTER_CLOSE )
    UC_ACTION( CONNECTION_RAW_FILTER_DISCONNECT )
    UC_ACTION( CONNECTION_BEGIN_DISCONNECT )
    UC_ACTION( CONNECTION_RESTART_DISCONNECT )
    UC_ACTION( CONNECTION_BEGIN_ABORT )
    UC_ACTION( CONNECTION_RESTART_ABORT )
    UC_ACTION( CONNECTION_TDI_DISCONNECT)
    UC_ACTION( CONNECTION_CLEANUP)
    UC_ACTION( CONNECTION_BEGIN_CONNECT)
    UC_ACTION( CONNECTION_RESTART_CONNECT)
    UC_ACTION( CONNECTION_CLEAN_PENDED)
    UC_ACTION( CONNECTION_CLEAN_RESUMED)
    UC_ACTION( CONNECTION_CLEANED)
    UC_ACTION( SERVINFO_FREE)

    UC_ACTION( MAX )   // *must* be last
END_UC_ACTION();
