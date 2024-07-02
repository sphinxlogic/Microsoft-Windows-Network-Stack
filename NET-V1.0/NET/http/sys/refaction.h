/*++

Copyright (c) 1998-2002 Microsoft Corporation

Module Name:

    refaction.h

Abstract:

    Action codes for reftracing http.sys. The !httpkd.ref debugger extension
    uses this file with a different definition of REF_ACTION() to
    print out symbolic information.

--*/

//
// Action codes.
//

#ifndef BEGIN_REF_ACTION
# define BEGIN_REF_ACTION()     typedef enum _REFTRACE_ACTION {
# define END_REF_ACTION()       } REFTRACE_ACTION, *PREFTRACE_ACTION;
# define REF_ACTION(x)          REF_ACTION_##x ,
#endif // !BEGIN_REF_ACTION

BEGIN_REF_ACTION()
    REF_ACTION( NO_OP )  // == 0
    
    REF_ACTION( REFERENCE_ENDPOINT )
    REF_ACTION( DEREFERENCE_ENDPOINT )

    REF_ACTION( REFERENCE_ENDPOINT_USAGE )
    REF_ACTION( DEREFERENCE_ENDPOINT_USAGE )

    REF_ACTION( REFERENCE_UL_CONNECTION )
    REF_ACTION( DEREFERENCE_UL_CONNECTION )
    REF_ACTION( ALLOC_UL_CONNECTION )
    REF_ACTION( FREE_UL_CONNECTION )
    REF_ACTION( ENQUEUE_UL_CONNECTION )
    REF_ACTION( DEQUEUE_UL_CONNECTION )

    REF_ACTION( SEND_AND_DISCONNECT )
    REF_ACTION( CLOSE_UL_CONN_GRACEFUL )
    REF_ACTION( CLOSE_UL_CONN_ABORTIVE )
    REF_ACTION( CLOSE_UL_CONN_RAW_CLOSE )
    REF_ACTION( CLOSE_UL_CONN_FORCE_ABORT )
    REF_ACTION( CLOSE_UL_CONN_ABORT_DISCONNECT )
    REF_ACTION( DRAIN_UL_CONN_START )
    REF_ACTION( DRAIN_UL_CONN_RESTART )
    REF_ACTION( DRAIN_UL_CONN_DISCONNECT_COMPLETE )
    REF_ACTION( ABORT_INDICATED )
    REF_ACTION( DISCONNECT_INDICATED )
    REF_ACTION( DISCONNECT_HANDLER )

    REF_ACTION( INIT )
    REF_ACTION( REPLENISH )
    REF_ACTION( CONNECT )
    REF_ACTION( RESTART_ACCEPT )
    REF_ACTION( DISCONN_ACTIVE )
    REF_ACTION( UNBIND_CONN )
    REF_ACTION( DISCONN_ALL )
    REF_ACTION( FINAL_DEREF )
    REF_ACTION( CONN_CLEANUP )
    REF_ACTION( CLEAN_BACKING_LIST )

    REF_ACTION( ADD_URI_ENTRY )
    REF_ACTION( CHECKIN_URI_ENTRY )
    REF_ACTION( CHECKOUT_URI_ENTRY )
    REF_ACTION( FLUSH_URI_ENTRY )
    REF_ACTION( FILTER_URI_ENTRY )
    REF_ACTION( CREATE_URI_ENTRY )
    REF_ACTION( ZOMBIFY_URI_ENTRY )
    REF_ACTION( UNZOMBIFY_URI_ENTRY )
    REF_ACTION( CLEAR_URI_ENTRY )

    REF_ACTION( ALLOCATE_MDL )
    REF_ACTION( FREE_MDL )
    REF_ACTION( SEND_MDL )
    REF_ACTION( SEND_MDL_COMPLETE )

    REF_ACTION( ACQUIRE_RESOURCE_EXCLUSIVE )
    REF_ACTION( ACQUIRE_RESOURCE_SHARED )
    REF_ACTION( RELEASE_RESOURCE )
    REF_ACTION( CONVERT_RESOURCE_EXCLUSIVE_TO_SHARED )
    REF_ACTION( TRY_ACQUIRE_RESOURCE_EXCLUSIVE )

    REF_ACTION( ACQUIRE_PUSH_LOCK_EXCLUSIVE )
    REF_ACTION( ACQUIRE_PUSH_LOCK_SHARED )
    REF_ACTION( RELEASE_PUSH_LOCK )

    REF_ACTION( REFERENCE_HTTP_CONNECTION )
    REF_ACTION( DEREFERENCE_HTTP_CONNECTION )
    REF_ACTION( DESTROY_HTTP_CONNECTION )
    REF_ACTION( EXPIRE_HTTP_CONNECTION )

    REF_ACTION( REFERENCE_HTTP_REQUEST )
    REF_ACTION( DEREFERENCE_HTTP_REQUEST )

    REF_ACTION( INSERT_BUFFER )
    REF_ACTION( INSERT_REQUEST )

    REF_ACTION( REFERENCE_BUFFER )
    REF_ACTION( DEREFERENCE_BUFFER )

    REF_ACTION( REFERENCE_APP_POOL )
    REF_ACTION( DEREFERENCE_APP_POOL )

    REF_ACTION( REFERENCE_APP_POOL_PROCESS )
    REF_ACTION( DEREFERENCE_APP_POOL_PROCESS )        

    REF_ACTION( REFERENCE_CONFIG_GROUP )
    REF_ACTION( DEREFERENCE_CONFIG_GROUP )

    REF_ACTION( REFERENCE_CONTROL_CHANNEL )
    REF_ACTION( DEREFERENCE_CONTROL_CHANNEL )
    REF_ACTION( CREATE_CONTROL_CHANNEL )
    REF_ACTION( CLEANUP_CONTROL_CHANNEL )
    REF_ACTION( CLOSE_CONTROL_CHANNEL )

    REF_ACTION( REFERENCE_HTTP_RESPONSE )
    REF_ACTION( DEREFERENCE_HTTP_RESPONSE )

    REF_ACTION( REFERENCE_FILTER )
    REF_ACTION( DEREFERENCE_FILTER )

    REF_ACTION( REFERENCE_SITE_COUNTER_ENTRY )
    REF_ACTION( DEREFERENCE_SITE_COUNTER_ENTRY )

    REF_ACTION( REFERENCE_CONFIG_GROUP_INFO )
    REF_ACTION( DEREFERENCE_CONFIG_GROUP_INFO )

    REF_ACTION( REFERENCE_CONNECTION_COUNT_ENTRY )
    REF_ACTION( DEREFERENCE_CONNECTION_COUNT_ENTRY )

    REF_ACTION( REFERENCE_CHUNK_TRACKER )
    REF_ACTION( DEREFERENCE_CHUNK_TRACKER )

    REF_ACTION( REFERENCE_THREAD )
    REF_ACTION( DEREFERENCE_THREAD )

    REF_ACTION( TC_ALLOC )    
    REF_ACTION( TC_UP )  
    REF_ACTION( TC_DOWN )  
    REF_ACTION( TC_CHANGE ) 
    REF_ACTION( TC_GFLOW_ADD ) 
    REF_ACTION( TC_GFLOW_REMOVE ) 
    REF_ACTION( TC_GFLOW_MODIFY ) 
    REF_ACTION( TC_FLOW_ADD ) 
    REF_ACTION( TC_FLOW_REMOVE ) 
    REF_ACTION( TC_FLOW_MODIFY )     
    REF_ACTION( TC_CLOSE )

    REF_ACTION( QUEUE_WORK_ITEM )
    REF_ACTION( QUEUE_SYNC_ITEM )
    REF_ACTION( QUEUE_WAIT_ITEM )
    REF_ACTION( QUEUE_HIGH_PRIORITY_ITEM )
    REF_ACTION( CALL_PASSIVE )
    REF_ACTION( FLUSH_WORK_ITEM )
    REF_ACTION( PROCESS_WORK_ITEM )
    REF_ACTION( PUSH_BACK_WORK_ITEM )
    
    REF_ACTION( POOL_ALLOC )
    REF_ACTION( POOL_ALLOC_FAIL_NO_MEM )
    REF_ACTION( POOL_ALLOC_FAIL_NO_QUOTA )
    REF_ACTION( POOL_FREE )

    REF_ACTION( ENDPOINT_USAGE_REFERENCE )
    REF_ACTION( ENDPOINT_USAGE_DEREFERENCE )

    REF_ACTION( ENDPOINT_EVENT_REFERENCE )
    REF_ACTION( ENDPOINT_EVENT_DEREFERENCE )


    REF_ACTION( REFERENCE_UC_REQUEST )
    REF_ACTION( DEREFERENCE_UC_REQUEST )

    REF_ACTION( MAX )   // *must* be last
END_REF_ACTION()
