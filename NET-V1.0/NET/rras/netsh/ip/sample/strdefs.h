/*++

Copyright (c) 1999, Microsoft Corporation

Module Name:

    sample\strdefs.h

Abstract:

    The file contains definitions for strings defined in resource file.

--*/

#define IPSAMPLELOG_BASE                44000

#define HLP_INSTALL                     (IPSAMPLELOG_BASE + 1)
#define HLP_INSTALL_EX                  (IPSAMPLELOG_BASE + 2)
#define HLP_UNINSTALL                   (IPSAMPLELOG_BASE + 3)
#define HLP_UNINSTALL_EX                (IPSAMPLELOG_BASE + 4)
#define HLP_HELP                        (IPSAMPLELOG_BASE + 5)
#define HLP_HELP_EX                     (IPSAMPLELOG_BASE + 6)
#define HLP_DUMP                        (IPSAMPLELOG_BASE + 7)
#define HLP_DUMP_EX                     (IPSAMPLELOG_BASE + 8)

#define HLP_GROUP_ADD                   (IPSAMPLELOG_BASE + 9)
#define HLP_GROUP_DELETE                (IPSAMPLELOG_BASE + 10)
#define HLP_GROUP_SET                   (IPSAMPLELOG_BASE + 11)
#define HLP_GROUP_SHOW                  (IPSAMPLELOG_BASE + 12)

#define HLP_SAMPLE_ADD_IF               (IPSAMPLELOG_BASE + 13)
#define HLP_SAMPLE_ADD_IF_EX            (IPSAMPLELOG_BASE + 14)

#define HLP_SAMPLE_DEL_IF               (IPSAMPLELOG_BASE + 15)
#define HLP_SAMPLE_DEL_IF_EX            (IPSAMPLELOG_BASE + 16)

#define HLP_SAMPLE_SET_IF               (IPSAMPLELOG_BASE + 17)
#define HLP_SAMPLE_SET_IF_EX            (IPSAMPLELOG_BASE + 18)
#define HLP_SAMPLE_SET_GLOBAL           (IPSAMPLELOG_BASE + 21)
#define HLP_SAMPLE_SET_GLOBAL_EX        (IPSAMPLELOG_BASE + 22)

#define HLP_SAMPLE_SHOW_IF              (IPSAMPLELOG_BASE + 23)
#define HLP_SAMPLE_SHOW_IF_EX           (IPSAMPLELOG_BASE + 24)
#define HLP_SAMPLE_SHOW_GLOBAL          (IPSAMPLELOG_BASE + 27)
#define HLP_SAMPLE_SHOW_GLOBAL_EX       (IPSAMPLELOG_BASE + 28)

#define HLP_SAMPLE_MIB_SHOW_STATS       (IPSAMPLELOG_BASE + 29)
#define HLP_SAMPLE_MIB_SHOW_STATS_EX    (IPSAMPLELOG_BASE + 30)
#define HLP_SAMPLE_MIB_SHOW_IFSTATS     (IPSAMPLELOG_BASE + 31)
#define HLP_SAMPLE_MIB_SHOW_IFSTATS_EX  (IPSAMPLELOG_BASE + 32)
#define HLP_SAMPLE_MIB_SHOW_IFBINDING       (IPSAMPLELOG_BASE + 58)
#define HLP_SAMPLE_MIB_SHOW_IFBINDING_EX    (IPSAMPLELOG_BASE + 59)

#define DMP_SAMPLE_HEADER               (IPSAMPLELOG_BASE + 33)
#define DMP_SAMPLE_FOOTER               (IPSAMPLELOG_BASE + 34)
#define DMP_SAMPLE_INTERFACE_HEADER     (IPSAMPLELOG_BASE + 35)

#define MSG_SAMPLE_GLOBAL_CONFIG        (IPSAMPLELOG_BASE + 36)
#define MSG_SAMPLE_IF_CONFIG            (IPSAMPLELOG_BASE + 37)
#define MSG_SAMPLE_IF_CONFIG_HEADER     (IPSAMPLELOG_BASE + 70)
#define MSG_SAMPLE_IF_CONFIG_ENTRY      (IPSAMPLELOG_BASE + 71)
#define MSG_SAMPLE_MIB_GS               (IPSAMPLELOG_BASE + 39)
#define MSG_SAMPLE_MIB_IFSTATS          (IPSAMPLELOG_BASE + 41)
#define MSG_SAMPLE_MIB_IFSTATS_HEADER   (IPSAMPLELOG_BASE + 72)
#define MSG_SAMPLE_MIB_IFSTATS_ENTRY    (IPSAMPLELOG_BASE + 73)
#define MSG_SAMPLE_MIB_IFBINDING        (IPSAMPLELOG_BASE + 56)
#define MSG_SAMPLE_MIB_IFBINDING_ADDR   (IPSAMPLELOG_BASE + 57)
#define MSG_SAMPLE_MIB_IFBINDING_HEADER (IPSAMPLELOG_BASE + 74)
#define MSG_SAMPLE_MIB_IFBINDING_ENTRY  (IPSAMPLELOG_BASE + 75)

#define STRING_PROTO_SAMPLE             (IPSAMPLELOG_BASE + 60)
#define STRING_LOGGING_NONE             (IPSAMPLELOG_BASE + 42)
#define STRING_LOGGING_ERROR            (IPSAMPLELOG_BASE + 43)
#define STRING_LOGGING_WARN             (IPSAMPLELOG_BASE + 44)
#define STRING_LOGGING_INFO             (IPSAMPLELOG_BASE + 45)
#define STRING_UNKNOWN                  (IPSAMPLELOG_BASE + 46)
#define STRING_BOUND                    (IPSAMPLELOG_BASE + 62)
#define STRING_ACTIVE                   (IPSAMPLELOG_BASE + 63)
#define STRING_UNBOUND                  (IPSAMPLELOG_BASE + 64)
#define STRING_INACTIVE                 (IPSAMPLELOG_BASE + 65)

#define EMSG_PROTO_NO_GLOBAL_CONFIG     (IPSAMPLELOG_BASE + 47)
#define EMSG_PROTO_NO_IF_CONFIG         (IPSAMPLELOG_BASE + 48)
#define EMSG_INTERFACE_EXISTS           (IPSAMPLELOG_BASE + 49)
#define EMSG_PROTO_NOT_INSTALLED        (IPSAMPLELOG_BASE + 50)
#define EMSG_PROTO_INSTALLED            (IPSAMPLELOG_BASE + 51)
#define EMSG_BAD_OPTION_VALUE           (IPSAMPLELOG_BASE + 52)
#define EMSG_RRAS_ERROR                 (IPSAMPLELOG_BASE + 53)
#define EMSG_NO_ENTRIES                 (IPSAMPLELOG_BASE + 54)

#define HLP_HELP1                       HLP_HELP
#define HLP_HELP1_EX                    HLP_HELP_EX
#define HLP_HELP2                       HLP_HELP
#define HLP_HELP2_EX                    HLP_HELP_EX
