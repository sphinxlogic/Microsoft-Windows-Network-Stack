

NTSTATUS ah_nullinit (PALGO_STATE, ULONG);
NTSTATUS ah_nullupdate (PALGO_STATE, PUCHAR, ULONG);
NTSTATUS ah_nullfinish (PALGO_STATE, PUCHAR, ULONG);

NTSTATUS ah_hmacmd5init (PALGO_STATE, ULONG);
NTSTATUS ah_hmacmd5update (PALGO_STATE, PUCHAR, ULONG);
NTSTATUS ah_hmacmd5finish (PALGO_STATE, PUCHAR, ULONG);

NTSTATUS ah_hmacshainit (PALGO_STATE, ULONG);
NTSTATUS ah_hmacshaupdate (PALGO_STATE, PUCHAR, ULONG);
NTSTATUS ah_hmacshafinish (PALGO_STATE, PUCHAR, ULONG);

