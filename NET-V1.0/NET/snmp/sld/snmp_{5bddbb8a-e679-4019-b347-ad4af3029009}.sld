<?xml version="1.0" encoding="UTF-16"?>
<!DOCTYPE DCARRIER SYSTEM "mantis.dtd" [
<!-- RegKey registry types (map to REG_SZ etc) -->
<!ENTITY RegTypeNone                        "0" >
<!ENTITY RegTypeSz                          "1" >
<!ENTITY RegTypeExpandSz                    "2" >
<!ENTITY RegTypeBinary                      "3" >
<!ENTITY RegTypeDword                       "4" >
<!ENTITY RegTypeDwordBigEndian              "5" >
<!ENTITY RegTypeLink                        "6" >
<!ENTITY RegTypeMultiSz                     "7" >
<!ENTITY RegTypeResourceList                "8" >
<!ENTITY RegTypeFullResourceDescriptor      "9" >
<!ENTITY RegTypeResourceRequirementsList    "10" >
<!ENTITY RegTypeQword                       "11" >

<!-- RegKey registry operations -->
<!ENTITY RegOpWrite               "1" >
<!ENTITY RegOpDelete              "2" >
<!ENTITY RegOpEdit                "3" >

<!-- RegKey registry conditionals -->
<!ENTITY RegCondAlways            "1" >
<!ENTITY RegCondIfExists          "2" >
<!ENTITY RegCondIfNotExists       "3" >

<!-- RawDep dependency types -->
<!ENTITY RawDepNone               "None" >
<!ENTITY RawDepCLSID              "CLSID" >
<!ENTITY RawDepFile               "File" >
<!ENTITY RawDepRegKey             "RegKey" >
<!ENTITY RawDepRegValue           "RegValue" >
<!ENTITY RawDepRegPath            "RegPath" >
]>
<DCARRIER CarrierRevision="1">
	<TOOLINFO ToolName="iCat"><![CDATA[<?xml version="1.0"?>
<!DOCTYPE TOOL SYSTEM "file://mess/icat/tool.dtd">
<TOOL>
	<CREATED><NAME>iCat</NAME><VSGUID>{f802f157-4623-426a-8b39-ac2eb4332c74}</VSGUID><VERSION>1.0.0.244</VERSION><BUILD>244</BUILD><DATE>5/8/2000</DATE></CREATED><LASTSAVED><NAME>iCat</NAME><VSGUID>{97b86ee0-259c-479f-bc46-6cea7ef4be4d}</VSGUID><VERSION>1.0.0.452</VERSION><BUILD>452</BUILD><DATE>4/9/2001</DATE></LASTSAVED></TOOL>
]]></TOOLINFO><COMPONENT ComponentVSGUID="{5BDDBB8A-E679-4019-B347-AD4AF3029009}" ComponentVIGUID="{64AA6675-53E1-41B1-BD51-52AA359A52A9}" PlatformGUID="{B784E719-C196-4DDB-B358-D9254426C38D}" RepositoryVSGUID="{8E0BE9ED-7649-47F3-810B-232D36C430B4}" Revision="12" Visibility="1000" MultiInstance="False" Released="1" Editable="True" HTMLFinal="False"><HELPCONTEXT src="H:\nt.pri\net\snmp\sld\_snmp_component_description.htm">&lt;!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN"&gt;
&lt;HTML DIR="LTR"&gt;&lt;HEAD&gt;
&lt;META HTTP-EQUIV="Content-Type" Content="text/html; charset=Windows-1252"&gt;
&lt;TITLE&gt;SNMP Component Description&lt;/TITLE&gt;
&lt;style type="text/css"&gt;@import url(td.css);&lt;/style&gt;&lt;/HEAD&gt;
&lt;BODY TOPMARGIN="0"&gt;
&lt;H1&gt;&lt;A NAME="_snmp_component_description"&gt;&lt;/A&gt;&lt;SUP&gt;&lt;/SUP&gt;SNMP Component Description&lt;/H1&gt;

&lt;P&gt;This component supports the Simple Network Management Protocol (SNMP). SNMP is an agent service that provides management systems with information about activities that occur at the Internet Protocol (IP) network layer. The SNMP agent monitors network traffic, and retrieves and updates local management information based on the requests from the SNMP manager. The agent also notifies registered managers with traps when significant events occur.&lt;/P&gt;

&lt;H1&gt;Component Configuration&lt;/H1&gt;

&lt;P&gt;By default, this component accepts SNMP &lt;B&gt;Get&lt;/B&gt;, &lt;B&gt;GetNext&lt;/B&gt; or &lt;B&gt;GetBulk&lt;/B&gt; requests within the public community name. The SNMP snap-in configuration tool can be used to change the configuration of this component. &lt;/P&gt;

&lt;/BODY&gt;
&lt;/HTML&gt;
</HELPCONTEXT><DISPLAYNAME>SNMP</DISPLAYNAME><VERSION>1.0</VERSION><DESCRIPTION>SNMP (Simple Network Management Protocol) provides a method of managing nework nodes from a centrally located host.</DESCRIPTION><COPYRIGHT>2000 Microsoft Corp.</COPYRIGHT><VENDOR>Microsoft Corp.</VENDOR><OWNERS>frankli</OWNERS><AUTHORS>frankli</AUTHORS><DATECREATED>5/8/2000</DATECREATED><DATEREVISED>4/9/2001</DATEREVISED><RESOURCE Name="File:&quot;%11%&quot;,&quot;snmp.exe&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">snmp.exe</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>Snmp.exe</DISPLAYNAME><DESCRIPTION>SNMP Service</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;snmpapi.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">snmpapi.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>snmpapi.dll</DISPLAYNAME><DESCRIPTION>common helper APIs for SNMP</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;snmpmib.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">snmpmib.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>snmpmib.dll (SNMP Subagent)</DISPLAYNAME><DESCRIPTION>SNMP MIB group of RFC 1213.</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;hostmib.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">hostmib.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>hostmib.dll (SNMP Subagent)</DISPLAYNAME><DESCRIPTION>Contains object-types for monitoring and managing host resources per RFC 1514.</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;lmmib2.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">lmmib2.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>lmmib2.dll ((SNMP Subagent))</DISPLAYNAME><DESCRIPTION>LAN Manager MIB-II covers workstation and server services.</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;mib.bin&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">mib.bin</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>mib.bin</DISPLAYNAME><DESCRIPTION>Used by the Management API (Mgmtapi.dll). Maps text-based object names to numerical object identifiers.</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;mgmtapi.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">mgmtapi.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>mgmtapi.dll</DISPLAYNAME><DESCRIPTION>SNMP Management API is a simple and limited API used by SNMP management software applications.</DESCRIPTION></RESOURCE><RESOURCE Name="File(819):&quot;%11%&quot;,&quot;wsnmp32.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">wsnmp32.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>wsnmp32.dll</DISPLAYNAME><DESCRIPTION>WinSNMP API provides a set of functions for encoding, decoding, sending, and receiving SNMP messages.</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;snmptrap.exe&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">snmptrap.exe</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>SnmpTrap.exe</DISPLAYNAME><DESCRIPTION>SNMP Trap Service</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;inetmib1.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">inetmib1.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>inetmib1.dll</DISPLAYNAME><DESCRIPTION>Management Information Base (MIB-II) provides a simple, workable architecture and system for managing TCP/IP-based internets. (RFC 1213)</DESCRIPTION></RESOURCE><RESOURCE Name="File:&quot;%11%&quot;,&quot;snmpsnap.dll&quot;" ResTypeVSGUID="{E66B49F6-4A35-4246-87E8-5C1A468315B5}" BuildTypeMask="819"><PROPERTY Name="DstPath" Format="String">%11%</PROPERTY><PROPERTY Name="DstName" Format="String">snmpsnap.dll</PROPERTY><PROPERTY Name="SrcFileSize" Format="Integer">0</PROPERTY><PROPERTY Name="NoExpand" Format="Boolean">0</PROPERTY><DISPLAYNAME>SnmpSnap.dll</DISPLAYNAME><DESCRIPTION>SNMP snap-in</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey(819):&quot;HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters&quot;,&quot;EnableAuthenticationTraps&quot;" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters</PROPERTY><PROPERTY Name="ValueName" Format="String">EnableAuthenticationTraps</PROPERTY><PROPERTY Name="RegValue" Format="Integer">1</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">3</PROPERTY><DISPLAYNAME>EnableAuthenticationTraps</DISPLAYNAME><DESCRIPTION>Enables and disables authentication traps.</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\NameResolutionRetries" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters</PROPERTY><PROPERTY Name="ValueName" Format="String">NameResolutionRetries</PROPERTY><PROPERTY Name="RegValue" Format="Integer">16</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\PermittedManagers\" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\PermittedManagers</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>PermittedManagers</DISPLAYNAME><DESCRIPTION>Stores the names of hosts that are permitted to send requests to an SNMP agent. (For example, 1 REG_SZ Host01. In this example, the host, Host01, can send requests to an agent. )</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\RFC1156Agent\sysContact" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\RFC1156Agent</PROPERTY><PROPERTY Name="ValueName" Format="String">sysContact</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>Contact</DISPLAYNAME><DESCRIPTION>The contact person for the administrator of the local computer.</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\RFC1156Agent\sysLocation" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\RFC1156Agent</PROPERTY><PROPERTY Name="ValueName" Format="String">sysLocation</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>Location</DISPLAYNAME><DESCRIPTION>The contact location for the administrator of the local computer.</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\RFC1156Agent\sysServices" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\RFC1156Agent</PROPERTY><PROPERTY Name="ValueName" Format="String">sysServices</PROPERTY><PROPERTY Name="RegValue" Format="Integer">76</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>Agent Properties</DISPLAYNAME><DESCRIPTION>Choices of Agent Properties are: Physical, Applications, Datalink and Subnet, Internet, End-to-End</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\TrapConfiguration\" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\TrapConfiguration</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>Traps</DISPLAYNAME><DESCRIPTION>The trap destinations for each community name.</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ValidCommunities\public" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ValidCommunities</PROPERTY><PROPERTY Name="ValueName" Format="String">public</PROPERTY><PROPERTY Name="RegValue" Format="Integer">4</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>Security</DISPLAYNAME><DESCRIPTION>Accepted community names and rights.</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\RFC1156Agent\CurrentVersion\Pathname" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\RFC1156Agent\CurrentVersion</PROPERTY><PROPERTY Name="ValueName" Format="String">Pathname</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\inetmib1.dll</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\LANManagerMIB2Agent\CurrentVersion\Pathname" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\LANManagerMIB2Agent\CurrentVersion</PROPERTY><PROPERTY Name="ValueName" Format="String">Pathname</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\lmmib2.dll</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HostMIB\CurrentVersion\Pathname" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HostMIB\CurrentVersion</PROPERTY><PROPERTY Name="ValueName" Format="String">Pathname</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\hostmib.dll</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\SNMPMIB\CurrentVersion\Pathname" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\SNMPMIB\CurrentVersion</PROPERTY><PROPERTY Name="ValueName" Format="String">Pathname</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\snmpmib.dll</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\RFC1156Agent\CurrentVersion\Parameters\TrapPollTimeMilliSecs" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\RFC1156Agent\CurrentVersion\Parameters</PROPERTY><PROPERTY Name="ValueName" Format="String">TrapPollTimeMilliSecs</PROPERTY><PROPERTY Name="RegValue" Format="Integer">15000</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMP\EventMessageFile" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">EventMessageFile</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\snmp.exe</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>EventMessageFile of SNMP.EXE</DISPLAYNAME><DESCRIPTION>Register SNMP.EXE as an event source</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMP\TypesSupported" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">TypesSupported</PROPERTY><PROPERTY Name="RegValue" Format="Integer">7</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>TypesSupported by SNMP.EXE</DISPLAYNAME><DESCRIPTION>Register SNMP.EXE as an event source</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMPTRAP\EventMessageFile" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">EventMessageFile</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\snmptrap.exe</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>EventMessageFile of SNMPTRAP.EXE</DISPLAYNAME><DESCRIPTION>Register SNMPTRAP.EXE as an event source</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMPTRAP\TypesSupported" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Eventlog\System\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">TypesSupported</PROPERTY><PROPERTY Name="RegValue" Format="Integer">7</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY><DISPLAYNAME>TypesSupported by SNMPTRAP.EXE</DISPLAYNAME><DESCRIPTION>Register SNMPTRAP.EXE as an event source</DESCRIPTION></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\DependOnGroup" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">DependOnGroup</PROPERTY><PROPERTY Name="RegType" Format="Integer">7</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\DependOnService" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">DependOnService</PROPERTY><PROPERTY Name="RegValue" Format="Multi">4500760065006E0074004C006F0067000000</PROPERTY><PROPERTY Name="RegType" Format="Integer">7</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Description" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">Description</PROPERTY><PROPERTY Name="RegValue" Format="String">Includes agents that monitor the activity in network devices and report to the network console workstation.</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\DisplayName" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">DisplayName</PROPERTY><PROPERTY Name="RegValue" Format="String">SNMP Service</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\ErrorControl" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">ErrorControl</PROPERTY><PROPERTY Name="RegValue" Format="Integer">1</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\ImagePath" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">ImagePath</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\snmp.exe</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\ObjectName" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">ObjectName</PROPERTY><PROPERTY Name="RegValue" Format="String">LocalSystem</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Start" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">Start</PROPERTY><PROPERTY Name="RegValue" Format="Integer">2</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Type" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP</PROPERTY><PROPERTY Name="ValueName" Format="String">Type</PROPERTY><PROPERTY Name="RegValue" Format="Integer">16</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\DependOnGroup" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">DependOnGroup</PROPERTY><PROPERTY Name="RegType" Format="Integer">7</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\DependOnService" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">DependOnService</PROPERTY><PROPERTY Name="RegValue" Format="Multi">4500760065006E0074004C006F0067000000</PROPERTY><PROPERTY Name="RegType" Format="Integer">7</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\Description" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">Description</PROPERTY><PROPERTY Name="RegValue" Format="String">Receives trap messages generated by local or remote SNMP agents and forwards the messages to SNMP management programs running on this computer.</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\DisplayName" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">DisplayName</PROPERTY><PROPERTY Name="RegValue" Format="String">SNMP Trap Service</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\ErrorControl" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">ErrorControl</PROPERTY><PROPERTY Name="RegValue" Format="Integer">1</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\ImagePath" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">ImagePath</PROPERTY><PROPERTY Name="RegValue" Format="String">%SystemRoot%\System32\snmptrap.exe</PROPERTY><PROPERTY Name="RegType" Format="Integer">2</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\Start" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">Start</PROPERTY><PROPERTY Name="RegValue" Format="Integer">3</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RegKey:HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP\Type" ResTypeVSGUID="{2C10DB69-39AB-48a4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">Type</PROPERTY><PROPERTY Name="RegValue" Format="Integer">16</PROPERTY><PROPERTY Name="RegType" Format="Integer">4</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE Name="RawDep:&quot;RawFile&quot;,&quot;ws2_32.dll&quot;" ResTypeVSGUID="{90D8E195-E710-4af6-B667-B1805FFC9B8F}" BuildTypeMask="819"><PROPERTY Name="RawType" Format="String">File</PROPERTY><PROPERTY Name="Value" Format="String">ws2_32.dll</PROPERTY></RESOURCE><RESOURCE Name="RawDep:&quot;RawFile&quot;,&quot;iphlpapi.dll&quot;" ResTypeVSGUID="{90D8E195-E710-4af6-B667-B1805FFC9B8F}" BuildTypeMask="819"><PROPERTY Name="RawType" Format="String">File</PROPERTY><PROPERTY Name="Value" Format="String">iphlpapi.dll</PROPERTY></RESOURCE><RESOURCE Name="RawDep:&quot;RawFile&quot;,&quot;mmc.exe&quot;" ResTypeVSGUID="{90D8E195-E710-4af6-B667-B1805FFC9B8F}" BuildTypeMask="819"><PROPERTY Name="RawType" Format="String">File</PROPERTY><PROPERTY Name="Value" Format="String">mmc.exe</PROPERTY></RESOURCE><RESOURCE Name="RawDep:&quot;RawFile&quot;,&quot;netapi32.dll&quot;" ResTypeVSGUID="{90D8E195-E710-4af6-B667-B1805FFC9B8F}" BuildTypeMask="819"><PROPERTY Name="RawType" Format="String">File</PROPERTY><PROPERTY Name="Value" Format="String">netapi32.dll</PROPERTY></RESOURCE><RESOURCE Name="RawDep:&quot;RawFile&quot;,&quot;eventlog.dll&quot;" ResTypeVSGUID="{90D8E195-E710-4af6-B667-B1805FFC9B8F}" BuildTypeMask="819"><PROPERTY Name="RawType" Format="String">File</PROPERTY><PROPERTY Name="Value" Format="String">eventlog.dll</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{2C10DB69-39AB-48A4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Name="RegKey(819):&quot;HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents&quot;,&quot;lmmib2&quot;" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents</PROPERTY><PROPERTY Name="ValueName" Format="String">lmmib2</PROPERTY><PROPERTY Name="RegValue" Format="String">SOFTWARE\Microsoft\LANManagerMIB2Agent\CurrentVersion</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{2C10DB69-39AB-48A4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Name="RegKey(819):&quot;HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents&quot;,&quot;inetmib1&quot;" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents</PROPERTY><PROPERTY Name="ValueName" Format="String">inetmib1</PROPERTY><PROPERTY Name="RegValue" Format="String">SOFTWARE\Microsoft\RFC1156Agent\CurrentVersion</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{2C10DB69-39AB-48A4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Name="RegKey(819):&quot;HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents&quot;,&quot;snmpmib&quot;" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents</PROPERTY><PROPERTY Name="ValueName" Format="String">snmpmib</PROPERTY><PROPERTY Name="RegValue" Format="String">SOFTWARE\Microsoft\SNMPMIB\CurrentVersion</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{2C10DB69-39AB-48A4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Name="RegKey(819):&quot;HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents&quot;,&quot;hostmib&quot;" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMP\Parameters\ExtensionAgents</PROPERTY><PROPERTY Name="ValueName" Format="String">hostmib</PROPERTY><PROPERTY Name="RegValue" Format="String">SOFTWARE\Microsoft\HostMIB\CurrentVersion</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{2C10DB69-39AB-48A4-A83F-9AB3ACBA7C45}" BuildTypeMask="819" Name="RegKey(819):&quot;HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP&quot;,&quot;ObjectName&quot;" Localize="0"><PROPERTY Name="KeyPath" Format="String">HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SNMPTRAP</PROPERTY><PROPERTY Name="ValueName" Format="String">ObjectName</PROPERTY><PROPERTY Name="RegValue" Format="String">NT AUTHORITY\LocalService</PROPERTY><PROPERTY Name="RegType" Format="Integer">1</PROPERTY><PROPERTY Name="RegOp" Format="Integer">1</PROPERTY><PROPERTY Name="RegCond" Format="Integer">1</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{90D8E195-E710-4AF6-B667-B1805FFC9B8F}" BuildTypeMask="819" Name="RawDep(819):&quot;File&quot;,&quot;regsvc.dll&quot;"><PROPERTY Name="RawType" Format="String">File</PROPERTY><PROPERTY Name="Value" Format="String">regsvc.dll</PROPERTY></RESOURCE><RESOURCE ResTypeVSGUID="{322D2CA9-219E-4380-989B-12E8A830DFFA}" BuildTypeMask="819" Name="FBRegDLL(819):&quot;%11%\snmpsnap.dll&quot;" Localize="0"><PROPERTY Name="Arguments" Format="String"></PROPERTY><PROPERTY Name="DLLEntryPoint" Format="String"></PROPERTY><PROPERTY Name="DLLInstall" Format="Boolean">False</PROPERTY><PROPERTY Name="DLLRegister" Format="Boolean">True</PROPERTY><PROPERTY Name="FilePath" Format="String">%11%\snmpsnap.dll</PROPERTY><PROPERTY Name="Flags" Format="Integer">0</PROPERTY><PROPERTY Name="Timeout" Format="Integer">0</PROPERTY><DISPLAYNAME>SNMP snapin</DISPLAYNAME><DESCRIPTION>Self registration of SNMP snapin</DESCRIPTION></RESOURCE><GROUPMEMBER GroupVSGUID="{388249D2-1897-44ff-86F2-E159A27AA037}"/><DEPENDENCY Class="Include" Type="All" DependOnGUID="{7E34D737-6FF4-4EB5-8DF6-97B321FEC915}"/><DEPENDENCY Class="Include" Type="All" DependOnGUID="{952A1521-0BE7-47FC-9DE9-438D316014A0}"/></COMPONENT></DCARRIER>
