// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file enum.h
 * @brief Defines common enum's
 * @author BG
 * @ingroup BasicEnums
 */
#ifndef LBA_ENUM_H
#define LBA_ENUM_H

#ifdef FALSE
#undef FALSE
#endif

#ifdef TRUE
#undef TRUE
#endif

/**
 * @enum eBool
 * @brief Enumerate TRUE,FALSE  
 * @ingroup BasicEnums
 */
enum    eBool   {

    FALSE       = 0,    
    TRUE        
};

/**
 * @enum eTriVal
 * @ingroup BasicEnums
 */
enum    eTriVal {
   
    TV_UNKNOWN  =  0,
    TV_FALSE    =  1,
    TV_TRUE     =  2 
};

/**
 * @enum eGoodBad
 * @brief Enumerate GOOD,BAD  
 * @ingroup BasicEnums
 */
enum    eGoodBad    {   

    GOOD        = 0,    
    BAD         
};

enum eRetryCancel {

    RETRY = 0,
    CANCEL
};
/**
 * @enum eStopGo
 * @brief Enumerate STOP,CONTINUE
 * @ingroup BasicEnums
 */
enum    eStopGo     {   

    STOP        = 0,    
    CONTINUE    
};

/**
 * @enum eOpenMode
 * @brief Enumerate F_READONLY ,F_READWRITE
 * @ingroup BasicEnums
 */
enum    eOpenMode   {   

    F_READONLY  = 0,    
    F_READWRITE 
};

/**
 * @enum eCrashMode 
 * @brief Enumerate F_CRASH ,F_NOCRASH
 * @ingroup BasicEnums
 */
enum eCrashMode {

    F_CRASH     = 0,
    F_NOCRASH
};

/**
 * @enum eCase
 * @brief Enumerates Character-cases (upper-case, lowercase etc.)
 * @ingroup BasicEnums
 */
enum    eCase      {   

        SK_UNKNOWN = 0,
        SK_NORMAL,
        SK_UCASE,
        SK_LCASE,
        SK_TITLE,
        SK_TITLE_EXACT,
        SK_PROPER,
        SK_FIRSTUPPER,
        SK_FILE_PATH,
        SK_FOLDER_PATH
};

/**
 * @enum eIdGenerationErrorCodes 
 * @brief Enumerates Error codes encoured while id generation 
 */
enum eIdGenerationErrorCodes
{
    INVALID_PARAMETERS = 0,
    ID_GENERATION_FAILED,
    INTERNAL_PROCESSING_ERROR,
};

/**
 * Defines the Error Status and Error Codes
 */
enum eStatusCodeDefines {

    STATUS_NO_ERROR = 0,
    STATUS_ERROR_FAILURE = 1,    // Generic failure

    STATUS_HTTP_METHOD_NOT_SUPPORTED = 15001,               ///< 15001 Message: Identifer for HTTP GET method not supported
    STATUS_HEADER_INFO_NOT_SUFFICIENT,                      ///< 15002 Message: Identifer for HTTP header does not contain mandatory info
    STATUS_INVALID_CHECKSUM,                                ///< 15003 Message: Tallysign is invalid
    STATUS_UNKNOWN_REQUEST,                                 ///< 15004 Message: Unknown request 
    STATUS_INVALID_XML,                                     ///< 15005 Message: Invalid request xml
    STATUS_NO_REQ_ID,                                       ///< 15006 Message: Request ID does not exists
    STATUS_SERVER_NOT_READY,                                ///< 15007 Message: Server not ready to serve
    STATUS_REQ_ID_MISMATCH,                                 ///< 15008 Message: Request ID in Message and Header not matching
    STATUS_DECRYPT_FAILED,                                  ///< 15009 Message: Decrypt failed
    STATUS_DECOMPRESS_FAILED,                               ///< 15010 Message: Decompress failed
    STATUS_REQ_MESSAGE_EMPTY,                               ///< 15011 Message: (No Message):Request data is empty
    STATUS_RE_REGISTER_IN_PROCESS,                          ///< 15012 Message: (No Message):status defining Re-Registration in process(:TRB:LDS)
    STATUS_CLIENT_CONNECTION_INACTIVE,                      ///< 15013 Message: (No Message):Connected client is inactive before processing its request(:LDS:TRB)
    STATUS_GATHERING_CONVERSATION_DATA_IN_PROCESS,          ///< 15014 Message: (No Message):status defining Gathering Conversation Data is under process
    STATUS_ERROR_SERIALIZATION_FAILED,                      ///< 15015 Message: (No Message)
    STATUS_ERROR_COMMUNICATION_WITH_PB_FAILED,              ///< 15016 Message: "Request cannot be served, please try later" Actual Reason : /Communication with Product Backend Failed
    STATUS_ERROR_CACHE_AUTH_INFO_EXPIRED,                   ///< 15017 Message: (No Message)
    STATUS_ERROR_PB_RESP_PARSING_FAILED,                    ///< 15018 Message: "Request cannot be served, please try later" Actual Reason : /Response received from Product Backend schema validation failed

    // Defines the Tally product Status and Error Codes

    STATUS_NO_TRB_REGISTERED = 16001,                       ///< 16001 Message: Request cannot be serverd [No TRB's registered]
    STATUS_NO_SERIAL_NUMBER,                                ///< 16002 Message: Serial Number does not exists
    STATUS_INCOMPLETE_AUTH_DATA,                            ///< 16003 Message: Tally Authentication data is incomplete
    STATUS_INVALID_NONCE,                                   ///< 16004 Message: Invalid nonce
    STATUS_INVALID_HANDSHAKE_DETAILS,                       ///< 16005 Message: Handshake details are not matching
    STATUS_NO_SERIAL_NO_SITEID_N_SESSIONID,                 ///< 16006 Message: Serial Number, Site ID and Session ID does not exists
    STATUS_NO_SITEID,                                       ///< 16007 Message: Site ID does not exists
    STATUS_NO_ACCOUNT_INTERNAL_ID,                          ///< 16008 Message: Account Internal ID does not exists
    STATUS_NO_SESSIONID,                                    ///< 16009 Message: Session Id does not exists
    STATUS_SERVER_CONN_FAILED,                              ///< 16010 Message: (Connection Failed)Request cannot be served, please try later
    STATUS_RESP_MESSGAGE_FORMAT_INVALID,                    ///< 16011 Message: (Invalid response xml)Request cannot be served, please try later
    STATUS_INVALID_USER,                                    ///< 16012 Message: Authentication failed, invalid user
    STATUS_EMPTY_COMPANYINFO,                               ///< 16013 Message: Company Info does not exist
    STATUS_CONNECT_COMP_SUCCESS,                            ///< 16014 Message: Company connected successfully
    STATUS_CONNECT_COMP_FAIL,                               ///< 16015 Message: Failed to connect company
    STATUS_COMP_ALREADY_CONNECTED,                          ///< 16016 Message: Company already connected
    STATUS_DISCONNECT_COMP_SUCCESS,                         ///< 16017 Message: Company disconnected successfully
    STATUS_DISCONNECT_COMP_FAIL,                            ///< 16018 Message: Failed to disconnect company
    STATUS_COMP_NOT_CONNECTED,                              ///< 16019 Message: Company not connected
    STATUS_UPDATE_COMP_SUCCESS,                             ///< 16020 Message: Company updated successfully
    STATUS_UPDATE_COMP_FAIL,                                ///< 16021 Message: Failed to update company                                                        
    STATUS_DISCONNECT_COMPANIES_SUCCESS,                    ///< 16022 Message: Companies disconnected successfully
    STATUS_DISCONNECT_COMPANIES_FAIL,                       ///< 16023 Message: Failed to disconnect companies
    STATUS_COMPANY_CONNECTED_BY_OTHER,                      ///< 16024 Message: Company is published by some other instance
    STATUS_CONNECTION_DELETE_SUCCESS,                       ///< 16025 Message: Server disconnect success
    STATUS_CONNECTION_DELETION_FAILED,                      ///< 16026 Message: Server disconnect fail 
    STATUS_INVALID_SESSION,                                 ///< 16027 Message: Invalid Session
    STATUS_CLOSE_SESSION_SUCCESS,                           ///< 16028 Message: Session Closed successfully
    STATUS_CLOSE_SESSION_FAIL,                              ///< 16029 Message: Failed to close session
    STATUS_SESSION_EXISTS_FOR_REMOTE_USER,                  ///< 16030 Message: Session exists for remote user
    STATUS_NO_TOKEN_OR_SESSIONID,                           ///< 16031 Message: Token or Session Id does not exists
    STATUS_TALLY_SERVER_NOT_CONNECTED,                      ///< 16032 Message: Tally Server instance is not connected to TNS
    STATUS_START_SESSION_SUCCESS,                           ///< 16033 Message: Session started successfully
    STATUS_START_SESSION_FAIL,                              ///< 16034 Message: Failed to start session
    STATUS_END_SESSION_SUCCESS,                             ///< 16035 Message: Session ended successfully
    STATUS_END_SESSION_FAIL,                                ///< 16036 Message: Failed to end session
    STATUS_TALLY_ACCOUNT_INFO_NOT_EXISTS,                   ///< 16037 Message: Tally to connect to does not exists as Account information not available for the request 
    STATUS_TALLY_HDR_INFO_NOT_SUFFICIENT,                   ///< 16038 Message: Tally to connect to does not exist for the request
    STATUS_TALLY_COMPANY_INFO_NOT_EXISTS,                   ///< 16039 Message: Tally to connect to does not exist as Company information not available for the request
    STATUS_SESSION_EXPIRED,                                 ///< 16040 Message: Session validity expired
    STATUS_SESSION_KILL_SUCCESS,                            ///< 16041 Message: User session killed successfully
    STATUS_SESSION_KILL_FAIL,                               ///< 16042 Message: Failed to kill user session
    STATUS_CURRENT_SESSION_DELETE_FAIL,                     ///< 16043 Message: Current session cannot be deleted
    STATUS_DUPLICATE_CONNECT_NAME_PRESENT,                  ///< 16044 Message: Duplicate connect names present for Connect or Update companies request
    STATUS_USER_ID_EMPTY,                                   ///< 16045 Message: User ID is empty in UpdateSMSSuffix request
    STATUS_INTERNAL_ERROR,                                  ///< 16046 Message: TNS internal error, like memory alloc fail or XML preparation fail...
    STATUS_CONNECTION_PIPE_IS_INACTIVE,                     ///< 16047 Message: The Connection pipe from Tally to TRB has become invalid      
    STATUS_MISSING_HANDSHAKE_INFO,                          ///< 16048 Message: Handshake information does not contain IP and system name of client machine
    STATUS_LICENSE_EXPIRED,                                 ///< 16049 Message: License expired
    STATUS_TNET_SUBS_EXPIRED,                               ///< 16050 Message: Tally Net subscription expired
    STATUS_NO_TNET_SUBS,                                    ///< 16051 Message: Tally Net subscription addon does not exists in addon list
    STATUS_UPDATE_LICENSE_SUCCESS,                          ///< 16052 Message: License updated successfully
    STATUS_DELETE_USER_SUCCESS,                             ///< 16053 Message: User deleted successfully
    STATUS_TRB_SHUTDOWN_IN_PROCESS,                         ///< 16054 Message: TRB Shutdown in process
    STATUS_REGISTRATION_VALIDTY_EXPIRED,                    ///< 16055 Message: TNS servers registration validity expired
    STATUS_USER_INVAILD,                                    ///< 16056 Message: User does not belong to the company
    STATUS_USER_ACCESS_TO_COMP_DENIED,                      ///< 16057 Message: Currently user is not allowed to access the company
    STATUS_CONN_SESSION_EXISTS,                             ///< 16058 Message: Session for connection exists
    STATUS_SESSION_FORCE_CLEAN,                             ///< 16059 Message: Session is closed forcibly by administrator
    STATUS_MULTIPLE_SESSION_CLEAN,                          ///< 16060 Message: Another session is established with the same username. Hence this session is closed.
    STATUS_EMPTY_CONN_CONTEXT,                              ///< 16061 Message: Request cannot be served. Please try later
    STATUS_TN_SUBSCRIPTION_IS_VALID,                        ///< 16062 Message: TallyNET subscription is valid.
    STATUS_CONCURRENT_ACCESS_LIMIT_EXCEEDED_ERROR,          ///< 16063 Message: for concurrent access limit message
    STATUS_HANDSHAKE_VALIDITY_DURATION_INVALID,             ///< 16064 Message: Handshake validity duration expired               

    //*****Break from Tally Product Status Code***********************************************************************************************************//
    STATUS_XBRL_SERVICE_SUBS_EXPIRED = 16074,               ///< 16074 Message: XBRL Service subscription expired
    STATUS_XBRL_SERVICE_SUBS_NOT_EXISTS,                    ///< 16075 Message: You have not subscribed for MCA XBRL Service to use this feature / facility. Go to 'Tally Shop' to buy the subscription.
    STATUS_REQUEST_TO_IRIS_SERVER_FAILED,                   ///< 16076 Message: Service unavailable for the moment. Contact Tally Solutions
    STATUS_MCA_SUBSCRIPTION_IS_VALID,                       ///< 16077 Message: MCA Service subscription is valid
    STATUS_MCA_INTERNAL_ERR,                                ///< 16078 Message: Internal error occurred. Request data is not valid.
    //****************************************************************************************************************************************************//

    //******Continuation of the Tally Product status code*************************************************************************************************//
    STATUS_SESSION_NOT_FOUND = 16101,                       ///< 16101 Message: 
    STATUS_LDS_CONN_FAILED,                                 ///< 16102 Message: Internal error occured
    STATUS_USER_TNS_EXPIRED,                                ///< 16103 Message: Your user name is not subscribed to a license with valid TallyNET Subscription
    //******Till Here Tally Product status code***********************************************************************************************************//

    /**
     * @brief VAT Requests Error Codes 
     *  
     */
    STATUS_VAT_INSUFFICIENT_DATA = 16120,                   ///< 16120 Message: Insufficient data to Login
    STATUS_VAT_CONNECTION_TO_SITE_FAILED = 16121,           ///< 16121 Message: Cannot connect to KVAT site
    STATUS_VAT_LOGIN_FAILED,                                ///< 16122 Message: Login Failed...Try Again
    STATUS_VAT_INVALID_URL,                                 ///< 16123 Message: Internal error occured. Contact Tally Solutions.
    STATUS_VAT_INVALID_SESSION,                             ///< 16124 Message: Internal error occured. Contact Tally Solutions.
    STATUS_VAT_SESSION_NODE_CREATION_FAIL,                  ///< 16125 Message: Internal error occured. Contact Tally Solutions.
    STATUS_READ_REQUEST_FAIL,                               ///< 16126 Message: Internal error occured. Contact Tally Solutions.
    STATUS_INVALID_VAT_STATE,                               ///< 16127 Message: Invalid State for Vat Upload
    STATUS_VAT_CAPTCHA_VALUE_IS_EMPTY,                      ///< 16128 Message: Please enter the captcha 

    /// 
    /***** TallyNET Object Error********************************************/
    STATUS_TALLY_NET_OBJECT_QUERY_EXECUTE_FAILED = 16201,   ///< 16201 Message: TallyNET Object Query execution failed
    STATUS_TALLY_NET_OBJECT_NOT_EXISTS,                     ///< 16202 Message: TallyNET Object does not exist

    /**
     * @brief Range 16301 - 16325 
     *  
     * Service: Third Party status codes 
     */
    STATUS_TP_INVALID_SOURCE = 16301,                       ///< 16301 Message: HTTP Header Source is Invalid
    STATUS_TP_INVALID_COMMUNICATION_PROTOCOL_USED,          ///< 16302 Message: Requests are supported only through HTTPS 
    STATUS_TP_INVALID_REQUEST,                              ///< 16303 Message: Request should not contain any TDL Nodes


    // Defines the TRB Status and Error Codes
 
    STATUS_REGISTER_SUCCESS = 17001,                        ///< 17001 Message: Register Success
    STATUS_REGISTER_FAIL,                                   ///< 17002 Message: Register fail
    STATUS_UNREGISTER_SUCCESS,                              ///< 17003 Message: Unregister Success
    STATUS_UNREGISTER_FAIL,                                 ///< 17004 Message: Unregister fail
    STATUS_HEARTBEAT_SUCCESS,                               ///< 17005 Message: Heartbeat Success
    STATUS_HEARTBEAT_FAIL,                                  ///< 17006 Message: Heartbeat update fail
    STATUS_RE_REGISTER,                                     ///< 17007 Message: Re-Register definition
    STATUS_CONNECTION_NOT_EXISTS,                           ///< 17008 Message: Active Connection Info does not exists
    STATUS_CONNECTION_ALREADY_EXISTS,                       ///< 17009 Message: Server information is already exists
    STATUS_CONNECTION_ADD_SUCCESS,                          ///< 17010 Message: Server connect success
    STATUS_CONNECTION_UPDATE_SUCCESS,                       ///< 17011 Message: Server information updated successfully
    STATUS_CONNECTION_UPDATE_FAIL,                          ///< 17012 Message: Server update fail
    STATUS_NO_ACTION_DEFINED,                               ///< 17013 Message: NOACTION request comes
    STATUS_RECONNECT_SUCCESS,                               ///< 17014 Message: Re connect company
    STATUS_VALID_SESSION,                                   ///< 17015 Message: Valid session
    STATUS_NO_CONNECTION_KEY,                               ///< 17016 Message: Connection key does not exists
    STATUS_COMP_STATISTICS_UPDATE_SUCCESS,                  ///< 17017 Message: Company statistics updated successfully
    STATUS_ANONYMOUS_ACTION_DEFINED,                        ///< 17018 Message: Anonymous action request        
    STATUS_CON_CLOSE_NORMAL,                                ///< 17019 Message: Tally Connection closed normally
    STATUS_CON_CLOSE_ABRUPT,                                ///< 17020 Message: Tally Connection closed due to Socket Failure
    STATUS_CON_CLOSE_CON_FAIL,                              ///< 17021 Message: Tally Connect request not received (CC is empty)
    STATUS_CON_CLOSE_LIC_EXP,                               ///< 17022 Message: Tally Connection is removed due to License expiry
    STATUS_RETRY_QUE_MSG,                                   ///< 17023 Message: (No Message):Status defining the msg is introduced into Retry Queue
    STATUS_TALLY_PING_MSG,                                  ///< 17024 Message: (No Message):Status defining msg is Tally Ping
    STATUS_SMS_INFO_MSG,                                    ///< 17025 Message: (No Message):Message is SMS message
    STATUS_RECONNECT_IN_PROCESS,                            ///< 17026 Message: (No Message):Reconnect to LDS in progress
    STATUS_FORCED_DISCONNECT_COMP_SUCCESS,                  ///< 17027 Message: (No Message):
    STATUS_TALLY_CONNECT_SUCCESS,                           ///< 17028 Message: (No Message):
    STATUS_UPDATE_SMS_INFO_SUCCESS,                         ///< 17029 Message: (No Message):
    STATUS_LICENSE_VALIDATION_SUCCESS,                      ///< 17030 Message: (No Message):
    STATUS_BSS_RESP_FAILURE,                                ///< 17031 Message: (No Message):Used when BSS has sent failure response
    STATUS_TNET_SUBS_IS_VALID,                              ///< 17032 Message: (No Message):Tally Net Subscription is valid
    STATUS_PREPARE_SHUTDOWN_COMPLETE,                       ///< 17033 Message: (No Message): 
    STATUS_VALID_NONCE,                                     ///< 17034 Message: Valid NONCE
    STATUS_PROCESS_RETRY_CLIENTS,                           ///< 17035 Message: (No Message):Used when the data response is processed and retry requests are present
    STATUS_ALERT_MSG_SUCCESS,                               ///< 17036 Request processed successfully
    STATUS_ALERT_MSG_FAIL,                                  ///< 17037 Request failed to process
    STATUS_ASYNC_CALL_IN_PROGRESS,                          ///< 17038 Message: (No Message):Used when a call to a server is made and the response is awaited asynchronously

    // Defines the LDS Status and Error Codes
    STATUS_NO_DATA = 18001,                                 ///< 18001 Message: Data does not exists 
    STATUS_HEALTH_CHECK_SUCCESS,                            ///< 18002 Message: Health Check done successfully 
    STATUS_SESSION_DELETE_SUCCESS,                          ///< 18003 Message: Session Deletion successfully 
    STATUS_PREPARE_FOR_UNREG_SUCCESS,                       ///< 18004 Message: Prepare TRB for Unregister success 
    STATUS_PREPARE_FOR_UNREG_FAIL,                          ///< 18005 Message: Prepare TRB for Unregister fail
    STATUS_PREPARE_FOR_SHUTDOWN_SUCCESS,                    ///< 18006 Message: Prepare for Shutdown success
    STATUS_PREPARE_FOR_SHUTDOWN_FAIL,                       ///< 18007 Message: Prepare for Shutdown fail
    STATUS_ADMIN_REQUEST_PROCESSED_SUCCESS,                 ///< 18008 Message: Admin Request processed successfully
    STATUS_REGISTRATION_SUCCESS,                            ///< 18009 Message: Server registered successfully
    STATUS_FORCED_UNREGISTER,                               ///< 18010 Message: (No Message):Forced unregister definition
    STATUS_LDS_REGISTRATION_SUCCESS,                        ///< 18011 Message: (No Message):Secondary LDS Registration success
    STATUS_REG_INFO_NOT_EXIST,                              ///< 18012 Message: (No Message):Registration data does not exist
    STATUS_REG_VALIDITY_EXPIRED,                            ///< 18013 Message: (No Message):Registration validity expired
    STATUS_SERVER_ID_EMPTY,                                 ///< 18014 Message: (No Message):Server ID is empty
    STATUS_RE_REGISTRATION_SUCCESS,                         ///< 18015 Message: (No Message):TRB Re-Registration success
    STATUS_PROP_AUTH_REQ_PROCESS_SUCCESS,                   ///< 18016 Message: Propagated AuthRemoteUser/AuthTallyClient success
    STATUS_PROP_GET_COMP_FOR_REMUSER_SUCCESS,               ///< 18017 Message: Propagated GetCompaniesForRemoteUser request success
    STATUS_PROP_GET_SPECIFIC_TRB_SUCCESS,                   ///< 18018 Message: Propagated GetSpecificTRB request success 
    STATUS_PROP_REQ,                                        ///< 18019 Message: (No Message): Used to identify a message should be propagated or not
    STATUS_VALIDATE_WITH_LDS,                               ///< 18020 Message: Used to identify querying session with other LDS is required or not
    //STATUS_SA_NOT_AVAILABLE,                                ///< 18021 Message: Support Agent not available for priority queue request
    //STATUS_USER_SA_DISCONNECTED_SUCCESS,                    ///< 18022 Message: User or Support Agent disconnected successfully
    STATUS_LDS_NOT_REGISTERED,                              ///< 18021 Message: LDS is not registered component
    STATUS_TRB_NOT_REGISTERED,                              ///< 18022 Message: TRB is not a registered component

    // Defines the SMS Status and Error Codes
    STATUS_SMS_ERROR_GENERAL = 19001,                       ///< 19001 Message: Request cannot be served, Please try later.
    STATUS_SMS_CHANGE_COMMAND_FORMAT_INVALID,               ///< 19002 Message: SMS Change command format is invalid
    STATUS_SMS_CHANGE_COMMAND_SUCCESS,                      ///< 19003 Message: Request processed successfully
    STATUS_SMS_PROCESS_IN_PROGRESS,                         ///< 19004 Message: (No Message):Used to avoid response ready while processing SMS request
    STATUS_PROCESS_SMS_CHANGE_CMD_SUCCESS,                  ///< 19005 Message: (No Message):Used to propagate if ChangeSMSSuffix response exists from BSS
    STATUS_PROCESS_SMS_LIST_CMD_SUCCESS,                    ///< 19006 Message: (No Message):Used to propagate if GetAllMobileNumbers response exists from BSS
    STATUS_SMS_COMPANY_NOT_CONNECTED,                       ///< 19007 Message: Company is currently not connected with Tally.NET Server
    STATUS_COMP_SMS_ACCESS_PERMISSION_DENIED,               ///< 19008 Message: SMS access is not enabled for %s
    STATUS_USER_SMS_ACCESS_PERMISSION_DENIED,               ///< 19009 Message: SMS access is not allowed for %s in %s
    STATUS_SUFFIX_NOT_ASSOCIATED_TO_COMPANY,                ///< 19010 Message: Invalid SMS Suffix.
    STATUS_SUFFIX_MENTIONED_IS_INVALID,                     ///< 19011 Message: Invalid SMS Suffix.
    STATUS_NO_COMPANIES_CONNECTED_FOR_USER,                 ///< 19012 Message: No companies are currently connected for %s
    STATUS_FORCED_CLEANUP_FOR_SMS_REQUEST,                  ///< 19013 Message: (No Message):Used if a SMS Request is received by LDS and no response is sent on that
    STATUS_CONTENT_LEN_EXCEEDED_EMAIL_SENT,                 ///< 19014 Message: Since the content is too lengthy an email has been sent to %s
    STATUS_REPORT_SUCCESS_WITH_MAX_LEN_EXCEED,              ///< 19015 Message: (No Message)
    STATUS_REPORT_FAIL_WITH_MAX_LEN_EXCEED,                 ///< 19016 Message: (No Message)
    STATUS_LIST_CMD_SUCCESS_WITH_MAX_LEN_EXCEED,            ///< 19017 Message: (No Message)

    START_UPLOAD_SUCCESS = 19800,                           ///<19800 Message: Start Upload Successful
    FILE_SAVED_SUCCESSFULLY_IN_TNFS,                        ///<19801 Message: File Saved Successfully
    FILE_NOT_SAVED,                                         ///<19802 Message: File Not Saved
    CONFIG_REFRESHED,                                       ///<19803 Message: Configuration refreshed
    FILE_NOT_FOUND,                                         ///<19804 Message: File Not found
    REFRESH_UNSUCCESSFUL,                                   ///<19805 Message: Refresh Unsuccessful
    REFRESH_SUCCESSFUL,                                     ///<19806 Message: Refresh Successful

    //Status codes for capsule related errors
    STATUS_CAPSULE_SERVICE_NOT_AVAIL  = 20001,              ///< 20001 Message: Capsule Server is not running on this TRB
    STATUS_INVALID_CDS_REQUEST_ID,                          ///< 20002 Message: Invalid Request ID for CDS
    STATUS_INVALID_CAPSULE_REQUEST,                         ///< 20003 Message: Internal error occured. Contact Tally Solutions.
    STATUS_INVALID_INDEX_REQUEST,                           ///< 20004 Message: Internal error occured. Contact Tally Solutions.
    STATUS_INVALID_DESC_INDEX_REQUEST,                      ///< 20005 Message: Internal error occured. Contact Tally Solutions.
    STATUS_CACHEMANAGER_NOT_INITIALIZED,                    ///< 20006 Message: Internal error occured. Contact Tally Solutions.

    //Status codes for offline sync related errors
    STATUS_FILE_NOT_FOUND   = 21001,                        ///< 21001 Message : File Not Found

    //Errors related to SVGETSYNCRULES
    STATUS_SVGETSYNCRULES_XML_WRITER_NOT_FOUND = 21002,     ///< 21002 Message : Failed to get sync rules

    //Errors related to TNFS Discovery
    STATUS_TNFS_URL_NOT_FOUND = 21003,                      ///< 21003 Message : TNFS URL Not Found

    //Errors related to SVGETSYNCRULE
    STATUS_SVGETSYNCRULE_DISK_FILE_ERROR = 21011,           ///< 21011 Message : Failed to get sync rule
    STATUS_SVGETSYNCRULE_NO_RULEGUID,                       ///< 21012 Message : Failed to get sync rule
                                                            
    //Errors related to SVISRULEACTIVE
    STATUS_SVISRULEACTIVE_CANNOT_PARSE_REQ = 21021,         ///< 21021 Message : Failed to get Rule Active Status
    STATUS_SVISRULEACTIVE_RULE_NOT_FOUND,                   ///< 21022 Message : Failed to get Rule Active Status
    STATUS_SVISRULEACTIVE_RESP_NOT_CREATED,                 ///< 21023 Message : Failed to get Rule Active Status

    //Errors related to SVSETUPREMOTESERVEROFFLINE
    STATUS_SVSETUPREMOTESERVEROFFLINE_ADD_RULE_FAILED = 21031,   ///< 21031 Message : Failed to Setup Offline Remote Server
    STATUS_SVSETUPREMOTESERVEROFFLINE_PERSIST_RULE_FAILED,       ///< 21032 Message : Failed to Setup Offline Remote Server

    //Errors related to SVGETDATAPOINT
    STATUS_SVGETDATAPOINT_CANNOT_PARSE_REQ = 21041,         ///< 21041 Message : Failed to get Data Point
    STATUS_SVGETDATAPOINT_RULE_NOT_FOUND,                   ///< 21042 Message : Failed to get Data Point
    STATUS_SVGETDATAPOINT_RESP_NOT_CREATED,                 ///< 21043 Message : Failed to get Data Point
                                                            
    //Errors related to SVPUTSYNCDATA
    STATUS_SVPUTSYNCDATA_RULE_NOT_FOUND = 21051,            ///< 21051 Message : Failed to save sync data
    STATUS_SVPUTSYNCDATA_RULE_NOT_ACTIVE,                   ///< 21052 Message : Failed to save sync data
    STATUS_SVPUTSYNCDATA_DATA_NOT_PRESENT,                  ///< 21053 Message : Failed to save sync data
    STATUS_SVPUTSYNCDATA_DATA_NOT_SAVED,                    ///< 21054 Message : Failed to save sync data
    STATUS_SVPUTSYNCDATA_RULE_NOT_UPDATED,                  ///< 21055 Message : Failed to save sync data

    //Errors related to SVUPDATERULE                                                     
    STATUS_SVUPDATERULE_CANNOT_PARSE_REQ = 21061,           ///< 21061 Message : Failed to update sync rule
    STATUS_SVUPDATERULE_CANNOT_UPDATE_RULE,                 ///< 21062 Message : Failed to update sync rule
                                                             
    //Errors related to SVGETSYNCDATA
    STATUS_SVGETSYNCDATA_DATA_NOT_FOUND = 21071,            ///< 21061 Message : Failed to Get Sync Data

    //Errors related to SVPUTEXCEPTION
    STATUS_SVPUTEXCEPTIONDATA_RULE_NOT_FOUND = 21081,       ///< 21081 Message : Failed to save exception data
    STATUS_SVPUTEXCEPTIONDATA_RULE_NOT_ACTIVE,              ///< 21052 Message : Failed to save exception data
    STATUS_SVPUTEXCEPTIONDATA_DATA_NOT_PRESENT,             ///< 21053 Message : Failed to save exception data
    STATUS_SVPUTEXCEPTIONDATA_DATA_NOT_SAVED,               ///< 21054 Message : Failed to save exception data

    //General Offline Sync Errors
    STATUS_OFFLINE_SYNC_NOT_PERMITTED = 21101,              ///< 21101 Message : Cannot Proceed with Offline Sync


    //Errors related to SVGETMSTACKFOR
    STATUS_GETMSTACKFOR_RULE_NOT_FOUND = 21091,             ///< 21091 Message : Failed to save Acknowledgement query
    STATUS_GETMSTACKFOR_RULE_NOT_ACTIVE,                    ///< 21092 Message : Failed to save Acknowledgement query
    STATUS_GETMSTACKFOR_DATA_NOT_PRESENT,                   ///< 21093 Message : Failed to save Acknowledgement query
    STATUS_GETMSTACKFOR_DATA_NOT_SAVED,                     ///< 21094 Message : Failed to save Acknowledgement query
    STATUS_GETMSTACKFOR_RULE_NOT_UPDATED,                   ///< 21095 Message : Failed to save Acknowledgement query
    STATUS_GETMSTACKFOR_TOPOINT_FROMPOINT_SAME,             ///< 21096 Message : Failed to save Acknowledgement query
                                                             
    //Errors related to SVPUTTRANSACK
    STATUS_SVPUTTRANSACK_RULE_NOT_FOUND = 21111,            ///< 21111 Message : Failed to save Acknowledgement
    STATUS_SVPUTTRANSACK_RULE_NOT_ACTIVE,                   ///< 21112 Message : Failed to save Acknowledgement
    STATUS_SVPUTTRANSACK_DATA_NOT_PRESENT,                  ///< 21113 Message : Failed to save Acknowledgement
    STATUS_SVPUTTRANSACK_DATA_NOT_SAVED,                    ///< 21114 Message : Failed to save Acknowledgement
    STATUS_SVPUTTRANSACK_RULE_NOT_UPDATED,                  ///< 21115 Message : Failed to save Acknowledgement

    STATUS_SVGETTRANSACK_DATA_NOT_FOUND = 21121,            ///< 21121 Message : Failed to Get Trans ACK

    STATUS_SVGETMSKACKRESP_DATA_NOT_FOUND = 21131,          ///< 21131 Message : Failed to Get Acknowledgement Query Response

    //Errors related to SVGetMstAckPoint
    STATUS_SVGETMSTACKPOINT_CANNOT_PARSE_REQ = 21141,       ///< 21141 Message : Failed to get Master Acknowledgement Point
    STATUS_SVGETMSTACKPOINT_RULE_NOT_FOUND,                 ///< 21142 Message : Failed to get Master Acknowledgement Point
    STATUS_SVGETMSTACKPOINT_RESP_NOT_CREATED,               ///< 21143 Message : Failed to get Master Acknowledgement Point
                                                              
    STATUS_SVGETPENDINGACKREQ_DATA_NOT_FOUND = 21151,       ///< 21151 Message : Failed to Get Pending Acknowledgements

    //Errors related to SVPUTMSTACKRESP
    STATUS_SVPUTMSTACKRESP_RULE_NOT_FOUND = 21161,            ///< 21161 Message : Failed to save ack resp
    STATUS_SVPUTMSTACKRESP_RULE_NOT_ACTIVE,                   ///< 21162 Message : Failed to save ack resp
    STATUS_SVPUTMSTACKRESP_DATA_NOT_PRESENT,                  ///< 21163 Message : Failed to save ack resp
    STATUS_SVPUTMSTACKRESP_DATA_NOT_SAVED,                    ///< 21164 Message : Failed to save ack resp
    STATUS_SVPUTMSTACKRESP_RULE_NOT_UPDATED,                  ///< 21165 Message : Failed to save ack resp
                                                              
    STATUS_RSA_SIGNATURE_NOT_OBTAINED   = 22001,              ///< 22001 Message : RSA signature Not Created

//-----Error code for banking at different components-----//

    //Bank Errors : These errors are mappings to bank status posted
    STATUS_PAYLOAD_SYNC_VALIDATION_FAILED = 25001,           ///< 25001 Message : Syncronous validation of payload failed

    STATUS_PAYLOAD_ASYNC_VALIDATION_FAILED = 26001,          ///< 26001 Message : Asyncronous payload verification failed

    STATUS_PAYMENT_AUTHORISATION_FAILED = 27001,             ///< 27001 Message : Payment authorisation failed

    STATUS_PAYMENT_PROCESSING_FAILED = 28001,                ///< 28001 Message : Payment processing failed
    STATUS_STATEMENT_PREPARATION_FAILED = 28002,             ///< 28002 Message : Statement preparation failed

    STATUS_BANK_STATUS_POST_INCORRECT_PAYLOAD = 29001,       ///< 29001 Message : Bank status post failed due to incorrect payload from bank

    //TNS Errors : These errors occur when TNS is unable to send request to Bank
    STATUS_TSS_PAYMENT_PAYLOAD_PREPARATION_FAILED = 30001,   ///< 30001 Message : Preparation of payment payload failed
    STATUS_TSS_STATEMENT_PAYLOAD_PREPARATION_FAILED,         ///< 30002 Message : Preparation of statement payload failed

    STATUS_TSS_PAYMENT_REQUEST_UPLOAD_FAILED = 31001,        ///< 31001 Message : Payment request upload failed
    STATUS_TSS_STATEMENT_REQUEST_UPLOAD_FAILED,              ///< 31002 Message : Statement request upload failed
    STATUS_TSS_STATEMENT_DOWNLOAD_FAILED,                    ///< 31003 Message : Statement file download failed

    //Gateway errors : These errors occurs at gateway when gateway tries to upload request to TSS
    STATUS_TGW_REQUEST_UPLOAD_FAILED = 35001,                ///< 35001 Message : Request upload failed from TGW to TSS

    STATUS_TGW_FAILED_PARSING_CLIENT_REQUEST = 36001,        ///< 36001 Message : Failed to parse client request

    //Tallyclient errors : These errors occur when client tries to upload bank request to TGW or TSS
    STATUS_TC_ENCRYPTION_CAPSULE_NOT_FOUND = 40001,          ///< 40001 Message : Unable to find encryption capsule
    STATUS_TC_RSA_ENCRYPTION_FAILED,                         ///< 40002 Message : RSA encryption failed
    STATUS_TC_METADATA_PARSING_FAILED,                       ///< 40003 Message : Failed to parse metadata XML

    STATUS_TC_FAILED_TO_UPLOAD_REQUEST_TO_TSS = 41001,       ///< 41001 Message : Request upload failed from TC to TSS
    STATUS_TC_FAILED_TO_UPLOAD_REQUEST_TO_TGW,               ///< 41002 Message : Request upload failed from TC to TGW
    STATUS_BANKING_NO_INTERNET_CONN,                         ///< 41003 Message : No internet connection to tss
    STATUS_BANKING_TNS_SERVER_UNAVAILABLE,                   ///< 41004 Message : Could not connect to TSS
    STATUS_BANKING_SESSION_ESTABLISH_FAIL,                   ///< 41005 Message : Session establishment failed
    STATUS_BANKING_SEND_REQ_TO_TNS_FAILED,                   ///< 41006 Message : Banking request can not be send to TSS
    STATUS_BANKING_LIC_STATE_OFFLINE,                        ///< 41007 Message : License connection status is offline.


//-----Error code for banking at different components end-----//
};

/**
 * @brief Component name for allocating the error code 
 *        description
 */
enum eComponentName {
    COMPONENT_NAME_TSS,
    COMPONENT_NAME_TGW,
    COMPONENT_NAME_TC,
};

enum eAlignment
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    CENTRE
};

typedef enum {

    TASK_UNKNOWN = 0,
    TASK_RECOMPUTE,
    TASK_EXCHANGE,
                        // new task type goes here
    TASK_MAX,           // should not changes this one, used to mark total intent type in use
    TASK_RESERVED = 10,

} eIntentType;

enum eVchDependencyType {

    VCH_DEP_NORMAL,
    VCH_DEP_REWRITE,
    VCH_DEP_LINK,
    VCH_DEP_UNLINK
};

enum eVchRecomputeType {

    VRT_FULL_UPDATE,
    VRT_SPV_UPDATE,
    VRT_SKIP_THIS,
};

enum eProductType {

    PDT_UNKNOWN = 0,
    PDT_TE9,
    PDT_TS9,
    PDT_TD9,
    PDT_TOC,           // Online Content
    PDT_TP,            // TallyPrime
    PDT_TPS,           // TallyPrime Server
    PDT_TPD,           // TallyPrime Developer
    PDT_TPEL,          // TallyPrime EditLog
    PDT_MAX,
};

enum eReturnType {

    RET_GOOD,
    RET_BAD,
    RET_DUPLICATE,
};

enum eWidgetType {

    WID_NONE,
    WID_QUERY,
    WID_MSG
};

//Error framework
enum eErrRecordingFlow {

    ERR_RECORDING_NONE,
    ERR_RECORDING_REPAIR,
    ERR_RECORDING_MIGRATION,
    ERR_RECORDING_SYNC,
    ERR_RECORDING_IMPORT,
    ERR_RECORDING_REPMIG
};

enum eErrType {

    ERR_TYPE_NONE,

    //Master related Errors
    ERR_MST_VAL_CONFLICT,
    ERR_MST_MISSING,
    ERR_MST_NAME_CONFLICT,
    ERR_MST_ALREADY_EXISTS,
    ERR_MST_DECIMAL_INVALID,
    ERR_MST_PRINTING,  
    ERR_MST_SPLIT_ISSUE,

    //Vouchers related errors.
    ERR_VCH_VAL_CONFLICT,
    ERR_VCH_DEP_INFO,
    ERR_VCH_TOTAL_MISMATCH,
    ERR_VCH_MST_VALUE_CONFLICT,

    ERR_SUM_TRANS_ISSUE,
    ERR_LED_NAME_NOT_PROVIDED,
    ERR_RET_TRANS_VAL_FAILED,
    ERR_MAX
};

// Used to indicate different kinds of errors that occur during
// PDF digital signing process. 
enum ePDF_SIGN_ERRORS {

    PSE_NO_ERROR,
    PSE_PARSING_ERROR,
    PSE_CERTIFICATE_ERROR,
    PSE_CERTIFICATE_EXPIRED_WARNING,
    PSE_EDU_LICENSE_WARNING,
    PSE_CERTIFICATE_PW_INFO,
    PSE_SIGN_WRITE_ERROR,
    PSE_IMAGE_ERROR,
    PSE_CUSTOM_IMAGE_PATH_WARNING,
    PSE_CUSTOM_IMAGE_SIZE_WARNING,
    PSE_FILE_CREATION_ERROR
};

#endif  // LBA_ENUM_H

