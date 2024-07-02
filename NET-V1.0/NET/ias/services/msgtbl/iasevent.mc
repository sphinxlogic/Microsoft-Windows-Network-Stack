;///////////////////////////////////////////////////////////////////////////////
;//
;// Copyright (c) 2000, Microsoft Corp. All rights reserved.
;//
;// FILE
;//
;//    iasevent.mc
;//
;// SYNOPSIS
;//
;//    This file defines the events used by the Everest core.
;//
;///////////////////////////////////////////////////////////////////////////////

SeverityNames =
(
Success       = 0x0:IAS_SEVERITY_SUCCESS
Informational = 0x1:IAS_SEVERITY_INFORMATIONAL
Warning       = 0x2:IAS_SEVERITY_WARNING
Error         = 0x3:IAS_SEVERITY_ERROR
)

FacilityNames =
(
Application    = 0x000:IAS_FACILITY_APPLICATION
Radius         = 0x001:IAS_FACILITY_RADIUS
)


;///////////////////////////////////////////////////////////////////////////////
;//
;// Message Text for reporting the result of an Access-Request.
;//
;///////////////////////////////////////////////////////////////////////////////

MessageId    = 1
Facility     = Application
Severity     = Informational
SymbolicName = IAS_RESPONSE_ACCEPT
Language     = English
User %1 was granted access.%n
Fully-Qualified-User-Name = %2%n
NAS-IP-Address = %3%n
NAS-Identifier = %4%n
Client-Friendly-Name = %5%n
Client-IP-Address = %6%n
Calling-Station-Identifier = %7%n
NAS-Port-Type = %8%n
NAS-Port = %9%n
Proxy-Policy-Name = %10%n
Authentication-Provider = %11%n
Authentication-Server = %12%n
Policy-Name = %13%n
Authentication-Type = %14%n
EAP-Type = %15
.

MessageId    = 2
Severity     = Warning
SymbolicName = IAS_RESPONSE_REJECT
Language     = English
User %1 was denied access.%n
Fully-Qualified-User-Name = %2%n
NAS-IP-Address = %3%n
NAS-Identifier = %4%n
Called-Station-Identifier = %5%n
Calling-Station-Identifier = %6%n
Client-Friendly-Name = %7%n
Client-IP-Address = %8%n
NAS-Port-Type = %9%n
NAS-Port = %10%n
Proxy-Policy-Name = %11%n
Authentication-Provider = %12%n
Authentication-Server = %13%n
Policy-Name = %14%n
Authentication-Type = %15%n
EAP-Type = %16%n
Reason-Code = %17%n
Reason = %18
.

MessageId    = 3
Severity     = Error
SymbolicName = IAS_RESPONSE_DISCARD
Language     = English
Access request for user %1 was discarded.%n
Fully-Qualified-User-Name = %2%n
NAS-IP-Address = %3%n
NAS-Identifier = %4%n
Called-Station-Identifier = %5%n
Calling-Station-Identifier = %6%n
Client-Friendly-Name = %7%n
Client-IP-Address = %8%n
NAS-Port-Type = %9%n
NAS-Port = %10%n
Proxy-Policy-Name = %11%n
Authentication-Provider = %12%n
Authentication-Server = %13%n
Reason-Code = %14%n
Reason = %15
.

MessageId    = 4
Severity     = Error
SymbolicName = IAS_ACCT_RESPONSE_DISCARD
Language     = English
Accounting request for user %1 was discarded.%n
Fully-Qualified-User-Name = %2%n
NAS-IP-Address = %3%n
NAS-Identifier = %4%n
Called-Station-Identifier = %5%n
Calling-Station-Identifier = %6%n
Client-Friendly-Name = %7%n
Client-IP-Address = %8%n
NAS-Port-Type = %9%n
NAS-Port = %10%n
Proxy-Policy-Name = %11%n
Accounting-Provider = %12%n
Accounting-Server = %13%n
Reason-Code = %14%n
Reason = %15
.

;///////////////////////////////////////////////////////////////////////////////
;//
;// Message text for events from the protocol component
;//
;///////////////////////////////////////////////////////////////////////////////

;// %1   - client address
;// %2   - client name
;// data - Win32 error code
MessageId    = 10
SymbolicName = RADIUS_E_CANT_RESOLVE_CLIENT_NAME
Language     = English
The name, %1, of the RADIUS client, %2, could not be resolved. The data is the error code generated by Windows Sockets.
.


;// %1   - client address
;// %2   - client name
MessageId    = 11
SymbolicName = RADIUS_E_INVALID_CLIENT_ADDRESS
Language     = English
The IP address, %1, of the RADIUS client, %2, is not a valid IP address.
.

;// data - Win32 error code
MessageId    = 12
SymbolicName = RADIUS_E_INTERNAL_ERROR
Language     = English
An internal error occurred while processing a request. The data is the error code.
.

;// %1   - source IP address
MessageId    = 13
SymbolicName = RADIUS_E_INVALID_CLIENT
Language     = English
A RADIUS message was received from the invalid RADIUS client IP address %1.
.

;// %1   - client name
MessageId    = 14
SymbolicName = RADIUS_E_BAD_AUTHENTICATOR
Language     = English
A RADIUS message was received from RADIUS client %1 with an invalid authenticator. This is typically caused by mismatched shared secrets. Verify the configuration of the shared secret for the RADIUS client in the Internet Authentication Service snap-in and the configuration of the network access server.
.

;// %1   - client name
;// data - RADIUS packet
MessageId    = 15
SymbolicName = RADIUS_E_MALFORMED_PACKET
Language     = English
A malformed RADIUS message was received from client %1. The data is the RADIUS message.
.

;// %1   - RADIUS packet code
;// %2   - destination IP port
;// %3   - client name
MessageId    = 16
SymbolicName = RADIUS_E_INVALID_PACKET_TYPE
Language     = English
A RADIUS message with the Code field set to %1, which is not valid, was received on port %2 from RADIUS client %3. Valid values of the RADIUS Code field are documented in RFC 2865.
.

;// %1   - client name
MessageId    = 17
SymbolicName = RADIUS_E_SIGNATURE_REQUIRED
Language     = English
An Access-Request message was received from RADIUS client %1 without a message authenticator attribute when a message authenticator attribute is required. Verify the configuration of the RADIUS client in the Internet Authentication Service snap-in (the "Client must always send the message authenticator attribute in the request" checkbox) and the configuration of the network access server.
.

;// %1   - client name
MessageId    = 18
SymbolicName = RADIUS_E_INVALID_SIGNATURE
Language     = English
An Access-Request message was received from RADIUS client %1 with a message authenticator attribute that is not valid.
.

;// %1   - client name
MessageId    = 19
SymbolicName = RADIUS_E_NO_SIGNATURE_WITH_EAP_MESSAGE
Language     = English
An Access-Request message was received from RADIUS client %1 with an Extensible Authentication Protocol (EAP) message but no message authenticator attribute.
.

;// data   - RADIUS attribute type
MessageId    = 20
SymbolicName = RADIUS_E_ATTRIBUTE_OVERFLOW
Language     = English
An attribute in the response to RADIUS client %1 exceeds the maximum RADIUS attribute length. The data is the RADIUS attribute type. For more information on the RADIUS attribute type, see RFC 2865 and http://www.isi.edu/in-notes/iana/assignments/radius-types.
.

MessageId    = 21
SymbolicName = RADIUS_E_PACKET_OVERFLOW
Language     = English
The response to RADIUS client %1 exceeds the maximum RADIUS message length of 4096 bytes.
.

;// data - Win32 error code
MessageId    = 22
SymbolicName = RADIUS_E_CANT_SEND_RESPONSE
Language     = English
The Internet Authentication Service (IAS) could not send a response due to a network error. The data is the error code generated by Windows Sockets.
.

;// This event is never reported, so it does not need any message text.
MessageId    = 23
SymbolicName = RADIUS_E_ERRORS_OCCURRED
Language     = English
.

;///////////////////////////////////////////////////////////////////////////////
;//
;//  RADIUS Proxy Events
;//
;///////////////////////////////////////////////////////////////////////////////

MessageId    = 24
Severity     = Error
SymbolicName = PROXY_E_HOST_NOT_FOUND
Language     = English
The RADIUS Proxy could not resolve the name of remote RADIUS server %1 in remote RADIUS server group %2 to an IP address. The error code is %3.
.

MessageId    = 25
Severity     = Error
SymbolicName = PROXY_E_LOCAL_SERVER
Language     = English
The address of remote RADIUS server %1 in remote RADIUS server group %2 resolves to local address %3. The address will be ignored.
.

MessageId    = 26
Severity     = Error
SymbolicName = PROXY_E_INVALID_ADDRESS
Language     = English
The RADIUS Proxy received a response from the invalid IP address %1:%2 (IP address:port).
.

MessageId    = 27
Severity     = Error
SymbolicName = PROXY_E_MALFORMED_RESPONSE
Language     = English
The RADIUS Proxy received a malformed response from server %1. The data is the RADIUS message.
.

MessageId    = 28
Severity     = Error
SymbolicName = PROXY_E_BAD_AUTHENTICATOR
Language     = English
The RADIUS Proxy received a response from server %1 with an invalid authenticator.
.

MessageId    = 29
Severity     = Error
SymbolicName = PROXY_E_BAD_SIGNATURE
Language     = English
The RADIUS Proxy received a response from server %1 with an invalid message authenticator attribute.
.

MessageId    = 30
Severity     = Error
SymbolicName = PROXY_E_MISSING_SIGNATURE
Language     = English
The RADIUS Proxy received a response from server %1 with a missing message authenticator attribute.
.

MessageId    = 31
Severity     = Error
SymbolicName = PROXY_E_UNKNOWN_TYPE
Language     = English
The RADIUS Proxy received a response from server %1 with the Code field set to the invalid value of %2. Valid values of the Code field are documented in RFC 2865.
.

MessageId    = 32
Severity     = Error
SymbolicName = PROXY_E_UNEXPECTED_RESPONSE
Language     = English
The RADIUS Proxy received an unexpected response from server %1. The data is the RADIUS message.
.

MessageId    = 33
Severity     = Error
SymbolicName = PROXY_E_SEND_ERROR
Language     = English
The RADIUS Proxy was unable to forward a RADIUS request to remote RADIUS server %1 because of a network error. The error code is %2.
.

MessageId    = 34
Severity     = Error
SymbolicName = PROXY_E_RECV_ERROR
Language     = English
The RADIUS Proxy is unable to receive responses because of a network error. The error code is %2.
.

MessageId    = 35
Severity     = Success
SymbolicName = PROXY_S_SERVER_AVAILABLE
Language     = English
The remote RADIUS server %1 is now available.
.

MessageId    = 36
Severity     = Warning
SymbolicName = PROXY_E_SERVER_UNAVAILABLE
Language     = English
The remote RADIUS server %1 has not responded to %2 consecutive requests. The server has been marked as unavailable.
.

;///////////////////////////////////////////////////////////////////////////////
;//
;// Insertion strings used for reporting attribute values.
;//
;///////////////////////////////////////////////////////////////////////////////

MessageId    = 37
SymbolicName = IASP_UNDETERMINED
Language     = English
<undetermined>
.

MessageId    = 38
SymbolicName = IASP_NOT_PRESENT
Language     = English
<not present>
.

MessageId    = 39
SymbolicName = IASP_NONE
Language     = English
<none>
.

MessageId    = 40
SymbolicName = IASP_PROVIDER_WINDOWS
Language     = English
Windows
.

MessageId    = 41
SymbolicName = IASP_PROVIDER_RADIUS_PROXY
Language     = English
RADIUS Proxy
.

;///////////////////////////////////////////////////////////////////////////////
;//
;// Accounting errors.
;//
;///////////////////////////////////////////////////////////////////////////////

MessageId    = 42
Severity     = Success
SymbolicName = ACCT_S_OLD_LOG_DELETED
Language     = English
Disk full. Deleted older logfile %1 to create free space.
.

MessageId    = 43
Severity     = Error
SymbolicName = ACCT_E_OLD_LOG_DELETE_ERROR
Language     = English
Disk full. Could not delete older logfile %1 to create free space.
.

MessageId    = 44
Severity     = Informational
SymbolicName = ACCT_I_OLD_LOG_NOT_FOUND
Language     = English
Disk full. Could not find older logfile to delete and create free space.
.

MessageId    = 45
SymbolicName = IASP_PROVIDER_EXTERNAL_AUTH
Language     = English
Remote RADIUS to Windows User Mapping
.


;///////////////////////////////////////////////////////////////////////////////
;//
;// Licensing errors.
;//
;///////////////////////////////////////////////////////////////////////////////

MessageId    = 46
Severity     = Error
SymbolicName = IAS_E_SERVICE_LICENSE_VIOLATION
Language     = English
This edition of Windows Server 2003 cannot support any of the following IAS configurations:%n
 - More than 50 RADIUS clients%n
 - More than two RADIUS server groups%n
 - Client identification by subnet mask%n
To set up your server to support any of these configurations, install Windows Server 2003, Enterprise Edition, or Windows Server 2003, Datacenter Edition.%n
.

;///////////////////////////////////////////////////////////////////////////////
;//
;// Message Text for IAS return codes.
;//
;///////////////////////////////////////////////////////////////////////////////
MessageId    = 0x1000
Severity     = Success
SymbolicName = IASP_SUCCESS
Language     = English
The operation completed successfully.
.
MessageId    = 0x1001
SymbolicName = IASP_INTERNAL_ERROR
Language     = English
An internal error occurred. Check the system event log for additional information.
.
MessageId    = 0x1002
SymbolicName = IASP_ACCESS_DENIED
Language     = English
There are not sufficient access rights to process the request.
.
MessageId    = 0x1003
SymbolicName = IASP_MALFORMED_REQUEST
Language     = English
The Remote Authentication Dial-In User Service (RADIUS) request was not properly formatted.
.
MessageId    = 0x1004
SymbolicName = IASP_GLOBAL_CATALOG_UNAVAILABLE
Language     = English
The Active Directory global catalog cannot be accessed.
.
MessageId    = 0x1005
SymbolicName = IASP_DOMAIN_UNAVAILABLE
Language     = English
The user account domain cannot be accessed.
.
MessageId    = 0x1006
SymbolicName = IASP_SERVER_UNAVAILABLE
Language     = English
The server is unavailable.
.
MessageId    = 0x1007
SymbolicName = IASP_NO_SUCH_DOMAIN
Language     = English
The specified domain does not exist.
.
MessageId    = 0x1008
SymbolicName = IASP_NO_SUCH_USER
Language     = English
The specified user account does not exist.
.
MessageId    = 0x1009
SymbolicName = IASP_EXTENSION_DISCARD
Language     = English
The request was discarded by a third-party extension DLL file.
.
MessageId    = 0x1010
SymbolicName = IASP_AUTH_FAILURE
Language     = English
Authentication was not successful because an unknown user name or incorrect password was used.
.
MessageId    = 0x1011
SymbolicName = IASP_CHANGE_PASSWORD_FAILURE
Language     = English
The user could not change his or her password because the new password did not meet the password requirements for this network.
.
MessageId    = 0x1012
SymbolicName = IASP_UNSUPPORTED_AUTH_TYPE
Language     = English
The specified authentication type is not supported.
.
MessageId    = 0x1013
SymbolicName = IASP_NO_CLEARTEXT_PASSWORD
Language     = English
The user could not be authenticated using Challenge Handshake Authentication Protocol (CHAP). A reversibly encrypted password does not exist for this user account. To ensure that reversibly encrypted passwords are enabled, check either the domain password policy or the password settings on the user account.
.
MessageId    = 0x1014
SymbolicName = IASP_LM_NOT_ALLOWED
Language     = English
LAN Manager authentication is not enabled.
.
MessageId    = 0x1015
SymbolicName = IASP_EXTENSION_REJECT
Language     = English
The request was rejected by a third-party extension DLL file.
.
MessageId    = 0x1016
SymbolicName = IASP_EAP_NEGOTIATION_FAILED
Language     = English
The client could not be authenticated  because the Extensible Authentication Protocol (EAP) Type cannot be processed by the server.
.
MessageId    = 0x1017
SymbolicName = IASP_UNEXPECTED_EAP_ERROR
Language     = English
Unexpected error. Possible error in server or client configuration.
.
MessageId    = 0x1020
SymbolicName = IASP_LOCAL_USERS_ONLY
Language     = English
The current server configuration supports only local user accounts.
.
MessageId    = 0x1021
SymbolicName = IASP_PASSWORD_MUST_CHANGE
Language     = English
The user must change his or her password.
.
MessageId    = 0x1022
SymbolicName = IASP_ACCOUNT_DISABLED
Language     = English
Authentication failed because the user account is not enabled. Before the account can be authenticated, a person with administrative rights for either the computer or the domain must enable the user account.
.
MessageId    = 0x1023
SymbolicName = IASP_ACCOUNT_EXPIRED
Language     = English
The user account has expired. Only a person with administrative rights for either the computer or the domain can reset the expiration date on the user account.
.
MessageId    = 0x1024
SymbolicName = IASP_ACCOUNT_LOCKED_OUT
Language     = English
The user account is currently locked and cannot be authenticated. Only a person with administrative rights for either the computer or the domain can unlock the user account.
.
MessageId    = 0x1025
SymbolicName = IASP_INVALID_LOGON_HOURS
Language     = English
Authentication failed because of a logon time restriction on the user account. Ensure that the permitted logon hours for the user account are correct.
.
MessageId    = 0x1026
SymbolicName = IASP_ACCOUNT_RESTRICTION
Language     = English
Authentication failed because of a user account restriction. Check the user account properties for restrictions.
.
MessageId    = 0x1030
SymbolicName = IASP_NO_POLICY_MATCH
Language     = English
The connection attempt did not match any remote access policy.
.
MessageId    = 0x1031
SymbolicName = IASP_NO_CONNECTION_REQUEST_POLICY_MATCH
Language     = English
The connection attempt did not match any connection request policy.
.
MessageId    = 0x1040
SymbolicName = IASP_DIALIN_LOCKED_OUT
Language     = English
The user account exceeded the remote access account lockout count.
.
MessageId    = 0x1041
SymbolicName = IASP_DIALIN_DISABLED
Language     = English
The connection attempt failed because remote access permission for the user account was denied. To allow remote access, enable remote access permission for the user account, or, if the user account specifies that access is controlled through the matching remote access policy, enable remote access permission for that remote access policy.
.
MessageId    = 0x1042
SymbolicName = IASP_INVALID_AUTH_TYPE
Language     = English
The user attempted to use an authentication method that is not enabled on the matching remote access policy.
.
MessageId    = 0x1043
SymbolicName = IASP_INVALID_CALLING_STATION
Language     = English
The user attempted to connect through either a phone number or calling station that does not match the Caller ID listed for the user account.
.
MessageId    = 0x1044
SymbolicName = IASP_INVALID_DIALIN_HOURS
Language     = English
The user attempted to connect outside of permitted hours. Check the dial-in constraints for the matching remote access policy.
.
MessageId    = 0x1045
SymbolicName = IASP_INVALID_CALLED_STATION
Language     = English
The user attempted to connect through a phone number that did not match the restricted dial-in number. Check the dial-in constraints for the matching remote access policy.
.
MessageId    = 0x1046
SymbolicName = IASP_INVALID_PORT_TYPE
Language     = English
The user attempted to connect using a dial-in medium that did not match the restricted dial-in media. Check the dial-in constraints for the matching remote access policy.
.
MessageId    = 0x1047
SymbolicName = IASP_DIALIN_RESTRICTION
Language     = English
A dial-in constraint caused the connection attempt to fail. Check the dial-in constraints for the matching remote access policy.
.
MessageId    = 0x1048
SymbolicName = IASP_CPW_NOT_ALLOWED
Language     = English
The user cannot change his or her password because the change password option is not enabled for the matching remote access policy.
.
MessageId    = 0x1049
SymbolicName = IASP_INVALID_CERT_EKU
Language     = English
The user attempted to authenticate using a certificate with an Extended Key Usage or Issuance Policy that is not allowed by the matching remote access policy.
.
MessageId    = 0x1050
SymbolicName = IASP_NO_RECORD
Language     = English
The authentication or accounting record could not be written to the log file location. Ensure that the log file location is accessible, has available space, can be written to, and that the directory or SQL server name is valid.
.
MessageId    = 0x1060
SymbolicName = IASP_SESSION_TIMEOUT
Language     = English
The authentication request was not processed because the session timed out.
.
MessageId    = 0x1061
SymbolicName = IASP_UNEXPECTED_REQUEST
Language     = English
The authentication request was not processed because it contained a Remote Authentication Dial-In User Service (RADIUS) message that was not appropriate for the secure authentication transaction.
.
MessageId    = 0x1070
SymbolicName = IASP_PROXY_REJECT
Language     = English
The remote RADIUS (Remote Authentication Dial-In User Service) server did not process the authentication request.
.
MessageId    = 0x1071
SymbolicName = IASP_PROXY_UNKNOWN_GROUP
Language     = English
The remote RADIUS (Remote Authentication Dial-In User Service) server group does not exist.
.
MessageId    = 0x1072
SymbolicName = IASP_PROXY_UNKNOWN_SERVER
Language     = English
The authentication request could not be forwarded to the remote RADIUS (Remote Authentication Dial-In User Service) server because this server is no longer configured from the local server.
.
MessageId    = 0x1073
SymbolicName = IASP_PROXY_PACKET_TOO_LONG
Language     = English
The authentication request could not be forwarded to the remote RADIUS (Remote Authentication Dial-In User Service) server because the issued packet was too large.
.
MessageId    = 0x1074
SymbolicName = IASP_PROXY_SEND_ERROR
Language     = English
The authentication request could not be forwarded to the remote RADIUS (Remote Authentication Dial-In User Service) server because of a network problem.
.
MessageId    = 0x1075
SymbolicName = IASP_PROXY_TIMEOUT
Language     = English
The remote RADIUS (Remote Authentication Dial-In User Service) server did not respond.
.
MessageId    = 0x1076
SymbolicName = IASP_PROXY_MALFORMED_RESPONSE
Language     = English
The remote RADIUS (Remote Authentication Dial-In User Service) server returned an unreadable response.
.
MessageId    = 0x1100
SymbolicName = IASP_CRYPT_E_REVOKED
Language     = English
The certificate is revoked.
.
MessageId    = 0x1101
SymbolicName = IASP_CRYPT_E_NO_REVOCATION_DLL
Language     = English
No Dll or exported function was found to verify revocation.
.
MessageId    = 0x1102
SymbolicName = IASP_CRYPT_E_NO_REVOCATION_CHECK
Language     = English
The revocation function was unable to check revocation for the certificate.
.
MessageId    = 0x1103
SymbolicName = IASP_CRYPT_E_REVOCATION_OFFLINE
Language     = English
The revocation function was unable to check revocation because the revocation server was offline.
.
MessageId    = 0x1104
SymbolicName = IASP_SEC_E_MESSAGE_ALTERED
Language     = English
The message or signature supplied for verification has been altered
.
MessageId    = 0x1105
SymbolicName = IASP_SEC_E_NO_AUTHENTICATING_AUTHORITY
Language     = English
No authority could be contacted for authentication.
.
MessageId    = 0x1106
SymbolicName = IASP_SEC_E_INCOMPLETE_MESSAGE
Language     = English
The supplied message is incomplete.  The signature was not verified.
.
MessageId    = 0x1107
SymbolicName = IASP_SEC_E_INCOMPLETE_CREDENTIALS
Language     = English
The credentials supplied were not complete, and could not be verified. The context could not be initialized.
.
MessageId    = 0x1108
SymbolicName = IASP_SEC_E_TIME_SKEW
Language     = English
The clocks on the client and server machines are skewed.
.
MessageId    = 0x1109
SymbolicName = IASP_SEC_E_UNTRUSTED_ROOT
Language     = English
The certificate chain was issued by an authority that is not trusted.
.
MessageId    = 0x110A
SymbolicName = IASP_SEC_E_ILLEGAL_MESSAGE
Language     = English
The message received was unexpected or badly formatted.
.
MessageId    = 0x110B
SymbolicName = IASP_SEC_E_CERT_WRONG_USAGE
Language     = English
The certificate is not valid for the requested usage.
.
MessageId    = 0x110C
SymbolicName = IASP_SEC_E_CERT_EXPIRED
Language     = English
The received certificate has expired.
.
MessageId    = 0x110D
SymbolicName = IASP_SEC_E_ALGORITHM_MISMATCH
Language     = English
The client and server cannot communicate, because they do not possess a common algorithm.
.
MessageId    = 0x110E
SymbolicName = IASP_SEC_E_SMARTCARD_LOGON_REQUIRED
Language     = English
Smartcard logon is required and was not used.
.
MessageId    = 0x110F
SymbolicName = IASP_SEC_E_SHUTDOWN_IN_PROGRESS
Language     = English
A system shutdown is in progress.
.
MessageId    = 0x1110
SymbolicName = IASP_SEC_E_MULTIPLE_ACCOUNTS
Language     = English
The received certificate was mapped to multiple accounts.
.
MessageId    = 0x1111
SymbolicName = IASP_TRUST_E_PROVIDER_UNKNOWN
Language     = English
Unknown trust provider.
.
MessageId    = 0x1112
SymbolicName = IASP_TRUST_E_ACTION_UNKNOWN
Language     = English
The trust verification action specified is not supported by the specified trust provider.
.
MessageId    = 0x1113
SymbolicName = IASP_TRUST_E_SUBJECT_FORM_UNKNOWN
Language     = English
The form specified for the subject is not one supported or known by the specified trust provider.
.
MessageId    = 0x1114
SymbolicName = IASP_TRUST_E_SUBJECT_NOT_TRUSTED
Language     = English
The subject is not trusted for the specified action.
.
MessageId    = 0x1115
SymbolicName = IASP_TRUST_E_NOSIGNATURE
Language     = English
No signature was present in the subject.
.
MessageId    = 0x1116
SymbolicName = IASP_CERT_E_EXPIRED
Language     = English
A required certificate is not within its validity period when verifying against the current system clock or the timestamp in the signed file.
.
MessageId    = 0x1117
SymbolicName = IASP_CERT_E_VALIDITYPERIODNESTING
Language     = English
The validity periods of the certification chain do not nest correctly.
.
MessageId    = 0x1118
SymbolicName = IASP_CERT_E_ROLE
Language     = English
A certificate that can only be used as an end-entity is being used as a CA or visa versa.
.
MessageId    = 0x1119
SymbolicName = IASP_CERT_E_PATHLENCONST
Language     = English
A path length constraint in the certification chain has been violated.
.
MessageId    = 0x111A
SymbolicName = IASP_CERT_E_CRITICAL
Language     = English
A certificate contains an unknown extension that is marked 'critical'.
.
MessageId    = 0x111B
SymbolicName = IASP_CERT_E_PURPOSE
Language     = English
A certificate being used for a purpose other than the ones specified by its CA.
.
MessageId    = 0x111C
SymbolicName = IASP_CERT_E_ISSUERCHAINING
Language     = English
A parent of a given certificate in fact did not issue that child certificate.
.
MessageId    = 0x111D
SymbolicName = IASP_CERT_E_MALFORMED
Language     = English
A certificate is missing or has an empty value for an important field, such as a subject or issuer name.
.
MessageId    = 0x111E
SymbolicName = IASP_CERT_E_UNTRUSTEDROOT
Language     = English
A certificate chain processed, but terminated in a root certificate which is not trusted by the trust provider.
.
MessageId    = 0x111F
SymbolicName = IASP_CERT_E_CHAINING
Language     = English
A certificate chain could not be built to a trusted root authority.
.
MessageId    = 0x1120
SymbolicName = IASP_TRUST_E_FAIL
Language     = English
Generic trust failure.
.
MessageId    = 0x1121
SymbolicName = IASP_CERT_E_REVOKED
Language     = English
A certificate was explicitly revoked by its issuer.
.
MessageId    = 0x1122
SymbolicName = IASP_CERT_E_UNTRUSTEDTESTROOT
Language     = English
The certification path terminates with the test root which is not trusted with the current policy settings.
.
MessageId    = 0x1123
SymbolicName = IASP_CERT_E_REVOCATION_FAILURE
Language     = English
The revocation process could not continue - the certificate(s) could not be checked.
.
MessageId    = 0x1124
SymbolicName = IASP_CERT_E_CN_NO_MATCH
Language     = English
The certificate's CN name does not match the passed value.
.
MessageId    = 0x1125
SymbolicName = IASP_CERT_E_WRONG_USAGE
Language     = English
The certificate is not valid for the requested usage.
.
MessageId    = 0x1126
SymbolicName = IASP_TRUST_E_EXPLICIT_DISTRUST
Language     = English
The certificate was explicitly marked as untrusted by the user.
.
MessageId    = 0x1127
SymbolicName = IASP_CERT_E_UNTRUSTEDCA
Language     = English
A certification chain processed correctly, but one of the CA certificates is not trusted by the policy provider.
.
MessageId    = 0x1128
SymbolicName = IASP_CERT_E_INVALID_POLICY
Language     = English
The certificate has invalid policy.
.
MessageId    = 0x1129
SymbolicName = IASP_CERT_E_INVALID_NAME
Language     = English
The certificate has an invalid name. The name is not included in the permitted list or is explicitly excluded.
.
MessageId    = 0x112A
SymbolicName = IASP_SEC_E_PKINIT_NAME_MISMATCH
Language     = English
The client cert name does not matches the user name or the KDC name is incorrect.
.
MessageId    = 0x112B
SymbolicName = IASP_SEC_E_OUT_OF_SEQUENCE
Language     = English
The message supplied for verification is out of sequence
.
MessageId    = 0x112C
SymbolicName = IASP_SEC_E_NO_CREDENTIALS
Language     = English
No credentials are available in the security package
.