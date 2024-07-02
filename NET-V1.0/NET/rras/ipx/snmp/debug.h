#ifndef _SNMP_MIPXMIB_
#define _SNMP_MIPXMIB_

#define DBG_LOAD				0x00000001
#define DBG_IPXBASE				0x00000010
#define DBG_IPXINTERFACES		0x00000020
#define DBG_DESTTABLE			0x00000040
#define DBG_STATICROUTES		0x00000080
#define DBG_SERVERTABLE			0x00000100
#define DBG_STATICSERVERS		0x00000200

#define DBG_RIPSAPBASE			0x00001000
#define DBG_RIPINTERFACES		0x00002000
#define DBG_SAPINTERFACES		0x00004000

#define DBG_NIPXBASICSYSENTRY	0x00010000
#define DBG_NIPXADVSYSENTRY		0x00020000
#define DBG_NIPXCIRCENTRY		0x00040000
#define DBG_NIPXDESTENTRY		0x00080000
#define DBG_NIPXSTATICRTENTRY	0x00100000
#define DBG_NIPXSERVENTRY		0x00200000
#define DBG_NIPXDESTSERVENTRY	0x00400000
#define DBG_NIPXSTATICSERVENTRY	0x00800000

#define DEF_DBGLEVEL			0x00000001

#if DBG

	extern	DWORD	DbgLevel;
	#define DbgTrace(level,args)	\
		do {						\
			if (level&&DbgLevel)	\
				DbgPrint args;		\
		}							\
		while (0)
#else	// if DBG

	#define DbgTrace(level,args)

#endif	// if DBG

#endif

