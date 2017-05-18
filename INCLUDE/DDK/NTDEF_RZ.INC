
; FASM SOURCE FILE
; http://flatassembler.net

; written by @L.CHEMIST (Andrey A. Meshkov)
; maalchemist@gmail.com
; maa-mail@yandex.ru

; ------------------------------------------------------------------------------

TYPEDEF CCHAR, char
TYPEDEF CSHORT, short

TYPEDEF NTSTATUS, LONG
TYPEDEF PNTSTATUS, PVOID

struct LARGE_INTEGER
    union ; LARGE_INTEGER
        struct
            LowPart  ULONG ?
            HighPart LONG ?
        ends
        struct ; u
            u.LowPart  ULONG ?
            u.HighPart LONG ?
        ends ; u
        QuadPart LONGLONG ?
    ends
ends
TYPEDEF PLARGE_INTEGER, PVOID

TYPEDEF PHYSICAL_ADDRESS, LARGE_INTEGER
TYPEDEF PPHYSICAL_ADDRESS, PVOID

TYPEDEF PUNICODE_STRING, PVOID
TYPEDEF PCUNICODE_STRING, PVOID
struct UNICODE_STRING
    Length        USHORT ?
    MaximumLength USHORT ?
                  PADDING 4, 0
    Buffer        PWSTR ?
ends
UNICODE_NULL = (0) ; // winnt

TYPEDEF PLIST_ENTRY, PVOID
TYPEDEF PRLIST_ENTRY, PVOID
struct LIST_ENTRY
    Flink PLIST_ENTRY ?
    Blink PLIST_ENTRY ?
ends

TYPEDEF KIRQL, UCHAR
TYPEDEF PKIRQL, PVOID

; ------------------------------------------------------------------------------
