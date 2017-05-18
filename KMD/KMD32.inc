
struc COUNTED_UNICODE_STR s {
.Length dw .End-.String
.MaximumLength dw .End-.String
.Buffer dd .String
.String du s
.End:
}

;ntdef.inc
;
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;  Status values are 32 bit values layed out as follows:
;
;   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;  +---+-+-------------------------+-------------------------------+
;  |Sev|C|       Facility          |               Code            |
;  +---+-+-------------------------+-------------------------------+
;
;  where
;
;      Sev - is the severity code
;
;          00 - Success
;          01 - Informational
;          10 - Warning
;          11 - Error
;
;      C - is the Customer code flag
;
;      Facility - is the facility code
;
;      Code - is the facility's status code
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

APPLICATION_ERROR_MASK       equ 020000000h
ERROR_SEVERITY_SUCCESS       equ 000000000h
ERROR_SEVERITY_INFORMATIONAL equ 040000000h
ERROR_SEVERITY_WARNING       equ 080000000h
ERROR_SEVERITY_ERROR         equ 0C0000000h

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Large (64-bit) integer types and operations
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc TIME {
        label .LowPart  DWORD at 0
        label .LowTime  DWORD at 0

        label .HighPart DWORD at 4
        label .HighTime DWORD at 4

        .QuadPart     dq   ?    ; signed
}
struct TIME


;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Locally Unique Identifier
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc LUID {
        .LowPart         dd   ?
        .HighPart        dd   ?
}
struct LUID

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Physical address.
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc PHYSICAL_ADDRESS {
        ;struct
                .LowPart    dd ?
                .HighPart   dd ?
        ;ends

        label .QuadPart  qword at 0    ; signed
}
struct PHYSICAL_ADDRESS

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Define operations to logically shift an int64 by 0..31 bits and to multiply
; 32-bits by 32-bits to form a 64-bit product.
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Event type
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _EVENT_TYPE {
        NotificationEvent               equ 0
        SynchronizationEvent    equ 1

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Timer type
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _TIMER_TYPE {
        NotificationTimer               equ 0
        SynchronizationTimer    equ 1

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Wait type
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _WAIT_TYPE {
        WaitAll equ 0
        WaitAny equ 1


;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Counted String
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc STRING STRUCT {
        .Length          dw    ?
        .MaximumLength   dw    ?
        .Buffer          dd    ?       ; PCHAR
}
struct STRING


;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Valid values for the Attributes field
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

OBJ_INHERIT             equ 00000002h
OBJ_PERMANENT           equ 00000010h
OBJ_EXCLUSIVE           equ 00000020h
OBJ_CASE_INSENSITIVE    equ 00000040h
OBJ_OPENIF              equ 00000080h
OBJ_OPENLINK            equ 00000100h
OBJ_KERNEL_HANDLE       equ 00000200h
OBJ_VALID_ATTRIBUTES    equ 000003F2h

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Object Attributes structure
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc OBJECT_ATTRIBUTES {                ; sizeof = 18h
        .Length                           dd                   ? ; original name Length
        .RootDirectory                    dd                   ?
        .ObjectName                       dd                   ?
        .Attributes                       dd                   ?
        .SecurityDescriptor               dd                   ? ; Points to type SECURITY_DESCRIPTOR
        .SecurityQualityOfService         dd                   ? ; Points to type SECURITY_QUALITY_OF_SERVICE
}
struct OBJECT_ATTRIBUTES


;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Constants
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


FALSE   equ 0
TRUE    equ 1

NULL    equ 0
NULL64  equ 0

MINCHAR     equ 080h
MAXCHAR     equ 07fh
MINSHORT    equ 08000h
MAXSHORT    equ 07fffh
MINLONG     equ 080000000h
MAXLONG     equ 07fffffffh
MAXUCHAR    equ 0ffh
MAXUSHORT   equ 0ffffh
MAXULONG    equ 0ffffffffh

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Product types
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _NT_PRODUCT_TYPE {
    NtProductWinNt              equ 1
    NtProductLanManNt   equ 2
    NtProductServer             equ 3

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; the bit mask, SharedUserData->SuiteMask, is a ULONG
; so there can be a maximum of 32 entries in this enum.
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _SUITE_TYPE {
    SmallBusiness                       equ 0
    Enterprise                          equ 1
    BackOffice                          equ 2
    CommunicationServer         equ 3
    TerminalServer                      equ 4
    SmallBusinessRestricted     equ 5
    EmbeddedNT                          equ 6
    DataCenter                          equ 7
    SingleUserTS                        equ 8
    Personal                            equ 9
    ServerAppliance                     equ 10
    MaxSuiteType                        equ 11

VER_SERVER_NT                       equ 80000000h
VER_WORKSTATION_NT                  equ 40000000h
VER_SUITE_SMALLBUSINESS             equ 00000001h
VER_SUITE_ENTERPRISE                equ 00000002h
VER_SUITE_BACKOFFICE                equ 00000004h
VER_SUITE_COMMUNICATIONS            equ 00000008h
VER_SUITE_TERMINAL                  equ 00000010h
VER_SUITE_SMALLBUSINESS_RESTRICTED  equ 00000020h
VER_SUITE_EMBEDDEDNT                equ 00000040h
VER_SUITE_DATACENTER                equ 00000080h
VER_SUITE_SINGLEUSERTS              equ 00000100h
VER_SUITE_PERSONAL                  equ 00000200h
VER_SUITE_SERVERAPPLIANCE           equ 00000400h

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;  Language IDs.
;
;  The following two combinations of primary language ID and
;  sublanguage ID have special semantics:
;
;    Primary Language ID   Sublanguage ID      Result
;    -------------------   ---------------     ------------------------
;    LANG_NEUTRAL          SUBLANG_NEUTRAL     Language neutral
;    LANG_NEUTRAL          SUBLANG_DEFAULT     User default language
;    LANG_NEUTRAL          SUBLANG_SYS_DEFAULT System default language
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;  Primary language IDs.
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

LANG_NEUTRAL                     equ 00

LANG_AFRIKAANS                   equ 36h
LANG_ALBANIAN                    equ 1ch
LANG_ARABIC                      equ 01h
LANG_ARMENIAN                    equ 2bh
LANG_ASSAMESE                    equ 4dh
LANG_AZERI                       equ 2ch
LANG_BASQUE                      equ 2dh
LANG_BELARUSIAN                  equ 23h
LANG_BENGALI                     equ 45h
LANG_BULGARIAN                   equ 02h
LANG_CATALAN                     equ 03h
LANG_CHINESE                     equ 04h
LANG_CROATIAN                    equ 1ah
LANG_CZECH                       equ 05h
LANG_DANISH                      equ 06h
LANG_DUTCH                       equ 13h
LANG_ENGLISH                     equ 09h
LANG_ESTONIAN                    equ 25h
LANG_FAEROESE                    equ 38h
LANG_FARSI                       equ 29h
LANG_FINNISH                     equ 0bh
LANG_FRENCH                      equ 0ch
LANG_GEORGIAN                    equ 37h
LANG_GERMAN                      equ 07h
LANG_GREEK                       equ 08h
LANG_GUJARATI                    equ 47h
LANG_HEBREW                      equ 0dh
LANG_HINDI                       equ 39h
LANG_HUNGARIAN                   equ 0eh
LANG_ICELANDIC                   equ 0fh
LANG_INDONESIAN                  equ 21h
LANG_ITALIAN                     equ 10h
LANG_JAPANESE                    equ 11h
LANG_KANNADA                     equ 4bh
LANG_KASHMIRI                    equ 60h
LANG_KAZAK                       equ 3fh
LANG_KONKANI                     equ 57h
LANG_KOREAN                      equ 12h
LANG_LATVIAN                     equ 26h
LANG_LITHUANIAN                  equ 27h
LANG_MACEDONIAN                  equ 2fh   ; the Former Yugoslav Republic of Macedonia
LANG_MALAY                       equ 3eh
LANG_MALAYALAM                   equ 4ch
LANG_MANIPURI                    equ 58h
LANG_MARATHI                     equ 4eh
LANG_NEPALI                      equ 61h
LANG_NORWEGIAN                   equ 14h
LANG_ORIYA                       equ 48h
LANG_POLISH                      equ 15h
LANG_PORTUGUESE                  equ 16h
LANG_PUNJABI                     equ 46h
LANG_ROMANIAN                    equ 18h
LANG_RUSSIAN                     equ 19h
LANG_SANSKRIT                    equ 4fh
LANG_SERBIAN                     equ 1ah
LANG_SINDHI                      equ 59h
LANG_SLOVAK                      equ 1bh
LANG_SLOVENIAN                   equ 24h
LANG_SPANISH                     equ 0ah
LANG_SWAHILI                     equ 41h
LANG_SWEDISH                     equ 1dh
LANG_TAMIL                       equ 49h
LANG_TATAR                       equ 44h
LANG_TELUGU                      equ 4ah
LANG_THAI                        equ 1eh
LANG_TURKISH                     equ 1fh
LANG_UKRAINIAN                   equ 22h
LANG_URDU                        equ 20h
LANG_UZBEK                       equ 43h
LANG_VIETNAMESE                  equ 2ah

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;  Sublanguage IDs.
;
;  The name immediately following SUBLANG_ dictates which primary
;  language ID that sublanguage ID can be combined with to form a
;  valid language ID.
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

SUBLANG_NEUTRAL                  equ 00    ; language neutral
SUBLANG_DEFAULT                  equ 01    ; user default
SUBLANG_SYS_DEFAULT              equ 02    ; system default

SUBLANG_ARABIC_SAUDI_ARABIA      equ 01    ; Arabic (Saudi Arabia)
SUBLANG_ARABIC_IRAQ              equ 02    ; Arabic (Iraq)
SUBLANG_ARABIC_EGYPT             equ 03    ; Arabic (Egypt)
SUBLANG_ARABIC_LIBYA             equ 04    ; Arabic (Libya)
SUBLANG_ARABIC_ALGERIA           equ 05    ; Arabic (Algeria)
SUBLANG_ARABIC_MOROCCO           equ 06    ; Arabic (Morocco)
SUBLANG_ARABIC_TUNISIA           equ 07    ; Arabic (Tunisia)
SUBLANG_ARABIC_OMAN              equ 08    ; Arabic (Oman)
SUBLANG_ARABIC_YEMEN             equ 09    ; Arabic (Yemen)
SUBLANG_ARABIC_SYRIA             equ 0ah   ; Arabic (Syria)
SUBLANG_ARABIC_JORDAN            equ 0bh   ; Arabic (Jordan)
SUBLANG_ARABIC_LEBANON           equ 0ch   ; Arabic (Lebanon)
SUBLANG_ARABIC_KUWAIT            equ 0dh   ; Arabic (Kuwait)
SUBLANG_ARABIC_UAE               equ 0eh   ; Arabic (U.A.E)
SUBLANG_ARABIC_BAHRAIN           equ 0fh   ; Arabic (Bahrain)
SUBLANG_ARABIC_QATAR             equ 10h   ; Arabic (Qatar)
SUBLANG_AZERI_LATIN              equ 01    ; Azeri (Latin)
SUBLANG_AZERI_CYRILLIC           equ 02    ; Azeri (Cyrillic)
SUBLANG_CHINESE_TRADITIONAL      equ 01    ; Chinese (Taiwan)
SUBLANG_CHINESE_SIMPLIFIED       equ 02    ; Chinese (PR China)
SUBLANG_CHINESE_HONGKONG         equ 03    ; Chinese (Hong Kong S.A.R., P.R.C.)
SUBLANG_CHINESE_SINGAPORE        equ 04    ; Chinese (Singapore)
SUBLANG_CHINESE_MACAU            equ 05    ; Chinese (Macau)
SUBLANG_DUTCH                    equ 01    ; Dutch
SUBLANG_DUTCH_BELGIAN            equ 02    ; Dutch (Belgian)
SUBLANG_ENGLISH_US               equ 01    ; English (USA)
SUBLANG_ENGLISH_UK               equ 02    ; English (UK)
SUBLANG_ENGLISH_AUS              equ 03    ; English (Australian)
SUBLANG_ENGLISH_CAN              equ 04    ; English (Canadian)
SUBLANG_ENGLISH_NZ               equ 05    ; English (New Zealand)
SUBLANG_ENGLISH_EIRE             equ 06    ; English (Irish)
SUBLANG_ENGLISH_SOUTH_AFRICA     equ 07    ; English (South Africa)
SUBLANG_ENGLISH_JAMAICA          equ 08    ; English (Jamaica)
SUBLANG_ENGLISH_CARIBBEAN        equ 09    ; English (Caribbean)
SUBLANG_ENGLISH_BELIZE           equ 0ah   ; English (Belize)
SUBLANG_ENGLISH_TRINIDAD         equ 0bh   ; English (Trinidad)
SUBLANG_ENGLISH_ZIMBABWE         equ 0ch   ; English (Zimbabwe)
SUBLANG_ENGLISH_PHILIPPINES      equ 0dh   ; English (Philippines)
SUBLANG_FRENCH                   equ 01    ; French
SUBLANG_FRENCH_BELGIAN           equ 02    ; French (Belgian)
SUBLANG_FRENCH_CANADIAN          equ 03    ; French (Canadian)
SUBLANG_FRENCH_SWISS             equ 04    ; French (Swiss)
SUBLANG_FRENCH_LUXEMBOURG        equ 05    ; French (Luxembourg)
SUBLANG_FRENCH_MONACO            equ 06    ; French (Monaco)
SUBLANG_GERMAN                   equ 01    ; German
SUBLANG_GERMAN_SWISS             equ 02    ; German (Swiss)
SUBLANG_GERMAN_AUSTRIAN          equ 03    ; German (Austrian)
SUBLANG_GERMAN_LUXEMBOURG        equ 04    ; German (Luxembourg)
SUBLANG_GERMAN_LIECHTENSTEIN     equ 05    ; German (Liechtenstein)
SUBLANG_ITALIAN                  equ 01    ; Italian
SUBLANG_ITALIAN_SWISS            equ 02    ; Italian (Swiss)
SUBLANG_KASHMIRI_INDIA           equ 02    ; Kashmiri (India)
SUBLANG_KOREAN                   equ 01    ; Korean (Extended Wansung)
SUBLANG_LITHUANIAN               equ 01    ; Lithuanian
SUBLANG_MALAY_MALAYSIA           equ 01    ; Malay (Malaysia)
SUBLANG_MALAY_BRUNEI_DARUSSALAM  equ 02    ; Malay (Brunei Darussalam)
SUBLANG_NEPALI_INDIA             equ 02    ; Nepali (India)
SUBLANG_NORWEGIAN_BOKMAL         equ 01    ; Norwegian (Bokmal)
SUBLANG_NORWEGIAN_NYNORSK        equ 02    ; Norwegian (Nynorsk)
SUBLANG_PORTUGUESE               equ 02    ; Portuguese
SUBLANG_PORTUGUESE_BRAZILIAN     equ 01    ; Portuguese (Brazilian)
SUBLANG_SERBIAN_LATIN            equ 02    ; Serbian (Latin)
SUBLANG_SERBIAN_CYRILLIC         equ 03    ; Serbian (Cyrillic)
SUBLANG_SPANISH                  equ 01    ; Spanish (Castilian)
SUBLANG_SPANISH_MEXICAN          equ 02    ; Spanish (Mexican)
SUBLANG_SPANISH_MODERN           equ 03    ; Spanish (Modern)
SUBLANG_SPANISH_GUATEMALA        equ 04    ; Spanish (Guatemala)
SUBLANG_SPANISH_COSTA_RICA       equ 05    ; Spanish (Costa Rica)
SUBLANG_SPANISH_PANAMA           equ 06    ; Spanish (Panama)
SUBLANG_SPANISH_DOMINICAN_REPUBLIC equ 07  ; Spanish (Dominican Republic)
SUBLANG_SPANISH_VENEZUELA        equ 08    ; Spanish (Venezuela)
SUBLANG_SPANISH_COLOMBIA         equ 09    ; Spanish (Colombia)
SUBLANG_SPANISH_PERU             equ 0ah   ; Spanish (Peru)
SUBLANG_SPANISH_ARGENTINA        equ 0bh   ; Spanish (Argentina)
SUBLANG_SPANISH_ECUADOR          equ 0ch   ; Spanish (Ecuador)
SUBLANG_SPANISH_CHILE            equ 0dh   ; Spanish (Chile)
SUBLANG_SPANISH_URUGUAY          equ 0eh   ; Spanish (Uruguay)
SUBLANG_SPANISH_PARAGUAY         equ 0fh   ; Spanish (Paraguay)
SUBLANG_SPANISH_BOLIVIA          equ 10h   ; Spanish (Bolivia)
SUBLANG_SPANISH_EL_SALVADOR      equ 11h   ; Spanish (El Salvador)
SUBLANG_SPANISH_HONDURAS         equ 12h   ; Spanish (Honduras)
SUBLANG_SPANISH_NICARAGUA        equ 13h   ; Spanish (Nicaragua)
SUBLANG_SPANISH_PUERTO_RICO      equ 14h   ; Spanish (Puerto Rico)
SUBLANG_SWEDISH                  equ 01    ; Swedish
SUBLANG_SWEDISH_FINLAND          equ 02    ; Swedish (Finland)
SUBLANG_URDU_PAKISTAN            equ 01    ; Urdu (Pakistan)
SUBLANG_URDU_INDIA               equ 02    ; Urdu (India)
SUBLANG_UZBEK_LATIN              equ 01    ; Uzbek (Latin)
SUBLANG_UZBEK_CYRILLIC           equ 02    ; Uzbek (Cyrillic)

;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;  Sorting IDs.
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

SORT_DEFAULT                     equ 0     ; sorting default

SORT_JAPANESE_XJIS               equ 0     ; Japanese XJIS order
SORT_JAPANESE_UNICODE            equ 1     ; Japanese Unicode order

SORT_CHINESE_BIG5                equ 0     ; Chinese BIG5 order
SORT_CHINESE_PRCP                equ 0     ; PRC Chinese Phonetic order
SORT_CHINESE_UNICODE             equ 1     ; Chinese Unicode order
SORT_CHINESE_PRC                 equ 2     ; PRC Chinese Stroke Count order
SORT_CHINESE_BOPOMOFO            equ 3     ; Traditional Chinese Bopomofo order

SORT_KOREAN_KSC                  equ 0     ; Korean KSC order
SORT_KOREAN_UNICODE              equ 1     ; Korean Unicode order

SORT_GERMAN_PHONE_BOOK           equ 1     ; German Phone Book order

SORT_HUNGARIAN_DEFAULT           equ 0     ; Hungarian Default order
SORT_HUNGARIAN_TECHNICAL         equ 1     ; Hungarian Technical order

SORT_GEORGIAN_TRADITIONAL        equ 0     ; Georgian Traditional order
SORT_GEORGIAN_MODERN             equ 1     ; Georgian Modern order



;ntddk.inc
;
;include ntdef.inc



; Kernel Mutex Level Numbers (must be globallly assigned within executive)
; The third token in the name is the sub-component name that defines and
; uses the level number.

; Used by Vdm for protecting io simulation structures

MUTEX_LEVEL_VDM_IO       = 00000001
MUTEX_LEVEL_EX_PROFILE   = 00000040h

; The LANMAN Redirector uses the file system major function, but defines
; it's own mutex levels.  We can do this safely because we know that the
; local filesystem will never call the remote filesystem and vice versa.

MUTEX_LEVEL_RDR_FILESYS_DATABASE    = 10100000h
MUTEX_LEVEL_RDR_FILESYS_SECURITY    = 10100001h

; File System levels.

MUTEX_LEVEL_FILESYSTEM_RAW_VCB      = 11000006h

; In the NT STREAMS environment, a mutex is used to serialize open, close
; and Scheduler threads executing in a subsystem-parallelized stack.

MUTEX_LEVEL_STREAMS_SUBSYS          = 11001001h

; Mutex level used by LDT support on x86

MUTEX_LEVEL_PS_LDT                  = 1F000000h

; Kernel definitions that need to be here for forward reference purposes

; Processor modes.


;typedef enum _MODE {
        KernelMode      = 0
        UserMode        = 1
        MaximumMode     = 2

; Asynchronous Procedure Call (APC) object


struc KAPC {
        .Type                    dw           ?       ; 0000h
        .Size                    dw           ?       ; 0002h
        .Spare0                  dd           ?       ; 0004h
        .Thread                  dd           ?       ; 0008h  PTR KTHREAD
        .ApcListEntry    rb           8       ;LIST_ENTRY <>   ; 000Ch
        .KernelRoutine   dd           ?       ; 0014h  KiSuspendNop
        .RundownRoutine  dd           ?       ; 0018h
        .NormalRoutine   dd           ?       ; 001Ch  KiSuspendThread
        .NormalContext   dd           ?       ; 0020h

        ; N.B. The following two members MUST be together.

        .SystemArgument1 dd           ?       ; 0024h
        .SystemArgument2 dd           ?       ; 0028h
        .ApcStateIndex   db           ?       ; 002Ch
        .ApcMode         db           ?       ; 002Dh  KPROCESSOR_MODE
        .Inserted        db           ?       ; 002Eh  BOOLEAN
                         db           ?       ; padding
}
struct KAPC

; Asynchronous Procedure Call (APC) object

; +
; Define DPC importance.
; LowImportance - Queue DPC at end of target DPC queue.
; MediumImportance - Queue DPC at end of target DPC queue.
; HighImportance - Queue DPC at front of target DPC DPC queue.
;
; If there is currently a DPC active on the target processor, or a DPC
; interrupt has already been requested on the target processor when a
; DPC is queued, then no further action is necessary. The DPC will be
; executed on the target processor when its queue entry is processed.
;
; If there is not a DPC active on the target processor and a DPC interrupt
; has not been requested on the target processor, then the exact treatment
; of the DPC is dependent on whether the host system is a UP system or an
; MP system.
;
; UP system.
;
; If the DPC is of medium or high importance, the current DPC queue depth
; is greater than the maximum target depth, or current DPC request rate is
; less the minimum target rate, then a DPC interrupt is requested on the
; host processor and the DPC will be processed when the interrupt occurs.
; Otherwise, no DPC interupt is requested and the DPC execution will be
; delayed until the DPC queue depth is greater that the target depth or the
; minimum DPC rate is less than the target rate.
;
; MP system.
;
; If the DPC is being queued to another processor and the depth of the DPC
; queue on the target processor is greater than the maximum target depth or
; the DPC is of high importance, then a DPC interrupt is requested on the
; target processor and the DPC will be processed when the interrupt occurs.
; Otherwise, the DPC execution will be delayed on the target processor until
; the DPC queue depth on the target processor is greater that the maximum
; target depth or the minimum DPC rate on the target processor is less than
; the target mimimum rate.
;
; If the DPC is being queued to the current processor and the DPC is not of
; low importance, the current DPC queue depth is greater than the maximum
; target depth, or the minimum DPC rate is less than the minimum target rate,
; then a DPC interrupt is request on the current processor and the DPV will
; be processed whne the interrupt occurs. Otherwise, no DPC interupt is
; requested and the DPC execution will be delayed until the DPC queue depth
; is greater that the target depth or the minimum DPC rate is less than the
; target rate.
; -

;typedef enum _KDPC_IMPORTANCE {
    LowImportance               = 0
    MediumImportance    = 1
    HighImportance              = 2

; Deferred Procedure Call (DPC) object

struc KDPC {
        .Type             dw          ?       ; 0000h  (IO_TYPE_DPC   = 13h)
        .Number           db          ?       ; 0002h
        .Importance       db          ?       ; 0003h
        .DpcListEntry     rb          8       ;LIST_ENTRY <>   ; 0004h
        .DeferredRoutine  dd          ?       ; 000Ch
        .DeferredContext  dd          ?       ; 0010h
        .SystemArgument1  dd          ?       ; 0014h
        .SystemArgument2  dd          ?       ; 0018h
        .Lock             dd          ?       ; 001Ch
}
struct KDPC

; +
; I/O system definitions.
;
; Define a Memory Descriptor List (MDL)
;
; An MDL describes pages in a virtual buffer in terms of physical pages.  The
; pages associated with the buffer are described in an array that is allocated
; just after the MDL header structure itself.  In a future compiler this will
; be placed at:
;
;      ULONG Pages[];
;
; Until this declaration is permitted, however, one simply calculates the
; base of the array by adding one to the base MDL pointer:
;
;      Pages = (PULONG) (Mdl + 1);
;
; Notice that while in the context of the subject thread, the base virtual
; address of a buffer mapped by an MDL may be referenced using the following:
;
;      Mdl->StartVa | Mdl->ByteOffset
; -


struc MDL {
        .Next                    dd           ?       ; 0000h  PTR MDL
        .Size                    dw           ?       ; 0004h
        .MdlFlags                dw           ?       ; 0006h
        .Process                 dd           ?       ; 0008h  PTR EPROCESS
        .MappedSystemVa          dd           ?       ; 000Ch
        .StartVa                 dd           ?       ; 0010h
        .ByteCount               dd           ?       ; 0014h
        .ByteOffset              dd           ?       ; 0018h
}
struct MDL

MDL_MAPPED_TO_SYSTEM_VA     = 0001h
MDL_PAGES_LOCKED            = 0002h
MDL_SOURCE_IS_NONPAGED_POOL = 0004h
MDL_ALLOCATED_FIXED_SIZE    = 0008h
MDL_PARTIAL                 = 0010h
MDL_PARTIAL_HAS_BEEN_MAPPED = 0020h
MDL_IO_PAGE_READ            = 0040h
MDL_WRITE_OPERATION         = 0080h
MDL_PARENT_MAPPED_SYSTEM_VA = 0100h
MDL_LOCK_HELD               = 0200h
MDL_PHYSICAL_VIEW           = 0400h
MDL_IO_SPACE                = 0800h
MDL_NETWORK_HEADER          = 1000h
MDL_MAPPING_CAN_FAIL        = 2000h
MDL_ALLOCATED_MUST_SUCCEED  = 4000h

MDL_SYSTEM_VA = MDL_PHYSICAL_VIEW ; MDL_SYSTEM_VA was used below, but not defined ???

MDL_MAPPING_FLAGS = MDL_MAPPED_TO_SYSTEM_VA or MDL_PAGES_LOCKED or MDL_SOURCE_IS_NONPAGED_POOL or MDL_PARTIAL_HAS_BEEN_MAPPED or MDL_PARENT_MAPPED_SYSTEM_VA or MDL_LOCK_HELD or MDL_SYSTEM_VA or MDL_IO_SPACE


;  The following are masks for the predefined standard access types

DELETE                           = 00010000h
READ_CONTROL                     = 00020000h
WRITE_DAC                        = 00040000h
WRITE_OWNER                      = 00080000h
SYNCHRONIZE                      = 00100000h

STANDARD_RIGHTS_REQUIRED         = 000F0000h

STANDARD_RIGHTS_READ             = READ_CONTROL
STANDARD_RIGHTS_WRITE            = READ_CONTROL
STANDARD_RIGHTS_EXECUTE          = READ_CONTROL

STANDARD_RIGHTS_ALL              = 001F0000h

SPECIFIC_RIGHTS_ALL              = 0000FFFFh

; AccessSystemAcl access type

ACCESS_SYSTEM_SECURITY           = 01000000h

; MaximumAllowed access type

MAXIMUM_ALLOWED                  = 02000000h

;  These are the generic rights.

GENERIC_READ                     = 80000000h
GENERIC_WRITE                    = 40000000h
GENERIC_EXECUTE                  = 20000000h
GENERIC_ALL                      = 10000000h

;  Define the generic mapping array.  This is used to denote the
;  mapping of each generic access right to a specific access mask.

struc GENERIC_MAPPING {
        .GenericRead     dd           ?       ; 0000h
        .GenericWrite    dd           ?       ; 0004h
        .GenericExecute  dd           ?       ; 0008h
        .GenericAll      dd           ?       ; 000Ch
}
struct GENERIC_MAPPING

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;:                                                                    ::
;:                        LUID_AND_ATTRIBUTES                         ::
;:                                                                    ::
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;#include <pshpack4.h>

struc LUID_AND_ATTRIBUTES {
        .Luid            rb     8       ; LUID    <>      ; 0000h
        .Attributes      dd     ?       ; 0008h
}
struct LUID_AND_ATTRIBUTES


; This is the *current* ACL revision

ACL_REVISION     = 2
ACL_REVISION_DS  = 4

; This is the history of ACL revisions.  Add a new one whenever
; ACL_REVISION is updated

ACL_REVISION1   = 1
ACL_REVISION2   = 2
MIN_ACL_REVISION = ACL_REVISION2
ACL_REVISION3   = 3
ACL_REVISION4   = 4
MAX_ACL_REVISION = ACL_REVISION4


struc ACL {
        .AclRevision     db            ?       ; 0000h
        .Sbz1            db            ?       ; 0001h
        .AclSize         dw            ?       ; 0002h
        .AceCount        dw            ?       ; 0004h
        .Sbz2            dw            ?       ; 0006h
}
struct ACL

; Current security descriptor revision value

SECURITY_DESCRIPTOR_REVISION    = 1
SECURITY_DESCRIPTOR_REVISION1   = 1

; Privilege attributes

SE_PRIVILEGE_ENABLED_BY_DEFAULT = 00000001
SE_PRIVILEGE_ENABLED            = 00000002
SE_PRIVILEGE_USED_FOR_ACCESS    = 80000000h

; Privilege Set Control flags

PRIVILEGE_SET_ALL_NECESSARY    = 1

; -
;  Privilege Set - This is defined for a privilege set of one.
;                  If more than one privilege is needed, then this structure
;                  will need to be allocated with more space.
;
;  Note: don't change this structure without fixing the INITIAL_PRIVILEGE_SET
;  structure (defined in se.h)
; -

struc PRIVILEGE_SET {
        .PrivilegeCount  dd        ?       ; 0000h
        .Control         dd        ?       ; 0004h
        .Privilege       rb        12      ;LUID_AND_ATTRIBUTES  1 dup(<>)   ; 0008h
}
struct PRIVILEGE_SET

; These must be converted to LUIDs before use.

SE_MIN_WELL_KNOWN_PRIVILEGE       = 2
SE_CREATE_TOKEN_PRIVILEGE         = 2
SE_ASSIGNPRIMARYTOKEN_PRIVILEGE   = 3
SE_LOCK_MEMORY_PRIVILEGE          = 4
SE_INCREASE_QUOTA_PRIVILEGE       = 5

; Unsolicited Input is obsolete and unused.

SE_UNSOLICITED_INPUT_PRIVILEGE    = 6

SE_MACHINE_ACCOUNT_PRIVILEGE      = 6
SE_TCB_PRIVILEGE                  = 7
SE_SECURITY_PRIVILEGE             = 8
SE_TAKE_OWNERSHIP_PRIVILEGE       = 9
SE_LOAD_DRIVER_PRIVILEGE          = 10
SE_SYSTEM_PROFILE_PRIVILEGE       = 11
SE_SYSTEMTIME_PRIVILEGE           = 12
SE_PROF_SINGLE_PROCESS_PRIVILEGE  = 13
SE_INC_BASE_PRIORITY_PRIVILEGE    = 14
SE_CREATE_PAGEFILE_PRIVILEGE      = 15
SE_CREATE_PERMANENT_PRIVILEGE     = 16
SE_BACKUP_PRIVILEGE               = 17
SE_RESTORE_PRIVILEGE              = 18
SE_SHUTDOWN_PRIVILEGE             = 19
SE_DEBUG_PRIVILEGE                = 20
SE_AUDIT_PRIVILEGE                = 21
SE_SYSTEM_ENVIRONMENT_PRIVILEGE   = 22
SE_CHANGE_NOTIFY_PRIVILEGE        = 23
SE_REMOTE_SHUTDOWN_PRIVILEGE      = 24
SE_UNDOCK_PRIVILEGE               = 25
SE_SYNC_AGENT_PRIVILEGE           = 26
SE_ENABLE_DELEGATION_PRIVILEGE    = 27
SE_MAX_WELL_KNOWN_PRIVILEGE       = SE_ENABLE_DELEGATION_PRIVILEGE

; +
; Impersonation Level
;
; Impersonation level is represented by a pair of bits in Windows.
; If a new impersonation level is added or lowest value is changed from
; 0 to something else, fix the Windows CreateFile call.
; -

;typedef enum _SECURITY_IMPERSONATION_LEVEL {
    SecurityAnonymous           = 0
    SecurityIdentification      = 1
    SecurityImpersonation       = 2
    SecurityDelegation          = 3
;    } SECURITY_IMPERSONATION_LEVEL, * PSECURITY_IMPERSONATION_LEVEL;

SECURITY_MAX_IMPERSONATION_LEVEL        = SecurityDelegation

DEFAULT_IMPERSONATION_LEVEL                     = SecurityImpersonation

; Security Tracking Mode

SECURITY_DYNAMIC_TRACKING      = TRUE
SECURITY_STATIC_TRACKING       = FALSE

; Quality Of Service

struc SECURITY_QUALITY_OF_SERVICE {
        .Length                  dd          ?       ; 0000h
        .ImpersonationLevel      dd          ?       ; 0004h  enum SECURITY_IMPERSONATION_LEVEL
        .ContextTrackingMode     db          ?       ; 0008h  SECURITY_CONTEXT_TRACKING_MODE
        .EffectiveOnly           db          ?       ; 0009h  BOOLEAN
                                 rb          2       ; padding
}
struct SECURITY_QUALITY_OF_SERVICE

; Used to represent information related to a thread impersonation

struc SE_IMPERSONATION_STATE {
        .Token                  dd    ?       ; 0000h  PACCESS_TOKEN
        .CopyOnOpen             db    ?       ; 0004h  BOOLEAN
        .EffectiveOnly          db    ?       ; 0005h  BOOLEAN
                                rb    2       ; padding
        .Level                  dd    ?       ; 0008  enum SECURITY_IMPERSONATION_LEVEL
}
struct SE_IMPERSONATION_STATE


OWNER_SECURITY_INFORMATION       = 00000001
GROUP_SECURITY_INFORMATION       = 00000002
DACL_SECURITY_INFORMATION        = 00000004
SACL_SECURITY_INFORMATION        = 00000008

PROTECTED_DACL_SECURITY_INFORMATION     = 80000000h
PROTECTED_SACL_SECURITY_INFORMATION     = 40000000h
UNPROTECTED_DACL_SECURITY_INFORMATION   = 20000000h
UNPROTECTED_SACL_SECURITY_INFORMATION   = 10000000h

LOW_PRIORITY                    = 0   ; Lowest thread priority level
LOW_REALTIME_PRIORITY   = 16  ; Lowest realtime priority level
HIGH_PRIORITY                   = 31  ; Highest thread priority level
MAXIMUM_PRIORITY                = 32  ; Number of thread priority levels
; begin_winnt
MAXIMUM_WAIT_OBJECTS    = 64  ; Maximum number of wait objects

MAXIMUM_SUSPEND_COUNT   = MAXCHAR     ; Maximum times thread can be suspended
; end_winnt


; Subroutines for dealing with the Registry

struc RTL_QUERY_REGISTRY_TABLE {
        .QueryRoutine    dd   ?       ; 0000h  PRTL_QUERY_REGISTRY_ROUTINE
        .Flags           dd   ?       ; 0004h
        .Name            dd   ?       ; 0008h
        .EntryContext    dd   ?       ; 000Ch
        .DefaultType     dd   ?       ; 0010h
        .DefaultData     dd   ?       ; 0014h
        .DefaultLength   dd   ?       ; 0018h
}
struct RTL_QUERY_REGISTRY_TABLE

; The following flags specify how the Name field of a RTL_QUERY_REGISTRY_TABLE
; entry is interpreted.  A NULL name indicates the end of the table.

RTL_QUERY_REGISTRY_SUBKEY   = 00000001h       ; Name is a subkey and remainder of
                                                                                        ; table or until next subkey are value
                                                                                        ; names for that subkey to look at.

RTL_QUERY_REGISTRY_TOPKEY   = 00000002h       ; Reset current key to original key for
                                                                                        ; this and all following table entries.

RTL_QUERY_REGISTRY_REQUIRED = 00000004h       ; Fail if no match found for this table entry.

RTL_QUERY_REGISTRY_NOVALUE  = 00000008h       ; Used to mark a table entry that has no
                                                                                        ; value name, just wants a call out, not
                                                                                        ; an enumeration of all values.

RTL_QUERY_REGISTRY_NOEXPAND = 00000010h       ; Used to suppress the expansion of
                                                                                        ; REG_MULTI_SZ into multiple callouts or
                                                                                        ; to prevent the expansion of environment
                                                                                        ; variable values in REG_EXPAND_SZ

RTL_QUERY_REGISTRY_DIRECT   = 00000020h       ; QueryRoutine field ignored.  EntryContext
                                                                                        ; field points to location to store value.
                                                                                        ; For null terminated strings, EntryContext
                                                                                        ; points to UNICODE_STRING structure that
                                                                                        ; that describes maximum size of buffer.
                                                                                        ; If .Buffer field is NULL then a buffer is
                                                                                        ; allocated.

RTL_QUERY_REGISTRY_DELETE   = 00000040h       ; Used to delete value keys after they
                                                                                        ; are queried.

; The following values for the RelativeTo parameter determine what the
; Path parameter to RtlQueryRegistryValues is relative to.

RTL_REGISTRY_ABSOLUTE     = 0         ; Path is a full path
RTL_REGISTRY_SERVICES     = 1         ; \Registry\Machine\System\CurrentControlSet\Services
RTL_REGISTRY_CONTROL      = 2         ; \Registry\Machine\System\CurrentControlSet\Control
RTL_REGISTRY_WINDOWS_NT   = 3         ; \Registry\Machine\Software\Microsoft\Windows NT\CurrentVersion
RTL_REGISTRY_DEVICEMAP    = 4         ; \Registry\Machine\Hardware\DeviceMap
RTL_REGISTRY_USER         = 5         ; \Registry\User\CurrentUser
RTL_REGISTRY_MAXIMUM      = 6
RTL_REGISTRY_HANDLE       = 40000000h ; Low order bits are registry handle
RTL_REGISTRY_OPTIONAL     = 80000000h ; Indicates the key node is optional

;  Time conversion routines

struc TIME_FIELDS {
        .Year                    dw           ?       ; 0000h range [1601...]
        .Month                   dw           ?       ; 0002h range [1..12]
        .Day                     dw           ?       ; 0004h range [1..31]
        .Hour                    dw           ?       ; 0006h range [0..23]
        .Minute                  dw           ?       ; 0008h range [0..59]
        .Second                  dw           ?       ; 000Ah range [0..59]
        .Milliseconds            dw           ?       ; 000Ch range [0..999]
        .Weekday                 dw           ?       ; 000Eh range [0..6] == [Sunday..Saturday]
}
struct TIME_FIELDS

; +
;  BitMap routines.  The following structure, routines, and macros are
;  for manipulating bitmaps.  The user is responsible for allocating a bitmap
;  structure (which is really a header) and a buffer (which must be longword
;  aligned and multiple longwords in size).
; -

struc RTL_BITMAP {
        .SizeOfBitMap    dd   ?       ; 00h  Number of bits in bit map
        .Buffer          dd   ?       ; 04h  Pointer to the bit map itself
}
struct RTL_BITMAP

; +
; Define the various device type values.  Note that values used by Microsoft
; Corporation are in the range 0-32767, and 32768-65535 are reserved for use
; by customers.
; -

FILE_DEVICE_BEEP                = 01
FILE_DEVICE_CD_ROM              = 02
FILE_DEVICE_CD_ROM_FILE_SYSTEM  = 03
FILE_DEVICE_CONTROLLER          = 04
FILE_DEVICE_DATALINK            = 05
FILE_DEVICE_DFS                 = 06
FILE_DEVICE_DISK                = 07
FILE_DEVICE_DISK_FILE_SYSTEM    = 08
FILE_DEVICE_FILE_SYSTEM         = 09
FILE_DEVICE_INPORT_PORT         = 0ah
FILE_DEVICE_KEYBOARD            = 0bh
FILE_DEVICE_MAILSLOT            = 0ch
FILE_DEVICE_MIDI_IN             = 0dh
FILE_DEVICE_MIDI_OUT            = 0eh
FILE_DEVICE_MOUSE               = 0fh
FILE_DEVICE_MULTI_UNC_PROVIDER  = 10h
FILE_DEVICE_NAMED_PIPE          = 11h
FILE_DEVICE_NETWORK             = 12h
FILE_DEVICE_NETWORK_BROWSER     = 13h
FILE_DEVICE_NETWORK_FILE_SYSTEM = 14h
FILE_DEVICE_NULL                = 15h
FILE_DEVICE_PARALLEL_PORT       = 16h
FILE_DEVICE_PHYSICAL_NETCARD    = 17h
FILE_DEVICE_PRINTER             = 18h
FILE_DEVICE_SCANNER             = 19h
FILE_DEVICE_SERIAL_MOUSE_PORT   = 1ah
FILE_DEVICE_SERIAL_PORT         = 1bh
FILE_DEVICE_SCREEN              = 1ch
FILE_DEVICE_SOUND               = 1dh
FILE_DEVICE_STREAMS             = 1eh
FILE_DEVICE_TAPE                = 1fh
FILE_DEVICE_TAPE_FILE_SYSTEM    = 20h
FILE_DEVICE_TRANSPORT           = 21h
FILE_DEVICE_UNKNOWN             = 22h
FILE_DEVICE_VIDEO               = 23h
FILE_DEVICE_VIRTUAL_DISK        = 24h
FILE_DEVICE_WAVE_IN             = 25h
FILE_DEVICE_WAVE_OUT            = 26h
FILE_DEVICE_8042_PORT           = 27h
FILE_DEVICE_NETWORK_REDIRECTOR  = 28h
FILE_DEVICE_BATTERY             = 29h
FILE_DEVICE_BUS_EXTENDER        = 2ah
FILE_DEVICE_MODEM               = 2bh
FILE_DEVICE_VDM                 = 2ch
FILE_DEVICE_MASS_STORAGE        = 2dh
FILE_DEVICE_SMB                 = 2eh
FILE_DEVICE_KS                  = 2fh
FILE_DEVICE_CHANGER             = 30h
FILE_DEVICE_SMARTCARD           = 31h
FILE_DEVICE_ACPI                = 32h
FILE_DEVICE_DVD                 = 33h
FILE_DEVICE_FULLSCREEN_VIDEO    = 34h
FILE_DEVICE_DFS_FILE_SYSTEM     = 35h
FILE_DEVICE_DFS_VOLUME          = 36h
FILE_DEVICE_SERENUM             = 37h
FILE_DEVICE_TERMSRV             = 38h
FILE_DEVICE_KSEC                = 39h

; +
; Macro definition for defining IOCTL and FSCTL function control codes.  Note
; that function codes 0-2047 are reserved for Microsoft Corporation, and
; 2048-4095 are reserved for customers.
; -

macro CTL_CODE Name,DeviceType,Function,Method,Access {
Name=(((DeviceType) SHL 16) OR ((Access) SHL 14) OR ((Function) SHL 2) OR (Method))
}


; Macro to extract device type out of the device io control code

macro DEVICE_TYPE_FROM_CTL_CODE name,ctrlCode {
Name=(((ctrlCode) AND 0ffff0000h) SHR 16)
}

; Define the method codes for how buffers are passed for I/O and FS controls

METHOD_BUFFERED                 = 0
METHOD_IN_DIRECT                = 1
METHOD_OUT_DIRECT               = 2
METHOD_NEITHER                  = 3

; Define the access check value for any access
;
; The FILE_READ_ACCESS and FILE_WRITE_ACCESS constants are also defined in
; ntioapi.h as FILE_READ_DATA and FILE_WRITE_DATA. The values for these
; constants *MUST* always be in sync.
;
; FILE_SPECIAL_ACCESS is checked by the NT I/O system the same as FILE_ANY_ACCESS.
; The file systems, however, may add additional access checks for I/O and FS controls
; that use this value.

FILE_ANY_ACCESS                 = 0
FILE_SPECIAL_ACCESS             = FILE_ANY_ACCESS
FILE_READ_ACCESS                = 1   ; file & pipe
FILE_WRITE_ACCESS               = 2   ; file & pipe

; Define access rights to files and directories

; +
; The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
; devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
; constants *MUST* always be in sync.
; The values are redefined in devioctl.h because they must be available to
; both DOS and NT.
; -

FILE_READ_DATA                          = 0001        ; file & pipe
FILE_LIST_DIRECTORY                     = 0001        ; directory

FILE_WRITE_DATA                         = 0002        ; file & pipe
FILE_ADD_FILE                           = 0002        ; directory

FILE_APPEND_DATA                        = 0004        ; file
FILE_ADD_SUBDIRECTORY           = 0004        ; directory
FILE_CREATE_PIPE_INSTANCE       = 0004        ; named pipe

FILE_READ_EA                            = 0008        ; file & directory

FILE_WRITE_EA                           = 0010h       ; file & directory

FILE_EXECUTE                            = 0020h       ; file
FILE_TRAVERSE                           = 0020h       ; directory

FILE_DELETE_CHILD                       = 0040h       ; directory

FILE_READ_ATTRIBUTES            = 0080h       ; all

FILE_WRITE_ATTRIBUTES           = 0100h       ; all

FILE_ALL_ACCESS                         = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 1FFh)

FILE_GENERIC_READ = (STANDARD_RIGHTS_READ or FILE_READ_DATA or FILE_READ_ATTRIBUTES or FILE_READ_EA or SYNCHRONIZE)

FILE_GENERIC_WRITE = (STANDARD_RIGHTS_WRITE or FILE_WRITE_DATA or FILE_WRITE_ATTRIBUTES or FILE_WRITE_EA or FILE_APPEND_DATA or SYNCHRONIZE)

FILE_GENERIC_EXECUTE = (STANDARD_RIGHTS_EXECUTE or FILE_READ_ATTRIBUTES or FILE_EXECUTE or SYNCHRONIZE)

; Define share access rights to files and directories

FILE_SHARE_READ                 = 1   ; winnt
FILE_SHARE_WRITE                = 2   ; winnt
FILE_SHARE_DELETE               = 4   ; winnt
FILE_SHARE_VALID_FLAGS          = 7

; +
; Define the file attributes values
;
; Note:  0x00000008 is reserved for use for the old DOS VOLID (volume ID)
;         and is therefore not considered valid in NT.
;
; Note:  0x00000010 is reserved for use for the old DOS SUBDIRECTORY flag
;         and is therefore not considered valid in NT.  This flag has
;         been disassociated with file attributes since the other flags are
;         protected with READ_ and WRITE_ATTRIBUTES access to the file.
;
; Note:  Note also that the order of these flags is set to allow both the
;         FAT and the Pinball File Systems to directly set the attributes
;         flags in attributes words without having to pick each flag out
;         individually.  The order of these flags should not be changed!
; -

FILE_ATTRIBUTE_READONLY             = 00000001h  ; winnt
FILE_ATTRIBUTE_HIDDEN               = 00000002h  ; winnt
FILE_ATTRIBUTE_SYSTEM               = 00000004h  ; winnt

FILE_ATTRIBUTE_DIRECTORY            = 00000010h  ; winnt
FILE_ATTRIBUTE_ARCHIVE              = 00000020h  ; winnt
FILE_ATTRIBUTE_DEVICE               = 00000040h  ; winnt
FILE_ATTRIBUTE_NORMAL               = 00000080h  ; winnt

FILE_ATTRIBUTE_TEMPORARY            = 00000100h  ; winnt
FILE_ATTRIBUTE_SPARSE_FILE          = 00000200h  ; winnt
FILE_ATTRIBUTE_REPARSE_POINT        = 00000400h  ; winnt
FILE_ATTRIBUTE_COMPRESSED           = 00000800h  ; winnt

FILE_ATTRIBUTE_OFFLINE              = 00001000h  ; winnt
FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  = 00002000h  ; winnt
FILE_ATTRIBUTE_ENCRYPTED            = 00004000h  ; winnt

; This definition is old and will disappear shortly

FILE_ATTRIBUTE_CONTENT_INDEXED  = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED

FILE_ATTRIBUTE_VALID_FLAGS      = 00007fb7h
FILE_ATTRIBUTE_VALID_SET_FLAGS  = 000031a7h

; Define the create disposition values

FILE_SUPERSEDE                  = 0
FILE_OPEN                       = 1
FILE_CREATE                     = 2
FILE_OPEN_IF                    = 3
FILE_OVERWRITE                  = 4
FILE_OVERWRITE_IF               = 5
FILE_MAXIMUM_DISPOSITION        = 5

; Define the create/open option flags

FILE_DIRECTORY_FILE                     = 00000001h
FILE_WRITE_THROUGH                      = 00000002h
FILE_SEQUENTIAL_ONLY                    = 00000004h
FILE_NO_INTERMEDIATE_BUFFERING          = 00000008h

FILE_SYNCHRONOUS_IO_ALERT               = 00000010h
FILE_SYNCHRONOUS_IO_NONALERT            = 00000020h
FILE_NON_DIRECTORY_FILE                 = 00000040h
FILE_CREATE_TREE_CONNECTION             = 00000080h

FILE_COMPLETE_IF_OPLOCKED               = 00000100h
FILE_NO_EA_KNOWLEDGE                    = 00000200h
FILE_OPEN_FOR_RECOVERY                  = 00000400h
FILE_RANDOM_ACCESS                      = 00000800h

FILE_DELETE_ON_CLOSE                    = 00001000h
FILE_OPEN_BY_FILE_ID                    = 00002000h
FILE_OPEN_FOR_BACKUP_INTENT             = 00004000h
FILE_NO_COMPRESSION                     = 00008000h

FILE_RESERVE_OPFILTER                   = 00100000h
FILE_OPEN_REPARSE_POINT                 = 00200000h
FILE_OPEN_NO_RECALL                     = 00400000h
FILE_OPEN_FOR_FREE_SPACE_QUERY          = 00800000h

FILE_COPY_STRUCTURED_STORAGE            = 00000041h
FILE_STRUCTURED_STORAGE                 = 00000441h

FILE_VALID_OPTION_FLAGS                 = 00ffffffh
FILE_VALID_PIPE_OPTION_FLAGS            = 00000032h
FILE_VALID_MAILSLOT_OPTION_FLAGS        = 00000032h
FILE_VALID_SET_FLAGS                    = 00000036h

; Define the I/O status information return values for NtCreateFile/NtOpenFile

FILE_SUPERSEDED                 = 0
FILE_OPENED                     = 1
FILE_CREATED                    = 2
FILE_OVERWRITTEN                = 3
FILE_EXISTS                     = 4
FILE_DOES_NOT_EXIST             = 5

; Define special ByteOffset parameters for read and write operations

FILE_WRITE_TO_END_OF_FILE       = 0ffffffffh
FILE_USE_FILE_POINTER_POSITION  = 0fffffffeh

; Define alignment requirement values

FILE_BYTE_ALIGNMENT             = 00000000h
FILE_WORD_ALIGNMENT             = 00000001h
FILE_LONG_ALIGNMENT             = 00000003h
FILE_QUAD_ALIGNMENT             = 00000007h
FILE_OCTA_ALIGNMENT             = 0000000fh
FILE_32_BYTE_ALIGNMENT          = 0000001fh
FILE_64_BYTE_ALIGNMENT          = 0000003fh
FILE_128_BYTE_ALIGNMENT         = 0000007fh
FILE_256_BYTE_ALIGNMENT         = 000000ffh
FILE_512_BYTE_ALIGNMENT         = 000001ffh

; Define the maximum length of a filename string

MAXIMUM_FILENAME_LENGTH         = 256

; Define the various device characteristics flags

FILE_REMOVABLE_MEDIA            = 00000001h
FILE_READ_ONLY_DEVICE           = 00000002h
FILE_FLOPPY_DISKETTE            = 00000004h
FILE_WRITE_ONCE_MEDIA           = 00000008h
FILE_REMOTE_DEVICE              = 00000010h
FILE_DEVICE_IS_MOUNTED          = 00000020h
FILE_VIRTUAL_VOLUME             = 00000040h
FILE_AUTOGENERATED_DEVICE_NAME  = 00000080h
FILE_DEVICE_SECURE_OPEN         = 00000100h

; end_wdm

; flags specified here will be propagated up and down a device stack
; after FDO and all filter devices are added, but before the device
; stack is started

FILE_CHARACTERISTICS_PROPAGATED = FILE_REMOVABLE_MEDIA or FILE_READ_ONLY_DEVICE or FILE_FLOPPY_DISKETTE or FILE_WRITE_ONCE_MEDIA or FILE_DEVICE_SECURE_OPEN

; Define the base asynchronous I/O argument types

struc IO_STATUS_BLOCK {
        .Status          dd          ?       ; 0000h  NTSTATUS
        .Information     dd          ?       ; 0004h
}
struct IO_STATUS_BLOCK

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Define the file information class values
;
; WARNING:  The order of the following values are assumed by the I/O system.
;           Any changes made here should be reflected there as well.
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation      = 1
    FileFullDirectoryInformation  = 2
    FileBothDirectoryInformation  = 3
    FileBasicInformation          = 4  ; wdm
    FileStandardInformation       = 5  ; wdm
    FileInternalInformation       = 6
    FileEaInformation             = 7
    FileAccessInformation         = 8
    FileNameInformation           = 9
    FileRenameInformation         = 10
    FileLinkInformation           = 11
    FileNamesInformation          = 12
    FileDispositionInformation    = 13
    FilePositionInformation       = 14 ; wdm
    FileFullEaInformation         = 15
    FileModeInformation           = 16
    FileAlignmentInformation      = 17
    FileAllInformation            = 18
    FileAllocationInformation     = 19
    FileEndOfFileInformation      = 20 ; wdm
    FileAlternateNameInformation  = 21
    FileStreamInformation         = 22
    FilePipeInformation           = 23
    FilePipeLocalInformation      = 24
    FilePipeRemoteInformation     = 25
    FileMailslotQueryInformation  = 26
    FileMailslotSetInformation    = 27
    FileCompressionInformation    = 28
    FileObjectIdInformation       = 29
    FileCompletionInformation     = 30
    FileMoveClusterInformation    = 31
    FileQuotaInformation          = 32
    FileReparsePointInformation   = 33
    FileNetworkOpenInformation    = 34
    FileAttributeTagInformation   = 35
    FileTrackingInformation       = 36
    FileMaximumInformation        = 37

struc FILE_ATTRIBUTE_TAG_INFORMATION {
        .FileAttributes  dd   ?
        .ReparseTag      dd   ?
}
struct FILE_ATTRIBUTE_TAG_INFORMATION

struc FILE_DISPOSITION_INFORMATION {
        .DeleteFile      db   ?
}
struct FILE_DISPOSITION_INFORMATION

struc FILE_END_OF_FILE_INFORMATION {
        .EndOfFile       rb   8  ; LARGE_INTEGER   <>
}
struct FILE_END_OF_FILE_INFORMATION

struc FILE_FULL_EA_INFORMATION {
        .NextEntryOffset         dd    ?       ; 00h
        .qwFlags                 db    ?       ; 04h
        .EaNameLength            db    ?       ; 05h
        .EaValueLength           dw    ?       ; 06h
        .EaName                  db    ?       ; 08h
                                 rb    3
}
struct FILE_FULL_EA_INFORMATION

; +
; Define the file system information class values
;
; WARNING:  The order of the following values are assumed by the I/O system.
;           Any changes made here should be reflected there as well.
; -

;typedef enum _FSINFOCLASS {
    FileFsVolumeInformation      = 1
    FileFsLabelInformation       = 2
    FileFsSizeInformation        = 3
    FileFsDeviceInformation      = 4
    FileFsAttributeInformation   = 5
    FileFsControlInformation     = 6
    FileFsFullSizeInformation    = 7
    FileFsObjectIdInformation    = 8
    FileFsMaximumInformation     = 9

struc FILE_FS_DEVICE_INFORMATION {
        .DeviceType              dd   ?       ; 00h DEVICE_TYPE
        .Characteristics         dd   ?       ; 04h
}
struct FILE_FS_DEVICE_INFORMATION

; Define types of bus information.

;typedef enum _BUS_DATA_TYPE {
    ConfigurationSpaceUndefined         = -1
    Cmos                                                        = 0
    EisaConfiguration                           = 1
    Pos                                                         = 2
    CbusConfiguration                           = 3
    PCIConfiguration                            = 4
    VMEConfiguration                            = 5
    NuBusConfiguration                          = 6
    PCMCIAConfiguration                         = 7
    MPIConfiguration                            = 8
    MPSAConfiguration                           = 9
    PNPISAConfiguration                         = 10
    SgiInternalConfiguration            = 11
    MaximumBusDataType                          = 12
;} BUS_DATA_TYPE, *PBUS_DATA_TYPE;

; Define I/O Driver error log packet structure.  This structure is filled in
; by the driver.

struc IO_ERROR_LOG_PACKET {
        .MajorFunctionCode                       db    ?
        .RetryCount                              db    ?
        .DumpDataSize                            dw    ?
        .NumberOfStrings                         dw    ?
        .StringOffset                            dw    ?
        .EventCategory                           dw    ?
        .ErrorCode                               dd    ?       ; NTSTATUS
        .UniqueErrorValue                        dd    ?
        .FinalStatus                             dd    ?       ; NTSTATUS
        .SequenceNumber                          dd    ?
        .IoControlCode                           dd    ?
        .DeviceOffset                            dq    ?       ;LARGE_INTEGER   <>
        .DumpData                                rd    1
}
struct IO_ERROR_LOG_PACKET

; Define the I/O error log message.  This message is sent by the error log
; thread over the lpc port.

struc IO_ERROR_LOG_MESSAGE {
        .Type                      dw    ?
        .Size                      dw    ?
        .DriverNameLength          dw    ?
                                   dw    ?       ; padding
        .TimeStamp                 dq    ?       ;LARGE_INTEGER   <>
        .DriverNameOffset          dd    ?
        .EntryData                 rb    sizeof.IO_ERROR_LOG_PACKET ;IO_ERROR_LOG_PACKET     <>
}
struct IO_ERROR_LOG_MESSAGE

; Define the maximum message size that will be sent over the LPC to the
; application reading the error log entries.

; Regardless of LPC size restrictions, ERROR_LOG_MAXIMUM_SIZE must remain
; a value that can fit in a UCHAR.

ERROR_LOG_LIMIT_SIZE            = (256-16)

; This limit, exclusive of IO_ERROR_LOG_MESSAGE_HEADER_LENGTH, also applies
; to IO_ERROR_LOG_MESSAGE_LENGTH

IO_ERROR_LOG_MESSAGE_HEADER_LENGTH      = ( (sizeof.IO_ERROR_LOG_MESSAGE) - (sizeof.IO_ERROR_LOG_PACKET) +  2*40 )

ERROR_LOG_MESSAGE_LIMIT_SIZE            = ( ERROR_LOG_LIMIT_SIZE + IO_ERROR_LOG_MESSAGE_HEADER_LENGTH )

IF DEFINED _WIN64
        PORT_MAXIMUM_MESSAGE_LENGTH     = 512
ELSE
        PORT_MAXIMUM_MESSAGE_LENGTH     = 256
END IF

; IO_ERROR_LOG_MESSAGE_LENGTH is
; min(PORT_MAXIMUM_MESSAGE_LENGTH, ERROR_LOG_MESSAGE_LIMIT_SIZE)

IF PORT_MAXIMUM_MESSAGE_LENGTH > ERROR_LOG_MESSAGE_LIMIT_SIZE
        IO_ERROR_LOG_MESSAGE_LENGTH                     = ERROR_LOG_MESSAGE_LIMIT_SIZE
ELSE
        IO_ERROR_LOG_MESSAGE_LENGTH                     = PORT_MAXIMUM_MESSAGE_LENGTH
END IF
;IO_ERROR_LOG_MESSAGE_LENGTH                    = ( (PORT_MAXIMUM_MESSAGE_LENGTH > ERROR_LOG_MESSAGE_LIMIT_SIZE) ?           \
;        ERROR_LOG_MESSAGE_LIMIT_SIZE :                                        \
;        PORT_MAXIMUM_MESSAGE_LENGTH)

; Define the maximum packet size a driver can allocate.

ERROR_LOG_MAXIMUM_SIZE                          = ( IO_ERROR_LOG_MESSAGE_LENGTH - IO_ERROR_LOG_MESSAGE_HEADER_LENGTH )

; Registry Specific Access Rights.

KEY_QUERY_VALUE         = 0001h
KEY_SET_VALUE           = 0002h
KEY_CREATE_SUB_KEY      = 0004h
KEY_ENUMERATE_SUB_KEYS  = 0008h
KEY_NOTIFY              = 0010h
KEY_CREATE_LINK         = 0020h

KEY_READ        = (STANDARD_RIGHTS_READ or KEY_QUERY_VALUE or KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY) AND NOT SYNCHRONIZE
KEY_WRITE       = (STANDARD_RIGHTS_WRITE or KEY_SET_VALUE or KEY_CREATE_SUB_KEY) AND NOT SYNCHRONIZE
KEY_EXECUTE     = (KEY_READ AND NOT SYNCHRONIZE)
KEY_ALL_ACCESS  = (STANDARD_RIGHTS_ALL or KEY_QUERY_VALUE or KEY_SET_VALUE or KEY_CREATE_SUB_KEY or KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY or KEY_CREATE_LINK) AND NOT SYNCHRONIZE

; Open/Create Options

REG_OPTION_RESERVED         = 00000000   ; Parameter is reserved
REG_OPTION_NON_VOLATILE     = 00000000   ; Key is preserved when system is rebooted
REG_OPTION_VOLATILE         = 00000001   ; Key is not preserved when system is rebooted
REG_OPTION_CREATE_LINK      = 00000002   ; Created key is a symbolic link
REG_OPTION_BACKUP_RESTORE   = 00000004   ; open for backup or restore special access rules privilege required
REG_OPTION_OPEN_LINK        = 00000008   ; Open symbolic link
REG_LEGAL_OPTION                        = (REG_OPTION_RESERVED or REG_OPTION_NON_VOLATILE or REG_OPTION_VOLATILE or REG_OPTION_CREATE_LINK or REG_OPTION_BACKUP_RESTORE or REG_OPTION_OPEN_LINK)

; Key creation/open disposition

REG_CREATED_NEW_KEY         = 00000001   ; New Registry Key created
REG_OPENED_EXISTING_KEY     = 00000002   ; Existing Key opened

; Key restore flags

REG_WHOLE_HIVE_VOLATILE     = 00000001   ; Restore whole hive volatile
REG_REFRESH_HIVE            = 00000002   ; Unwind changes to last flush
REG_NO_LAZY_FLUSH           = 00000004   ; Never lazy flush this hive
REG_FORCE_RESTORE           = 00000008   ; Force the restore process even when we have open handles on subkeys

; Value entry query structures

struc KEY_VALUE_BASIC_INFORMATION {
        .TitleIndex      dd    ?       ; 00h
        .Type            dd    ?       ; 04h
        .NameLength      dd    ?       ; 08h
        .Name            dw    ?       ; 0Ch  WCHAR Variable size
                         dw    ?       ; padding
}
struct KEY_VALUE_BASIC_INFORMATION

struc KEY_VALUE_FULL_INFORMATION {
        .TitleIndex      dd    ?       ; 00h
        .Type            dd    ?       ; 04h
        .DataOffset      dd    ?       ; 08h
        .DataLength      dd    ?       ; 0Ch
        .NameLength      dd    ?       ; 10h
        .Name            dw    ?       ; 14h  WCHAR Variable size
                         dw    ?       ; 16h  padding
        .Data:                         ; Data[1];     // Variable size data not declared
}
struct KEY_VALUE_FULL_INFORMATION

struc KEY_VALUE_PARTIAL_INFORMATION {
        .TitleIndex      dd      ?
        .Type            dd      ?
        .DataLength      dd      ?
        .Data            db      ?       ; Variable size
                         rb      3       ; padding
}
struct KEY_VALUE_PARTIAL_INFORMATION

struc KEY_VALUE_PARTIAL_INFORMATION_ALIGN64 {
        .Type            dd    ?
        .DataLength      dd    ?
        .Data            db    ?       ; Variable size
                         rb    3       ; padding
}
struct KEY_VALUE_PARTIAL_INFORMATION_ALIGN64

struc KEY_VALUE_ENTRY {
        .ValueName       dd   ?       ; PTR UNICODE_STRING
        .DataLength      dd   ?
        .DataOffset      dd   ?
        .Type            dd   ?
}
struct KEY_VALUE_ENTRY

;typedef enum _KEY_VALUE_INFORMATION_CLASS {
KeyValueBasicInformation                        = 0
KeyValueFullInformation                         = 1
KeyValuePartialInformation                      = 2
KeyValueFullInformationAlign64          = 3
KeyValuePartialInformationAlign64       = 4

;OBJ_NAME_PATH_SEPARATOR                dw "\", "\"

; Object Manager Object Type Specific Access Rights.

OBJECT_TYPE_CREATE              = 0001

OBJECT_TYPE_ALL_ACCESS  = (STANDARD_RIGHTS_REQUIRED or 1)

; Object Manager Directory Specific Access Rights.

DIRECTORY_QUERY                 = 0001
DIRECTORY_TRAVERSE              = 0002
DIRECTORY_CREATE_OBJECT         = 0004
DIRECTORY_CREATE_SUBDIRECTORY   = 0008

DIRECTORY_ALL_ACCESS                    = (STANDARD_RIGHTS_REQUIRED or 0Fh)

; Object Manager Symbolic Link Specific Access Rights.

SYMBOLIC_LINK_QUERY                             = 0001

SYMBOLIC_LINK_ALL_ACCESS                = (STANDARD_RIGHTS_REQUIRED or 1)

struc OBJECT_NAME_INFORMATION {
        .Name   rb   8    ; UNICODE_STRING  <>
}
struct OBJECT_NAME_INFORMATION

DUPLICATE_CLOSE_SOURCE      = 00000001  ; winnt
DUPLICATE_SAME_ACCESS       = 00000002  ; winnt
DUPLICATE_SAME_ATTRIBUTES   = 00000004

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Section Information Structures.
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;typedef enum _SECTION_INHERIT {
    ViewShare   = 1
    ViewUnmap   = 2

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Section Access Rights.
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

;; begin_winnt
SECTION_QUERY       = 0001h
SECTION_MAP_WRITE   = 0002h
SECTION_MAP_READ    = 0004h
SECTION_MAP_EXECUTE = 0008h
SECTION_EXTEND_SIZE = 0010h

SECTION_ALL_ACCESS                      = (STANDARD_RIGHTS_REQUIRED or SECTION_QUERY or SECTION_MAP_WRITE or SECTION_MAP_READ or SECTION_MAP_EXECUTE or SECTION_EXTEND_SIZE)

;; end_winnt

SEGMENT_ALL_ACCESS                      = SECTION_ALL_ACCESS

PAGE_NOACCESS                   = 01h     ; winnt
PAGE_READONLY                   = 02h     ; winnt
PAGE_READWRITE                  = 04h     ; winnt
PAGE_WRITECOPY                  = 08h     ; winnt
PAGE_EXECUTE                    = 10h     ; winnt
PAGE_EXECUTE_READ               = 20h     ; winnt
PAGE_EXECUTE_READWRITE  = 40h     ; winnt
PAGE_EXECUTE_WRITECOPY  = 80h     ; winnt
PAGE_GUARD                              = 100h     ; winnt
PAGE_NOCACHE                    = 200h     ; winnt
PAGE_WRITECOMBINE               = 400h     ; winnt

MEM_COMMIT                              = 1000h
MEM_RESERVE                             = 2000h
MEM_DECOMMIT                    = 4000h
MEM_RELEASE                             = 8000h
MEM_FREE                                = 10000h
MEM_PRIVATE                             = 20000h
MEM_MAPPED                              = 40000h
MEM_RESET                               = 80000h
MEM_TOP_DOWN                    = 100000h
MEM_LARGE_PAGES                 = 20000000h
MEM_4MB_PAGES                   = 80000000h
SEC_RESERVE                             = 4000000h
PROCESS_DUP_HANDLE              = 0040h  ; winnt
PROCESS_ALL_ACCESS              = STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 0FFFh

MAXIMUM_PROCESSORS              = 32

; Thread Specific Access Rights

THREAD_TERMINATE                        = 0001h  ; winnt
THREAD_SET_INFORMATION          = 0020h  ; winnt

THREAD_ALL_ACCESS                       = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 3FFh)

; ClientId

struc CLIENT_ID {        ; sizeof = 8
        .UniqueProcess   dd  ?
        .UniqueThread    dd  ?
}
struct CLIENT_ID

; Thread Environment Block (and portable part of Thread Information Block)

; +
;  NT_TIB - Thread Information Block - Portable part.
;
;      This is the subsystem portable part of the Thread Information Block.
;      It appears as the first part of the TEB for all threads which have
;      a user mode component.
; -

struc NT_TIB {                           ; sizeof = 1Ch
        .ExceptionList                   dd   ?       ; PTR EXCEPTION_REGISTRATION_RECORD
        .StackBase                       dd   ?       ; 04h
        .StackLimit                      dd   ?       ; 08h
        .SubSystemTib                    dd   ?       ; 0Ch
        ;union
                .FiberData:                           ; 10h
                .Version                 dd   ?       ; 10h
        ;ends
        .ArbitraryUserPointer            dd   ?       ; 14h
        .Self                            dd   ?       ; 18h PTR NT_TIB
}
struct NT_TIB

; Process Information Classes

; typedef enum _PROCESSINFOCLASS
    ProcessBasicInformation                     = 0
    ProcessQuotaLimits                          = 1
    ProcessIoCounters                           = 2
    ProcessVmCounters                           = 3
    ProcessTimes                                        = 4
    ProcessBasePriority                         = 5
    ProcessRaisePriority                        = 6
    ProcessDebugPort                            = 7
    ProcessExceptionPort                        = 8
    ProcessAccessToken                          = 9
    ProcessLdtInformation                       = 10
    ProcessLdtSize                                      = 11
    ProcessDefaultHardErrorMode         = 12
    ProcessIoPortHandlers                       = 13 ; Note: this is kernel mode only
    ProcessPooledUsageAndLimits         = 14
    ProcessWorkingSetWatch                      = 15
    ProcessUserModeIOPL                         = 16
    ProcessEnableAlignmentFaultFixup = 17
    ProcessPriorityClass                        = 18
    ProcessWx86Information                      = 19
    ProcessHandleCount                          = 20
    ProcessAffinityMask                         = 21
    ProcessPriorityBoost                        = 22
    ProcessDeviceMap                            = 23
    ProcessSessionInformation           = 24
    ProcessForegroundInformation        = 25
    ProcessWow64Information                     = 26
    MaxProcessInfoClass                         = 27

; Thread Information Classes

; typedef enum _THREADINFOCLASS
    ThreadBasicInformation                      = 0
    ThreadTimes                                         = 1
    ThreadPriority                                      = 2
    ThreadBasePriority                          = 3
    ThreadAffinityMask                          = 4
    ThreadImpersonationToken            = 5
    ThreadDescriptorTableEntry          = 6
    ThreadEnableAlignmentFaultFixup     = 7
    ThreadEventPair_Reusable            = 8
    ThreadQuerySetWin32StartAddress     = 9
    ThreadZeroTlsCell                           = 10
    ThreadPerformanceCount                      = 11
    ThreadAmILastThread                         = 12
    ThreadIdealProcessor                        = 13
    ThreadPriorityBoost                         = 14
    ThreadSetTlsArrayAddress            = 15
    ThreadIsIoPending                           = 16
    ThreadHideFromDebugger                      = 17
    MaxThreadInfoClass                          = 18

; Process Information Structures

; +
; PageFaultHistory Information
;  NtQueryInformationProcess using ProcessWorkingSetWatch
; -

struc PROCESS_WS_WATCH_INFORMATION {     ; sizeof = 8
        .FaultingPc      dd   ?
        .FaultingVa      dd   ?
}
struct PROCESS_WS_WATCH_INFORMATION

; +
; Basic Process Information
;  NtQueryInformationProcess using ProcessBasicInfo
; -

struc PROCESS_BASIC_INFORMATION {        ; sizeof = 18h
        .ExitStatus                      dd        ?
        .PebBaseAddress                  dd           ? ; PPEB
        .AffinityMask                    dd           ?
        .BasePriority                    dd           ? ; KPRIORITY
        .UniqueProcessId                 dd           ?
        .InheritedFromUniqueProcessId    dd           ?
}
struct PROCESS_BASIC_INFORMATION

; +
; Process I/O Counters
;  NtQueryInformationProcess using ProcessIoCounters
; -

struc IO_COUNTERS {              ; sizeof = 30h
        .ReadOperationCount      dq   ?
        .WriteOperationCount     dq   ?       ; 08h
        .OtherOperationCount     dq   ?       ; 10h
        .ReadTransferCount       dq   ?       ; 18h
        .WriteTransferCount      dq   ?       ; 20h
        .OtherTransferCount      dq   ?       ; 28h
}
struct IO_COUNTERS

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Interrupt Request Level definitions
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

PASSIVE_LEVEL           = 0                   ; Passive release level
LOW_LEVEL                       = 0                   ; Lowest interrupt level
APC_LEVEL                       = 1                   ; APC interrupt level
DISPATCH_LEVEL          = 2                   ; Dispatcher level

PROFILE_LEVEL           = 27                  ; timer used for profiling.
CLOCK1_LEVEL            = 28                  ; Interval clock 1 level - Not used on x86
CLOCK2_LEVEL            = 28                  ; Interval clock 2 level
IPI_LEVEL                       = 29                  ; Interprocessor interrupt level
POWER_LEVEL                     = 30                  ; Power failure level
HIGH_LEVEL                      = 31                  ; Highest interrupt level
SYNCH_LEVEL                     = (IPI_LEVEL-1)       ; synchronization level

; Processor Control Region Structure Definition

PCR_MINOR_VERSION       = 1
PCR_MAJOR_VERSION       = 1

; base address 0FFDFF000h

struc KPCR {                     ; sizeof = 54h

        ; Start of the architecturally defined section of the PCR. This section
        ; may be directly addressed by vendor/platform specific HAL code and will
        ; not change from version to version of NT.

        .NtTib                   rb           sizeof.NT_TIB ; NT_TIB  <>
        .SelfPcr                 dd           ? ; 1Ch PTR KPCR flat address of this PCR
        .Prcb                    dd           ? ; 20h pointer to Prcb
        .Irql                    db           ? ; 24h KIRQL
                                 rb           3 ; padding
        .IRR                     dd           ? ; 28h
        .IrrActive               dd           ? ; 2Ch
        .IDR                     dd           ? ; 30h
        .Reserved2               dd           ?

        .IDT                     dd           ? ; 38h PTR KIDTENTRY
        .GDT                     dd           ? ; 3Ch PTR KGDTENTRY
        .TSS                     dd           ? ; 40h PTR KTSS
        .MajorVersion            dw           ? ; 44h
        .MinorVersion            dw           ? ; 46h
        .SetMember               dd           ? ; 48h
        .StallScaleFactor        dd           ? ; 4Ch
        .DebugActive             db           ? ; 50h
        .Number                  db           ? ; 51h
                                 rb           2 ; padding
}
struct KPCR

; i386 Specific portions of mm component

; Define the page size for the Intel 386 as 4096 (0x1000).

PAGE_SIZE       = 1000h

; Define the number of trailing zeroes in a page aligned virtual address.
; This is used as the shift count when shifting virtual addresses to
; virtual page numbers.

PAGE_SHIFT      = 12

; Define the number of bits to shift to right justify the Page Directory Index
; field of a PTE.

PDI_SHIFT_X86           = 22
PDI_SHIFT_X86PAE        = 21
PPI_SHIFT                       = 30  ; X86PAE

; Define the number of bits to shift to right justify the Page Table Index
; field of a PTE.

PTI_SHIFT       = 12

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; The lowest user address reserves the low 64k.
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

MM_LOWEST_USER_ADDRESS  = 10000h

; The lowest address for system space.

MM_LOWEST_SYSTEM_ADDRESS = 0C0C00000h

KI_USER_SHARED_DATA     = 0ffdf0000h
SharedUserData          = KI_USER_SHARED_DATA

; +
; Result type definition for i386.  (Machine specific enumerate type
; which is return type for portable exinterlockedincrement/decrement
; procedures.)  In general, you should use the enumerated type defined
; in ex.h instead of directly referencing these constants.
; -

; Flags loaded into AH by LAHF instruction

EFLAG_SIGN              = 8000h
EFLAG_ZERO              = 4000h
EFLAG_SELECT    = EFLAG_SIGN or EFLAG_ZERO

; Processor Control Block (PRCB)

PRCB_MINOR_VERSION              = 1
PRCB_MAJOR_VERSION              = 1
PRCB_BUILD_DEBUG                = 1
PRCB_BUILD_UNIPROCESSOR = 2

; KPRCB base address is 0FFDFF120h

struc KPRCB {            ; sizeof = 1Ch

; Major and minor version numbers of the PCR.

        .MinorVersion    dw    ?
        .MajorVersion    dw    ?

        ; Start of the architecturally defined section of the PRCB. This section
        ; may be directly addressed by vendor/platform specific HAL code and will
        ; not change from version to version of NT.

        .CurrentThread   dd    ? ; 04h PTR KTHREAD
        .NextThread      dd    ? ; 08h PTR KTHREAD
        .IdleThread      dd    ? ; 0Ch PTR KTHREAD
        .Number          db    ? ; 10h
        .Reserved        db    ? ; 11h
        .BuildType       dw    ? ; 12h
        .SetMember       dd    ? ; 14h

        .RestartBlock    dd    ? ; 18h PTR RESTART_BLOCK

        ; End of the architecturally defined section of the PRCB. This section
        ; may be directly addressed by vendor/platform specific HAL code and will
        ; not change from version to version of NT.

}
struct KPRCB

; Define system time structure.

struc KSYSTEM_TIME {             ; sizeof = 0Ch
        .LowPart         dd          ?       ; 0000h
        .High1Time       dd          ?       ; 0004h
        .High2Time       dd          ?       ; 0008h
}
struct KSYSTEM_TIME

; Size of kernel mode stack.

KERNEL_STACK_SIZE                       = 12288

; Define size of large kernel mode stack for callbacks.

KERNEL_LARGE_STACK_SIZE         = 61440

; Define number of pages to initialize in a large kernel stack.

KERNEL_LARGE_STACK_COMMIT       = 12288

;  Define the size of the 80387 save area, which is in the context frame.

SIZE_OF_80387_REGISTERS         = 80

; The following flags control the contents of the CONTEXT structure.

CONTEXT_i386                            = 00010000h    ; this assumes that i386 and
CONTEXT_i486                            = 00010000h    ; i486 have identical context records

CONTEXT_CONTROL                         = (CONTEXT_i386 or 00000001h) ; SS:SP, CS:IP, FLAGS, BP
CONTEXT_INTEGER                         = (CONTEXT_i386 or 00000002h) ; AX, BX, CX, DX, SI, DI
CONTEXT_SEGMENTS                        = (CONTEXT_i386 or 00000004h) ; DS, ES, FS, GS
CONTEXT_FLOATING_POINT          = (CONTEXT_i386 or 00000008h) ; 387 state
CONTEXT_DEBUG_REGISTERS         = (CONTEXT_i386 or 00000010h) ; DB 0-3,6,7
CONTEXT_EXTENDED_REGISTERS      = (CONTEXT_i386 or 00000020h) ; cpu specific extensions

CONTEXT_FULL                            = (CONTEXT_CONTROL or CONTEXT_INTEGER or CONTEXT_SEGMENTS)

MAXIMUM_SUPPORTED_EXTENSION     = 512


struc FLOATING_SAVE_AREA {               ; sizeof = 070h
        .ControlWord     dd           ?       ; 0000h
        .StatusWord      dd           ?       ; 0004h
        .TagWord         dd           ?       ; 0008h
        .ErrorOffset     dd           ?       ; 000Ch
        .ErrorSelector   dd           ?       ; 0010h
        .DataOffset      dd           ?       ; 0014h
        .DataSelector    dd           ?       ; 0018h
        .RegisterArea    rb           SIZE_OF_80387_REGISTERS  ; 001Ch
        .Cr0NpxState     dd           ?       ; 006Ch
}
struct FLOATING_SAVE_AREA


; +
; Context Frame
;
;  This frame has a several purposes: 1) it is used as an argument to
;  NtContinue, 2) is is used to constuct a call frame for APC delivery,
;  and 3) it is used in the user level thread creation routines.
;
;  The layout of the record conforms to a standard call frame.
; -

struc CONTEXT {                  ; sizeof = 02CCh

        ; The flags values within this flag control the contents of
        ; a CONTEXT record.
        ;
        ; If the context record is used as an input parameter, then
        ; for each portion of the context record controlled by a flag
        ; whose value is set, it is assumed that that portion of the
        ; context record contains valid context. If the context record
        ; is being used to modify a threads context, then only that
        ; portion of the threads context will be modified.
        ;
        ; If the context record is used as an IN OUT parameter to capture
        ; the context of a thread, then only those portions of the thread's
        ; context corresponding to set flags will be returned.
        ;
        ; The context record is never used as an OUT only parameter.

        .ContextFlags            dd           ?       ; 0000h

        ; This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
        ; set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
        ; included in CONTEXT_FULL.

        .regDr0                          dd           ?       ; 0004h
        .regDr1                          dd           ?       ; 0008h
        .regDr2                          dd           ?       ; 000Ch
        .regDr3                          dd           ?       ; 0010h
        .regDr6                          dd           ?       ; 0014h
        .regDr7                          dd           ?       ; 0018h

        ; This section is specified/returned if the
        ; ContextFlags word contians the flag CONTEXT_FLOATING_POINT.

        .FloatSave                       rb sizeof.FLOATING_SAVE_AREA ; 001Ch

        ; This section is specified/returned if the
        ; ContextFlags word contians the flag CONTEXT_SEGMENTS.

        .regSegGs                        dd           ?       ; 008Ch
        .regSegFs                        dd           ?       ; 0090h
        .regSegEs                        dd           ?       ; 0094h
        .regSegDs                        dd           ?       ; 0098h

        ; This section is specified/returned if the
        ; ContextFlags word contians the flag CONTEXT_INTEGER.

        .regEdi                          dd           ?       ; 009Ch
        .regEsi                          dd           ?       ; 00A0h
        .regEbx                          dd           ?       ; 00A4h
        .regEdx                          dd           ?       ; 00A8h
        .regEcx                          dd           ?       ; 00ACh
        .regEax                          dd           ?       ; 00B0h

        ; This section is specified/returned if the
        ; ContextFlags word contians the flag CONTEXT_CONTROL.

        .regEbp                          dd           ?       ; 00B4h
        .regEip                          dd           ?       ; 00B8h
        .regSegCs                        dd           ?       ; 00BCh  MUST BE SANITIZED
        .regEFlags                       dd           ?       ; 00C0h  MUST BE SANITIZED
        .regEsp                          dd           ?       ; 00C4h
        .regSegSs                        dd           ?       ; 00C8h


        ; This section is specified/returned if the ContextFlags word
        ; contains the flag CONTEXT_EXTENDED_REGISTERS.
        ; The format and contexts are processor specific

        .ExtendedRegisters       rb            MAXIMUM_SUPPORTED_EXTENSION  ; 00CCh

}
struct CONTEXT

;/ Event Specific Access Rights.

EVENT_QUERY_STATE       = 0001
EVENT_MODIFY_STATE      = 0002  ; winnt
EVENT_ALL_ACCESS                = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 3) ; winnt

; Semaphore Specific Access Rights.

SEMAPHORE_QUERY_STATE       = 0001
SEMAPHORE_MODIFY_STATE      = 0002  ; winnt

SEMAPHORE_ALL_ACCESS            = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or 3) ; winnt

; Defined processor features

PF_FLOATING_POINT_PRECISION_ERRATA  = 0
PF_FLOATING_POINT_EMULATED          = 1
PF_COMPARE_EXCHANGE_DOUBLE          = 2
PF_MMX_INSTRUCTIONS_AVAILABLE       = 3
PF_PPC_MOVEMEM_64BIT_OK             = 4
PF_ALPHA_BYTE_INSTRUCTIONS          = 5
PF_XMMI_INSTRUCTIONS_AVAILABLE      = 6
PF_3DNOW_INSTRUCTIONS_AVAILABLE     = 7
PF_RDTSC_INSTRUCTION_AVAILABLE      = 8
PF_PAE_ENABLED                      = 9

;typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE {
        StandardDesign  = 0   ; None == 0 == standard design
        NEC98x86                = 1   ; NEC PC98xx series on X86
        EndAlternatives = 2   ; past end of known alternatives

PROCESSOR_FEATURE_MAX   = 64

; Predefined Value Types.

REG_NONE                                                = 0 ; No value type
REG_SZ                                                  = 1 ; Unicode nul terminated string
REG_EXPAND_SZ                                   = 2 ; Unicode nul terminated string (with environment variable references)
REG_BINARY                                              = 3 ; Free form binary
REG_DWORD                                               = 4 ; 32-bit number
REG_DWORD_LITTLE_ENDIAN                 = 4 ; 32-bit number (same as REG_DWORD)
REG_DWORD_BIG_ENDIAN                    = 5 ; 32-bit number
REG_LINK                                                = 6 ; Symbolic Link (unicode)
REG_MULTI_SZ                                    = 7 ; Multiple Unicode strings
REG_RESOURCE_LIST                               = 8 ; Resource list in the resource map
REG_FULL_RESOURCE_DESCRIPTOR    = 9 ; Resource list in the hardware description
REG_RESOURCE_REQUIREMENTS_LIST  = 10
REG_QWORD                                               = 11 ; 64-bit number
REG_QWORD_LITTLE_ENDIAN                 = 11 ; 64-bit number (same as REG_QWORD)

; Service Types (Bit Mask)

SERVICE_KERNEL_DRIVER          = 00000001
SERVICE_FILE_SYSTEM_DRIVER     = 00000002
SERVICE_ADAPTER                = 00000004
SERVICE_RECOGNIZER_DRIVER      = 00000008

SERVICE_DRIVER                 = (SERVICE_KERNEL_DRIVER or SERVICE_FILE_SYSTEM_DRIVER or SERVICE_RECOGNIZER_DRIVER)

SERVICE_WIN32_OWN_PROCESS      = 00000010h
SERVICE_WIN32_SHARE_PROCESS    = 00000020h
SERVICE_WIN32                  = (SERVICE_WIN32_OWN_PROCESS or SERVICE_WIN32_SHARE_PROCESS)

SERVICE_INTERACTIVE_PROCESS    = 00000100h

SERVICE_TYPE_ALL               = (SERVICE_WIN32 or SERVICE_ADAPTER or SERVICE_DRIVER or SERVICE_INTERACTIVE_PROCESS)

; Start Type

SERVICE_BOOT_START             = 00000000
SERVICE_SYSTEM_START           = 00000001
SERVICE_AUTO_START             = 00000002
SERVICE_DEMAND_START           = 00000003
SERVICE_DISABLED               = 00000004

; Error control type

SERVICE_ERROR_IGNORE           = 00000000
SERVICE_ERROR_NORMAL           = 00000001
SERVICE_ERROR_SEVERE           = 00000002
SERVICE_ERROR_CRITICAL         = 00000003

; Define the registry driver node enumerations

;typedef enum _CM_SERVICE_NODE_TYPE {
    DriverType               = SERVICE_KERNEL_DRIVER
    FileSystemType           = SERVICE_FILE_SYSTEM_DRIVER
    Win32ServiceOwnProcess   = SERVICE_WIN32_OWN_PROCESS
    Win32ServiceShareProcess = SERVICE_WIN32_SHARE_PROCESS
    AdapterType              = SERVICE_ADAPTER
    RecognizerType           = SERVICE_RECOGNIZER_DRIVER

;typedef enum _CM_SERVICE_LOAD_TYPE {
    BootLoad    = SERVICE_BOOT_START
    SystemLoad  = SERVICE_SYSTEM_START
    AutoLoad    = SERVICE_AUTO_START
    DemandLoad  = SERVICE_DEMAND_START
    DisableLoad = SERVICE_DISABLED

;typedef enum _CM_ERROR_CONTROL_TYPE {
    IgnoreError   = SERVICE_ERROR_IGNORE
    NormalError   = SERVICE_ERROR_NORMAL
    SevereError   = SERVICE_ERROR_SEVERE
    CriticalError = SERVICE_ERROR_CRITICAL

; Exception flag definitions.

EXCEPTION_NONCONTINUABLE                        = 1   ; Noncontinuable exception

; Define maximum number of exception parameters.

EXCEPTION_MAXIMUM_PARAMETERS            = 15  ; maximum number of exception parameters

; Exception record definition.

struc EXCEPTION_RECORD {         ; sizeof = 050h
        .ExceptionCode                   dd           ?       ; 0000h
        .ExceptionFlags                  dd           ?       ; 0004h
        .ExceptionRecord                 dd           ?       ; 0008h PTR EXCEPTION_RECORD
        .ExceptionAddress                dd           ?       ; 000Ch
        .NumberParameters                dd           ?       ; 0010h
        .ExceptionInformation            rd           EXCEPTION_MAXIMUM_PARAMETERS ; 0014h
}
struct EXCEPTION_RECORD

struc EXCEPTION_RECORD32 {
        .ExceptionCode                   dd   ?
        .ExceptionFlags                  dd   ?
        .ExceptionRecord                 dd   ?
        .ExceptionAddress                dd   ?
        .NumberParameters                dd   ?
        .ExceptionInformation            rd   EXCEPTION_MAXIMUM_PARAMETERS
}
struct EXCEPTION_RECORD32

; Typedef for pointer returned by exception_info()

struc EXCEPTION_POINTERS {
        .ExceptionRecord dd   ?       ; PTR EXCEPTION_RECORD
        .ContextRecord   dd   ?       ; PTR CONTEXT
}
struct EXCEPTION_POINTERS

; Wait reasons

;typedef enum _KWAIT_REASON {
    Executive                   = 0
    FreePage                    = 1
    PageIn                              = 2
    PoolAllocation              = 3
    DelayExecution              = 4
    Suspended                   = 5
    UserRequest                 = 6
    WrExecutive                 = 7
    WrFreePage                  = 8
    WrPageIn                    = 9
    WrPoolAllocation    = 10
    WrDelayExecution    = 11
    WrSuspended                 = 12
    WrUserRequest               = 13
    WrEventPair                 = 14
    WrQueue                             = 15
    WrLpcReceive                = 16
    WrLpcReply                  = 17
    WrVirtualMemory             = 18
    WrPageOut                   = 19
    WrRendezvous                = 20
    Spare2                              = 21
    Spare3                              = 22
    Spare4                              = 23
    Spare5                              = 24
    Spare6                              = 25
    WrKernel                    = 26
    MaximumWaitReason   = 27

; +
; Common dispatcher object header
;
; N.B. The size field contains the number of dwords in the structure.
; -

struc DISPATCHER_HEADER {                ; sizeof = 010h
        .Type                    db          ?       ; 0000h  DISP_TYPE_*
        .Absolute                db          ?       ; 0001h
        .Size                    db          ?       ; 0002h
        .Inserted                db          ?       ; 0003h
        .SignalState             dd          ?       ; 0004h
        .WaitListHead            rb          8       ; LIST_ENTRY <>   ; 0008h
}
struct DISPATCHER_HEADER

struc KWAIT_BLOCK {              ; sizeof = 018h
        .WaitListEntry           rb           8       ; LIST_ENTRY <>   ; 0000h
        .Thread                  dd           ?       ; 0008h  PTR KTHREAD
        .Object                  dd           ?       ; 000Ch
        .NextWaitBlock           dd           ?       ; 0010h  PTR KWAIT_BLOCK
        .WaitKey                 dw           ?       ; 0014h
        .WaitType                dw           ?       ; 0016h
}
struct KWAIT_BLOCK

; Kernel object structure definitions

; Device Queue object and entry

struc KDEVICE_QUEUE {            ; sizeof = 014h
        .Type                    dw           ?       ; 0000h
        .Size                    dw           ?       ; 0002h
        .DeviceListHead          rb           8       ; LIST_ENTRY <>   ; 0004h
        .Lock                    dd           ?       ; 000Ch  KSPIN_LOCK
        .Busy                    db           ?       ; 0010h  BOOLEAN
                                 rb           3       ; padding
}
struct KDEVICE_QUEUE

struc KDEVICE_QUEUE_ENTRY {              ; sizeof = 010h
        .DeviceListEntry         rb            8       ; LIST_ENTRY <>   ; 0000h
        .SortKey                 dd            ?       ; 0008h
        .Inserted                db            ?       ; 000Ch
                                 rb            3       ; padding
}
struct KDEVICE_QUEUE_ENTRY

; Event object

struc KEVENT {   ; sizeof = 10h
        .Header    rb   sizeof.DISPATCHER_HEADER
}
struct KEVENT

; Mutant object

struc KMUTANT {          ; sizeof = 020h
        .Header                  rb             sizeof.DISPATCHER_HEADER ; 0000h
        .MutantListEntry         rb             8  ; LIST_ENTRY  <>      ; 0010h
        .OwnerThread             dd             ?       ; 0018h PTR KTHREAD *RESTRICTED_POINTER
        .Abandoned               db             ?       ; 001Ch  BOOLEAN
        .ApcDisable              db             ?       ; 001Dh
                                 dw             ?       ; 001Eh  padding
}
struct KMUTANT

KMUTEX = KMUTANT


; Semaphore object

struc KSEMAPHORE {       ; sizeof = 14h
        .Header  rb             sizeof.DISPATCHER_HEADER
        .Limit   dd             ?
}
struct KSEMAPHORE

; Timer object

struc KTIMER {           ; sizeof = 028h
        .Header          rb     sizeof.DISPATCHER_HEADER ; 0000h
        .DueTime         dq     ?       ; ULARGE_INTEGER  <>      ; 0010h
        .TimerListEntry  rb     8       ; LIST_ENTRY              <>      ; 0018h
        .Dpc             dd     ?       ; 0020h PTR KDPC
        .Period          dd     ?       ; 0024h
}
struct KTIMER

; Pool Allocation routines (in pool.c)

;typedef enum _POOL_TYPE {
    NonPagedPool                                                        = 0
    PagedPool                                                           = 1
    NonPagedPoolMustSucceed                                     = 2
    DontUseThisType                                                     = 3
    NonPagedPoolCacheAligned                            = 4
    PagedPoolCacheAligned                                       = 5
    NonPagedPoolCacheAlignedMustS                       = 6
    MaxPoolType                                                         = 7

        ; Note these per session types are carefully chosen so that the appropriate
        ; masking still applies as well as MaxPoolType above.

    NonPagedPoolSession                                         = 32
    PagedPoolSession                                            = 33
    NonPagedPoolMustSucceedSession                      = 34
    DontUseThisTypeSession                                      = 35
    NonPagedPoolCacheAlignedSession                     = 36
    PagedPoolCacheAlignedSession                        = 37
    NonPagedPoolCacheAlignedMustSSession        = 38

; +
; _EX_POOL_PRIORITY_ provides a method for the system to handle requests
; intelligently in low resource conditions.
;
; LowPoolPriority should be used when it is acceptable to the driver for the
; mapping request to fail if the system is low on resources.  An example of
; this could be for a non-critical network connection where the driver can
; handle the failure case when system resources are close to being depleted.
;
; NormalPoolPriority should be used when it is acceptable to the driver for the
; mapping request to fail if the system is very low on resources.  An example
; of this could be for a non-critical local filesystem request.
;
; HighPoolPriority should be used when it is unacceptable to the driver for the
; mapping request to fail unless the system is completely out of resources.
; An example of this would be the paging file path in a driver.
;
; SpecialPool can be specified to bound the allocation at a page end (or
; beginning).  This should only be done on systems being debugged as the
; memory cost is expensive.
;
; N.B.  These values are very carefully chosen so that the pool allocation
;       code can quickly crack the priority request.
; -

;typedef enum _EX_POOL_PRIORITY {
    LowPoolPriority                                                     = 0
    LowPoolPrioritySpecialPoolOverrun           = 8
    LowPoolPrioritySpecialPoolUnderrun          = 9
    NormalPoolPriority                                          = 16
    NormalPoolPrioritySpecialPoolOverrun        = 24
    NormalPoolPrioritySpecialPoolUnderrun       = 25
    HighPoolPriority                                            = 32
    HighPoolPrioritySpecialPoolOverrun          = 40
    HighPoolPrioritySpecialPoolUnderrun         = 41

; Routines to support fast mutexes.

struc FAST_MUTEX {               ; sizeof = 020h
        .Count           dd          ?       ; 0000h
        .Owner           dd          ?       ; 0004h PTR KTHREAD
        .Contention      dd          ?       ; 0008h
        .Event           rb          sizeof.KEVENT ; 000Ch
        .OldIrql         dd          ?       ; 001Ch
}
struct FAST_MUTEX

;  Define executive resource data structures.


struc OWNER_ENTRY {                              ; sizeof = 08h
        .OwnerThread            dd    ?       ; 0000h
        ;union
                .OwnerCount:                  ; 0004h
                .TableSize      dd    ?       ; 0004h
        ;ends
}
struct OWNER_ENTRY

struc ERESOURCE {                ; sizeof = 038h
        .SystemResourcesList             rb       8       ; LIST_ENTRY <>   ; 0000h
        .OwnerTable                      dd       ?       ; 0008h PTR OWNER_ENTRY
        .ActiveCount                     dd       ?       ; 000Ch
        .Flag                            dw       ?       ; 000Eh
        .SharedWaiters                   dd       ?       ; 0010h PTR KSEMAPHORE
        .ExclusiveWaiters                dd       ?       ; 0014h PTR KEVENT
        .OwnerThreads                    rb       sizeof.OWNER_ENTRY*2 ; 0018h
        .ContentionCount                 dd       ?       ; 0028h
        .NumberOfSharedWaiters           dw       ?       ; 002Ch
        .NumberOfExclusiveWaiters        dw       ?       ; 002Eh
        ;union
                .Address:                                 ; 0030h
                .CreatorBackTraceIndex   dd       ?       ; 0030h
        ;ends
        .SpinLock                        dd       ?       ; 0034h  KSPIN_LOCK
}
struct ERESOURCE

;  Values for ERESOURCE.Flag

ResourceNeverExclusive       = 10h
ResourceReleaseByOtherThread = 20h
ResourceOwnedExclusive       = 80h

RESOURCE_HASH_TABLE_SIZE     = 64

; Priority increment definitions.  The comment for each definition gives
; the names of the system services that use the definition when satisfying
; a wait.

; Priority increment used when satisfying a wait on an executive event
; (NtPulseEvent and NtSetEvent)

EVENT_INCREMENT                 = 1

; Priority increment when no I/O has been done.  This is used by device
; and file system drivers when completing an IRP (IoCompleteRequest).

IO_NO_INCREMENT                 = 0

; Priority increment for completing CD-ROM I/O.  This is used by CD-ROM device
; and file system drivers when completing an IRP (IoCompleteRequest)

IO_CD_ROM_INCREMENT             = 1

; Priority increment for completing disk I/O.  This is used by disk device
; and file system drivers when completing an IRP (IoCompleteRequest)

IO_DISK_INCREMENT               = 1

; Priority increment for completing keyboard I/O.  This is used by keyboard
; device drivers when completing an IRP (IoCompleteRequest)

IO_KEYBOARD_INCREMENT   = 6

; Priority increment for completing mailslot I/O.  This is used by the mail-
; slot file system driver when completing an IRP (IoCompleteRequest).

IO_MAILSLOT_INCREMENT   = 2

; Priority increment for completing mouse I/O.  This is used by mouse device
; drivers when completing an IRP (IoCompleteRequest)

IO_MOUSE_INCREMENT              = 6

; Priority increment for completing named pipe I/O.  This is used by the
; named pipe file system driver when completing an IRP (IoCompleteRequest).

IO_NAMED_PIPE_INCREMENT = 2

; Priority increment for completing network I/O.  This is used by network
; device and network file system drivers when completing an IRP
; (IoCompleteRequest).

IO_NETWORK_INCREMENT    = 2

; Priority increment for completing parallel I/O.  This is used by parallel
; device drivers when completing an IRP (IoCompleteRequest)

IO_PARALLEL_INCREMENT   = 1

; Priority increment for completing serial I/O.  This is used by serial device
; drivers when completing an IRP (IoCompleteRequest)

IO_SERIAL_INCREMENT             = 2

; Priority increment for completing sound I/O.  This is used by sound device
; drivers when completing an IRP (IoCompleteRequest)

IO_SOUND_INCREMENT              = 8

; Priority increment for completing video I/O.  This is used by video device
; drivers when completing an IRP (IoCompleteRequest)

IO_VIDEO_INCREMENT              = 1

; Priority increment used when satisfying a wait on an executive semaphore
; (NtReleaseSemaphore)

SEMAPHORE_INCREMENT             = 1

; +
; Define I/O system data structure type codes.  Each major data structure in
; the I/O system has a type code  The type field in each structure is at the
; same offset.  The following values can be used to determine which type of
; data structure a pointer refers to.
; -

IO_TYPE_ADAPTER                                 = 1
IO_TYPE_CONTROLLER                              = 2
IO_TYPE_DEVICE                                  = 3
IO_TYPE_DRIVER                                  = 4
IO_TYPE_FILE                                    = 5
IO_TYPE_IRP                                             = 6
IO_TYPE_MASTER_ADAPTER                  = 7
IO_TYPE_OPEN_PACKET                             = 8
IO_TYPE_TIMER                                   = 9
IO_TYPE_VPB                                             = 0Ah
IO_TYPE_ERROR_LOG                               = 0Bh
IO_TYPE_ERROR_MESSAGE                   = 0Ch
IO_TYPE_DEVICE_OBJECT_EXTENSION = 0Dh

; Define the major function codes for IRPs.

IRP_MJ_CREATE                                   = 0
IRP_MJ_CREATE_NAMED_PIPE                = 1
IRP_MJ_CLOSE                                    = 2
IRP_MJ_READ                                             = 3
IRP_MJ_WRITE                                    = 4
IRP_MJ_QUERY_INFORMATION                = 5
IRP_MJ_SET_INFORMATION                  = 6
IRP_MJ_QUERY_EA                                 = 7
IRP_MJ_SET_EA                                   = 8
IRP_MJ_FLUSH_BUFFERS                    = 9
IRP_MJ_QUERY_VOLUME_INFORMATION = 0Ah
IRP_MJ_SET_VOLUME_INFORMATION   = 0Bh
IRP_MJ_DIRECTORY_CONTROL                = 0Ch
IRP_MJ_FILE_SYSTEM_CONTROL              = 0Dh
IRP_MJ_DEVICE_CONTROL                   = 0Eh
IRP_MJ_INTERNAL_DEVICE_CONTROL  = 0Fh
IRP_MJ_SHUTDOWN                                 = 10h
IRP_MJ_LOCK_CONTROL                             = 11h
IRP_MJ_CLEANUP                                  = 12h
IRP_MJ_CREATE_MAILSLOT                  = 13h
IRP_MJ_QUERY_SECURITY                   = 14h
IRP_MJ_SET_SECURITY                             = 15h
IRP_MJ_POWER                                    = 16h
IRP_MJ_SYSTEM_CONTROL                   = 17h
IRP_MJ_DEVICE_CHANGE                    = 18h
IRP_MJ_QUERY_QUOTA                              = 19h
IRP_MJ_SET_QUOTA                                = 1Ah
IRP_MJ_PNP                                              = 1Bh
IRP_MJ_PNP_POWER                                = IRP_MJ_PNP  ; Obsolete....
IRP_MJ_MAXIMUM_FUNCTION                 = 1Bh

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Volume Parameter Block (VPB)
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

MAXIMUM_VOLUME_LABEL_LENGTH     = (32 * 2)        ; 32 characters

struc VPB {                              ; sizeof = 058h
        .Type                   dw           ?       ; 0000h  (IO_TYPE_VPB = 0Ah)
        .Size                   dw           ?       ; 0002h
        .Flags                   dw           ?       ; 0004h
        .VolumeLabelLength       dw           ?       ; 0006h  (in bytes without terminat. zero)
        .DeviceObject            dd           ?       ; 0008h PTR DEVICE_OBJECT
        .RealDevice              dd           ?       ; 000Ch PTR DEVICE_OBJECT
        .SerialNumber            dd           ?       ; 0010h
        .ReferenceCount          dd           ?       ; 0014h
        .VolumeLabel             rw (MAXIMUM_VOLUME_LABEL_LENGTH / 2) ; 0018h
}
struct VPB

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; Define Wait Context Block (WCB)
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc WAIT_CONTEXT_BLOCK {               ; sizeof = 028h
        .WaitQueueEntry          rb           sizeof.KDEVICE_QUEUE_ENTRY ; 0000h
        .DeviceRoutine           dd           ?       ; 0010h  PDRIVER_CONTROL
        .DeviceContext           dd           ?       ; 0014h
        .NumberOfMapRegisters    dd           ?       ; 0018h
        .DeviceObject            dd           ?       ; 001Ch
        .CurrentIrp              dd           ?       ; 0020h
        .BufferChainingDpc       dd           ?       ; 0024h PTR KDPC
}
struct WAIT_CONTEXT_BLOCK

struc CONTROLLER_OBJECT {
        .Type                    dw           ?       ; 000h
        .Size                    dw           ?       ; 002h
        .ControllerExtension     dd           ?       ; 004h
        .DeviceWaitQueue         rb           sizeof.KDEVICE_QUEUE  ; 008h

        .Spare1                  dd           ?       ; 01Ch
        .Spare2                  dq           ?       ; LARGE_INTEGER  <>  ; 020h

}
struct CONTROLLER_OBJECT

; Define Device Object (DO) flags

DO_VERIFY_VOLUME                = 00000002h
DO_BUFFERED_IO                  = 00000004h
DO_EXCLUSIVE                    = 00000008h
DO_DIRECT_IO                    = 00000010h
DO_MAP_IO_BUFFER                = 00000020h
DO_DEVICE_HAS_NAME              = 00000040h
DO_DEVICE_INITIALIZING          = 00000080h
DO_SYSTEM_BOOT_PARTITION        = 00000100h
DO_LONG_TERM_REQUESTS           = 00000200h
DO_NEVER_LAST_DEVICE            = 00000400h
DO_SHUTDOWN_REGISTERED          = 00000800h
DO_BUS_ENUMERATED_DEVICE        = 00001000h
DO_POWER_PAGABLE                = 00002000h
DO_POWER_INRUSH                 = 00004000h
DO_LOW_PRIORITY_FILESYSTEM      = 00010000h

; Device Object structure definition

struc DEVICE_OBJECT {            ; sizeof = 0B8h
        .Type                            dw           ?       ; 0000h  (IO_TYPE_DEVICE = 3)
        .Size                            dw           ?       ; 0002h
        .ReferenceCount                  dd           ?       ; 0004h
        .DriverObject                    dd           ?       ; 0008h  PTR DRIVER_OBJECT
        .NextDevice                      dd           ?       ; 000Ch  PTR DEVICE_OBJECT
        .AttachedDevice                  dd           ?       ; 0010h  PTR DEVICE_OBJECT
        .CurrentIrp                      dd           ?       ; 0014h  PTR IRP
        .Timer                           dd           ?       ; 0018h  PTR IO_TIMER
        .Flags                           dd           ?       ; 001Ch  DO_*
        .Characteristics                 dd           ?       ; 0020h  FILE_*
        .Vpb                             dd           ?       ; 0024h  PTR VPB
        .DeviceExtension                 dd           ?       ; 0028h
        .DeviceType                      dd           ?       ; 002Ch  DEVICE_TYPE
        .StackSize                       db           ?       ; 0030h
                                         rb           3       ; padding
        ;UNION Queue
                .Queue.ListEntry:                             ; 0034h   LIST_ENTRY <>
                .Queue.Wcb               rb           8       ; 0034h   WAIT_CONTEXT_BLOCK <>
        ;ENDS ; Queue
        .AlignmentRequirement            dd           ?       ; 005Ch
        .DeviceQueue                     rb           sizeof.KDEVICE_QUEUE ; 0060h
        .Dpc                             rb           sizeof.KDPC          ; 0074h

        ; The following field is for exclusive use by the filesystem to keep
        ; track of the number of Fsp threads currently using the device

        .ActiveThreadCount               dd           ?       ; 0094h
        .SecurityDescriptor              dd           ?       ; 0098h  PSECURITY_DESCRIPTOR
        .DeviceLock                      rb           sizeof.KEVENT ; 009Ch

        .SectorSize                      dw           ?       ; 00ACh
        .Spare1                          dw           ?       ; 00AEh

        .DeviceObjectExtension           dd           ?       ; 00B0h PTR DEVOBJ_EXTENSION
        .Reserved                        dd           ?       ; 00B4h
}
struct DEVICE_OBJECT

;;struct  _DEVICE_OBJECT_POWER_EXTENSION;

struc DEVOBJ_EXTENSION {                 ; sizeof = 024h
        .Type                   dw        ?       ; 0000h
        .Size                   dw        ?       ; 0002h

        ; Public part of the DeviceObjectExtension structure

        .DeviceObject           dd        ?       ; 0004h PTR DEVICE_OBJECT owning device object

        ; *!!!* The fields below are not defined in original ntddk.h file *!!!*
        ; Use it on your own

        .PowerFlags             dd        ?       ; 0008h
        .Dope                   dd        ?       ; 000Ch PTR DEVICE_OBJECT_POWER_EXTENSION
        .ExtensionFlags         dd        ?       ; 0010h
        .DeviceNode             dd        ?       ; 0014h
        .AttachedTo             dd        ?       ; 0018h PTR DEVICE_OBJECT
        .FileObjectList         rb        8       ; LIST_ENTRY <>   ; 001Ch
}
struct DEVOBJ_EXTENSION

struc DRIVER_EXTENSION {         ; sizeof = 14h

        ; Back pointer to Driver Object

        .DriverObject            dd                   ?       ; 00h PDRIVER_OBJECT

        ; The AddDevice entry point is called by the Plug & Play manager
        ; to inform the driver when a new device instance arrives that this
        ; driver must control.

        .AddDevice               dd                   ?       ; 04h PDRIVER_ADD_DEVICE

        ; The count field is used to count the number of times the driver has
        ; had its registered reinitialization routine invoked.

        .Count                   dd                   ?       ; 08h

        ; The service name field is used by the pnp manager to determine
        ; where the driver related info is stored in the registry.

        .ServiceKeyName          rb                   8       ; UNICODE_STRING  <>      ; 0Ch

        ; Note: any new shared fields get added here.

        ; *!!!* The field below is not defined in original ntddk.h file *!!!*
        ; Use it on your own

        .ClientDriverExtension   dd                   ?       ; 0014h PTR IO_CLIENT_EXTENSION

}
struct DRIVER_EXTENSION

;

struc DRIVER_OBJECT {    ; sizeof= 0A8h
        .Type                   dw                   ?       ; 0000h  (IO_TYPE_DRIVER = 4)
        .Size                   dw                   ?       ; 0004h

        ; The following links all of the devices created by a single driver
        ; together on a list, and the Flags word provides an extensible flag
        ; location for driver objects.

        .DeviceObject            dd           ?       ; 0004h PTR DEVICE_OBJECT
        .Flags                   dd           ?       ; 0008h

        ; The following section describes where the driver is loaded.  The count
        ; field is used to count the number of times the driver has had its
        ; registered reinitialization routine invoked.

        .DriverStart             dd           ?       ; 000Ch
        .DriverSize              dd           ?       ; 0010h
        .DriverSection           dd           ?       ; 0014h
        .DriverExtension         dd           ?       ; 0018h PTR DRIVER_EXTENSIO

        ; The driver name field is used by the error log thread
        ; determine the name of the driver that an I/O request is/was bound.

        .DriverName              rb           8       ; UNICODE_STRING <>       ; 001Ch

        ; The following section is for registry support.  Thise is a pointer
        ; to the path to the hardware information in the registry

        .HardwareDatabase        dd           ?       ; 0024h PTR UNICODE_STRING

        ; The following section contains the optional pointer to an array of
        ; alternate entry points to a driver for "fast I/O" support.  Fast I/O
        ; is performed by invoking the driver routine directly with separate
        ; parameters, rather than using the standard IRP call mechanism.  Note
        ; that these functions may only be used for synchronous I/O, and when
        ; the file is cached.

        .FastIoDispatch          dd           ?       ; 0028h PTR FAST_IO_DISPATCH

        ; The following section describes the entry points to this particular
        ; driver.  Note that the major function dispatch table must be the last
        ; field in the object so that it remains extensible.

        .DriverInit              dd           ?       ; 002Ch
        .DriverStartIo           dd           ?       ; 0030h
        .DriverUnload            dd           ?       ; 0034h
        .MajorFunction           rd           (IRP_MJ_MAXIMUM_FUNCTION + 1)  ; 0038h

}
struct DRIVER_OBJECT

; The following structure is pointed to by the SectionObject pointer field
; of a file object, and is allocated by the various NT file systems.

struc SECTION_OBJECT_POINTERS {          ; sizeof = 0Ch
        .DataSectionObject       dd           ?       ; 0000h
        .SharedCacheMap          dd           ?       ; 0004h
        .ImageSectionObject      dd           ?       ; 0008h
}
struct SECTION_OBJECT_POINTERS

; Define the format of a completion message.

struc IO_COMPLETION_CONTEXT {            ; sizeof = 08h
        .Port    dd           ?       ; 0000h
        .Key     dd           ?       ; 0004h
}
struct IO_COMPLETION_CONTEXT

; Define File Object (FO) flags

FO_FILE_OPEN                    = 00000001h
FO_SYNCHRONOUS_IO               = 00000002h
FO_ALERTABLE_IO                 = 00000004h
FO_NO_INTERMEDIATE_BUFFERING    = 00000008h
FO_WRITE_THROUGH                = 00000010h
FO_SEQUENTIAL_ONLY              = 00000020h
FO_CACHE_SUPPORTED              = 00000040h
FO_NAMED_PIPE                   = 00000080h
FO_STREAM_FILE                  = 00000100h
FO_MAILSLOT                     = 00000200h
FO_GENERATE_AUDIT_ON_CLOSE      = 00000400h
FO_DIRECT_DEVICE_OPEN           = 00000800h
FO_FILE_MODIFIED                = 00001000h
FO_FILE_SIZE_CHANGED            = 00002000h
FO_CLEANUP_COMPLETE             = 00004000h
FO_TEMPORARY_FILE               = 00008000h
FO_DELETE_ON_CLOSE              = 00010000h
FO_OPENED_CASE_SENSITIVE        = 00020000h
FO_HANDLE_CREATED               = 00040000h
FO_FILE_FAST_IO_READ            = 00080000h
FO_RANDOM_ACCESS                = 00100000h
FO_FILE_OPEN_CANCELLED          = 00200000h
FO_VOLUME_OPEN                  = 00400000h

struc FILE_OBJECT {              ; sizeof = 070h
        .Type                            dw           ?       ; 0000h  IO_TYPE_FILE
        .Size                            dw           ?       ; 0002h
        .DeviceObject                    dd           ?       ; 0004h PTR DEVICE_OBJECT
        .Vpb                             dd           ?       ; 0008h PTR VPB
        .FsContext                       dd           ?       ; 000Ch
        .FsContext2                      dd           ?       ; 0010h
        .SectionObjectPointer            dd           ?       ; 0014h PTR SECTION_OBJECT_POINTERS
        .PrivateCacheMap                 dd           ?       ; 0018h
        .FinalStatus                     dd           ?       ; 001Ch
        .RelatedFileObject               dd           ?       ; 0020h PTR FILE_OBJECT
        .LockOperation                   db           ?       ; 0024h  BOOLEAN
        .DeletePending                   db           ?       ; 0025h  BOOLEAN
        .ReadAccess                      db           ?       ; 0026h  BOOLEAN
        .WriteAccess                     db           ?       ; 0027h  BOOLEAN
        .DeleteAccess                    db           ?       ; 0028h  BOOLEAN
        .SharedRead                      db           ?       ; 0029h  BOOLEAN
        .SharedWrite                     db           ?       ; 002Ah  BOOLEAN
        .SharedDelete                    db           ?       ; 002Bh  BOOLEAN
        .Flags                           dd           ?       ; 002Ch
        .FileName                        rb           8       ; UNICODE_STRING <>       ; 0030h
        .CurrentByteOffset               dq           ?       ; LARGE_INTEGER <>        ; 0038h
        .Waiters                         dd           ?       ; 0040h
        .Busy                            dd           ?       ; 0044h
        .LastLock                        dd           ?       ; 0048h
        .Lock                            rb           sizeof.KEVENT ; 004Ch
        .Event                           rb           sizeof.KEVENT ; 005Ch
        .CompletionContext               dd           ?       ; 006Ch PTR IO_COMPLETION_CONTEXT
}
struct FILE_OBJECT

; Define I/O Request Packet (IRP) flags

IRP_NOCACHE                     = 00000001h
IRP_PAGING_IO                   = 00000002h
IRP_MOUNT_COMPLETION            = 00000002h
IRP_SYNCHRONOUS_API             = 00000004h
IRP_ASSOCIATED_IRP              = 00000008h
IRP_BUFFERED_IO                 = 00000010h
IRP_DEALLOCATE_BUFFER           = 00000020h
IRP_INPUT_OPERATION             = 00000040h
IRP_SYNCHRONOUS_PAGING_IO       = 00000040h
IRP_CREATE_OPERATION            = 00000080h
IRP_READ_OPERATION              = 00000100h
IRP_WRITE_OPERATION             = 00000200h
IRP_CLOSE_OPERATION             = 00000400h

IRP_DEFER_IO_COMPLETION         = 00000800h
IRP_OB_QUERY_NAME               = 00001000h
IRP_HOLD_DEVICE_QUEUE           = 00002000h
IRP_RETRY_IO_COMPLETION         = 00004000h

; Define I/O request packet (IRP) alternate flags for allocation control.

IRP_QUOTA_CHARGED               = 01h
IRP_ALLOCATED_MUST_SUCCEED      = 02h
IRP_ALLOCATED_FIXED_SIZE        = 04h
IRP_LOOKASIDE_ALLOCATION        = 08h

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; I/O Request Packet (IRP) definition
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struc IRP {                             ; sizeof = 70h
        .Type                           dw    ?       ; 00h
        .Size                           dw    ?       ; 02h

        ; Define the common fields used to control the IRP.

        ; Define a pointer to the Memory Descriptor List (MDL) for this I/O
        ; request.  This field is only used if the I/O is "direct I/O".

        .MdlAddress                     dd           ?       ; 04h PMDL

        ; Flags word - used to remember various flags.

        .Flags                          dd           ?       ; 08h

        ; The following union is used for one of three purposes:
        ;
        ; 1. This IRP is an associated IRP.  The field is a pointer to a master IRP.
        ;
        ; 2. This is the master IRP.  The field is the count of the number of
        ; IRPs which must complete (associated IRPs) before the master can
        ; complete.
        ;
        ; 3. This operation is being buffered and the field is the address of
        ; the system space buffer.

        ;UNION AssociatedIrp
                label .AssociatedIrp.MasterIrp dword                        ; 0Ch PIRP
                label .AssociatedIrp.IrpCount dword                         ; 0Ch
                .AssociatedIrp.SystemBuffer            dd           ?       ; 0Ch
        ;ENDS    ; AssociatedIrp

        ; Thread list entry - allows queueing the IRP to the thread pending I/O
        ; request packet list.

        .ThreadListEntry                 rb  8 ; LIST_ENTRY      <>      ; 10h

        ; I/O status - final status of operation.

        .IoStatus:                        ;rb sizeof.IO_STATUS_BLOCK      ; 18h
        .IoStatus.Status          dd          ?       ; 0000h  NTSTATUS
        .IoStatus.Information     dd          ?       ; 0004h


        ; Requestor mode - mode of the original requestor of this operation.

        .RequestorMode                   db            ?       ; 20h KPROCESSOR_MODE

        ; Pending returned - TRUE if pending was initially returned as the
        ; status for this packet.

        .PendingReturned                  db           ?       ; 21h

        ; Stack state information.

        .StackCount                       db           ?       ; 22h
        .CurrentLocation                  db           ?       ; 23h

        ; Cancel - packet has been canceled.

        .Cancel                          db            ?       ; 24h

        ; Cancel Irql - Irql at which the cancel spinlock was acquired.

        .CancelIrql                      db            ?       ; 25h

        ; ApcEnvironment - Used to save the APC environment at the time that the
        ; packet was initialized.

        .ApcEnvironment                  db            ?       ; 26h

        ; Allocation control flags.

        .AllocationFlags                 db            ?       ; 27h

        ; User parameters.

        .UserIosb                        dd            ?       ; 28h
        .UserEvent                       dd            ?       ; 2Ch
        ;UNION Overlay                                           ; 30h
                ;STRUCT AsynchronousParameters   ; 30h
                        label .Overlay.AsynchronousParameters.UserApcRoutine dword       ; 30h PIO_APC_ROUTINE
                        label .Overlay.AsynchronousParameters.UserApcContext dword at $+4       ; 34h
                ;ENDS    ; AsynchronousParameters
                .Overlay.AllocationSize          dq  ? ;LARGE_INTEGER   <>      ; 30h
        ;ENDS    ; Overlay

        ; CancelRoutine - Used to contain the address of a cancel routine supplied
        ; by a device driver when the IRP is in a cancelable state.

        .CancelRoutine           dd           ?               ; 38h PDRIVER_CANCEL

        ; Note that the UserBuffer parameter is outside of the stack so that I/O
        ; completion can copy data back into the user's address space without
        ; having to know exactly which service was being invoked.  The length
        ; of the copy is stored in the second half of the I/O status block. If
        ; the UserBuffer field is NULL, then no copy is performed.

        .UserBuffer                      dd           ?       ; 3Ch

        ; Kernel structures
        ;
        ; The following section contains kernel structures which the IRP needs
        ; in order to place various work information in kernel controller system
        ; queues.  Because the size and alignment cannot be controlled, they are
        ; placed here at the end so they just hang off and do not affect the
        ; alignment of other fields in the IRP.

        ;UNION Tail
                ;STRUCT Overlay
                        ;UNION
                                ; DeviceQueueEntry - The device queue entry field is used to
                                ; queue the IRP to the device driver device queue.

                                .Tail.Overlay.DeviceQueueEntry:        ;KDEVICE_QUEUE_ENTRY

                                ;STRUCT
                                        ; The following are available to the driver to use in
                                        ; whatever manner is desired, while the driver owns the
                                        ; packet.
                                        .Tail.Overlay.DriverContext   rd   4
                                ;ENDS

                        ;ENDS

                        ; Thread - pointer to caller's Thread Control Block.

                        .Tail.Overlay.Thread                          dd   ?                       ; PETHREAD

                        ; Auxiliary buffer - pointer to any auxiliary buffer that is
                        ; required to pass information to a driver that is not contained
                        ; in a normal buffer.

                        .Tail.Overlay.AuxiliaryBuffer         dd   ?

                        ; The following unnamed structure must be exactly identical
                        ; to the unnamed structure used in the minipacket header used
                        ; for completion queue entries.

                        ;STRUCT

                                ; List entry - used to queue the packet to completion queue, among
                                ; others.

                                .Tail.Overlay.ListEntry               rb  8 ; LIST_ENTRY      <>

                                ;UNION

                                        ; Current stack location - contains a pointer to the current
                                        ; IO_STACK_LOCATION structure in the IRP stack.  This field
                                        ; should never be directly accessed by drivers.  They should
                                        ; use the standard functions.
                                        label .Tail.Overlay.CurrentStackLocation dword       ; PTR IO_STACK_LOCATION

                                        ; Minipacket type.

                                        .Tail.Overlay.PacketType                              dd   ?
                                ;ENDS
                        ;ENDS

                        ; Original file object - pointer to the original file object
                        ; that was used to open the file.  This field is owned by the
                        ; I/O system and should not be used by any other drivers.

                        .Tail.Overlay.OriginalFileObject      dd    ?

                ;ENDS    ; Overlay

                ; APC - This APC control block is used for the special kernel APC as
                ; well as for the caller's APC, if one was specified in the original
                ; argument list.  If so, then the APC is reused for the normal APC for
                ; whatever mode the caller was in and the "special" routine that is
                ; invoked before the APC gets control simply deallocates the IRP.

                label .Tail.Apc at .Tail.Overlay.DeviceQueueEntry   ;rb   sizeof.KAPC

                ; CompletionKey - This is the key that is used to distinguish
                ; individual I/O operations initiated on a single file handle.

                label .Tail.CompletionKey   dword at .Tail.Overlay.DeviceQueueEntry ;dd   ?

        ;ENDS    ;Tail

}
struct IRP

; Define stack location control flags

SL_PENDING_RETURNED                             = 01h
SL_INVOKE_ON_CANCEL                             = 20h
SL_INVOKE_ON_SUCCESS                    = 40h
SL_INVOKE_ON_ERROR                              = 80h

; Define flags for various functions

;
; Create / Create Named Pipe
;
; The following flags must exactly match those in the IoCreateFile call's
; options.  The case sensitive flag is added in later, by the parse routine,
; and is not an actual option to open.  Rather, it is part of the object
; manager's attributes structure.
;

SL_FORCE_ACCESS_CHECK                   = 01
SL_OPEN_PAGING_FILE                             = 02
SL_OPEN_TARGET_DIRECTORY                = 04

SL_CASE_SENSITIVE                               = 80h

; Read / Write

SL_KEY_SPECIFIED                                = 01
SL_OVERRIDE_VERIFY_VOLUME               = 02
SL_WRITE_THROUGH                                = 04
SL_FT_SEQUENTIAL_WRITE                  = 08


; Device I/O Control
;
; Same SL_OVERRIDE_VERIFY_VOLUME as for read/write above.
;
; Lock

SL_FAIL_IMMEDIATELY                             = 01
SL_EXCLUSIVE_LOCK                               = 02

; QueryDirectory / QueryEa / QueryQuota

SL_RESTART_SCAN                                 = 01
SL_RETURN_SINGLE_ENTRY                  = 02
SL_INDEX_SPECIFIED                              = 04

; NotifyDirectory

SL_WATCH_TREE                   = 01

; FileSystemControl
;
;    minor: mount/verify volume

SL_ALLOW_RAW_MOUNT              = 01

; Define PNP/POWER types required by IRP_MJ_PNP/IRP_MJ_POWER.

;typedef enum _DEVICE_RELATION_TYPE {
    BusRelations                                = 0
    EjectionRelations                   = 1
    PowerRelations                              = 2
    RemovalRelations                    = 3
    TargetDeviceRelation                = 4

struc IO_STACK_LOCATION {        ; sizeof = 24h
        .MajorFunction           db    ?       ; 00h
        .MinorFunction           db    ?       ; 01h
        .Flags                           db    ?       ; 02h
        .Control                         db    ?       ; 03h

        ; The following user parameters are based on the service that is being
        ; invoked.  Drivers and file systems can determine which set to use based
        ; on the above major and minor function codes.

        ;union Parameters                                ; 04h

                ; System service parameters for:  NtCreateFile

                ;struct Create                           ; 04h
                        .Parameters.Create.SecurityContext      dd   ?       ; 04h PTR IO_SECURITY_CONTEXT
                        .Parameters.Create.Options              dd   ?       ; 08h
                        ; if _WIN64
                        ;       POINTER_ALIGNMENT DECLSPEC_ALIGN(8)
                        ; endif
                        .Parameters.Create.FileAttributes        dw    ?       ; 0Ch POINTER_ALIGNMENT
                        .Parameters.Create.ShareAccess           dw    ?       ; 0Eh
                        .Parameters.Create.EaLength              dd    ?       ; 10h POINTER_ALIGNMENT
                ;ends    ; Create

                ; System service parameters for:  NtReadFile

                ;struct Read                                     ; 04h
                        label .Parameters.Read.dwLength   dword at 4            ; 04h
                        label .Parameters.Read.Key        dword at 8            ; 08h POINTER_ALIGNMENT
                        label .Parameters.Read.ByteOffset qword at 0Ch          ; LARGE_INTEGER <> ; 0Ch
                ;ends    ; Read

                ; System service parameters for:  NtWriteFile

                ;struct Write                            ; 04h
                        label .Parameters.Write.dwLength          dword at 4    ; 04h
                        label .Parameters.Write.Key               dword at 8    ; 08h POINTER_ALIGNMENT
                        label .Parameters.Write.ByteOffset        qword at 0Ch  ; 0Ch
                ;ends    ; Write

                ; System service parameters for:  NtQueryInformationFile

                ;struct QueryFile
                        label .Parameters.QueryFile.Length                  dword at 4   ; 04h
                        label .Parameters.QueryFile.FileInformationClass    dword at 8   ; 08h POINTER_ALIGNMENT
                ;ends    ; QueryFile


                ; System service parameters for:  NtFlushBuffersFile
                ;
                ; No extra user-supplied parameters.

                ; System service parameters for:  NtDeviceIoControlFile
                ;
                ; Note that the user's output buffer is stored in the UserBuffer field
                ; and the user's input buffer is stored in the SystemBuffer field.

                ;struct DeviceIoControl          ; 04h
                        label .Parameters.DeviceIoControl.OutputBufferLength  dword at 4   ; 04h
                        label .Parameters.DeviceIoControl.InputBufferLength   dword at 8   ; 08h POINTER_ALIGNMENT
                        label .Parameters.DeviceIoControl.IoControlCode       dword at 0Ch ; 0Ch POINTER_ALIGNMENT
                        label .Parameters.DeviceIoControl.Type3InputBuffer    dword at 10h ; 10h
                ;ends    ; DeviceIoControl

                ; Parameters for IRP_MN_READ_CONFIG and IRP_MN_WRITE_CONFIG

                ;struct ReadWriteConfig                  ; 04h
                        label .Parameters.ReadWriteConfig.WhichSpace          dword at 4   ; 04h
                        label .Parameters.ReadWriteConfig.Buffer              dword at 8   ; 08h
                        label .Parameters.ReadWriteConfig.dwOffset            dword at 0Ch ; 0Ch
                        label .Parameters.ReadWriteConfig.Length              dword at 10h ; 10h POINTER_ALIGNMENT
                ;ends

                ; Parameters for IRP_MN_SET_LOCK

                ;struct SetLock                                  ; 04h
                        label .Parameters.SetLock.Lock  byte at 4        ; 04h
                                                        ;db 3 dup(?)     ; padding ???
                ;ends

                ; Others - driver-specific

                ;struct Others
                        label .Parameters.Others.Argument1 dword at 4
                        label .Parameters.Others.Argument2 dword at 8
                        label .Parameters.Others.Argument3 dword at 0Ch
                        label .Parameters.Others.Argument4 dword at 10h
                ;ends

        ;ends    ; Parameters

        ; Save a pointer to this device driver's device object for this request
        ; so it can be passed to the completion routine if needed.

        .DeviceObject            dd  ?

        ; The following location contains a pointer to the file object for this

        .FileObject                      dd    ?

        ; The following routine is invoked depending on the flags in the above
        ; flags field.

        .CompletionRoutine       dd   ?       ; PIO_COMPLETION_ROUTINE

        ; The following is used to store the address of the context parameter
        ; that should be passed to the CompletionRoutine.

        .Context                         dd   ?

}
struct IO_STACK_LOCATION

; +
; PIO_STACK_LOCATION IoGetCurrentIrpStackLocation( IN PIRP Irp )
;
; Macro Description:
;
;     This macro is invoked to return a pointer to the current stack location
;     in an I/O Request Packet (IRP).
;
; Arguments:
;
;     Irp - Pointer to the I/O Request Packet.
;
; Return Value:
;
;     The function value is a pointer to the current stack location in the
;     packet.
; -

;IoGetCurrentIrpStackLocation MACRO pIrp:REQ
;        IFDIFI <pIrp>, <eax>    ;; don't move eax onto itself
;                mov eax, pIrp
;        ENDIF
;        mov eax, (_IRP PTR [eax]).Tail.Overlay.CurrentStackLocation
;ENDM






;ntstatus.inc
;:
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;
; Standard Success values
;
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

; The success status codes 0 - 63 are reserved for wait completion status.
; FacilityCodes 0x5 - 0xF have been allocated by various drivers.

STATUS_SUCCESS          = 0

;
;  Values are 32 bit values layed out as follows:
;
;   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;  +---+-+-+-----------------------+-------------------------------+
;  |Sev|C|R|     Facility          |               Code            |
;  +---+-+-+-----------------------+-------------------------------+
;
;  where
;
;      Sev - is the severity code
;
;          00 - Success
;          01 - Informational
;          10 - Warning
;          11 - Error
;
;      C - is the Customer code flag
;
;      R - is a reserved bit
;
;      Facility - is the facility code
;
;      Code - is the facility's status code
;
;
; Define the facility codes
;
FACILITY_USB_ERROR_CODE          = 10h
FACILITY_TERMINAL_SERVER         = 0Ah
FACILITY_RPC_STUBS               = 3
FACILITY_RPC_RUNTIME             = 2
FACILITY_IO_ERROR_CODE           = 4
FACILITY_HID_ERROR_CODE          = 11h
FACILITY_FIREWIRE_ERROR_CODE     = 12h
FACILITY_DEBUGGER                = 1
FACILITY_CLUSTER_ERROR_CODE      = 13h
FACILITY_ACPI_ERROR_CODE         = 14h

;
; Define the severity codes
;
STATUS_SEVERITY_WARNING          = 2
STATUS_SEVERITY_SUCCESS          = 0
STATUS_SEVERITY_INFORMATIONAL    = 1
STATUS_SEVERITY_ERROR            = 3

;
; MessageId: STATUS_WAIT_0
;
; MessageText:
;
;  STATUS_WAIT_0
;
STATUS_WAIT_0                    = 00000000    ; winnt

;
; MessageId: STATUS_WAIT_1
;
; MessageText:
;
;  STATUS_WAIT_1
;
STATUS_WAIT_1                    = 00000001

;
; MessageId: STATUS_WAIT_2
;
; MessageText:
;
;  STATUS_WAIT_2
;
STATUS_WAIT_2                    = 00000002

;
; MessageId: STATUS_WAIT_3
;
; MessageText:
;
;  STATUS_WAIT_3
;
STATUS_WAIT_3                    = 00000003

;
; MessageId: STATUS_WAIT_63
;
; MessageText:
;
;  STATUS_WAIT_63
;
STATUS_WAIT_63                   = 0000003Fh


;
; The success status codes 128 - 191 are reserved for wait completion
; status with an abandoned mutant object.
;
STATUS_ABANDONED                        = 00000080h

;
; MessageId: STATUS_ABANDONED_WAIT_0
;
; MessageText:
;
;  STATUS_ABANDONED_WAIT_0
;
STATUS_ABANDONED_WAIT_0          = 00000080h    ; winnt

;
; MessageId: STATUS_ABANDONED_WAIT_63
;
; MessageText:
;
;  STATUS_ABANDONED_WAIT_63
;
STATUS_ABANDONED_WAIT_63         = 000000BFh


;
; The success status codes 256, 257, 258, and 258 are reserved for
; User APC, Kernel APC, Alerted, and Timeout.
;
;
; MessageId: STATUS_USER_APC
;
; MessageText:
;
;  STATUS_USER_APC
;
STATUS_USER_APC                  = 000000C0h    ; winnt

;
; MessageId: STATUS_KERNEL_APC
;
; MessageText:
;
;  STATUS_KERNEL_APC
;
STATUS_KERNEL_APC                = 00000100h

;
; MessageId: STATUS_ALERTED
;
; MessageText:
;
;  STATUS_ALERTED
;
STATUS_ALERTED                   = 00000101h

;
; MessageId: STATUS_TIMEOUT
;
; MessageText:
;
;  STATUS_TIMEOUT
;
STATUS_TIMEOUT                   = 00000102h    ; winnt

;
; MessageId: STATUS_PENDING
;
; MessageText:
;
;  The operation that was requested is pending completion.
;
STATUS_PENDING                   = 00000103h    ; winnt

;
; MessageId: STATUS_REPARSE
;
; MessageText:
;
;  A reparse should be performed by the Object Manager since the name of the file resulted in a symbolic link.
;
STATUS_REPARSE                   = 00000104h

;
; MessageId: STATUS_MORE_ENTRIES
;
; MessageText:
;
;  Returned by enumeration APIs to indicate more information is available to successive calls.
;
STATUS_MORE_ENTRIES              = 00000105h

;
; MessageId: STATUS_NOT_ALL_ASSIGNED
;
; MessageText:
;
;  Indicates not all privileges referenced are assigned to the caller.
;  This allows, for example, all privileges to be disabled without having to know exactly which privileges are assigned.
;
STATUS_NOT_ALL_ASSIGNED          = 00000106h

;
; MessageId: STATUS_SOME_NOT_MAPPED
;
; MessageText:
;
;  Some of the information to be translated has not been translated.
;
STATUS_SOME_NOT_MAPPED           = 00000107h

;
; MessageId: STATUS_OPLOCK_BREAK_IN_PROGRESS
;
; MessageText:
;
;  An open/create operation completed while an oplock break is underway.
;
STATUS_OPLOCK_BREAK_IN_PROGRESS  = 00000108h

;
; MessageId: STATUS_VOLUME_MOUNTED
;
; MessageText:
;
;  A new volume has been mounted by a file system.
;
STATUS_VOLUME_MOUNTED            = 00000109h

;
; MessageId: STATUS_RXACT_COMMITTED
;
; MessageText:
;
;  This success level status indicates that the transaction state already exists for the registry sub-tree,
;  but that a transaction commit was previously aborted.
;  The commit has now been completed.
;
STATUS_RXACT_COMMITTED           = 0000010Ah

;
; MessageId: STATUS_NOTIFY_CLEANUP
;
; MessageText:
;
;  This indicates that a notify change request has been completed due to closing the handle
;  which made the notify change request.
;
STATUS_NOTIFY_CLEANUP            = 0000010Bh

;
; MessageId: STATUS_NOTIFY_ENUM_DIR
;
; MessageText:
;
;  This indicates that a notify change request is being completed and that the information
;  is not being returned in the caller's buffer.
;  The caller now needs to enumerate the files to find the changes.
;
STATUS_NOTIFY_ENUM_DIR           = 0000010Ch

;
; MessageId: STATUS_NO_QUOTAS_FOR_ACCOUNT
;
; MessageText:
;
;  {No Quotas}
;  No system quota limits are specifically set for this account.
;
STATUS_NO_QUOTAS_FOR_ACCOUNT     = 0000010Dh

;
; MessageId: STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED
;
; MessageText:
;
;  {Connect Failure on Primary Transport}
;  An attempt was made to connect to the remote server %hs on the primary transport, but the connection failed.
;  The computer WAS able to connect on a secondary transport.
;
STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED = 0000010Eh

;
; MessageId: STATUS_PAGE_FAULT_TRANSITION
;
; MessageText:
;
;  Page fault was a transition fault.
;
STATUS_PAGE_FAULT_TRANSITION     = 00000110h

;
; MessageId: STATUS_PAGE_FAULT_DEMAND_ZERO
;
; MessageText:
;
;  Page fault was a demand zero fault.
;
STATUS_PAGE_FAULT_DEMAND_ZERO    = 00000111h

;
; MessageId: STATUS_PAGE_FAULT_COPY_ON_WRITE
;
; MessageText:
;
;  Page fault was a demand zero fault.
;
STATUS_PAGE_FAULT_COPY_ON_WRITE  = 00000112h

;
; MessageId: STATUS_PAGE_FAULT_GUARD_PAGE
;
; MessageText:
;
;  Page fault was a demand zero fault.
;
STATUS_PAGE_FAULT_GUARD_PAGE     = 00000113h

;
; MessageId: STATUS_PAGE_FAULT_PAGING_FILE
;
; MessageText:
;
;  Page fault was satisfied by reading from a secondary storage device.
;
STATUS_PAGE_FAULT_PAGING_FILE    = 00000114h

;
; MessageId: STATUS_CACHE_PAGE_LOCKED
;
; MessageText:
;
;  Cached page was locked during operation.
;
STATUS_CACHE_PAGE_LOCKED         = 00000115h

;
; MessageId: STATUS_CRASH_DUMP
;
; MessageText:
;
;  Crash dump exists in paging file.
;
STATUS_CRASH_DUMP                = 00000116h

;
; MessageId: STATUS_BUFFER_ALL_ZEROS
;
; MessageText:
;
;  Specified buffer contains all zeros.
;
STATUS_BUFFER_ALL_ZEROS          = 00000117h

;
; MessageId: STATUS_REPARSE_OBJECT
;
; MessageText:
;
;  A reparse should be performed by the Object Manager since the name of the file resulted in a symbolic link.
;
STATUS_REPARSE_OBJECT            = 00000118h

;
; MessageId: STATUS_RESOURCE_REQUIREMENTS_CHANGED
;
; MessageText:
;
;  The device has succeeded a query-stop and its resource requirements have changed.
;
STATUS_RESOURCE_REQUIREMENTS_CHANGED = 00000119h

;
; MessageId: STATUS_TRANSLATION_COMPLETE
;
; MessageText:
;
;  The translator has translated these resources into the global space and no further translations should be performed.
;
STATUS_TRANSLATION_COMPLETE      = 00000120h

;
; MessageId: STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY
;
; MessageText:
;
;  The directory service evaluated group memberships locally, as it was unable to contact a global catalog server.
;
STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY = 00000121h

;
; MessageId: DBG_EXCEPTION_HANDLED
;
; MessageText:
;
;  Debugger handled exception
;
DBG_EXCEPTION_HANDLED            = 00010001h    ; windbgkd

;
; MessageId: DBG_CONTINUE
;
; MessageText:
;
;  Debugger continued
;
DBG_CONTINUE                     = 00010002h    ; winnt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;
; Standard Information values
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

;
; MessageId: STATUS_OBJECT_NAME_EXISTS
;
; MessageText:
;
;  {Object Exists}
;  An attempt was made to create an object and the object name already existed.
;
STATUS_OBJECT_NAME_EXISTS        = 40000000h

;
; MessageId: STATUS_THREAD_WAS_SUSPENDED
;
; MessageText:
;
;  {Thread Suspended}
;  A thread termination occurred while the thread was suspended. The thread was resumed, and termination proceeded.
;
STATUS_THREAD_WAS_SUSPENDED      = 40000001h

;
; MessageId: STATUS_WORKING_SET_LIMIT_RANGE
;
; MessageText:
;
;  {Working Set Range Error}
;  An attempt was made to set the working set minimum or maximum to values which are outside of the allowable range.
;
STATUS_WORKING_SET_LIMIT_RANGE   = 40000002h

;
; MessageId: STATUS_IMAGE_NOT_AT_BASE
;
; MessageText:
;
;  {Image Relocated}
;  An image file could not be mapped at the address specified in the image file. Local fixups must be performed on this image.
;
STATUS_IMAGE_NOT_AT_BASE         = 40000003h

;
; MessageId: STATUS_RXACT_STATE_CREATED
;
; MessageText:
;
;  This informational level status indicates that a specified registry sub-tree transaction state did not yet exist and had to be created.
;
STATUS_RXACT_STATE_CREATED       = 40000004h

;
; MessageId: STATUS_SEGMENT_NOTIFICATION
;
; MessageText:
;
;  {Segment Load}
;  A virtual DOS machine (VDM) is loading, unloading, or moving an MS-DOS or Win16 program segment image.
;  An exception is raised so a debugger can load, unload or track symbols and breakpoints within these 16-bit segments.
;
STATUS_SEGMENT_NOTIFICATION      = 40000005h    ; winnt

;
; MessageId: STATUS_LOCAL_USER_SESSION_KEY
;
; MessageText:
;
;  {Local Session Key}
;  A user session key was requested for a local RPC connection. The session key returned is a constant value and not unique to this connection.
;
STATUS_LOCAL_USER_SESSION_KEY    = 40000006h

;
; MessageId: STATUS_BAD_CURRENT_DIRECTORY
;
; MessageText:
;
;  {Invalid Current Directory}
;  The process cannot switch to the startup current directory %hs.
;  Select OK to set current directory to %hs, or select CANCEL to exit.
;
STATUS_BAD_CURRENT_DIRECTORY     = 40000007h

;
; MessageId: STATUS_SERIAL_MORE_WRITES
;
; MessageText:
;
;  {Serial IOCTL Complete}
;  A serial I/O operation was completed by another write to a serial port.
;  (The IOCTL_SERIAL_XOFF_COUNTER reached zero.)
;
STATUS_SERIAL_MORE_WRITES        = 40000008h

;
; MessageId: STATUS_REGISTRY_RECOVERED
;
; MessageText:
;
;  {Registry Recovery}
;  One of the files containing the system's Registry data had to be recovered by use of a log or alternate copy.
;  The recovery was successful.
;
STATUS_REGISTRY_RECOVERED        = 40000009h

;
; MessageId: STATUS_FT_READ_RECOVERY_FROM_BACKUP
;
; MessageText:
;
;  {Redundant Read}
;  To satisfy a read request, the NT fault-tolerant file system successfully read the requested data from a redundant copy.
;  This was done because the file system encountered a failure on a member of the fault-tolerant volume,
;  but was unable to reassign the failing area of the device.
;
STATUS_FT_READ_RECOVERY_FROM_BACKUP = 4000000Ah

;
; MessageId: STATUS_FT_WRITE_RECOVERY
;
; MessageText:
;
;  {Redundant Write}
;  To satisfy a write request, the NT fault-tolerant file system successfully wrote a redundant copy of the information.
;  This was done because the file system encountered a failure on a member of the fault-tolerant volume,
;  but was not able to reassign the failing area of the device.
;
STATUS_FT_WRITE_RECOVERY         = 4000000Bh

;
; MessageId: STATUS_SERIAL_COUNTER_TIMEOUT
;
; MessageText:
;
;  {Serial IOCTL Timeout}
;  A serial I/O operation completed because the time-out period expired.
;  (The IOCTL_SERIAL_XOFF_COUNTER had not reached zero.)
;
STATUS_SERIAL_COUNTER_TIMEOUT    = 4000000Ch

;
; MessageId: STATUS_NULL_LM_PASSWORD
;
; MessageText:
;
;  {Password Too Complex}
;  The Windows password is too complex to be converted to a LAN Manager password.
;  The LAN Manager password returned is a NULL string.
;
STATUS_NULL_LM_PASSWORD          = 4000000Dh

;
; MessageId: STATUS_IMAGE_MACHINE_TYPE_MISMATCH
;
; MessageText:
;
;  {Machine Type Mismatch}
;  The image file %hs is valid, but is for a machine type other than the current machine. Select OK to continue, or CANCEL to fail the DLL load.
;
STATUS_IMAGE_MACHINE_TYPE_MISMATCH = 4000000Eh

;
; MessageId: STATUS_RECEIVE_PARTIAL
;
; MessageText:
;
;  {Partial Data Received}
;  The network transport returned partial data to its client. The remaining data will be sent later.
;
STATUS_RECEIVE_PARTIAL           = 4000000Fh

;
; MessageId: STATUS_RECEIVE_EXPEDITED
;
; MessageText:
;
;  {Expedited Data Received}
;  The network transport returned data to its client that was marked as expedited by the remote system.
;
STATUS_RECEIVE_EXPEDITED         = 40000010h

;
; MessageId: STATUS_RECEIVE_PARTIAL_EXPEDITED
;
; MessageText:
;
;  {Partial Expedited Data Received}
;  The network transport returned partial data to its client and this data was marked as expedited by the remote system. The remaining data will be sent later.
;
STATUS_RECEIVE_PARTIAL_EXPEDITED = 40000011h

;
; MessageId: STATUS_EVENT_DONE
;
; MessageText:
;
;  {TDI Event Done}
;  The TDI indication has completed successfully.
;
STATUS_EVENT_DONE                = 40000012h

;
; MessageId: STATUS_EVENT_PENDING
;
; MessageText:
;
;  {TDI Event Pending}
;  The TDI indication has entered the pending state.
;
STATUS_EVENT_PENDING             = 40000013h

;
; MessageId: STATUS_CHECKING_FILE_SYSTEM
;
; MessageText:
;
;  Checking file system on %wZ
;
STATUS_CHECKING_FILE_SYSTEM      = 40000014h

;
; MessageId: STATUS_FATAL_APP_EXIT
;
; MessageText:
;
;  {Fatal Application Exit}
;  %hs
;
STATUS_FATAL_APP_EXIT            = 40000015h

;
; MessageId: STATUS_PREDEFINED_HANDLE
;
; MessageText:
;
;  The specified registry key is referenced by a predefined handle.
;
STATUS_PREDEFINED_HANDLE         = 40000016h

;
; MessageId: STATUS_WAS_UNLOCKED
;
; MessageText:
;
;  {Page Unlocked}
;  The page protection of a locked page was changed to 'No Access' and the page was unlocked from memory and from the process.
;
STATUS_WAS_UNLOCKED              = 40000017h

;
; MessageId: STATUS_SERVICE_NOTIFICATION
;
; MessageText:
;
;  %hs
;
STATUS_SERVICE_NOTIFICATION      = 40000018h

;
; MessageId: STATUS_WAS_LOCKED
;
; MessageText:
;
;  {Page Locked}
;  One of the pages to lock was already locked.
;
STATUS_WAS_LOCKED                = 40000019h

;
; MessageId: STATUS_LOG_HARD_ERROR
;
; MessageText:
;
;  Application popup: %1 : %2
;
STATUS_LOG_HARD_ERROR            = 4000001Ah

;
; MessageId: STATUS_ALREADY_WIN32
;
; MessageText:
;
;  STATUS_ALREADY_WIN32
;
STATUS_ALREADY_WIN32             = 4000001Bh

;
; MessageId: STATUS_WX86_UNSIMULATE
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_UNSIMULATE           = 4000001Ch

;
; MessageId: STATUS_WX86_CONTINUE
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_CONTINUE             = 4000001Dh

;
; MessageId: STATUS_WX86_SINGLE_STEP
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_SINGLE_STEP          = 4000001Eh

;
; MessageId: STATUS_WX86_BREAKPOINT
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_BREAKPOINT           = 4000001Fh

;
; MessageId: STATUS_WX86_EXCEPTION_CONTINUE
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_EXCEPTION_CONTINUE   = 40000020h

;
; MessageId: STATUS_WX86_EXCEPTION_LASTCHANCE
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_EXCEPTION_LASTCHANCE = 40000021h

;
; MessageId: STATUS_WX86_EXCEPTION_CHAIN
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_EXCEPTION_CHAIN      = 40000022h

;
; MessageId: STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE
;
; MessageText:
;
;  {Machine Type Mismatch}
;  The image file %hs is valid, but is for a machine type other than the current machine.
;
STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE = 40000023h

;
; MessageId: STATUS_NO_YIELD_PERFORMED
;
; MessageText:
;
;  A yield execution was performed and no thread was available to run.
;
STATUS_NO_YIELD_PERFORMED        = 40000024h

;
; MessageId: STATUS_TIMER_RESUME_IGNORED
;
; MessageText:
;
;  The resumable flag to a timer API was ignored.
;
STATUS_TIMER_RESUME_IGNORED      = 40000025h

;
; MessageId: STATUS_ARBITRATION_UNHANDLED
;
; MessageText:
;
;  The arbiter has deferred arbitration of these resources to its parent
;
STATUS_ARBITRATION_UNHANDLED     = 40000026h

;
; MessageId: STATUS_CARDBUS_NOT_SUPPORTED
;
; MessageText:
;
;  The device "%hs" has detected a CardBus card in its slot, but the firmware on this system is not configured to allow the CardBus controller to be run in CardBus mode.
;  The operating system will currently accept only 16-bit (R2) pc-cards on this controller.
;
STATUS_CARDBUS_NOT_SUPPORTED     = 40000027h

;
; MessageId: STATUS_WX86_CREATEWX86TIB
;
; MessageText:
;
;  Exception status code used by Win32 x86 emulation subsystem.
;
STATUS_WX86_CREATEWX86TIB        = 40000028h

;
; MessageId: STATUS_MP_PROCESSOR_MISMATCH
;
; MessageText:
;
;  The CPUs in this multiprocessor system are not all the same revision level.  To use all processors the operating system restricts itself to the features of the least capable processor in the system.  Should problems occur with this system, contact the C
;
STATUS_MP_PROCESSOR_MISMATCH     = 40000029h

;
; MessageId: DBG_REPLY_LATER
;
; MessageText:
;
;  Debugger will reply later.
;
DBG_REPLY_LATER                  = 40010001h

;
; MessageId: DBG_UNABLE_TO_PROVIDE_HANDLE
;
; MessageText:
;
;  Debugger can not provide handle.
;
DBG_UNABLE_TO_PROVIDE_HANDLE     = 40010002h

;
; MessageId: DBG_TERMINATE_THREAD
;
; MessageText:
;
;  Debugger terminated thread.
;
DBG_TERMINATE_THREAD             = 40010003h    ; winnt

;
; MessageId: DBG_TERMINATE_PROCESS
;
; MessageText:
;
;  Debugger terminated process.
;
DBG_TERMINATE_PROCESS            = 40010004h    ; winnt

;
; MessageId: DBG_CONTROL_C
;
; MessageText:
;
;  Debugger got control C.
;
DBG_CONTROL_C                    = 40010005h    ; winnt

;
; MessageId: DBG_PRINTEXCEPTION_C
;
; MessageText:
;
;  Debugger printerd exception on control C.
;
DBG_PRINTEXCEPTION_C             = 40010006h

;
; MessageId: DBG_RIPEXCEPTION
;
; MessageText:
;
;  Debugger recevice RIP exception.
;
DBG_RIPEXCEPTION                 = 40010007h

;
; MessageId: DBG_CONTROL_BREAK
;
; MessageText:
;
;  Debugger received control break.
;
DBG_CONTROL_BREAK                = 40010008h    ; winnt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;
; Standard Warning values
;
;
; Note:  Do NOT use the value 0x80000000L, as this is a non-portable value
;        for the NT_SUCCESS macro. Warning values start with a code of 1.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

;
; MessageId: STATUS_GUARD_PAGE_VIOLATION
;
; MessageText:
;
;  {EXCEPTION}
;  Guard Page Exception
;  A page of memory that marks the end of a data structure, such as a stack or an array, has been accessed.
;
STATUS_GUARD_PAGE_VIOLATION      = 80000001h    ; winnt

;
; MessageId: STATUS_DATATYPE_MISALIGNMENT
;
; MessageText:
;
;  {EXCEPTION}
;  Alignment Fault
;  A datatype misalignment was detected in a load or store instruction.
;
STATUS_DATATYPE_MISALIGNMENT     = 80000002h    ; winnt

;
; MessageId: STATUS_BREAKPOINT
;
; MessageText:
;
;  {EXCEPTION}
;  Breakpoint
;  A breakpoint has been reached.
;
STATUS_BREAKPOINT                = 80000003h    ; winnt

;
; MessageId: STATUS_SINGLE_STEP
;
; MessageText:
;
;  {EXCEPTION}
;  Single Step
;  A single step or trace operation has just been completed.
;
STATUS_SINGLE_STEP               = 80000004h    ; winnt

;
; MessageId: STATUS_BUFFER_OVERFLOW
;
; MessageText:
;
;  {Buffer Overflow}
;  The data was too large to fit into the specified buffer.
;
STATUS_BUFFER_OVERFLOW           = 80000005h

;
; MessageId: STATUS_NO_MORE_FILES
;
; MessageText:
;
;  {No More Files}
;  No more files were found which match the file specification.
;
STATUS_NO_MORE_FILES             = 80000006h

;
; MessageId: STATUS_WAKE_SYSTEM_DEBUGGER
;
; MessageText:
;
;  {Kernel Debugger Awakened}
;  the system debugger was awakened by an interrupt.
;
STATUS_WAKE_SYSTEM_DEBUGGER      = 80000007h

;
; MessageId: STATUS_HANDLES_CLOSED
;
; MessageText:
;
;  {Handles Closed}
;  Handles to objects have been automatically closed as a result of the requested operation.
;
STATUS_HANDLES_CLOSED            = 8000000Ah

;
; MessageId: STATUS_NO_INHERITANCE
;
; MessageText:
;
;  {Non-Inheritable ACL}
;  An access control list (ACL) contains no components that can be inherited.
;
STATUS_NO_INHERITANCE            = 8000000Bh

;
; MessageId: STATUS_GUID_SUBSTITUTION_MADE
;
; MessageText:
;
;  {GUID Substitution}
;  During the translation of a global identifier (GUID) to a Windows security ID (SID), no administratively-defined GUID prefix was found.
;  A substitute prefix was used, which will not compromise system security.
;  However, this may provide a more restrictive access than intended.
;
STATUS_GUID_SUBSTITUTION_MADE    = 8000000Ch

;
; MessageId: STATUS_PARTIAL_COPY
;
; MessageText:
;
;  {Partial Copy}
;  Due to protection conflicts not all the requested bytes could be copied.
;
STATUS_PARTIAL_COPY              = 8000000Dh

;
; MessageId: STATUS_DEVICE_PAPER_EMPTY
;
; MessageText:
;
;  {Out of Paper}
;  The printer is out of paper.
;
STATUS_DEVICE_PAPER_EMPTY        = 8000000Eh

;
; MessageId: STATUS_DEVICE_POWERED_OFF
;
; MessageText:
;
;  {Device Power Is Off}
;  The printer power has been turned off.
;
STATUS_DEVICE_POWERED_OFF        = 8000000Fh

;
; MessageId: STATUS_DEVICE_OFF_LINE
;
; MessageText:
;
;  {Device Offline}
;  The printer has been taken offline.
;
STATUS_DEVICE_OFF_LINE           = 80000010h

;
; MessageId: STATUS_DEVICE_BUSY
;
; MessageText:
;
;  {Device Busy}
;  The device is currently busy.
;
STATUS_DEVICE_BUSY               = 80000011h

;
; MessageId: STATUS_NO_MORE_EAS
;
; MessageText:
;
;  {No More EAs}
;  No more extended attributes (EAs) were found for the file.
;
STATUS_NO_MORE_EAS               = 80000012h

;
; MessageId: STATUS_INVALID_EA_NAME
;
; MessageText:
;
;  {Illegal EA}
;  The specified extended attribute (EA) name contains at least one illegal character.
;
STATUS_INVALID_EA_NAME           = 80000013h

;
; MessageId: STATUS_EA_LIST_INCONSISTENT
;
; MessageText:
;
;  {Inconsistent EA List}
;  The extended attribute (EA) list is inconsistent.
;
STATUS_EA_LIST_INCONSISTENT      = 80000014h

;
; MessageId: STATUS_INVALID_EA_FLAG
;
; MessageText:
;
;  {Invalid EA Flag}
;  An invalid extended attribute (EA) flag was set.
;
STATUS_INVALID_EA_FLAG           = 80000015h

;
; MessageId: STATUS_VERIFY_REQUIRED
;
; MessageText:
;
;  {Verifying Disk}
;  The media has changed and a verify operation is in progress so no reads or writes may be performed to the device, except those used in the verify operation.
;
STATUS_VERIFY_REQUIRED           = 80000016h

;
; MessageId: STATUS_EXTRANEOUS_INFORMATION
;
; MessageText:
;
;  {Too Much Information}
;  The specified access control list (ACL) contained more information than was expected.
;
STATUS_EXTRANEOUS_INFORMATION    = 80000017h

;
; MessageId: STATUS_RXACT_COMMIT_NECESSARY
;
; MessageText:
;
;  This warning level status indicates that the transaction state already exists for the registry sub-tree, but that a transaction commit was previously aborted.
;  The commit has NOT been completed, but has not been rolled back either (so it may still be committed if desired).
;
STATUS_RXACT_COMMIT_NECESSARY    = 80000018h

;
; MessageId: STATUS_NO_MORE_ENTRIES
;
; MessageText:
;
;  {No More Entries}
;  No more entries are available from an enumeration operation.
;
STATUS_NO_MORE_ENTRIES           = 8000001Ah

;
; MessageId: STATUS_FILEMARK_DETECTED
;
; MessageText:
;
;  {Filemark Found}
;  A filemark was detected.
;
STATUS_FILEMARK_DETECTED         = 8000001Bh

;
; MessageId: STATUS_MEDIA_CHANGED
;
; MessageText:
;
;  {Media Changed}
;  The media may have changed.
;
STATUS_MEDIA_CHANGED             = 8000001Ch

;
; MessageId: STATUS_BUS_RESET
;
; MessageText:
;
;  {I/O Bus Reset}
;  An I/O bus reset was detected.
;
STATUS_BUS_RESET                 = 8000001Dh

;
; MessageId: STATUS_END_OF_MEDIA
;
; MessageText:
;
;  {End of Media}
;  The end of the media was encountered.
;
STATUS_END_OF_MEDIA              = 8000001Eh

;
; MessageId: STATUS_BEGINNING_OF_MEDIA
;
; MessageText:
;
;  Beginning of tape or partition has been detected.
;
STATUS_BEGINNING_OF_MEDIA        = 8000001Fh

;
; MessageId: STATUS_MEDIA_CHECK
;
; MessageText:
;
;  {Media Changed}
;  The media may have changed.
;
STATUS_MEDIA_CHECK               = 80000020h

;
; MessageId: STATUS_SETMARK_DETECTED
;
; MessageText:
;
;  A tape access reached a setmark.
;
STATUS_SETMARK_DETECTED          = 80000021h

;
; MessageId: STATUS_NO_DATA_DETECTED
;
; MessageText:
;
;  During a tape access, the end of the data written is reached.
;
STATUS_NO_DATA_DETECTED          = 80000022h

;
; MessageId: STATUS_REDIRECTOR_HAS_OPEN_HANDLES
;
; MessageText:
;
;  The redirector is in use and cannot be unloaded.
;
STATUS_REDIRECTOR_HAS_OPEN_HANDLES = 80000023h

;
; MessageId: STATUS_SERVER_HAS_OPEN_HANDLES
;
; MessageText:
;
;  The server is in use and cannot be unloaded.
;
STATUS_SERVER_HAS_OPEN_HANDLES   = 80000024h

;
; MessageId: STATUS_ALREADY_DISCONNECTED
;
; MessageText:
;
;  The specified connection has already been disconnected.
;
STATUS_ALREADY_DISCONNECTED      = 80000025h

;
; MessageId: STATUS_LONGJUMP
;
; MessageText:
;
;  A long jump has been executed.
;
STATUS_LONGJUMP                  = 80000026h

;
; MessageId: DBG_EXCEPTION_NOT_HANDLED
;
; MessageText:
;
;  Debugger did not handle the exception.
;
DBG_EXCEPTION_NOT_HANDLED        = 80010001h    ; winnt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;
;  Standard Error values
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

;
; MessageId: STATUS_UNSUCCESSFUL
;
; MessageText:
;
;  {Operation Failed}
;  The requested operation was unsuccessful.
;
STATUS_UNSUCCESSFUL              = 0C0000001h

;
; MessageId: STATUS_NOT_IMPLEMENTED
;
; MessageText:
;
; {Not Implemented}
; The requested operation is not implemented.

STATUS_NOT_IMPLEMENTED          = 0C0000002h

;
; MessageId: STATUS_INVALID_INFO_CLASS
;
; MessageText:
;
;  {Invalid Parameter}
;  The specified information class is not a valid information class for the specified object.
;
STATUS_INVALID_INFO_CLASS        = 0C0000003h    ; ntsubauth

;
; MessageId: STATUS_INFO_LENGTH_MISMATCH
;
; MessageText:
;
;  The specified information record length does not match the length required for the specified information class.
;
STATUS_INFO_LENGTH_MISMATCH      = 0C0000004h

;
; MessageId: STATUS_ACCESS_VIOLATION
;
; MessageText:
;
;  The instruction at "0x%08lx" referenced memory at "0x%08lx". The memory could not be "%s".
;
STATUS_ACCESS_VIOLATION          = 0C0000005h    ; winnt

;
; MessageId: STATUS_IN_PAGE_ERROR
;
; MessageText:
;
;  The instruction at "0x%08lx" referenced memory at "0x%08lx". The required data was not placed into memory because of an I/O error status of "0x%08lx".
;
STATUS_IN_PAGE_ERROR             = 0C0000006h    ; winnt

;
; MessageId: STATUS_PAGEFILE_QUOTA
;
; MessageText:
;
;  The pagefile quota for the process has been exhausted.
;
STATUS_PAGEFILE_QUOTA            = 0C0000007h

;
; MessageId: STATUS_INVALID_HANDLE
;
; MessageText:
;
;  An invalid HANDLE was specified.
;
STATUS_INVALID_HANDLE            = 0C0000008h    ; winnt

;
; MessageId: STATUS_BAD_INITIAL_STACK
;
; MessageText:
;
;  An invalid initial stack was specified in a call to NtCreateThread.
;
STATUS_BAD_INITIAL_STACK         = 0C0000009h

;
; MessageId: STATUS_BAD_INITIAL_PC
;
; MessageText:
;
;  An invalid initial start address was specified in a call to NtCreateThread.
;
STATUS_BAD_INITIAL_PC            = 0C000000Ah

;
; MessageId: STATUS_INVALID_CID
;
; MessageText:
;
;  An invalid Client ID was specified.
;
STATUS_INVALID_CID               = 0C000000Bh

;
; MessageId: STATUS_TIMER_NOT_CANCELED
;
; MessageText:
;
;  An attempt was made to cancel or set a timer that has an associated APC and the subject thread is not the thread that originally set the timer with an associated APC routine.
;
STATUS_TIMER_NOT_CANCELED        = 0C000000Ch

;
; MessageId: STATUS_INVALID_PARAMETER
;
; MessageText:
;
;  An invalid parameter was passed to a service or function.
;
STATUS_INVALID_PARAMETER         = 0C000000Dh

;
; MessageId: STATUS_NO_SUCH_DEVICE
;
; MessageText:
;
;  A device which does not exist was specified.
;
STATUS_NO_SUCH_DEVICE            = 0C000000Eh

;
; MessageId: STATUS_NO_SUCH_FILE
;
; MessageText:
;
;  {File Not Found}
;  The file %hs does not exist.
;
STATUS_NO_SUCH_FILE              = 0C000000Fh

; MessageId: STATUS_INVALID_DEVICE_REQUEST
;
; MessageText:
;
;  The specified request is not a valid operation for the target device.

STATUS_INVALID_DEVICE_REQUEST   = 00C0000010h

; MessageId: STATUS_END_OF_FILE
;
; MessageText:
;
;  The end-of-file marker has been reached. There is no valid data in the file beyond this marker.

STATUS_END_OF_FILE                              = 0C0000011h

;
; MessageId: STATUS_WRONG_VOLUME
;
; MessageText:
;
;  {Wrong Volume}
;  The wrong volume is in the drive.
;  Please insert volume %hs into drive %hs.
;
STATUS_WRONG_VOLUME              = 0C0000012h

;
; MessageId: STATUS_NO_MEDIA_IN_DEVICE
;
; MessageText:
;
;  {No Disk}
;  There is no disk in the drive.
;  Please insert a disk into drive %hs.
;
STATUS_NO_MEDIA_IN_DEVICE        = 0C0000013h

;
; MessageId: STATUS_UNRECOGNIZED_MEDIA
;
; MessageText:
;
;  {Unknown Disk Format}
;  The disk in drive %hs is not formatted properly.
;  Please check the disk, and reformat if necessary.
;
STATUS_UNRECOGNIZED_MEDIA        = 0C0000014h

;
; MessageId: STATUS_NONEXISTENT_SECTOR
;
; MessageText:
;
;  {Sector Not Found}
;  The specified sector does not exist.
;
STATUS_NONEXISTENT_SECTOR        = 0C0000015h

;
; MessageId: STATUS_MORE_PROCESSING_REQUIRED
;
; MessageText:
;
;  {Still Busy}
;  The specified I/O request packet (IRP) cannot be disposed of because the I/O operation is not complete.
;
STATUS_MORE_PROCESSING_REQUIRED  = 0C0000016h

;
; MessageId: STATUS_NO_MEMORY
;
; MessageText:
;
;  {Not Enough Quota}
;  Not enough virtual memory or paging file quota is available to complete the specified operation.
;
STATUS_NO_MEMORY                 = 0C0000017h    ; winnt

;
; MessageId: STATUS_CONFLICTING_ADDRESSES
;
; MessageText:
;
;  {Conflicting Address Range}
;  The specified address range conflicts with the address space.
;
STATUS_CONFLICTING_ADDRESSES     = 0C0000018h

;
; MessageId: STATUS_NOT_MAPPED_VIEW
;
; MessageText:
;
;  Address range to unmap is not a mapped view.
;
STATUS_NOT_MAPPED_VIEW           = 0C0000019h

;
; MessageId: STATUS_UNABLE_TO_FREE_VM
;
; MessageText:
;
;  Virtual memory cannot be freed.
;
STATUS_UNABLE_TO_FREE_VM         = 0C000001Ah

;
; MessageId: STATUS_UNABLE_TO_DELETE_SECTION
;
; MessageText:
;
;  Specified section cannot be deleted.
;
STATUS_UNABLE_TO_DELETE_SECTION  = 0C000001Bh

;
; MessageId: STATUS_INVALID_SYSTEM_SERVICE
;
; MessageText:
;
;  An invalid system service was specified in a system service call.
;
STATUS_INVALID_SYSTEM_SERVICE    = 0C000001Ch

;
; MessageId: STATUS_ILLEGAL_INSTRUCTION
;
; MessageText:
;
;  {EXCEPTION}
;  Illegal Instruction
;  An attempt was made to execute an illegal instruction.
;
STATUS_ILLEGAL_INSTRUCTION       = 0C000001Dh    ; winnt

;
; MessageId: STATUS_INVALID_LOCK_SEQUENCE
;
; MessageText:
;
;  {Invalid Lock Sequence}
;  An attempt was made to execute an invalid lock sequence.
;
STATUS_INVALID_LOCK_SEQUENCE     = 0C000001Eh

;
; MessageId: STATUS_INVALID_VIEW_SIZE
;
; MessageText:
;
;  {Invalid Mapping}
;  An attempt was made to create a view for a section which is bigger than the section.
;
STATUS_INVALID_VIEW_SIZE         = 0C000001Fh

;
; MessageId: STATUS_INVALID_FILE_FOR_SECTION
;
; MessageText:
;
;  {Bad File}
;  The attributes of the specified mapping file for a section of memory cannot be read.
;
STATUS_INVALID_FILE_FOR_SECTION  = 0C0000020h

;
; MessageId: STATUS_ALREADY_COMMITTED
;
; MessageText:
;
;  {Already Committed}
;  The specified address range is already committed.
;
STATUS_ALREADY_COMMITTED         = 0C0000021h

;
; MessageId: STATUS_ACCESS_DENIED
;
; MessageText:
;
;  {Access Denied}
;  A process has requested access to an object, but has not been granted those access rights.
;
STATUS_ACCESS_DENIED             = 0C0000022h

;
; MessageId: STATUS_BUFFER_TOO_SMALL
;
; MessageText:
;
;  {Buffer Too Small}
;  The buffer is too small to contain the entry. No information has been written to the buffer.

STATUS_BUFFER_TOO_SMALL         = 0C0000023h

; MessageId: STATUS_OBJECT_TYPE_MISMATCH
;
; MessageText:
;
;  {Wrong Type}
;  There is a mismatch between the type of object required by the requested operation and the type of object that is specified in the request.

STATUS_OBJECT_TYPE_MISMATCH     = 0C0000024h

; MessageId: STATUS_NONCONTINUABLE_EXCEPTION
;
; MessageText:
;
;  {EXCEPTION}
;  Cannot Continue
;  Windows cannot continue from this exception.

STATUS_NONCONTINUABLE_EXCEPTION = 0C0000025h  ; winnt

; MessageId: STATUS_INVALID_DISPOSITION
;
; MessageText:
;
;  An invalid exception disposition was returned by an exception handler.

STATUS_INVALID_DISPOSITION              = 0C0000026h  ; winnt

;
; MessageId: STATUS_UNWIND
;
; MessageText:
;
;  Unwind exception code.
;
STATUS_UNWIND                    = 0C0000027h

;
; MessageId: STATUS_BAD_STACK
;
; MessageText:
;
;  An invalid or unaligned stack was encountered during an unwind operation.
;
STATUS_BAD_STACK                 = 0C0000028h

;
; MessageId: STATUS_INVALID_UNWIND_TARGET
;
; MessageText:
;
;  An invalid unwind target was encountered during an unwind operation.
;
STATUS_INVALID_UNWIND_TARGET     = 0C0000029h

;
; MessageId: STATUS_NOT_LOCKED
;
; MessageText:
;
;  An attempt was made to unlock a page of memory which was not locked.
;
STATUS_NOT_LOCKED                = 0C000002Ah

;
; MessageId: STATUS_PARITY_ERROR
;
; MessageText:
;
;  Device parity error on I/O operation.
;
STATUS_PARITY_ERROR              = 0C000002Bh

;
; MessageId: STATUS_UNABLE_TO_DECOMMIT_VM
;
; MessageText:
;
;  An attempt was made to decommit uncommitted virtual memory.
;
STATUS_UNABLE_TO_DECOMMIT_VM     = 0C000002Ch

;
; MessageId: STATUS_NOT_COMMITTED
;
; MessageText:
;
;  An attempt was made to change the attributes on memory that has not been committed.
;
STATUS_NOT_COMMITTED             = 0C000002Dh

;
; MessageId: STATUS_INVALID_PORT_ATTRIBUTES
;
; MessageText:
;
;  Invalid Object Attributes specified to NtCreatePort or invalid Port Attributes specified to NtConnectPort
;
STATUS_INVALID_PORT_ATTRIBUTES   = 0C000002Eh

;
; MessageId: STATUS_PORT_MESSAGE_TOO_LONG
;
; MessageText:
;
;  Length of message passed to NtRequestPort or NtRequestWaitReplyPort was longer than the maximum message allowed by the port.
;
STATUS_PORT_MESSAGE_TOO_LONG     = 0C000002Fh

;
; MessageId: STATUS_INVALID_PARAMETER_MIX
;
; MessageText:
;
;  An invalid combination of parameters was specified.
;
STATUS_INVALID_PARAMETER_MIX     = 0C0000030h

;
; MessageId: STATUS_INVALID_QUOTA_LOWER
;
; MessageText:
;
;  An attempt was made to lower a quota limit below the current usage.
;
STATUS_INVALID_QUOTA_LOWER       = 0C0000031h

;
; MessageId: STATUS_DISK_CORRUPT_ERROR
;
; MessageText:
;
;  {Corrupt Disk}
;  The file system structure on the disk is corrupt and unusable.
;  Please run the Chkdsk utility on the volume %hs.
;
STATUS_DISK_CORRUPT_ERROR        = 0C0000032h

;
; MessageId: STATUS_OBJECT_NAME_INVALID
;
; MessageText:
;
;  Object Name invalid.
;
STATUS_OBJECT_NAME_INVALID       = 0C0000033h

;
; MessageId: STATUS_OBJECT_NAME_NOT_FOUND
;
; MessageText:
;
;  Object Name not found.
;
STATUS_OBJECT_NAME_NOT_FOUND     = 0C0000034h

;
; MessageId: STATUS_OBJECT_NAME_COLLISION
;
; MessageText:
;
;  Object Name already exists.
;
STATUS_OBJECT_NAME_COLLISION     = 0C0000035h

;
; MessageId: STATUS_PORT_DISCONNECTED
;
; MessageText:
;
;  Attempt to send a message to a disconnected communication port.
;
STATUS_PORT_DISCONNECTED         = 0C0000037h

;
; MessageId: STATUS_DEVICE_ALREADY_ATTACHED
;
; MessageText:
;
;  An attempt was made to attach to a device that was already attached to another device.
;
STATUS_DEVICE_ALREADY_ATTACHED   = 0C0000038h

;
; MessageId: STATUS_OBJECT_PATH_INVALID
;
; MessageText:
;
;  Object Path Component was not a directory object.
;
STATUS_OBJECT_PATH_INVALID       = 0C0000039h

;
; MessageId: STATUS_OBJECT_PATH_NOT_FOUND
;
; MessageText:
;
;  {Path Not Found}
;  The path %hs does not exist.
;
STATUS_OBJECT_PATH_NOT_FOUND     = 0C000003Ah

;
; MessageId: STATUS_OBJECT_PATH_SYNTAX_BAD
;
; MessageText:
;
;  Object Path Component was not a directory object.
;
STATUS_OBJECT_PATH_SYNTAX_BAD    = 0C000003Bh

;
; MessageId: STATUS_DATA_OVERRUN
;
; MessageText:
;
;  {Data Overrun}
;  A data overrun error occurred.
;
STATUS_DATA_OVERRUN              = 0C000003Ch

;
; MessageId: STATUS_DATA_LATE_ERROR
;
; MessageText:
;
;  {Data Late}
;  A data late error occurred.
;
STATUS_DATA_LATE_ERROR           = 0C000003Dh

;
; MessageId: STATUS_DATA_ERROR
;
; MessageText:
;
;  {Data Error}
;  An error in reading or writing data occurred.
;
STATUS_DATA_ERROR                = 0C000003Eh

;
; MessageId: STATUS_CRC_ERROR
;
; MessageText:
;
;  {Bad CRC}
;  A cyclic redundancy check (CRC) checksum error occurred.
;
STATUS_CRC_ERROR                 = 0C000003Fh

;
; MessageId: STATUS_SECTION_TOO_BIG
;
; MessageText:
;
;  {Section Too Large}
;  The specified section is too big to map the file.
;
STATUS_SECTION_TOO_BIG           = 0C0000040h

;
; MessageId: STATUS_PORT_CONNECTION_REFUSED
;
; MessageText:
;
;  The NtConnectPort request is refused.
;
STATUS_PORT_CONNECTION_REFUSED   = 0C0000041h

;
; MessageId: STATUS_INVALID_PORT_HANDLE
;
; MessageText:
;
;  The type of port handle is invalid for the operation requested.
;
STATUS_INVALID_PORT_HANDLE       = 0C0000042h

;
; MessageId: STATUS_SHARING_VIOLATION
;
; MessageText:
;
;  A file cannot be opened because the share access flags are incompatible.
;
STATUS_SHARING_VIOLATION         = 0C0000043h

;
; MessageId: STATUS_QUOTA_EXCEEDED
;
; MessageText:
;
;  Insufficient quota exists to complete the operation
;
STATUS_QUOTA_EXCEEDED            = 0C0000044h

;
; MessageId: STATUS_INVALID_PAGE_PROTECTION
;
; MessageText:
;
;  The specified page protection was not valid.
;
STATUS_INVALID_PAGE_PROTECTION   = 0C0000045h

;
; MessageId: STATUS_MUTANT_NOT_OWNED
;
; MessageText:
;
;  An attempt to release a mutant object was made by a thread that was not the owner of the mutant object.
;
STATUS_MUTANT_NOT_OWNED          = 0C0000046h

;
; MessageId: STATUS_SEMAPHORE_LIMIT_EXCEEDED
;
; MessageText:
;
;  An attempt was made to release a semaphore such that its maximum count would have been exceeded.
;
STATUS_SEMAPHORE_LIMIT_EXCEEDED  = 0C0000047h

;
; MessageId: STATUS_PORT_ALREADY_SET
;
; MessageText:
;
;  An attempt to set a processes DebugPort or ExceptionPort was made, but a port already exists in the process.
;
STATUS_PORT_ALREADY_SET          = 0C0000048h

;
; MessageId: STATUS_SECTION_NOT_IMAGE
;
; MessageText:
;
;  An attempt was made to query image information on a section which does not map an image.
;
STATUS_SECTION_NOT_IMAGE         = 0C0000049h

;
; MessageId: STATUS_SUSPEND_COUNT_EXCEEDED
;
; MessageText:
;
;  An attempt was made to suspend a thread whose suspend count was at its maximum.
;
STATUS_SUSPEND_COUNT_EXCEEDED    = 0C000004Ah

;
; MessageId: STATUS_THREAD_IS_TERMINATING
;
; MessageText:
;
;  An attempt was made to suspend a thread that has begun termination.
;
STATUS_THREAD_IS_TERMINATING     = 0C000004Bh

;
; MessageId: STATUS_BAD_WORKING_SET_LIMIT
;
; MessageText:
;
;  An attempt was made to set the working set limit to an invalid value (minimum greater than maximum, etc).
;
STATUS_BAD_WORKING_SET_LIMIT     = 0C000004Ch

;
; MessageId: STATUS_INCOMPATIBLE_FILE_MAP
;
; MessageText:
;
;  A section was created to map a file which is not compatible to an already existing section which maps the same file.
;
STATUS_INCOMPATIBLE_FILE_MAP     = 0C000004Dh

;
; MessageId: STATUS_SECTION_PROTECTION
;
; MessageText:
;
;  A view to a section specifies a protection which is incompatible with the initial view's protection.
;
STATUS_SECTION_PROTECTION        = 0C000004Eh

;
; MessageId: STATUS_EAS_NOT_SUPPORTED
;
; MessageText:
;
;  An operation involving EAs failed because the file system does not support EAs.
;
STATUS_EAS_NOT_SUPPORTED         = 0C000004Fh

;
; MessageId: STATUS_EA_TOO_LARGE
;
; MessageText:
;
;  An EA operation failed because EA set is too large.
;
STATUS_EA_TOO_LARGE              = 0C0000050h

;
; MessageId: STATUS_NONEXISTENT_EA_ENTRY
;
; MessageText:
;
;  An EA operation failed because the name or EA index is invalid.
;
STATUS_NONEXISTENT_EA_ENTRY      = 0C0000051h

;
; MessageId: STATUS_NO_EAS_ON_FILE
;
; MessageText:
;
;  The file for which EAs were requested has no EAs.
;
STATUS_NO_EAS_ON_FILE            = 0C0000052h

;
; MessageId: STATUS_EA_CORRUPT_ERROR
;
; MessageText:
;
;  The EA is corrupt and non-readable.
;
STATUS_EA_CORRUPT_ERROR          = 0C0000053h

;
; MessageId: STATUS_FILE_LOCK_CONFLICT
;
; MessageText:
;
;  A requested read/write cannot be granted due to a conflicting file lock.
;
STATUS_FILE_LOCK_CONFLICT        = 0C0000054h

;
; MessageId: STATUS_LOCK_NOT_GRANTED
;
; MessageText:
;
;  A requested file lock cannot be granted due to other existing locks.
;
STATUS_LOCK_NOT_GRANTED          = 0C0000055h

;
; MessageId: STATUS_DELETE_PENDING
;
; MessageText:
;
;  A non close operation has been requested of a file object with a delete pending.
;
STATUS_DELETE_PENDING            = 0C0000056h

;
; MessageId: STATUS_CTL_FILE_NOT_SUPPORTED
;
; MessageText:
;
;  An attempt was made to set the control attribute on a file. This attribute is not supported in the target file system.
;
STATUS_CTL_FILE_NOT_SUPPORTED    = 0C0000057h

;
; MessageId: STATUS_UNKNOWN_REVISION
;
; MessageText:
;
;  Indicates a revision number encountered or specified is not one known by the service. It may be a more recent revision than the service is aware of.
;
STATUS_UNKNOWN_REVISION          = 0C0000058h

;
; MessageId: STATUS_REVISION_MISMATCH
;
; MessageText:
;
;  Indicates two revision levels are incompatible.
;
STATUS_REVISION_MISMATCH         = 0C0000059h

;
; MessageId: STATUS_INVALID_OWNER
;
; MessageText:
;
;  Indicates a particular Security ID may not be assigned as the owner of an object.
;
STATUS_INVALID_OWNER             = 0C000005Ah

;
; MessageId: STATUS_INVALID_PRIMARY_GROUP
;
; MessageText:
;
;  Indicates a particular Security ID may not be assigned as the primary group of an object.
;
STATUS_INVALID_PRIMARY_GROUP     = 0C000005Bh

;
; MessageId: STATUS_NO_IMPERSONATION_TOKEN
;
; MessageText:
;
;  An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client.
;
STATUS_NO_IMPERSONATION_TOKEN    = 0C000005Ch

;
; MessageId: STATUS_CANT_DISABLE_MANDATORY
;
; MessageText:
;
;  A mandatory group may not be disabled.
;
STATUS_CANT_DISABLE_MANDATORY    = 0C000005Dh

;
; MessageId: STATUS_NO_LOGON_SERVERS
;
; MessageText:
;
;  There are currently no logon servers available to service the logon request.
;
STATUS_NO_LOGON_SERVERS          = 0C000005Eh

;
; MessageId: STATUS_NO_SUCH_LOGON_SESSION
;
; MessageText:
;
;  A specified logon session does not exist. It may already have been terminated.
;
STATUS_NO_SUCH_LOGON_SESSION     = 0C000005Fh

;
; MessageId: STATUS_NO_SUCH_PRIVILEGE
;
; MessageText:
;
;  A specified privilege does not exist.
;
STATUS_NO_SUCH_PRIVILEGE         = 0C0000060h

;
; MessageId: STATUS_PRIVILEGE_NOT_HELD
;
; MessageText:
;
;  A required privilege is not held by the client.
;
STATUS_PRIVILEGE_NOT_HELD        = 0C0000061h

;
; MessageId: STATUS_INVALID_ACCOUNT_NAME
;
; MessageText:
;
;  The name provided is not a properly formed account name.
;
STATUS_INVALID_ACCOUNT_NAME      = 0C0000062h

;
; MessageId: STATUS_USER_EXISTS
;
; MessageText:
;
;  The specified user already exists.
;
STATUS_USER_EXISTS               = 0C0000063h

;
; MessageId: STATUS_NO_SUCH_USER
;
; MessageText:
;
;  The specified user does not exist.
;
STATUS_NO_SUCH_USER              = 0C0000064h     ; ntsubauth

;
; MessageId: STATUS_GROUP_EXISTS
;
; MessageText:
;
;  The specified group already exists.
;
STATUS_GROUP_EXISTS              = 0C0000065h

;
; MessageId: STATUS_NO_SUCH_GROUP
;
; MessageText:
;
;  The specified group does not exist.
;
STATUS_NO_SUCH_GROUP             = 0C0000066h

;
; MessageId: STATUS_MEMBER_IN_GROUP
;
; MessageText:
;
;  The specified user account is already in the specified group account.
;  Also used to indicate a group cannot be deleted because it contains a member.
;
STATUS_MEMBER_IN_GROUP           = 0C0000067h

;
; MessageId: STATUS_MEMBER_NOT_IN_GROUP
;
; MessageText:
;
;  The specified user account is not a member of the specified group account.
;
STATUS_MEMBER_NOT_IN_GROUP       = 0C0000068h

;
; MessageId: STATUS_LAST_ADMIN
;
; MessageText:
;
;  Indicates the requested operation would disable or delete the last remaining administration account.
;  This is not allowed to prevent creating a situation in which the system cannot be administrated.
;
STATUS_LAST_ADMIN                = 0C0000069h

;
; MessageId: STATUS_WRONG_PASSWORD
;
; MessageText:
;
;  When trying to update a password, this return status indicates that the value provided as the current password is not correct.
;
STATUS_WRONG_PASSWORD            = 0C000006Ah     ; ntsubauth

;
; MessageId: STATUS_ILL_FORMED_PASSWORD
;
; MessageText:
;
;  When trying to update a password, this return status indicates that the value provided for the new password contains values that are not allowed in passwords.
;
STATUS_ILL_FORMED_PASSWORD       = 0C000006Bh

;
; MessageId: STATUS_PASSWORD_RESTRICTION
;
; MessageText:
;
;  When trying to update a password, this status indicates that some password update rule has been violated. For example, the password may not meet length criteria.
;
STATUS_PASSWORD_RESTRICTION      = 0C000006Ch     ; ntsubauth

;
; MessageId: STATUS_LOGON_FAILURE
;
; MessageText:
;
;  The attempted logon is invalid. This is either due to a bad username or authentication information.
;
STATUS_LOGON_FAILURE             = 0C000006Dh     ; ntsubauth

;
; MessageId: STATUS_ACCOUNT_RESTRICTION
;
; MessageText:
;
;  Indicates a referenced user name and authentication information are valid, but some user account restriction has prevented successful authentication (such as time-of-day restrictions).
;
STATUS_ACCOUNT_RESTRICTION       = 0C000006Eh     ; ntsubauth

;
; MessageId: STATUS_INVALID_LOGON_HOURS
;
; MessageText:
;
;  The user account has time restrictions and may not be logged onto at this time.
;
STATUS_INVALID_LOGON_HOURS       = 0C000006Fh     ; ntsubauth

;
; MessageId: STATUS_INVALID_WORKSTATION
;
; MessageText:
;
;  The user account is restricted such that it may not be used to log on from the source workstation.
;
STATUS_INVALID_WORKSTATION       = 0C0000070h     ; ntsubauth

;
; MessageId: STATUS_PASSWORD_EXPIRED
;
; MessageText:
;
;  The user account's password has expired.
;
STATUS_PASSWORD_EXPIRED          = 0C0000071h     ; ntsubauth

;
; MessageId: STATUS_ACCOUNT_DISABLED
;
; MessageText:
;
;  The referenced account is currently disabled and may not be logged on to.
;
STATUS_ACCOUNT_DISABLED          = 0C0000072h     ; ntsubauth

;
; MessageId: STATUS_NONE_MAPPED
;
; MessageText:
;
;  None of the information to be translated has been translated.
;
STATUS_NONE_MAPPED               = 0C0000073h

;
; MessageId: STATUS_TOO_MANY_LUIDS_REQUESTED
;
; MessageText:
;
;  The number of LUIDs requested may not be allocated with a single allocation.
;
STATUS_TOO_MANY_LUIDS_REQUESTED  = 0C0000074h

;
; MessageId: STATUS_LUIDS_EXHAUSTED
;
; MessageText:
;
;  Indicates there are no more LUIDs to allocate.
;
STATUS_LUIDS_EXHAUSTED           = 0C0000075h

;
; MessageId: STATUS_INVALID_SUB_AUTHORITY
;
; MessageText:
;
;  Indicates the sub-authority value is invalid for the particular use.
;
STATUS_INVALID_SUB_AUTHORITY     = 0C0000076h

;
; MessageId: STATUS_INVALID_ACL
;
; MessageText:
;
;  Indicates the ACL structure is not valid.
;
STATUS_INVALID_ACL               = 0C0000077h

;
; MessageId: STATUS_INVALID_SID
;
; MessageText:
;
;  Indicates the SID structure is not valid.
;
STATUS_INVALID_SID               = 0C0000078h

;
; MessageId: STATUS_INVALID_SECURITY_DESCR
;
; MessageText:
;
;  Indicates the SECURITY_DESCRIPTOR structure is not valid.
;
STATUS_INVALID_SECURITY_DESCR    = 0C0000079h

;
; MessageId: STATUS_PROCEDURE_NOT_FOUND
;
; MessageText:
;
;  Indicates the specified procedure address cannot be found in the DLL.
;
STATUS_PROCEDURE_NOT_FOUND       = 0C000007Ah

;
; MessageId: STATUS_INVALID_IMAGE_FORMAT
;
; MessageText:
;
;  {Bad Image}
;  The application or DLL %hs is not a valid Windows image. Please check this against your installation diskette.
;
STATUS_INVALID_IMAGE_FORMAT      = 0C000007Bh

;
; MessageId: STATUS_NO_TOKEN
;
; MessageText:
;
;  An attempt was made to reference a token that doesn't exist.
;  This is typically done by referencing the token associated with a thread when the thread is not impersonating a client.
;
STATUS_NO_TOKEN                  = 0C000007Ch

;
; MessageId: STATUS_BAD_INHERITANCE_ACL
;
; MessageText:
;
;  Indicates that an attempt to build either an inherited ACL or ACE was not successful.
;  This can be caused by a number of things. One of the more probable causes is the replacement of a CreatorId with an SID that didn't fit into the ACE or ACL.
;
STATUS_BAD_INHERITANCE_ACL       = 0C000007Dh

;
; MessageId: STATUS_RANGE_NOT_LOCKED
;
; MessageText:
;
;  The range specified in NtUnlockFile was not locked.
;
STATUS_RANGE_NOT_LOCKED          = 0C000007Eh

;
; MessageId: STATUS_DISK_FULL
;
; MessageText:
;
;  An operation failed because the disk was full.
;
STATUS_DISK_FULL                 = 0C000007Fh

;
; MessageId: STATUS_SERVER_DISABLED
;
; MessageText:
;
;  The GUID allocation server is [already] disabled at the moment.
;
STATUS_SERVER_DISABLED           = 0C0000080h

;
; MessageId: STATUS_SERVER_NOT_DISABLED
;
; MessageText:
;
;  The GUID allocation server is [already] enabled at the moment.
;
STATUS_SERVER_NOT_DISABLED       = 0C0000081h

;
; MessageId: STATUS_TOO_MANY_GUIDS_REQUESTED
;
; MessageText:
;
;  Too many GUIDs were requested from the allocation server at once.
;
STATUS_TOO_MANY_GUIDS_REQUESTED  = 0C0000082h

;
; MessageId: STATUS_GUIDS_EXHAUSTED
;
; MessageText:
;
;  The GUIDs could not be allocated because the Authority Agent was exhausted.
;
STATUS_GUIDS_EXHAUSTED           = 0C0000083h

;
; MessageId: STATUS_INVALID_ID_AUTHORITY
;
; MessageText:
;
;  The value provided was an invalid value for an identifier authority.
;
STATUS_INVALID_ID_AUTHORITY      = 0C0000084h

;
; MessageId: STATUS_AGENTS_EXHAUSTED
;
; MessageText:
;
;  There are no more authority agent values available for the given identifier authority value.
;
STATUS_AGENTS_EXHAUSTED          = 0C0000085h

;
; MessageId: STATUS_INVALID_VOLUME_LABEL
;
; MessageText:
;
;  An invalid volume label has been specified.
;
STATUS_INVALID_VOLUME_LABEL      = 0C0000086h

;
; MessageId: STATUS_SECTION_NOT_EXTENDED
;
; MessageText:
;
;  A mapped section could not be extended.
;
STATUS_SECTION_NOT_EXTENDED      = 0C0000087h

;
; MessageId: STATUS_NOT_MAPPED_DATA
;
; MessageText:
;
;  Specified section to flush does not map a data file.
;
STATUS_NOT_MAPPED_DATA           = 0C0000088h

;
; MessageId: STATUS_RESOURCE_DATA_NOT_FOUND
;
; MessageText:
;
;  Indicates the specified image file did not contain a resource section.
;
STATUS_RESOURCE_DATA_NOT_FOUND   = 0C0000089h

;
; MessageId: STATUS_RESOURCE_TYPE_NOT_FOUND
;
; MessageText:
;
;  Indicates the specified resource type cannot be found in the image file.
;
STATUS_RESOURCE_TYPE_NOT_FOUND   = 0C000008Ah

;
; MessageId: STATUS_RESOURCE_NAME_NOT_FOUND
;
; MessageText:
;
;  Indicates the specified resource name cannot be found in the image file.
;
STATUS_RESOURCE_NAME_NOT_FOUND   = 0C000008Bh

;
; MessageId: STATUS_ARRAY_BOUNDS_EXCEEDED
;
; MessageText:
;
;  {EXCEPTION}
;  Array bounds exceeded.
;
STATUS_ARRAY_BOUNDS_EXCEEDED     = 0C000008Ch    ; winnt

;
; MessageId: STATUS_FLOAT_DENORMAL_OPERAND
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point denormal operand.
;
STATUS_FLOAT_DENORMAL_OPERAND    = 0C000008Dh    ; winnt

;
; MessageId: STATUS_FLOAT_DIVIDE_BY_ZERO
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point division by zero.
;
STATUS_FLOAT_DIVIDE_BY_ZERO      = 0C000008Eh    ; winnt

;
; MessageId: STATUS_FLOAT_INEXACT_RESULT
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point inexact result.
;
STATUS_FLOAT_INEXACT_RESULT      = 0C000008Fh    ; winnt

;
; MessageId: STATUS_FLOAT_INVALID_OPERATION
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point invalid operation.
;
STATUS_FLOAT_INVALID_OPERATION   = 0C0000090h    ; winnt

;
; MessageId: STATUS_FLOAT_OVERFLOW
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point overflow.
;
STATUS_FLOAT_OVERFLOW            = 0C0000091h    ; winnt

;
; MessageId: STATUS_FLOAT_STACK_CHECK
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point stack check.
;
STATUS_FLOAT_STACK_CHECK         = 0C0000092h    ; winnt

;
; MessageId: STATUS_FLOAT_UNDERFLOW
;
; MessageText:
;
;  {EXCEPTION}
;  Floating-point underflow.
;
STATUS_FLOAT_UNDERFLOW           = 0C0000093h    ; winnt

;
; MessageId: STATUS_INTEGER_DIVIDE_BY_ZERO
;
; MessageText:
;
;  {EXCEPTION}
;  Integer division by zero.
;
STATUS_INTEGER_DIVIDE_BY_ZERO    = 0C0000094h    ; winnt

;
; MessageId: STATUS_INTEGER_OVERFLOW
;
; MessageText:
;
;  {EXCEPTION}
;  Integer overflow.
;
STATUS_INTEGER_OVERFLOW          = 0C0000095h    ; winnt

;
; MessageId: STATUS_PRIVILEGED_INSTRUCTION
;
; MessageText:
;
;  {EXCEPTION}
;  Privileged instruction.
;
STATUS_PRIVILEGED_INSTRUCTION    = 0C0000096h    ; winnt

;
; MessageId: STATUS_TOO_MANY_PAGING_FILES
;
; MessageText:
;
;  An attempt was made to install more paging files than the system supports.
;
STATUS_TOO_MANY_PAGING_FILES     = 0C0000097h

;
; MessageId: STATUS_FILE_INVALID
;
; MessageText:
;
;  The volume for a file has been externally altered such that the opened file is no longer valid.
;
STATUS_FILE_INVALID              = 0C0000098h

;
; MessageId: STATUS_ALLOTTED_SPACE_EXCEEDED
;
; MessageText:
;
;  When a block of memory is allotted for future updates, such as the memory
;  allocated to hold discretionary access control and primary group information, successive updates may exceed the amount of memory originally allotted.
;  Since quota may already have been charged to several processes which have handles to the object, it is not reasonable to alter the size of the allocated memory.
;  Instead, a request that requires more memory than has been allotted must fail and the STATUS_ALLOTED_SPACE_EXCEEDED error returned.
;
STATUS_ALLOTTED_SPACE_EXCEEDED   = 0C0000099h

;
; MessageId: STATUS_INSUFFICIENT_RESOURCES
;
; MessageText:
;
;  Insufficient system resources exist to complete the API.
;
STATUS_INSUFFICIENT_RESOURCES    = 0C000009Ah     ; ntsubauth

;
; MessageId: STATUS_DFS_EXIT_PATH_FOUND
;
; MessageText:
;
;  An attempt has been made to open a DFS exit path control file.
;
STATUS_DFS_EXIT_PATH_FOUND       = 0C000009Bh

;
; MessageId: STATUS_DEVICE_DATA_ERROR
;
; MessageText:
;
;  STATUS_DEVICE_DATA_ERROR
;
STATUS_DEVICE_DATA_ERROR         = 0C000009Ch

;
; MessageId: STATUS_DEVICE_NOT_CONNECTED
;
; MessageText:
;
;  STATUS_DEVICE_NOT_CONNECTED
;
STATUS_DEVICE_NOT_CONNECTED      = 0C000009Dh

;
; MessageId: STATUS_DEVICE_POWER_FAILURE
;
; MessageText:
;
;  STATUS_DEVICE_POWER_FAILURE
;
STATUS_DEVICE_POWER_FAILURE      = 0C000009Eh

;
; MessageId: STATUS_FREE_VM_NOT_AT_BASE
;
; MessageText:
;
;  Virtual memory cannot be freed as base address is not the base of the region and a region size of zero was specified.
;
STATUS_FREE_VM_NOT_AT_BASE       = 0C000009Fh

;
; MessageId: STATUS_MEMORY_NOT_ALLOCATED
;
; MessageText:
;
;  An attempt was made to free virtual memory which is not allocated.
;
STATUS_MEMORY_NOT_ALLOCATED      = 0C00000A0h

;
; MessageId: STATUS_WORKING_SET_QUOTA
;
; MessageText:
;
;  The working set is not big enough to allow the requested pages to be locked.
;
STATUS_WORKING_SET_QUOTA         = 0C00000A1h

;
; MessageId: STATUS_MEDIA_WRITE_PROTECTED
;
; MessageText:
;
;  {Write Protect Error}
;  The disk cannot be written to because it is write protected.
;  Please remove the write protection from the volume %hs in drive %hs.
;
STATUS_MEDIA_WRITE_PROTECTED     = 0C00000A2h

;
; MessageId: STATUS_DEVICE_NOT_READY
;
; MessageText:
;
;  {Drive Not Ready}
;  The drive is not ready for use; its door may be open.
;  Please check drive %hs and make sure that a disk is inserted and that the drive door is closed.
;
STATUS_DEVICE_NOT_READY          = 0C00000A3h

;
; MessageId: STATUS_INVALID_GROUP_ATTRIBUTES
;
; MessageText:
;
;  The specified attributes are invalid, or incompatible with the attributes for the group as a whole.
;
STATUS_INVALID_GROUP_ATTRIBUTES  = 0C00000A4h

;
; MessageId: STATUS_BAD_IMPERSONATION_LEVEL
;
; MessageText:
;
;  A specified impersonation level is invalid.
;  Also used to indicate a required impersonation level was not provided.
;
STATUS_BAD_IMPERSONATION_LEVEL   = 0C00000A5h

;
; MessageId: STATUS_CANT_OPEN_ANONYMOUS
;
; MessageText:
;
;  An attempt was made to open an Anonymous level token.
;  Anonymous tokens may not be opened.
;
STATUS_CANT_OPEN_ANONYMOUS       = 0C00000A6h

;
; MessageId: STATUS_BAD_VALIDATION_CLASS
;
; MessageText:
;
;  The validation information class requested was invalid.
;
STATUS_BAD_VALIDATION_CLASS      = 0C00000A7h

;
; MessageId: STATUS_BAD_TOKEN_TYPE
;
; MessageText:
;
;  The type of a token object is inappropriate for its attempted use.
;
STATUS_BAD_TOKEN_TYPE            = 0C00000A8h

;
; MessageId: STATUS_BAD_MASTER_BOOT_RECORD
;
; MessageText:
;
;  The type of a token object is inappropriate for its attempted use.
;
STATUS_BAD_MASTER_BOOT_RECORD    = 0C00000A9h

;
; MessageId: STATUS_INSTRUCTION_MISALIGNMENT
;
; MessageText:
;
;  An attempt was made to execute an instruction at an unaligned address and the host system does not support unaligned instruction references.
;
STATUS_INSTRUCTION_MISALIGNMENT  = 0C00000AAh

;
; MessageId: STATUS_INSTANCE_NOT_AVAILABLE
;
; MessageText:
;
;  The maximum named pipe instance count has been reached.
;
STATUS_INSTANCE_NOT_AVAILABLE    = 0C00000ABh

;
; MessageId: STATUS_PIPE_NOT_AVAILABLE
;
; MessageText:
;
;  An instance of a named pipe cannot be found in the listening state.
;
STATUS_PIPE_NOT_AVAILABLE        = 0C00000ACh

;
; MessageId: STATUS_INVALID_PIPE_STATE
;
; MessageText:
;
;  The named pipe is not in the connected or closing state.
;
STATUS_INVALID_PIPE_STATE        = 0C00000ADh

;
; MessageId: STATUS_PIPE_BUSY
;
; MessageText:
;
;  The specified pipe is set to complete operations and there are current I/O operations queued so it cannot be changed to queue operations.
;
STATUS_PIPE_BUSY                 = 0C00000AEh

;
; MessageId: STATUS_ILLEGAL_FUNCTION
;
; MessageText:
;
;  The specified handle is not open to the server end of the named pipe.
;
STATUS_ILLEGAL_FUNCTION          = 0C00000AFh

;
; MessageId: STATUS_PIPE_DISCONNECTED
;
; MessageText:
;
;  The specified named pipe is in the disconnected state.
;
STATUS_PIPE_DISCONNECTED         = 0C00000B0h

;
; MessageId: STATUS_PIPE_CLOSING
;
; MessageText:
;
;  The specified named pipe is in the closing state.
;
STATUS_PIPE_CLOSING              = 0C00000B1h

;
; MessageId: STATUS_PIPE_CONNECTED
;
; MessageText:
;
;  The specified named pipe is in the connected state.
;
STATUS_PIPE_CONNECTED            = 0C00000B2h

;
; MessageId: STATUS_PIPE_LISTENING
;
; MessageText:
;
;  The specified named pipe is in the listening state.
;
STATUS_PIPE_LISTENING            = 0C00000B3h

;
; MessageId: STATUS_INVALID_READ_MODE
;
; MessageText:
;
;  The specified named pipe is not in message mode.
;
STATUS_INVALID_READ_MODE         = 0C00000B4h

;
; MessageId: STATUS_IO_TIMEOUT
;
; MessageText:
;
;  {Device Timeout}
;  The specified I/O operation on %hs was not completed before the time-out period expired.
;
STATUS_IO_TIMEOUT                = 0C00000B5h

;
; MessageId: STATUS_FILE_FORCED_CLOSED
;
; MessageText:
;
;  The specified file has been closed by another process.
;
STATUS_FILE_FORCED_CLOSED        = 0C00000B6h

;
; MessageId: STATUS_PROFILING_NOT_STARTED
;
; MessageText:
;
;  Profiling not started.
;
STATUS_PROFILING_NOT_STARTED     = 0C00000B7h

;
; MessageId: STATUS_PROFILING_NOT_STOPPED
;
; MessageText:
;
;  Profiling not stopped.
;
STATUS_PROFILING_NOT_STOPPED     = 0C00000B8h

;
; MessageId: STATUS_COULD_NOT_INTERPRET
;
; MessageText:
;
;  The passed ACL did not contain the minimum required information.
;
STATUS_COULD_NOT_INTERPRET       = 0C00000B9h

;
; MessageId: STATUS_FILE_IS_A_DIRECTORY
;
; MessageText:
;
;  The file that was specified as a target is a directory and the caller specified that it could be anything but a directory.
;
STATUS_FILE_IS_A_DIRECTORY       = 0C00000BAh

;
; Network specific errors.
;
;
;
; MessageId: STATUS_NOT_SUPPORTED
;
; MessageText:
;
;  The network request is not supported.
;
STATUS_NOT_SUPPORTED             = 0C00000BBh

;
; MessageId: STATUS_REMOTE_NOT_LISTENING
;
; MessageText:
;
;  This remote computer is not listening.
;
STATUS_REMOTE_NOT_LISTENING      = 0C00000BCh

;
; MessageId: STATUS_DUPLICATE_NAME
;
; MessageText:
;
;  A duplicate name exists on the network.
;
STATUS_DUPLICATE_NAME            = 0C00000BDh

;
; MessageId: STATUS_BAD_NETWORK_PATH
;
; MessageText:
;
;  The network path cannot be located.
;
STATUS_BAD_NETWORK_PATH          = 0C00000BEh

;
; MessageId: STATUS_NETWORK_BUSY
;
; MessageText:
;
;  The network is busy.
;
STATUS_NETWORK_BUSY              = 0C00000BFh

;
; MessageId: STATUS_DEVICE_DOES_NOT_EXIST
;
; MessageText:
;
;  This device does not exist.
;
STATUS_DEVICE_DOES_NOT_EXIST     = 0C00000C0h

;
; MessageId: STATUS_TOO_MANY_COMMANDS
;
; MessageText:
;
;  The network BIOS command limit has been reached.
;
STATUS_TOO_MANY_COMMANDS         = 0C00000C1h

;
; MessageId: STATUS_ADAPTER_HARDWARE_ERROR
;
; MessageText:
;
;  An I/O adapter hardware error has occurred.
;
STATUS_ADAPTER_HARDWARE_ERROR    = 0C00000C2h

;
; MessageId: STATUS_INVALID_NETWORK_RESPONSE
;
; MessageText:
;
;  The network responded incorrectly.
;
STATUS_INVALID_NETWORK_RESPONSE  = 0C00000C3h

;
; MessageId: STATUS_UNEXPECTED_NETWORK_ERROR
;
; MessageText:
;
;  An unexpected network error occurred.
;
STATUS_UNEXPECTED_NETWORK_ERROR  = 0C00000C4h

;
; MessageId: STATUS_BAD_REMOTE_ADAPTER
;
; MessageText:
;
;  The remote adapter is not compatible.
;
STATUS_BAD_REMOTE_ADAPTER        = 0C00000C5h

;
; MessageId: STATUS_PRINT_QUEUE_FULL
;
; MessageText:
;
;  The printer queue is full.
;
STATUS_PRINT_QUEUE_FULL          = 0C00000C6h

;
; MessageId: STATUS_NO_SPOOL_SPACE
;
; MessageText:
;
;  Space to store the file waiting to be printed is not available on the server.
;
STATUS_NO_SPOOL_SPACE            = 0C00000C7h

;
; MessageId: STATUS_PRINT_CANCELLED
;
; MessageText:
;
;  The requested print file has been canceled.
;
STATUS_PRINT_CANCELLED           = 0C00000C8h

;
; MessageId: STATUS_NETWORK_NAME_DELETED
;
; MessageText:
;
;  The network name was deleted.
;
STATUS_NETWORK_NAME_DELETED      = 0C00000C9h

;
; MessageId: STATUS_NETWORK_ACCESS_DENIED
;
; MessageText:
;
;  Network access is denied.
;
STATUS_NETWORK_ACCESS_DENIED     = 0C00000CAh

;
; MessageId: STATUS_BAD_DEVICE_TYPE
;
; MessageText:
;
;  {Incorrect Network Resource Type}
;  The specified device type (LPT, for example) conflicts with the actual device type on the remote resource.
;
STATUS_BAD_DEVICE_TYPE           = 0C00000CBh

;
; MessageId: STATUS_BAD_NETWORK_NAME
;
; MessageText:
;
;  {Network Name Not Found}
;  The specified share name cannot be found on the remote server.
;
STATUS_BAD_NETWORK_NAME          = 0C00000CCh

;
; MessageId: STATUS_TOO_MANY_NAMES
;
; MessageText:
;
;  The name limit for the local computer network adapter card was exceeded.
;
STATUS_TOO_MANY_NAMES            = 0C00000CDh

;
; MessageId: STATUS_TOO_MANY_SESSIONS
;
; MessageText:
;
;  The network BIOS session limit was exceeded.
;
STATUS_TOO_MANY_SESSIONS         = 0C00000CEh

;
; MessageId: STATUS_SHARING_PAUSED
;
; MessageText:
;
;  File sharing has been temporarily paused.
;
STATUS_SHARING_PAUSED            = 0C00000CFh

;
; MessageId: STATUS_REQUEST_NOT_ACCEPTED
;
; MessageText:
;
;  No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept.
;
STATUS_REQUEST_NOT_ACCEPTED      = 0C00000D0h

;
; MessageId: STATUS_REDIRECTOR_PAUSED
;
; MessageText:
;
;  Print or disk redirection is temporarily paused.
;
STATUS_REDIRECTOR_PAUSED         = 0C00000D1h

;
; MessageId: STATUS_NET_WRITE_FAULT
;
; MessageText:
;
;  A network data fault occurred.
;
STATUS_NET_WRITE_FAULT           = 0C00000D2h

;
; MessageId: STATUS_PROFILING_AT_LIMIT
;
; MessageText:
;
;  The number of active profiling objects is at the maximum and no more may be started.
;
STATUS_PROFILING_AT_LIMIT        = 0C00000D3h

;
; MessageId: STATUS_NOT_SAME_DEVICE
;
; MessageText:
;
;  {Incorrect Volume}
;  The target file of a rename request is located on a different device than the source of the rename request.
;
STATUS_NOT_SAME_DEVICE           = 0C00000D4h

;
; MessageId: STATUS_FILE_RENAMED
;
; MessageText:
;
;  The file specified has been renamed and thus cannot be modified.
;
STATUS_FILE_RENAMED              = 0C00000D5h

;
; MessageId: STATUS_VIRTUAL_CIRCUIT_CLOSED
;
; MessageText:
;
;  {Network Request Timeout}
;  The session with a remote server has been disconnected because the time-out interval for a request has expired.
;
STATUS_VIRTUAL_CIRCUIT_CLOSED    = 0C00000D6h

;
; MessageId: STATUS_NO_SECURITY_ON_OBJECT
;
; MessageText:
;
;  Indicates an attempt was made to operate on the security of an object that does not have security associated with it.
;
STATUS_NO_SECURITY_ON_OBJECT     = 0C00000D7h

;
; MessageId: STATUS_CANT_WAIT
;
; MessageText:
;
;  Used to indicate that an operation cannot continue without blocking for I/O.
;
STATUS_CANT_WAIT                 = 0C00000D8h

;
; MessageId: STATUS_PIPE_EMPTY
;
; MessageText:
;
;  Used to indicate that a read operation was done on an empty pipe.
;
STATUS_PIPE_EMPTY                = 0C00000D9h

;
; MessageId: STATUS_CANT_ACCESS_DOMAIN_INFO
;
; MessageText:
;
;  Configuration information could not be read from the domain controller, either because the machine is unavailable, or access has been denied.
;
STATUS_CANT_ACCESS_DOMAIN_INFO   = 0C00000DAh

;
; MessageId: STATUS_CANT_TERMINATE_SELF
;
; MessageText:
;
;  Indicates that a thread attempted to terminate itself by default (called NtTerminateThread with NULL) and it was the last thread in the current process.
;
STATUS_CANT_TERMINATE_SELF       = 0C00000DBh

;
; MessageId: STATUS_INVALID_SERVER_STATE
;
; MessageText:
;
;  Indicates the Sam Server was in the wrong state to perform the desired operation.
;
STATUS_INVALID_SERVER_STATE      = 0C00000DCh

;
; MessageId: STATUS_INVALID_DOMAIN_STATE
;
; MessageText:
;
;  Indicates the Domain was in the wrong state to perform the desired operation.
;
STATUS_INVALID_DOMAIN_STATE      = 0C00000DDh

;
; MessageId: STATUS_INVALID_DOMAIN_ROLE
;
; MessageText:
;
;  This operation is only allowed for the Primary Domain Controller of the domain.
;
STATUS_INVALID_DOMAIN_ROLE       = 0C00000DEh

;
; MessageId: STATUS_NO_SUCH_DOMAIN
;
; MessageText:
;
;  The specified Domain did not exist.
;
STATUS_NO_SUCH_DOMAIN            = 0C00000DFh

;
; MessageId: STATUS_DOMAIN_EXISTS
;
; MessageText:
;
;  The specified Domain already exists.
;
STATUS_DOMAIN_EXISTS             = 0C00000E0h

;
; MessageId: STATUS_DOMAIN_LIMIT_EXCEEDED
;
; MessageText:
;
;  An attempt was made to exceed the limit on the number of domains per server for this release.
;
STATUS_DOMAIN_LIMIT_EXCEEDED     = 0C00000E1h

;
; MessageId: STATUS_OPLOCK_NOT_GRANTED
;
; MessageText:
;
;  Error status returned when oplock request is denied.
;
STATUS_OPLOCK_NOT_GRANTED        = 0C00000E2h

;
; MessageId: STATUS_INVALID_OPLOCK_PROTOCOL
;
; MessageText:
;
;  Error status returned when an invalid oplock acknowledgment is received by a file system.
;
STATUS_INVALID_OPLOCK_PROTOCOL   = 0C00000E3h

;
; MessageId: STATUS_INTERNAL_DB_CORRUPTION
;
; MessageText:
;
;  This error indicates that the requested operation cannot be completed due to a catastrophic media failure or on-disk data structure corruption.
;
STATUS_INTERNAL_DB_CORRUPTION    = 0C00000E4h

;
; MessageId: STATUS_INTERNAL_ERROR
;
; MessageText:
;
;  An internal error occurred.
;
STATUS_INTERNAL_ERROR            = 0C00000E5h

;
; MessageId: STATUS_GENERIC_NOT_MAPPED
;
; MessageText:
;
;  Indicates generic access types were contained in an access mask which should already be mapped to non-generic access types.
;
STATUS_GENERIC_NOT_MAPPED        = 0C00000E6h

;
; MessageId: STATUS_BAD_DESCRIPTOR_FORMAT
;
; MessageText:
;
;  Indicates a security descriptor is not in the necessary format (absolute or self-relative).
;
STATUS_BAD_DESCRIPTOR_FORMAT     = 0C00000E7h

;
; Status codes raised by the Cache Manager which must be considered as
; "expected" by its callers.
;
;
; MessageId: STATUS_INVALID_USER_BUFFER
;
; MessageText:
;
;  An access to a user buffer failed at an "expected" point in time.
;  This code is defined since the caller does not want to accept STATUS_ACCESS_VIOLATION in its filter.
;
STATUS_INVALID_USER_BUFFER       = 0C00000E8h

;
; MessageId: STATUS_UNEXPECTED_IO_ERROR
;
; MessageText:
;
;  If an I/O error is returned which is not defined in the standard FsRtl filter, it is converted to the following error which is guaranteed to be in the filter.
;  In this case information is lost, however, the filter correctly handles the exception.
;
STATUS_UNEXPECTED_IO_ERROR       = 0C00000E9h

;
; MessageId: STATUS_UNEXPECTED_MM_CREATE_ERR
;
; MessageText:
;
;  If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter.
;  In this case information is lost, however, the filter correctly handles the exception.
;
STATUS_UNEXPECTED_MM_CREATE_ERR  = 0C00000EAh

;
; MessageId: STATUS_UNEXPECTED_MM_MAP_ERROR
;
; MessageText:
;
;  If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter.
;  In this case information is lost, however, the filter correctly handles the exception.
;
STATUS_UNEXPECTED_MM_MAP_ERROR   = 0C00000EBh

;
; MessageId: STATUS_UNEXPECTED_MM_EXTEND_ERR
;
; MessageText:
;
;  If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter.
;  In this case information is lost, however, the filter correctly handles the exception.
;
STATUS_UNEXPECTED_MM_EXTEND_ERR  = 0C00000ECh

;
; MessageId: STATUS_NOT_LOGON_PROCESS
;
; MessageText:
;
;  The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process.
;
STATUS_NOT_LOGON_PROCESS         = 0C00000EDh

;
; MessageId: STATUS_LOGON_SESSION_EXISTS
;
; MessageText:
;
;  An attempt has been made to start a new session manager or LSA logon session with an ID that is already in use.
;
STATUS_LOGON_SESSION_EXISTS      = 0C00000EEh

;
; MessageId: STATUS_INVALID_PARAMETER_1
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the first argument.
;
STATUS_INVALID_PARAMETER_1       = 0C00000EFh

;
; MessageId: STATUS_INVALID_PARAMETER_2
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the second argument.
;
STATUS_INVALID_PARAMETER_2       = 0C00000F0h

;
; MessageId: STATUS_INVALID_PARAMETER_3
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the third argument.
;
STATUS_INVALID_PARAMETER_3       = 0C00000F1h

;
; MessageId: STATUS_INVALID_PARAMETER_4
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the fourth argument.
;
STATUS_INVALID_PARAMETER_4       = 0C00000F2h

;
; MessageId: STATUS_INVALID_PARAMETER_5
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the fifth argument.
;
STATUS_INVALID_PARAMETER_5       = 0C00000F3h

;
; MessageId: STATUS_INVALID_PARAMETER_6
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the sixth argument.
;
STATUS_INVALID_PARAMETER_6       = 0C00000F4h

;
; MessageId: STATUS_INVALID_PARAMETER_7
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the seventh argument.
;
STATUS_INVALID_PARAMETER_7       = 0C00000F5h

;
; MessageId: STATUS_INVALID_PARAMETER_8
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the eighth argument.
;
STATUS_INVALID_PARAMETER_8       = 0C00000F6h

;
; MessageId: STATUS_INVALID_PARAMETER_9
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the ninth argument.
;
STATUS_INVALID_PARAMETER_9       = 0C00000F7h

;
; MessageId: STATUS_INVALID_PARAMETER_10
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the tenth argument.
;
STATUS_INVALID_PARAMETER_10      = 0C00000F8h

;
; MessageId: STATUS_INVALID_PARAMETER_11
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the eleventh argument.
;
STATUS_INVALID_PARAMETER_11      = 0C00000F9h

;
; MessageId: STATUS_INVALID_PARAMETER_12
;
; MessageText:
;
;  An invalid parameter was passed to a service or function as the twelfth argument.
;
STATUS_INVALID_PARAMETER_12      = 0C00000FAh

;
; MessageId: STATUS_REDIRECTOR_NOT_STARTED
;
; MessageText:
;
;  An attempt was made to access a network file, but the network software was not yet started.
;
STATUS_REDIRECTOR_NOT_STARTED    = 0C00000FBh

;
; MessageId: STATUS_REDIRECTOR_STARTED
;
; MessageText:
;
;  An attempt was made to start the redirector, but the redirector has already been started.
;
STATUS_REDIRECTOR_STARTED        = 0C00000FCh

;
; MessageId: STATUS_STACK_OVERFLOW
;
; MessageText:
;
;  A new guard page for the stack cannot be created.
;
STATUS_STACK_OVERFLOW            = 0C00000FDh    ; winnt

;
; MessageId: STATUS_NO_SUCH_PACKAGE
;
; MessageText:
;
;  A specified authentication package is unknown.
;
STATUS_NO_SUCH_PACKAGE           = 0C00000FEh

;
; MessageId: STATUS_BAD_FUNCTION_TABLE
;
; MessageText:
;
;  A malformed function table was encountered during an unwind operation.
;
STATUS_BAD_FUNCTION_TABLE        = 0C00000FFh

;
; MessageId: STATUS_VARIABLE_NOT_FOUND
;
; MessageText:
;
;  Indicates the specified environment variable name was not found in the specified environment block.
;
STATUS_VARIABLE_NOT_FOUND        = 0C0000100h

;
; MessageId: STATUS_DIRECTORY_NOT_EMPTY
;
; MessageText:
;
;  Indicates that the directory trying to be deleted is not empty.
;
STATUS_DIRECTORY_NOT_EMPTY       = 0C0000101h

;
; MessageId: STATUS_FILE_CORRUPT_ERROR
;
; MessageText:
;
;  {Corrupt File}
;  The file or directory %hs is corrupt and unreadable.
;  Please run the Chkdsk utility.
;
STATUS_FILE_CORRUPT_ERROR        = 0C0000102h

;
; MessageId: STATUS_NOT_A_DIRECTORY
;
; MessageText:
;
;  A requested opened file is not a directory.
;
STATUS_NOT_A_DIRECTORY           = 0C0000103h

;
; MessageId: STATUS_BAD_LOGON_SESSION_STATE
;
; MessageText:
;
;  The logon session is not in a state that is consistent with the requested operation.
;
STATUS_BAD_LOGON_SESSION_STATE   = 0C0000104h

;
; MessageId: STATUS_LOGON_SESSION_COLLISION
;
; MessageText:
;
;  An internal LSA error has occurred. An authentication package has requested the creation of a Logon Session but the ID of an already existing Logon Session has been specified.
;
STATUS_LOGON_SESSION_COLLISION   = 0C0000105h

;
; MessageId: STATUS_NAME_TOO_LONG
;
; MessageText:
;
;  A specified name string is too long for its intended use.
;
STATUS_NAME_TOO_LONG             = 0C0000106h

;
; MessageId: STATUS_FILES_OPEN
;
; MessageText:
;
;  The user attempted to force close the files on a redirected drive, but there were opened files on the drive, and the user did not specify a sufficient level of force.
;
STATUS_FILES_OPEN                = 0C0000107h

;
; MessageId: STATUS_CONNECTION_IN_USE
;
; MessageText:
;
;  The user attempted to force close the files on a redirected drive, but there were opened directories on the drive, and the user did not specify a sufficient level of force.
;
STATUS_CONNECTION_IN_USE         = 0C0000108h

;
; MessageId: STATUS_MESSAGE_NOT_FOUND
;
; MessageText:
;
;  RtlFindMessage could not locate the requested message ID in the message table resource.
;
STATUS_MESSAGE_NOT_FOUND         = 0C0000109h

;
; MessageId: STATUS_PROCESS_IS_TERMINATING
;
; MessageText:
;
;  An attempt was made to duplicate an object handle into or out of an exiting process.
;
STATUS_PROCESS_IS_TERMINATING    = 0C000010Ah

;
; MessageId: STATUS_INVALID_LOGON_TYPE
;
; MessageText:
;
;  Indicates an invalid value has been provided for the LogonType requested.
;
STATUS_INVALID_LOGON_TYPE        = 0C000010Bh

;
; MessageId: STATUS_NO_GUID_TRANSLATION
;
; MessageText:
;
;  Indicates that an attempt was made to assign protection to a file system file or directory and one of the SIDs in the security descriptor could not be translated into a GUID that could be stored by the file system.
;  This causes the protection attempt to fail, which may cause a file creation attempt to fail.
;
STATUS_NO_GUID_TRANSLATION       = 0C000010Ch

;
; MessageId: STATUS_CANNOT_IMPERSONATE
;
; MessageText:
;
;  Indicates that an attempt has been made to impersonate via a named pipe that has not yet been read from.
;
STATUS_CANNOT_IMPERSONATE        = 0C000010Dh

;
; MessageId: STATUS_IMAGE_ALREADY_LOADED
;
; MessageText:
;
;  Indicates that the specified image is already loaded.
;
STATUS_IMAGE_ALREADY_LOADED      = 0C000010Eh


;
; ============================================================
; NOTE: The following ABIOS error code should be reserved on
;       non ABIOS kernel. Eventually, I will remove the ifdef
;       ABIOS.
; ============================================================
;
;
; MessageId: STATUS_ABIOS_NOT_PRESENT
;
; MessageText:
;
;  STATUS_ABIOS_NOT_PRESENT
;
STATUS_ABIOS_NOT_PRESENT         = 0C000010Fh

;
; MessageId: STATUS_ABIOS_LID_NOT_EXIST
;
; MessageText:
;
;  STATUS_ABIOS_LID_NOT_EXIST
;
STATUS_ABIOS_LID_NOT_EXIST       = 0C0000110h

;
; MessageId: STATUS_ABIOS_LID_ALREADY_OWNED
;
; MessageText:
;
;  STATUS_ABIOS_LID_ALREADY_OWNED
;
STATUS_ABIOS_LID_ALREADY_OWNED   = 0C0000111h

;
; MessageId: STATUS_ABIOS_NOT_LID_OWNER
;
; MessageText:
;
;  STATUS_ABIOS_NOT_LID_OWNER
;
STATUS_ABIOS_NOT_LID_OWNER       = 0C0000112h

;
; MessageId: STATUS_ABIOS_INVALID_COMMAND
;
; MessageText:
;
;  STATUS_ABIOS_INVALID_COMMAND
;
STATUS_ABIOS_INVALID_COMMAND     = 0C0000113h

;
; MessageId: STATUS_ABIOS_INVALID_LID
;
; MessageText:
;
;  STATUS_ABIOS_INVALID_LID
;
STATUS_ABIOS_INVALID_LID         = 0C0000114h

;
; MessageId: STATUS_ABIOS_SELECTOR_NOT_AVAILABLE
;
; MessageText:
;
;  STATUS_ABIOS_SELECTOR_NOT_AVAILABLE
;
STATUS_ABIOS_SELECTOR_NOT_AVAILABLE = 0C0000115h

;
; MessageId: STATUS_ABIOS_INVALID_SELECTOR
;
; MessageText:
;
;  STATUS_ABIOS_INVALID_SELECTOR
;
STATUS_ABIOS_INVALID_SELECTOR    = 0C0000116h

;
; MessageId: STATUS_NO_LDT
;
; MessageText:
;
;  Indicates that an attempt was made to change the size of the LDT for a process that has no LDT.
;
STATUS_NO_LDT                    = 0C0000117h

;
; MessageId: STATUS_INVALID_LDT_SIZE
;
; MessageText:
;
;  Indicates that an attempt was made to grow an LDT by setting its size, or that the size was not an even number of selectors.
;
STATUS_INVALID_LDT_SIZE          = 0C0000118h

;
; MessageId: STATUS_INVALID_LDT_OFFSET
;
; MessageText:
;
;  Indicates that the starting value for the LDT information was not an integral multiple of the selector size.
;
STATUS_INVALID_LDT_OFFSET        = 0C0000119h

;
; MessageId: STATUS_INVALID_LDT_DESCRIPTOR
;
; MessageText:
;
;  Indicates that the user supplied an invalid descriptor when trying to set up Ldt descriptors.
;
STATUS_INVALID_LDT_DESCRIPTOR    = 0C000011Ah

;
; MessageId: STATUS_INVALID_IMAGE_NE_FORMAT
;
; MessageText:
;
;  The specified image file did not have the correct format. It appears to be NE format.
;
STATUS_INVALID_IMAGE_NE_FORMAT   = 0C000011Bh

;
; MessageId: STATUS_RXACT_INVALID_STATE
;
; MessageText:
;
;  Indicates that the transaction state of a registry sub-tree is incompatible with the requested operation.
;  For example, a request has been made to start a new transaction with one already in progress,
;  or a request has been made to apply a transaction when one is not currently in progress.
;
STATUS_RXACT_INVALID_STATE       = 0C000011Ch

;
; MessageId: STATUS_RXACT_COMMIT_FAILURE
;
; MessageText:
;
;  Indicates an error has occurred during a registry transaction commit.
;  The database has been left in an unknown, but probably inconsistent, state.
;  The state of the registry transaction is left as COMMITTING.
;
STATUS_RXACT_COMMIT_FAILURE      = 0C000011Dh

;
; MessageId: STATUS_MAPPED_FILE_SIZE_ZERO
;
; MessageText:
;
;  An attempt was made to map a file of size zero with the maximum size specified as zero.
;
STATUS_MAPPED_FILE_SIZE_ZERO     = 0C000011Eh

;
; MessageId: STATUS_TOO_MANY_OPENED_FILES
;
; MessageText:
;
;  Too many files are opened on a remote server.
;  This error should only be returned by the Windows redirector on a remote drive.
;
STATUS_TOO_MANY_OPENED_FILES     = 0C000011Fh

;
; MessageId: STATUS_CANCELLED
;
; MessageText:
;
;  The I/O request was canceled.
;
STATUS_CANCELLED                 = 0C0000120h

;
; MessageId: STATUS_CANNOT_DELETE
;
; MessageText:
;
;  An attempt has been made to remove a file or directory that cannot be deleted.
;
STATUS_CANNOT_DELETE             = 0C0000121h

;
; MessageId: STATUS_INVALID_COMPUTER_NAME
;
; MessageText:
;
;  Indicates a name specified as a remote computer name is syntactically invalid.
;
STATUS_INVALID_COMPUTER_NAME     = 0C0000122h

;
; MessageId: STATUS_FILE_DELETED
;
; MessageText:
;
;  An I/O request other than close was performed on a file after it has been deleted,
;  which can only happen to a request which did not complete before the last handle was closed via NtClose.
;
STATUS_FILE_DELETED              = 0C0000123h

;
; MessageId: STATUS_SPECIAL_ACCOUNT
;
; MessageText:
;
;  Indicates an operation has been attempted on a built-in (special) SAM account which is incompatible with built-in accounts.
;  For example, built-in accounts cannot be deleted.
;
STATUS_SPECIAL_ACCOUNT           = 0C0000124h

;
; MessageId: STATUS_SPECIAL_GROUP
;
; MessageText:
;
;  The operation requested may not be performed on the specified group because it is a built-in special group.
;
STATUS_SPECIAL_GROUP             = 0C0000125h

;
; MessageId: STATUS_SPECIAL_USER
;
; MessageText:
;
;  The operation requested may not be performed on the specified user because it is a built-in special user.
;
STATUS_SPECIAL_USER              = 0C0000126h

;
; MessageId: STATUS_MEMBERS_PRIMARY_GROUP
;
; MessageText:
;
;  Indicates a member cannot be removed from a group because the group is currently the member's primary group.
;
STATUS_MEMBERS_PRIMARY_GROUP     = 0C0000127h

;
; MessageId: STATUS_FILE_CLOSED
;
; MessageText:
;
;  An I/O request other than close and several other special case operations was attempted using a file object that had already been closed.
;
STATUS_FILE_CLOSED               = 0C0000128h

;
; MessageId: STATUS_TOO_MANY_THREADS
;
; MessageText:
;
;  Indicates a process has too many threads to perform the requested action. For example, assignment of a primary token may only be performed when a process has zero or one threads.
;
STATUS_TOO_MANY_THREADS          = 0C0000129h

;
; MessageId: STATUS_THREAD_NOT_IN_PROCESS
;
; MessageText:
;
;  An attempt was made to operate on a thread within a specific process, but the thread specified is not in the process specified.
;
STATUS_THREAD_NOT_IN_PROCESS     = 0C000012Ah

;
; MessageId: STATUS_TOKEN_ALREADY_IN_USE
;
; MessageText:
;
;  An attempt was made to establish a token for use as a primary token but the token is already in use. A token can only be the primary token of one process at a time.
;
STATUS_TOKEN_ALREADY_IN_USE      = 0C000012Bh

;
; MessageId: STATUS_PAGEFILE_QUOTA_EXCEEDED
;
; MessageText:
;
;  Page file quota was exceeded.
;
STATUS_PAGEFILE_QUOTA_EXCEEDED   = 0C000012Ch

;
; MessageId: STATUS_COMMITMENT_LIMIT
;
; MessageText:
;
;  {Out of Virtual Memory}
;  Your system is low on virtual memory. To ensure that Windows runs properly, increase the size of your virtual memory paging file. For more information, see Help.
;
STATUS_COMMITMENT_LIMIT          = 0C000012Dh

;
; MessageId: STATUS_INVALID_IMAGE_LE_FORMAT
;
; MessageText:
;
;  The specified image file did not have the correct format, it appears to be LE format.
;
STATUS_INVALID_IMAGE_LE_FORMAT   = 0C000012Eh

;
; MessageId: STATUS_INVALID_IMAGE_NOT_MZ
;
; MessageText:
;
;  The specified image file did not have the correct format, it did not have an initial MZ.
;
STATUS_INVALID_IMAGE_NOT_MZ      = 0C000012Fh

;
; MessageId: STATUS_INVALID_IMAGE_PROTECT
;
; MessageText:
;
;  The specified image file did not have the correct format, it did not have a proper e_lfarlc in the MZ header.
;
STATUS_INVALID_IMAGE_PROTECT     = 0C0000130h

;
; MessageId: STATUS_INVALID_IMAGE_WIN_16
;
; MessageText:
;
;  The specified image file did not have the correct format, it appears to be a 16-bit Windows image.
;
STATUS_INVALID_IMAGE_WIN_16      = 0C0000131h

;
; MessageId: STATUS_LOGON_SERVER_CONFLICT
;
; MessageText:
;
;  The Netlogon service cannot start because another Netlogon service running in the domain conflicts with the specified role.
;
STATUS_LOGON_SERVER_CONFLICT     = 0C0000132h

;
; MessageId: STATUS_TIME_DIFFERENCE_AT_DC
;
; MessageText:
;
;  The time at the Primary Domain Controller is different than the time at the Backup Domain Controller or member server by too large an amount.
;
STATUS_TIME_DIFFERENCE_AT_DC     = 0C0000133h

;
; MessageId: STATUS_SYNCHRONIZATION_REQUIRED
;
; MessageText:
;
;  The SAM database on a Windows Server is significantly out of synchronization with the copy on the Domain Controller. A complete synchronization is required.
;
STATUS_SYNCHRONIZATION_REQUIRED  = 0C0000134h

;
; MessageId: STATUS_DLL_NOT_FOUND
;
; MessageText:
;
;  {Unable To Locate DLL}
;  The dynamic link library %hs could not be found in the specified path %hs.
;
STATUS_DLL_NOT_FOUND             = 0C0000135h

;
; MessageId: STATUS_OPEN_FAILED
;
; MessageText:
;
;  The NtCreateFile API failed. This error should never be returned to an application, it is a place holder for the Windows Lan Manager Redirector to use in its internal error mapping routines.
;
STATUS_OPEN_FAILED               = 0C0000136h

;
; MessageId: STATUS_IO_PRIVILEGE_FAILED
;
; MessageText:
;
;  {Privilege Failed}
;  The I/O permissions for the process could not be changed.
;
STATUS_IO_PRIVILEGE_FAILED       = 0C0000137h

;
; MessageId: STATUS_ORDINAL_NOT_FOUND
;
; MessageText:
;
;  {Ordinal Not Found}
;  The ordinal %ld could not be located in the dynamic link library %hs.
;
STATUS_ORDINAL_NOT_FOUND         = 0C0000138h

;
; MessageId: STATUS_ENTRYPOINT_NOT_FOUND
;
; MessageText:
;
;  {Entry Point Not Found}
;  The procedure entry point %hs could not be located in the dynamic link library %hs.
;
STATUS_ENTRYPOINT_NOT_FOUND      = 0C0000139h

;
; MessageId: STATUS_CONTROL_C_EXIT
;
; MessageText:
;
;  {Application Exit by CTRL+C}
;  The application terminated as a result of a CTRL+C.
;
STATUS_CONTROL_C_EXIT            = 0C000013Ah    ; winnt

;
; MessageId: STATUS_LOCAL_DISCONNECT
;
; MessageText:
;
;  {Virtual Circuit Closed}
;  The network transport on your computer has closed a network connection. There may or may not be I/O requests outstanding.
;
STATUS_LOCAL_DISCONNECT          = 0C000013Bh

;
; MessageId: STATUS_REMOTE_DISCONNECT
;
; MessageText:
;
;  {Virtual Circuit Closed}
;  The network transport on a remote computer has closed a network connection. There may or may not be I/O requests outstanding.
;
STATUS_REMOTE_DISCONNECT         = 0C000013Ch

;
; MessageId: STATUS_REMOTE_RESOURCES
;
; MessageText:
;
;  {Insufficient Resources on Remote Computer}
;  The remote computer has insufficient resources to complete the network request. For instance, there may not be enough memory available on the remote computer to carry out the request at this time.
;
STATUS_REMOTE_RESOURCES          = 0C000013Dh

;
; MessageId: STATUS_LINK_FAILED
;
; MessageText:
;
;  {Virtual Circuit Closed}
;  An existing connection (virtual circuit) has been broken at the remote computer. There is probably something wrong with the network software protocol or the network hardware on the remote computer.
;
STATUS_LINK_FAILED               = 0C000013Eh

;
; MessageId: STATUS_LINK_TIMEOUT
;
; MessageText:
;
;  {Virtual Circuit Closed}
;  The network transport on your computer has closed a network connection because it had to wait too long for a response from the remote computer.
;
STATUS_LINK_TIMEOUT              = 0C000013Fh

;
; MessageId: STATUS_INVALID_CONNECTION
;
; MessageText:
;
;  The connection handle given to the transport was invalid.
;
STATUS_INVALID_CONNECTION        = 0C0000140h

;
; MessageId: STATUS_INVALID_ADDRESS
;
; MessageText:
;
;  The address handle given to the transport was invalid.
;
STATUS_INVALID_ADDRESS           = 0C0000141h

;
; MessageId: STATUS_DLL_INIT_FAILED
;
; MessageText:
;
;  {DLL Initialization Failed}
;  Initialization of the dynamic link library %hs failed. The process is terminating abnormally.
;
STATUS_DLL_INIT_FAILED           = 0C0000142h

;
; MessageId: STATUS_MISSING_SYSTEMFILE
;
; MessageText:
;
;  {Missing System File}
;  The required system file %hs is bad or missing.
;
STATUS_MISSING_SYSTEMFILE        = 0C0000143h

;
; MessageId: STATUS_UNHANDLED_EXCEPTION
;
; MessageText:
;
;  {Application Error}
;  The exception %s = %08lx) occurred in the application at location 0x%08lx.
;
STATUS_UNHANDLED_EXCEPTION       = 0C0000144h

;
; MessageId: STATUS_APP_INIT_FAILURE
;
; MessageText:
;
;  {Application Error}
;  The application failed to initialize properly = %lx). Click on OK to terminate the application.
;
STATUS_APP_INIT_FAILURE          = 0C0000145h

;
; MessageId: STATUS_PAGEFILE_CREATE_FAILED
;
; MessageText:
;
;  {Unable to Create Paging File}
;  The creation of the paging file %hs failed (%lx). The requested size was %ld.
;
STATUS_PAGEFILE_CREATE_FAILED    = 0C0000146h

;
; MessageId: STATUS_NO_PAGEFILE
;
; MessageText:
;
;  {No Paging File Specified}
;  No paging file was specified in the system configuration.
;
STATUS_NO_PAGEFILE               = 0C0000147h

;
; MessageId: STATUS_INVALID_LEVEL
;
; MessageText:
;
;  {Incorrect System Call Level}
;  An invalid level was passed into the specified system call.
;
STATUS_INVALID_LEVEL             = 0C0000148h

;
; MessageId: STATUS_WRONG_PASSWORD_CORE
;
; MessageText:
;
;  {Incorrect Password to LAN Manager Server}
;  You specified an incorrect password to a LAN Manager 2.x or MS-NET server.
;
STATUS_WRONG_PASSWORD_CORE       = 0C0000149h

;
; MessageId: STATUS_ILLEGAL_FLOAT_CONTEXT
;
; MessageText:
;
;  {EXCEPTION}
;  A real-mode application issued a floating-point instruction and floating-point hardware is not present.
;
STATUS_ILLEGAL_FLOAT_CONTEXT     = 0C000014Ah

;
; MessageId: STATUS_PIPE_BROKEN
;
; MessageText:
;
;  The pipe operation has failed because the other end of the pipe has been closed.
;
STATUS_PIPE_BROKEN               = 0C000014Bh

;
; MessageId: STATUS_REGISTRY_CORRUPT
;
; MessageText:
;
;  {The Registry Is Corrupt}
;  The structure of one of the files that contains Registry data is corrupt, or the image of the file in memory is corrupt, or the file could not be recovered because the alternate copy or log was absent or corrupt.
;
STATUS_REGISTRY_CORRUPT          = 0C000014Ch

;
; MessageId: STATUS_REGISTRY_IO_FAILED
;
; MessageText:
;
;  An I/O operation initiated by the Registry failed unrecoverably.
;  The Registry could not read in, or write out, or flush, one of the files that contain the system's image of the Registry.
;
STATUS_REGISTRY_IO_FAILED        = 0C000014Dh

;
; MessageId: STATUS_NO_EVENT_PAIR
;
; MessageText:
;
;  An event pair synchronization operation was performed using the thread specific client/server event pair object, but no event pair object was associated with the thread.
;
STATUS_NO_EVENT_PAIR             = 0C000014Eh

;
; MessageId: STATUS_UNRECOGNIZED_VOLUME
;
; MessageText:
;
;  The volume does not contain a recognized file system.
;  Please make sure that all required file system drivers are loaded and that the volume is not corrupt.
;
STATUS_UNRECOGNIZED_VOLUME       = 0C000014Fh

;
; MessageId: STATUS_SERIAL_NO_DEVICE_INITED
;
; MessageText:
;
;  No serial device was successfully initialized. The serial driver will unload.
;
STATUS_SERIAL_NO_DEVICE_INITED   = 0C0000150h

;
; MessageId: STATUS_NO_SUCH_ALIAS
;
; MessageText:
;
;  The specified local group does not exist.
;
STATUS_NO_SUCH_ALIAS             = 0C0000151h

;
; MessageId: STATUS_MEMBER_NOT_IN_ALIAS
;
; MessageText:
;
;  The specified account name is not a member of the local group.
;
STATUS_MEMBER_NOT_IN_ALIAS       = 0C0000152h

;
; MessageId: STATUS_MEMBER_IN_ALIAS
;
; MessageText:
;
;  The specified account name is already a member of the local group.
;
STATUS_MEMBER_IN_ALIAS           = 0C0000153h

;
; MessageId: STATUS_ALIAS_EXISTS
;
; MessageText:
;
;  The specified local group already exists.
;
STATUS_ALIAS_EXISTS              = 0C0000154h

;
; MessageId: STATUS_LOGON_NOT_GRANTED
;
; MessageText:
;
;  A requested type of logon (e.g., Interactive, Network, Service) is not granted by the target system's local security policy.
;  Please ask the system administrator to grant the necessary form of logon.
;
STATUS_LOGON_NOT_GRANTED         = 0C0000155h

;
; MessageId: STATUS_TOO_MANY_SECRETS
;
; MessageText:
;
;  The maximum number of secrets that may be stored in a single system has been exceeded. The length and number of secrets is limited to satisfy United States State Department export restrictions.
;
STATUS_TOO_MANY_SECRETS          = 0C0000156h

;
; MessageId: STATUS_SECRET_TOO_LONG
;
; MessageText:
;
;  The length of a secret exceeds the maximum length allowed. The length and number of secrets is limited to satisfy United States State Department export restrictions.
;
STATUS_SECRET_TOO_LONG           = 0C0000157h

;
; MessageId: STATUS_INTERNAL_DB_ERROR
;
; MessageText:
;
;  The Local Security Authority (LSA) database contains an internal inconsistency.
;
STATUS_INTERNAL_DB_ERROR         = 0C0000158h

;
; MessageId: STATUS_FULLSCREEN_MODE
;
; MessageText:
;
;  The requested operation cannot be performed in fullscreen mode.
;
STATUS_FULLSCREEN_MODE           = 0C0000159h

;
; MessageId: STATUS_TOO_MANY_CONTEXT_IDS
;
; MessageText:
;
;  During a logon attempt, the user's security context accumulated too many security IDs. This is a very unusual situation.
;  Remove the user from some global or local groups to reduce the number of security ids to incorporate into the security context.
;
STATUS_TOO_MANY_CONTEXT_IDS      = 0C000015Ah

;
; MessageId: STATUS_LOGON_TYPE_NOT_GRANTED
;
; MessageText:
;
;  A user has requested a type of logon (e.g., interactive or network) that has not been granted. An administrator has control over who may logon interactively and through the network.
;
STATUS_LOGON_TYPE_NOT_GRANTED    = 0C000015Bh

;
; MessageId: STATUS_NOT_REGISTRY_FILE
;
; MessageText:
;
;  The system has attempted to load or restore a file into the registry, and the specified file is not in the format of a registry file.
;
STATUS_NOT_REGISTRY_FILE         = 0C000015Ch

;
; MessageId: STATUS_NT_CROSS_ENCRYPTION_REQUIRED
;
; MessageText:
;
;  An attempt was made to change a user password in the security account manager without providing the necessary Windows cross-encrypted password.
;
STATUS_NT_CROSS_ENCRYPTION_REQUIRED = 0C000015Dh

;
; MessageId: STATUS_DOMAIN_CTRLR_CONFIG_ERROR
;
; MessageText:
;
;  A Windows Server has an incorrect configuration.
;
STATUS_DOMAIN_CTRLR_CONFIG_ERROR = 0C000015Eh

;
; MessageId: STATUS_FT_MISSING_MEMBER
;
; MessageText:
;
;  An attempt was made to explicitly access the secondary copy of information via a device control to the Fault Tolerance driver and the secondary copy is not present in the system.
;
STATUS_FT_MISSING_MEMBER         = 0C000015Fh

;
; MessageId: STATUS_ILL_FORMED_SERVICE_ENTRY
;
; MessageText:
;
;  A configuration registry node representing a driver service entry was ill-formed and did not contain required value entries.
;
STATUS_ILL_FORMED_SERVICE_ENTRY  = 0C0000160h

;
; MessageId: STATUS_ILLEGAL_CHARACTER
;
; MessageText:
;
;  An illegal character was encountered. For a multi-byte character set this includes a lead byte without a succeeding trail byte. For the Unicode character set this includes the characters 0xFFFF and 0xFFFE.
;
STATUS_ILLEGAL_CHARACTER         = 0C0000161h

;
; MessageId: STATUS_UNMAPPABLE_CHARACTER
;
; MessageText:
;
;  No mapping for the Unicode character exists in the target multi-byte code page.
;
STATUS_UNMAPPABLE_CHARACTER      = 0C0000162h

;
; MessageId: STATUS_UNDEFINED_CHARACTER
;
; MessageText:
;
;  The Unicode character is not defined in the Unicode character set installed on the system.
;
STATUS_UNDEFINED_CHARACTER       = 0C0000163h

;
; MessageId: STATUS_FLOPPY_VOLUME
;
; MessageText:
;
;  The paging file cannot be created on a floppy diskette.
;
STATUS_FLOPPY_VOLUME             = 0C0000164h

;
; MessageId: STATUS_FLOPPY_ID_MARK_NOT_FOUND
;
; MessageText:
;
;  {Floppy Disk Error}
;  While accessing a floppy disk, an ID address mark was not found.
;
STATUS_FLOPPY_ID_MARK_NOT_FOUND  = 0C0000165h

;
; MessageId: STATUS_FLOPPY_WRONG_CYLINDER
;
; MessageText:
;
;  {Floppy Disk Error}
;  While accessing a floppy disk, the track address from the sector ID field was found to be different than the track address maintained by the controller.
;
STATUS_FLOPPY_WRONG_CYLINDER     = 0C0000166h

;
; MessageId: STATUS_FLOPPY_UNKNOWN_ERROR
;
; MessageText:
;
;  {Floppy Disk Error}
;  The floppy disk controller reported an error that is not recognized by the floppy disk driver.
;
STATUS_FLOPPY_UNKNOWN_ERROR      = 0C0000167h

;
; MessageId: STATUS_FLOPPY_BAD_REGISTERS
;
; MessageText:
;
;  {Floppy Disk Error}
;  While accessing a floppy-disk, the controller returned inconsistent results via its registers.
;
STATUS_FLOPPY_BAD_REGISTERS      = 0C0000168h

;
; MessageId: STATUS_DISK_RECALIBRATE_FAILED
;
; MessageText:
;
;  {Hard Disk Error}
;  While accessing the hard disk, a recalibrate operation failed, even after retries.
;
STATUS_DISK_RECALIBRATE_FAILED   = 0C0000169h

;
; MessageId: STATUS_DISK_OPERATION_FAILED
;
; MessageText:
;
;  {Hard Disk Error}
;  While accessing the hard disk, a disk operation failed even after retries.
;
STATUS_DISK_OPERATION_FAILED     = 0C000016Ah

;
; MessageId: STATUS_DISK_RESET_FAILED
;
; MessageText:
;
;  {Hard Disk Error}
;  While accessing the hard disk, a disk controller reset was needed, but even that failed.
;
STATUS_DISK_RESET_FAILED         = 0C000016Bh

;
; MessageId: STATUS_SHARED_IRQ_BUSY
;
; MessageText:
;
;  An attempt was made to open a device that was sharing an IRQ with other devices.
;  At least one other device that uses that IRQ was already opened.
;  Two concurrent opens of devices that share an IRQ and only work via interrupts is not supported for the particular bus type that the devices use.
;
STATUS_SHARED_IRQ_BUSY           = 0C000016Ch

;
; MessageId: STATUS_FT_ORPHANING
;
; MessageText:
;
;  {FT Orphaning}
;  A disk that is part of a fault-tolerant volume can no longer be accessed.
;
STATUS_FT_ORPHANING              = 0C000016Dh

;
; MessageId: STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT
;
; MessageText:
;
;  The system bios failed to connect a system interrupt to the device or bus for
;  which the device is connected.
;
STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT = 0C000016Eh

;
; MessageId: STATUS_PARTITION_FAILURE
;
; MessageText:
;
;  Tape could not be partitioned.
;
STATUS_PARTITION_FAILURE         = 0C0000172h

;
; MessageId: STATUS_INVALID_BLOCK_LENGTH
;
; MessageText:
;
;  When accessing a new tape of a multivolume partition, the current blocksize is incorrect.
;
STATUS_INVALID_BLOCK_LENGTH      = 0C0000173h

;
; MessageId: STATUS_DEVICE_NOT_PARTITIONED
;
; MessageText:
;
;  Tape partition information could not be found when loading a tape.
;
STATUS_DEVICE_NOT_PARTITIONED    = 0C0000174h

;
; MessageId: STATUS_UNABLE_TO_LOCK_MEDIA
;
; MessageText:
;
;  Attempt to lock the eject media mechanism fails.
;
STATUS_UNABLE_TO_LOCK_MEDIA      = 0C0000175h

;
; MessageId: STATUS_UNABLE_TO_UNLOAD_MEDIA
;
; MessageText:
;
;  Unload media fails.
;
STATUS_UNABLE_TO_UNLOAD_MEDIA    = 0C0000176h

;
; MessageId: STATUS_EOM_OVERFLOW
;
; MessageText:
;
;  Physical end of tape was detected.
;
STATUS_EOM_OVERFLOW              = 0C0000177h

;
; MessageId: STATUS_NO_MEDIA
;
; MessageText:
;
;  {No Media}
;  There is no media in the drive.
;  Please insert media into drive %hs.
;
STATUS_NO_MEDIA                  = 0C0000178h

;
; MessageId: STATUS_NO_SUCH_MEMBER
;
; MessageText:
;
;  A member could not be added to or removed from the local group because the member does not exist.
;
STATUS_NO_SUCH_MEMBER            = 0C000017Ah

;
; MessageId: STATUS_INVALID_MEMBER
;
; MessageText:
;
;  A new member could not be added to a local group because the member has the wrong account type.
;
STATUS_INVALID_MEMBER            = 0C000017Bh

;
; MessageId: STATUS_KEY_DELETED
;
; MessageText:
;
;  Illegal operation attempted on a registry key which has been marked for deletion.
;
STATUS_KEY_DELETED               = 0C000017Ch

;
; MessageId: STATUS_NO_LOG_SPACE
;
; MessageText:
;
;  System could not allocate required space in a registry log.
;
STATUS_NO_LOG_SPACE              = 0C000017Dh

;
; MessageId: STATUS_TOO_MANY_SIDS
;
; MessageText:
;
;  Too many Sids have been specified.
;
STATUS_TOO_MANY_SIDS             = 0C000017Eh

;
; MessageId: STATUS_LM_CROSS_ENCRYPTION_REQUIRED
;
; MessageText:
;
;  An attempt was made to change a user password in the security account manager without providing the necessary LM cross-encrypted password.
;
STATUS_LM_CROSS_ENCRYPTION_REQUIRED = 0C000017Fh

;
; MessageId: STATUS_KEY_HAS_CHILDREN
;
; MessageText:
;
;  An attempt was made to create a symbolic link in a registry key that already has subkeys or values.
;
STATUS_KEY_HAS_CHILDREN          = 0C0000180h

;
; MessageId: STATUS_CHILD_MUST_BE_VOLATILE
;
; MessageText:
;
;  An attempt was made to create a Stable subkey under a Volatile parent key.
;
STATUS_CHILD_MUST_BE_VOLATILE    = 0C0000181h

;
; MessageId: STATUS_DEVICE_CONFIGURATION_ERROR
;
; MessageText:
;
; The I/O device is configured incorrectly or the configuration parameters to the driver are incorrect.

STATUS_DEVICE_CONFIGURATION_ERROR               = 00C0000182h

;
; MessageId: STATUS_DRIVER_INTERNAL_ERROR
;
; MessageText:
;
;  An error was detected between two drivers or within an I/O driver.
;
STATUS_DRIVER_INTERNAL_ERROR     = 0C0000183h

;
; MessageId: STATUS_INVALID_DEVICE_STATE
;
; MessageText:
;
;  The device is not in a valid state to perform this request.
;
STATUS_INVALID_DEVICE_STATE      = 0C0000184h

;
; MessageId: STATUS_IO_DEVICE_ERROR
;
; MessageText:
;
;  The I/O device reported an I/O error.
;
STATUS_IO_DEVICE_ERROR           = 0C0000185h

;
; MessageId: STATUS_DEVICE_PROTOCOL_ERROR
;
; MessageText:
;
;  A protocol error was detected between the driver and the device.
;
STATUS_DEVICE_PROTOCOL_ERROR     = 0C0000186h

;
; MessageId: STATUS_BACKUP_CONTROLLER
;
; MessageText:
;
;  This operation is only allowed for the Primary Domain Controller of the domain.
;
STATUS_BACKUP_CONTROLLER         = 0C0000187h

;
; MessageId: STATUS_LOG_FILE_FULL
;
; MessageText:
;
;  Log file space is insufficient to support this operation.
;
STATUS_LOG_FILE_FULL             = 0C0000188h

;
; MessageId: STATUS_TOO_LATE
;
; MessageText:
;
;  A write operation was attempted to a volume after it was dismounted.
;
STATUS_TOO_LATE                  = 0C0000189h

;
; MessageId: STATUS_NO_TRUST_LSA_SECRET
;
; MessageText:
;
;  The workstation does not have a trust secret for the primary domain in the local LSA database.
;
STATUS_NO_TRUST_LSA_SECRET       = 0C000018Ah

;
; MessageId: STATUS_NO_TRUST_SAM_ACCOUNT
;
; MessageText:
;
;  The SAM database on the Windows Server does not have a computer account for this workstation trust relationship.
;
STATUS_NO_TRUST_SAM_ACCOUNT      = 0C000018Bh

;
; MessageId: STATUS_TRUSTED_DOMAIN_FAILURE
;
; MessageText:
;
;  The logon request failed because the trust relationship between the primary domain and the trusted domain failed.
;
STATUS_TRUSTED_DOMAIN_FAILURE    = 0C000018Ch

;
; MessageId: STATUS_TRUSTED_RELATIONSHIP_FAILURE
;
; MessageText:
;
;  The logon request failed because the trust relationship between this workstation and the primary domain failed.
;
STATUS_TRUSTED_RELATIONSHIP_FAILURE = 0C000018Dh

;
; MessageId: STATUS_EVENTLOG_FILE_CORRUPT
;
; MessageText:
;
;  The Eventlog log file is corrupt.
;
STATUS_EVENTLOG_FILE_CORRUPT     = 0C000018Eh

;
; MessageId: STATUS_EVENTLOG_CANT_START
;
; MessageText:
;
;  No Eventlog log file could be opened. The Eventlog service did not start.
;
STATUS_EVENTLOG_CANT_START       = 0C000018Fh

;
; MessageId: STATUS_TRUST_FAILURE
;
; MessageText:
;
;  The network logon failed. This may be because the validation authority can't be reached.
;
STATUS_TRUST_FAILURE             = 0C0000190h

;
; MessageId: STATUS_MUTANT_LIMIT_EXCEEDED
;
; MessageText:
;
;  An attempt was made to acquire a mutant such that its maximum count would have been exceeded.
;
STATUS_MUTANT_LIMIT_EXCEEDED     = 0C0000191h

;
; MessageId: STATUS_NETLOGON_NOT_STARTED
;
; MessageText:
;
;  An attempt was made to logon, but the netlogon service was not started.
;
STATUS_NETLOGON_NOT_STARTED      = 0C0000192h

;
; MessageId: STATUS_ACCOUNT_EXPIRED
;
; MessageText:
;
;  The user's account has expired.
;
STATUS_ACCOUNT_EXPIRED           = 0C0000193h    ; ntsubauth

;
; MessageId: STATUS_POSSIBLE_DEADLOCK
;
; MessageText:
;
;  {EXCEPTION}
;  Possible deadlock condition.
;
STATUS_POSSIBLE_DEADLOCK         = 0C0000194h

;
; MessageId: STATUS_NETWORK_CREDENTIAL_CONFLICT
;
; MessageText:
;
;  The credentials supplied conflict with an existing set of credentials.
;
STATUS_NETWORK_CREDENTIAL_CONFLICT = 0C0000195h

;
; MessageId: STATUS_REMOTE_SESSION_LIMIT
;
; MessageText:
;
;  An attempt was made to establish a session to a network server, but there are already too many sessions established to that server.
;
STATUS_REMOTE_SESSION_LIMIT      = 0C0000196h

;
; MessageId: STATUS_EVENTLOG_FILE_CHANGED
;
; MessageText:
;
;  The log file has changed between reads.
;
STATUS_EVENTLOG_FILE_CHANGED     = 0C0000197h

;
; MessageId: STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT
;
; MessageText:
;
;  The account used is an Interdomain Trust account. Use your global user account or local user account to access this server.
;
STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT = 0C0000198h

;
; MessageId: STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT
;
; MessageText:
;
;  The account used is a Computer Account. Use your global user account or local user account to access this server.
;
STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT = 0C0000199h

;
; MessageId: STATUS_NOLOGON_SERVER_TRUST_ACCOUNT
;
; MessageText:
;
;  The account used is an Server Trust account. Use your global user account or local user account to access this server.
;
STATUS_NOLOGON_SERVER_TRUST_ACCOUNT = 0C000019Ah

;
; MessageId: STATUS_DOMAIN_TRUST_INCONSISTENT
;
; MessageText:
;
;  The name or SID of the domain specified is inconsistent with the trust information for that domain.
;
STATUS_DOMAIN_TRUST_INCONSISTENT = 0C000019Bh

;
; MessageId: STATUS_FS_DRIVER_REQUIRED
;
; MessageText:
;
;  A volume has been accessed for which a file system driver is required that has not yet been loaded.
;
STATUS_FS_DRIVER_REQUIRED        = 0C000019Ch

;
; MessageId: STATUS_NO_USER_SESSION_KEY
;
; MessageText:
;
;  There is no user session key for the specified logon session.
;
STATUS_NO_USER_SESSION_KEY       = 0C0000202h

;
; MessageId: STATUS_USER_SESSION_DELETED
;
; MessageText:
;
;  The remote user session has been deleted.
;
STATUS_USER_SESSION_DELETED      = 0C0000203h

;
; MessageId: STATUS_RESOURCE_LANG_NOT_FOUND
;
; MessageText:
;
;  Indicates the specified resource language ID cannot be found in the
;  image file.
;
STATUS_RESOURCE_LANG_NOT_FOUND   = 0C0000204h

;
; MessageId: STATUS_INSUFF_SERVER_RESOURCES
;
; MessageText:
;
;  Insufficient server resources exist to complete the request.
;
STATUS_INSUFF_SERVER_RESOURCES   = 0C0000205h

;
; MessageId: STATUS_INVALID_BUFFER_SIZE
;
; MessageText:
;
;  The size of the buffer is invalid for the specified operation.
;
STATUS_INVALID_BUFFER_SIZE       = 0C0000206h

;
; MessageId: STATUS_INVALID_ADDRESS_COMPONENT
;
; MessageText:
;
;  The transport rejected the network address specified as invalid.
;
STATUS_INVALID_ADDRESS_COMPONENT = 0C0000207h

;
; MessageId: STATUS_INVALID_ADDRESS_WILDCARD
;
; MessageText:
;
;  The transport rejected the network address specified due to an
;  invalid use of a wildcard.
;
STATUS_INVALID_ADDRESS_WILDCARD  = 0C0000208h

;
; MessageId: STATUS_TOO_MANY_ADDRESSES
;
; MessageText:
;
;  The transport address could not be opened because all the available
;  addresses are in use.
;
STATUS_TOO_MANY_ADDRESSES        = 0C0000209h

;
; MessageId: STATUS_ADDRESS_ALREADY_EXISTS
;
; MessageText:
;
;  The transport address could not be opened because it already exists.
;
STATUS_ADDRESS_ALREADY_EXISTS    = 0C000020Ah

;
; MessageId: STATUS_ADDRESS_CLOSED
;
; MessageText:
;
;  The transport address is now closed.
;
STATUS_ADDRESS_CLOSED            = 0C000020Bh

;
; MessageId: STATUS_CONNECTION_DISCONNECTED
;
; MessageText:
;
;  The transport connection is now disconnected.
;
STATUS_CONNECTION_DISCONNECTED   = 0C000020Ch

;
; MessageId: STATUS_CONNECTION_RESET
;
; MessageText:
;
;  The transport connection has been reset.
;
STATUS_CONNECTION_RESET          = 0C000020Dh

;
; MessageId: STATUS_TOO_MANY_NODES
;
; MessageText:
;
;  The transport cannot dynamically acquire any more nodes.
;
STATUS_TOO_MANY_NODES            = 0C000020Eh

;
; MessageId: STATUS_TRANSACTION_ABORTED
;
; MessageText:
;
;  The transport aborted a pending transaction.
;
STATUS_TRANSACTION_ABORTED       = 0C000020Fh

;
; MessageId: STATUS_TRANSACTION_TIMED_OUT
;
; MessageText:
;
;  The transport timed out a request waiting for a response.
;
STATUS_TRANSACTION_TIMED_OUT     = 0C0000210h

;
; MessageId: STATUS_TRANSACTION_NO_RELEASE
;
; MessageText:
;
;  The transport did not receive a release for a pending response.
;
STATUS_TRANSACTION_NO_RELEASE    = 0C0000211h

;
; MessageId: STATUS_TRANSACTION_NO_MATCH
;
; MessageText:
;
;  The transport did not find a transaction matching the specific
;  token.
;
STATUS_TRANSACTION_NO_MATCH      = 0C0000212h

;
; MessageId: STATUS_TRANSACTION_RESPONDED
;
; MessageText:
;
;  The transport had previously responded to a transaction request.
;
STATUS_TRANSACTION_RESPONDED     = 0C0000213h

;
; MessageId: STATUS_TRANSACTION_INVALID_ID
;
; MessageText:
;
;  The transport does not recognized the transaction request identifier specified.
;
STATUS_TRANSACTION_INVALID_ID    = 0C0000214h

;
; MessageId: STATUS_TRANSACTION_INVALID_TYPE
;
; MessageText:
;
;  The transport does not recognize the transaction request type specified.
;
STATUS_TRANSACTION_INVALID_TYPE  = 0C0000215h

;
; MessageId: STATUS_NOT_SERVER_SESSION
;
; MessageText:
;
;  The transport can only process the specified request on the server side of a session.
;
STATUS_NOT_SERVER_SESSION        = 0C0000216h

;
; MessageId: STATUS_NOT_CLIENT_SESSION
;
; MessageText:
;
;  The transport can only process the specified request on the client side of a session.
;
STATUS_NOT_CLIENT_SESSION        = 0C0000217h

;
; MessageId: STATUS_CANNOT_LOAD_REGISTRY_FILE
;
; MessageText:
;
;  {Registry File Failure}
;  The registry cannot load the hive (file):
;  %hs
;  or its log or alternate.
;  It is corrupt, absent, or not writable.
;
STATUS_CANNOT_LOAD_REGISTRY_FILE = 0C0000218h

;
; MessageId: STATUS_DEBUG_ATTACH_FAILED
;
; MessageText:
;
;  {Unexpected Failure in DebugActiveProcess}
;  An unexpected failure occurred while processing a DebugActiveProcess API request. You may choose OK to terminate the process, or Cancel to ignore the error.
;
STATUS_DEBUG_ATTACH_FAILED       = 0C0000219h

;
; MessageId: STATUS_SYSTEM_PROCESS_TERMINATED
;
; MessageText:
;
;  {Fatal System Error}
;  The %hs system process terminated unexpectedly
;  with a status of 0x%08x (0x%08x 0x%08x).
;  The system has been shut down.
;
STATUS_SYSTEM_PROCESS_TERMINATED = 0C000021Ah

;
; MessageId: STATUS_DATA_NOT_ACCEPTED
;
; MessageText:
;
;  {Data Not Accepted}
;  The TDI client could not handle the data received during an indication.
;
STATUS_DATA_NOT_ACCEPTED         = 0C000021Bh

;
; MessageId: STATUS_NO_BROWSER_SERVERS_FOUND
;
; MessageText:
;
;  {Unable to Retrieve Browser Server List}
;  The list of servers for this workgroup is not currently available.
;
STATUS_NO_BROWSER_SERVERS_FOUND  = 0C000021Ch

;
; MessageId: STATUS_VDM_HARD_ERROR
;
; MessageText:
;
;  NTVDM encountered a hard error.
;
STATUS_VDM_HARD_ERROR            = 0C000021Dh

;
; MessageId: STATUS_DRIVER_CANCEL_TIMEOUT
;
; MessageText:
;
;  {Cancel Timeout}
;  The driver %hs failed to complete a cancelled I/O request in the allotted time.
;
STATUS_DRIVER_CANCEL_TIMEOUT     = 0C000021Eh

;
; MessageId: STATUS_REPLY_MESSAGE_MISMATCH
;
; MessageText:
;
;  {Reply Message Mismatch}
;  An attempt was made to reply to an LPC message, but the thread specified by the client ID in the message was not waiting on that message.
;
STATUS_REPLY_MESSAGE_MISMATCH    = 0C000021Fh

;
; MessageId: STATUS_MAPPED_ALIGNMENT
;
; MessageText:
;
;  {Mapped View Alignment Incorrect}
;  An attempt was made to map a view of a file, but either the specified base address or the offset into the file were not aligned on the proper allocation granularity.
;
STATUS_MAPPED_ALIGNMENT          = 0C0000220h

;
; MessageId: STATUS_IMAGE_CHECKSUM_MISMATCH
;
; MessageText:
;
;  {Bad Image Checksum}
;  The image %hs is possibly corrupt. The header checksum does not match the computed checksum.
;
STATUS_IMAGE_CHECKSUM_MISMATCH   = 0C0000221h

;
; MessageId: STATUS_LOST_WRITEBEHIND_DATA
;
; MessageText:
;
;  {Delayed Write Failed}
;  Windows was unable to save all the data for the file %hs. The data has been lost.
;  This error may be caused by a failure of your computer hardware or network connection. Please try to save this file elsewhere.
;
STATUS_LOST_WRITEBEHIND_DATA     = 0C0000222h

;
; MessageId: STATUS_CLIENT_SERVER_PARAMETERS_INVALID
;
; MessageText:
;
;  The parameter(s) passed to the server in the client/server shared memory
;  window were invalid. Too much data may have been put in the shared memory window.
;
STATUS_CLIENT_SERVER_PARAMETERS_INVALID = 0C0000223h

;
; MessageId: STATUS_PASSWORD_MUST_CHANGE
;
; MessageText:
;
;  The user's password must be changed before logging on the first time.
;
STATUS_PASSWORD_MUST_CHANGE      = 0C0000224h    ; ntsubauth

;
; MessageId: STATUS_NOT_FOUND
;
; MessageText:
;
;  The object was not found.
;
STATUS_NOT_FOUND                 = 0C0000225h

;
; MessageId: STATUS_NOT_TINY_STREAM
;
; MessageText:
;
;  The stream is not a tiny stream.
;
STATUS_NOT_TINY_STREAM           = 0C0000226h

;
; MessageId: STATUS_RECOVERY_FAILURE
;
; MessageText:
;
;  A transaction recover failed.
;
STATUS_RECOVERY_FAILURE          = 0C0000227h

;
; MessageId: STATUS_STACK_OVERFLOW_READ
;
; MessageText:
;
;  The request must be handled by the stack overflow code.
;
STATUS_STACK_OVERFLOW_READ       = 0C0000228h

;
; MessageId: STATUS_FAIL_CHECK
;
; MessageText:
;
;  A consistency check failed.
;
STATUS_FAIL_CHECK                = 0C0000229h

;
; MessageId: STATUS_DUPLICATE_OBJECTID
;
; MessageText:
;
;  The attempt to insert the ID in the index failed because the ID is already in the index.
;
STATUS_DUPLICATE_OBJECTID        = 0C000022Ah

;
; MessageId: STATUS_OBJECTID_EXISTS
;
; MessageText:
;
;  The attempt to set the object's ID failed because the object already has an ID.
;
STATUS_OBJECTID_EXISTS           = 0C000022Bh

;
; MessageId: STATUS_CONVERT_TO_LARGE
;
; MessageText:
;
;  Internal OFS status codes indicating how an allocation operation is handled. Either it is retried after the containing onode is moved or the extent stream is converted to a large stream.
;
STATUS_CONVERT_TO_LARGE          = 0C000022Ch

;
; MessageId: STATUS_RETRY
;
; MessageText:
;
;  The request needs to be retried.
;
STATUS_RETRY                     = 0C000022Dh

;
; MessageId: STATUS_FOUND_OUT_OF_SCOPE
;
; MessageText:
;
;  The attempt to find the object found an object matching by ID on the volume but it is out of the scope of the handle used for the operation.
;
STATUS_FOUND_OUT_OF_SCOPE        = 0C000022Eh

;
; MessageId: STATUS_ALLOCATE_BUCKET
;
; MessageText:
;
;  The bucket array must be grown. Retry transaction after doing so.
;
STATUS_ALLOCATE_BUCKET           = 0C000022Fh

;
; MessageId: STATUS_PROPSET_NOT_FOUND
;
; MessageText:
;
;  The property set specified does not exist on the object.
;
STATUS_PROPSET_NOT_FOUND         = 0C0000230h

;
; MessageId: STATUS_MARSHALL_OVERFLOW
;
; MessageText:
;
;  The user/kernel marshalling buffer has overflowed.
;
STATUS_MARSHALL_OVERFLOW         = 0C0000231h

;
; MessageId: STATUS_INVALID_VARIANT
;
; MessageText:
;
;  The supplied variant structure contains invalid data.
;
STATUS_INVALID_VARIANT           = 0C0000232h

;
; MessageId: STATUS_DOMAIN_CONTROLLER_NOT_FOUND
;
; MessageText:
;
;  Could not find a domain controller for this domain.
;
STATUS_DOMAIN_CONTROLLER_NOT_FOUND = 0C0000233h

;
; MessageId: STATUS_ACCOUNT_LOCKED_OUT
;
; MessageText:
;
;  The user account has been automatically locked because too many invalid logon attempts or password change attempts have been requested.
;
STATUS_ACCOUNT_LOCKED_OUT        = 0C0000234h    ; ntsubauth

;
; MessageId: STATUS_HANDLE_NOT_CLOSABLE
;
; MessageText:
;
;  NtClose was called on a handle that was protected from close via NtSetInformationObject.
;
STATUS_HANDLE_NOT_CLOSABLE       = 0C0000235h

;
; MessageId: STATUS_CONNECTION_REFUSED
;
; MessageText:
;
;  The transport connection attempt was refused by the remote system.
;
STATUS_CONNECTION_REFUSED        = 0C0000236h

;
; MessageId: STATUS_GRACEFUL_DISCONNECT
;
; MessageText:
;
;  The transport connection was gracefully closed.
;
STATUS_GRACEFUL_DISCONNECT       = 0C0000237h

;
; MessageId: STATUS_ADDRESS_ALREADY_ASSOCIATED
;
; MessageText:
;
;  The transport endpoint already has an address associated with it.
;
STATUS_ADDRESS_ALREADY_ASSOCIATED = 0C0000238h

;
; MessageId: STATUS_ADDRESS_NOT_ASSOCIATED
;
; MessageText:
;
;  An address has not yet been associated with the transport endpoint.
;
STATUS_ADDRESS_NOT_ASSOCIATED    = 0C0000239h

;
; MessageId: STATUS_CONNECTION_INVALID
;
; MessageText:
;
;  An operation was attempted on a nonexistent transport connection.
;
STATUS_CONNECTION_INVALID        = 0C000023Ah

;
; MessageId: STATUS_CONNECTION_ACTIVE
;
; MessageText:
;
;  An invalid operation was attempted on an active transport connection.
;
STATUS_CONNECTION_ACTIVE         = 0C000023Bh

;
; MessageId: STATUS_NETWORK_UNREACHABLE
;
; MessageText:
;
;  The remote network is not reachable by the transport.
;
STATUS_NETWORK_UNREACHABLE       = 0C000023Ch

;
; MessageId: STATUS_HOST_UNREACHABLE
;
; MessageText:
;
;  The remote system is not reachable by the transport.
;
STATUS_HOST_UNREACHABLE          = 0C000023Dh

;
; MessageId: STATUS_PROTOCOL_UNREACHABLE
;
; MessageText:
;
;  The remote system does not support the transport protocol.
;
STATUS_PROTOCOL_UNREACHABLE      = 0C000023Eh

;
; MessageId: STATUS_PORT_UNREACHABLE
;
; MessageText:
;
;  No service is operating at the destination port of the transport on the remote system.
;
STATUS_PORT_UNREACHABLE          = 0C000023Fh

;
; MessageId: STATUS_REQUEST_ABORTED
;
; MessageText:
;
;  The request was aborted.
;
STATUS_REQUEST_ABORTED           = 0C0000240h

;
; MessageId: STATUS_CONNECTION_ABORTED
;
; MessageText:
;
;  The transport connection was aborted by the local system.
;
STATUS_CONNECTION_ABORTED        = 0C0000241h

;
; MessageId: STATUS_BAD_COMPRESSION_BUFFER
;
; MessageText:
;
;  The specified buffer contains ill-formed data.
;
STATUS_BAD_COMPRESSION_BUFFER    = 0C0000242h

;
; MessageId: STATUS_USER_MAPPED_FILE
;
; MessageText:
;
;  The requested operation cannot be performed on a file with a user mapped section open.
;
STATUS_USER_MAPPED_FILE          = 0C0000243h

;
; MessageId: STATUS_AUDIT_FAILED
;
; MessageText:
;
;  {Audit Failed}
;  An attempt to generate a security audit failed.
;
STATUS_AUDIT_FAILED              = 0C0000244h

;
; MessageId: STATUS_TIMER_RESOLUTION_NOT_SET
;
; MessageText:
;
;  The timer resolution was not previously set by the current process.
;
STATUS_TIMER_RESOLUTION_NOT_SET  = 0C0000245h

;
; MessageId: STATUS_CONNECTION_COUNT_LIMIT
;
; MessageText:
;
;  A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached.
;
STATUS_CONNECTION_COUNT_LIMIT    = 0C0000246h

;
; MessageId: STATUS_LOGIN_TIME_RESTRICTION
;
; MessageText:
;
;  Attempting to login during an unauthorized time of day for this account.
;
STATUS_LOGIN_TIME_RESTRICTION    = 0C0000247h

;
; MessageId: STATUS_LOGIN_WKSTA_RESTRICTION
;
; MessageText:
;
;  The account is not authorized to login from this station.
;
STATUS_LOGIN_WKSTA_RESTRICTION   = 0C0000248h

;
; MessageId: STATUS_IMAGE_MP_UP_MISMATCH
;
; MessageText:
;
;  {UP/MP Image Mismatch}
;  The image %hs has been modified for use on a uniprocessor system, but you are running it on a multiprocessor machine.
;  Please reinstall the image file.
;
STATUS_IMAGE_MP_UP_MISMATCH      = 0C0000249h

;
; MessageId: STATUS_INSUFFICIENT_LOGON_INFO
;
; MessageText:
;
;  There is insufficient account information to log you on.
;
STATUS_INSUFFICIENT_LOGON_INFO   = 0C0000250h

;
; MessageId: STATUS_BAD_DLL_ENTRYPOINT
;
; MessageText:
;
;  {Invalid DLL Entrypoint}
;  The dynamic link library %hs is not written correctly. The stack pointer has been left in an inconsistent state.
;  The entrypoint should be declared as WINAPI or STDCALL. Select YES to fail the DLL load. Select NO to continue
;  execution. Selecting NO may cause the application to operate incorrectly.
;
STATUS_BAD_DLL_ENTRYPOINT        = 0C0000251h

;
; MessageId: STATUS_BAD_SERVICE_ENTRYPOINT
;
; MessageText:
;
;  {Invalid Service Callback Entrypoint}
;  The %hs service is not written correctly. The stack pointer has been left in an inconsistent state.
;  The callback entrypoint should be declared as WINAPI or STDCALL. Selecting OK will cause the
;  service to continue operation. However, the service process may operate incorrectly.
;
STATUS_BAD_SERVICE_ENTRYPOINT    = 0C0000252h

;
; MessageId: STATUS_LPC_REPLY_LOST
;
; MessageText:
;
;  The server received the messages but did not send a reply.
;
STATUS_LPC_REPLY_LOST            = 0C0000253h

;
; MessageId: STATUS_IP_ADDRESS_CONFLICT1
;
; MessageText:
;
;  The system has detected an IP address conflict with another system on the network. The local interface has been disabled.
;  More details are available in the system event log.
;  Consult your network administrator to resolve the conflict.
;
STATUS_IP_ADDRESS_CONFLICT1      = 0C0000254h

;
; MessageId: STATUS_IP_ADDRESS_CONFLICT2
;
; MessageText:
;
;  The system has detected an IP address conflict with another system on the network. Network operations on this system may be disrupted as a result.
;  More details are available in the system event log.
;  Consult your network administrator immediately to resolve the conflict.
;
STATUS_IP_ADDRESS_CONFLICT2      = 0C0000255h

;
; MessageId: STATUS_REGISTRY_QUOTA_LIMIT
;
; MessageText:
;
;  {Low On Registry Space}
;  Your maximum registry size is too small. To ensure that Windows runs properly, increase your maximum registry size. For more information, see Help.
;
STATUS_REGISTRY_QUOTA_LIMIT      = 0C0000256h

;
; MessageId: STATUS_PATH_NOT_COVERED
;
; MessageText:
;
;  The contacted server does not support the indicated part of the DFS namespace.
;
STATUS_PATH_NOT_COVERED          = 0C0000257h

;
; MessageId: STATUS_NO_CALLBACK_ACTIVE
;
; MessageText:
;
;  A callback return system service cannot be executed when no callback is active.
;
STATUS_NO_CALLBACK_ACTIVE        = 0C0000258h

;
; MessageId: STATUS_LICENSE_QUOTA_EXCEEDED
;
; MessageText:
;
;  The service being accessed is licensed for a particular number of connections.
;  No more connections can be made to the service at this time because there are already as many connections as the service can accept.
;
STATUS_LICENSE_QUOTA_EXCEEDED    = 0C0000259h

;
; MessageId: STATUS_PWD_TOO_SHORT
;
; MessageText:
;
;  The password provided is too short to meet the policy of your user account.
;  Please choose a longer password.
;
STATUS_PWD_TOO_SHORT             = 0C000025Ah

;
; MessageId: STATUS_PWD_TOO_RECENT
;
; MessageText:
;
;  The policy of your user account does not allow you to change passwords too frequently.
;  This is done to prevent users from changing back to a familiar, but potentially discovered, password.
;  If you feel your password has been compromised then please contact your administrator immediately to have a new one assigned.
;
STATUS_PWD_TOO_RECENT            = 0C000025Bh

;
; MessageId: STATUS_PWD_HISTORY_CONFLICT
;
; MessageText:
;
;  You have attempted to change your password to one that you have used in the past.
;  The policy of your user account does not allow this. Please select a password that you have not previously used.
;
STATUS_PWD_HISTORY_CONFLICT      = 0C000025Ch

;
; MessageId: STATUS_PLUGPLAY_NO_DEVICE
;
; MessageText:
;
;  You have attempted to load a legacy device driver while its device instance had been disabled.
;
STATUS_PLUGPLAY_NO_DEVICE        = 0C000025Eh

;
; MessageId: STATUS_UNSUPPORTED_COMPRESSION
;
; MessageText:
;
;  The specified compression format is unsupported.
;
STATUS_UNSUPPORTED_COMPRESSION   = 0C000025Fh

;
; MessageId: STATUS_INVALID_HW_PROFILE
;
; MessageText:
;
;  The specified hardware profile configuration is invalid.
;
STATUS_INVALID_HW_PROFILE        = 0C0000260h

;
; MessageId: STATUS_INVALID_PLUGPLAY_DEVICE_PATH
;
; MessageText:
;
;  The specified Plug and Play registry device path is invalid.
;
STATUS_INVALID_PLUGPLAY_DEVICE_PATH = 0C0000261h

;
; MessageId: STATUS_DRIVER_ORDINAL_NOT_FOUND
;
; MessageText:
;
;  {Driver Entry Point Not Found}
;  The %hs device driver could not locate the ordinal %ld in driver %hs.
;
STATUS_DRIVER_ORDINAL_NOT_FOUND  = 0C0000262h

;
; MessageId: STATUS_DRIVER_ENTRYPOINT_NOT_FOUND
;
; MessageText:
;
;  {Driver Entry Point Not Found}
;  The %hs device driver could not locate the entry point %hs in driver %hs.
;
STATUS_DRIVER_ENTRYPOINT_NOT_FOUND = 0C0000263h

;
; MessageId: STATUS_RESOURCE_NOT_OWNED
;
; MessageText:
;
;  {Application Error}
;  The application attempted to release a resource it did not own. Click on OK to terminate the application.
;
STATUS_RESOURCE_NOT_OWNED        = 0C0000264h

;
; MessageId: STATUS_TOO_MANY_LINKS
;
; MessageText:
;
;  An attempt was made to create more links on a file than the file system supports.
;
STATUS_TOO_MANY_LINKS            = 0C0000265h

;
; MessageId: STATUS_QUOTA_LIST_INCONSISTENT
;
; MessageText:
;
;  The specified quota list is internally inconsistent with its descriptor.
;
STATUS_QUOTA_LIST_INCONSISTENT   = 0C0000266h

;
; MessageId: STATUS_FILE_IS_OFFLINE
;
; MessageText:
;
;  The specified file has been relocated to offline storage.
;
STATUS_FILE_IS_OFFLINE           = 0C0000267h

;
; MessageId: STATUS_EVALUATION_EXPIRATION
;
; MessageText:
;
;  {Windows Evaluation Notification}
;  The evaluation period for this installation of Windows has expired. This system will shutdown in 1 hour. To restore access to this installation of Windows, please upgrade this installation using a licensed distribution of this product.
;
STATUS_EVALUATION_EXPIRATION     = 0C0000268h

;
; MessageId: STATUS_ILLEGAL_DLL_RELOCATION
;
; MessageText:
;
;  {Illegal System DLL Relocation}
;  The system DLL %hs was relocated in memory. The application will not run properly.
;  The relocation occurred because the DLL %hs occupied an address range reserved for Windows system DLLs. The vendor supplying the DLL should be contacted for a new DLL.
;
STATUS_ILLEGAL_DLL_RELOCATION    = 0C0000269h

;
; MessageId: STATUS_LICENSE_VIOLATION
;
; MessageText:
;
;  {License Violation}
;  The system has detected tampering with your registered product type. This is a violation of your software license. Tampering with product type is not permitted.
;
STATUS_LICENSE_VIOLATION         = 0C000026Ah

;
; MessageId: STATUS_DLL_INIT_FAILED_LOGOFF
;
; MessageText:
;
;  {DLL Initialization Failed}
;  The application failed to initialize because the window station is shutting down.
;
STATUS_DLL_INIT_FAILED_LOGOFF    = 0C000026Bh

;
; MessageId: STATUS_DRIVER_UNABLE_TO_LOAD
;
; MessageText:
;
;  {Unable to Load Device Driver}
;  %hs device driver could not be loaded.
;  Error Status was 0x%x
;
STATUS_DRIVER_UNABLE_TO_LOAD     = 0C000026Ch

;
; MessageId: STATUS_DFS_UNAVAILABLE
;
; MessageText:
;
;  DFS is unavailable on the contacted server.
;
STATUS_DFS_UNAVAILABLE           = 0C000026Dh

;
; MessageId: STATUS_VOLUME_DISMOUNTED
;
; MessageText:
;
;  An operation was attempted to a volume after it was dismounted.
;
STATUS_VOLUME_DISMOUNTED         = 0C000026Eh

;
; MessageId: STATUS_WX86_INTERNAL_ERROR
;
; MessageText:
;
;  An internal error occurred in the Win32 x86 emulation subsystem.
;
STATUS_WX86_INTERNAL_ERROR       = 0C000026Fh

;
; MessageId: STATUS_WX86_FLOAT_STACK_CHECK
;
; MessageText:
;
;  Win32 x86 emulation subsystem Floating-point stack check.
;
STATUS_WX86_FLOAT_STACK_CHECK    = 0C0000270h

;
; MessageId: STATUS_VALIDATE_CONTINUE
;
; MessageText:
;
;  The validation process needs to continue on to the next step.
;
STATUS_VALIDATE_CONTINUE         = 0C0000271h

;
; MessageId: STATUS_NO_MATCH
;
; MessageText:
;
;  There was no match for the specified key in the index.
;
STATUS_NO_MATCH                  = 0C0000272h

;
; MessageId: STATUS_NO_MORE_MATCHES
;
; MessageText:
;
;  There are no more matches for the current index enumeration.
;
STATUS_NO_MORE_MATCHES           = 0C0000273h

;
; MessageId: STATUS_NOT_A_REPARSE_POINT
;
; MessageText:
;
;  The NTFS file or directory is not a reparse point.
;
STATUS_NOT_A_REPARSE_POINT       = 0C0000275h

;
; MessageId: STATUS_IO_REPARSE_TAG_INVALID
;
; MessageText:
;
;  The Windows I/O reparse tag passed for the NTFS reparse point is invalid.
;
STATUS_IO_REPARSE_TAG_INVALID    = 0C0000276h

;
; MessageId: STATUS_IO_REPARSE_TAG_MISMATCH
;
; MessageText:
;
;  The Windows I/O reparse tag does not match the one present in the NTFS reparse point.
;
STATUS_IO_REPARSE_TAG_MISMATCH   = 0C0000277h

;
; MessageId: STATUS_IO_REPARSE_DATA_INVALID
;
; MessageText:
;
;  The user data passed for the NTFS reparse point is invalid.
;
STATUS_IO_REPARSE_DATA_INVALID   = 0C0000278h

;
; MessageId: STATUS_IO_REPARSE_TAG_NOT_HANDLED
;
; MessageText:
;
;  The layered file system driver for this IO tag did not handle it when needed.
;
STATUS_IO_REPARSE_TAG_NOT_HANDLED = 0C0000279h

;
; MessageId: STATUS_REPARSE_POINT_NOT_RESOLVED
;
; MessageText:
;
;  The NTFS symbolic link could not be resolved even though the initial file name is valid.
;
STATUS_REPARSE_POINT_NOT_RESOLVED = 0C0000280h

;
; MessageId: STATUS_DIRECTORY_IS_A_REPARSE_POINT
;
; MessageText:
;
;  The NTFS directory is a reparse point.
;
STATUS_DIRECTORY_IS_A_REPARSE_POINT = 0C0000281h

;
; MessageId: STATUS_RANGE_LIST_CONFLICT
;
; MessageText:
;
;  The range could not be added to the range list because of a conflict.
;
STATUS_RANGE_LIST_CONFLICT       = 0C0000282h

;
; MessageId: STATUS_SOURCE_ELEMENT_EMPTY
;
; MessageText:
;
;  The specified medium changer source element contains no media.
;
STATUS_SOURCE_ELEMENT_EMPTY      = 0C0000283h

;
; MessageId: STATUS_DESTINATION_ELEMENT_FULL
;
; MessageText:
;
;  The specified medium changer destination element already contains media.
;
STATUS_DESTINATION_ELEMENT_FULL  = 0C0000284h

;
; MessageId: STATUS_ILLEGAL_ELEMENT_ADDRESS
;
; MessageText:
;
;  The specified medium changer element does not exist.
;
STATUS_ILLEGAL_ELEMENT_ADDRESS   = 0C0000285h

;
; MessageId: STATUS_MAGAZINE_NOT_PRESENT
;
; MessageText:
;
;  The specified element is contained within a magazine that is no longer present.
;
STATUS_MAGAZINE_NOT_PRESENT      = 0C0000286h

;
; MessageId: STATUS_REINITIALIZATION_NEEDED
;
; MessageText:
;
;  The device requires reinitialization due to hardware errors.
;
STATUS_REINITIALIZATION_NEEDED   = 0C0000287h

;
; MessageId: STATUS_DEVICE_REQUIRES_CLEANING
;
; MessageText:
;
;  The device has indicated that cleaning is necessary.
;
STATUS_DEVICE_REQUIRES_CLEANING  = 80000288h

;
; MessageId: STATUS_DEVICE_DOOR_OPEN
;
; MessageText:
;
;  The device has indicated that it's door is open. Further operations require it closed and secured.
;
STATUS_DEVICE_DOOR_OPEN          = 80000289h

;
; MessageId: STATUS_ENCRYPTION_FAILED
;
; MessageText:
;
;  The file encryption attempt failed.
;
STATUS_ENCRYPTION_FAILED         = 0C000028Ah

;
; MessageId: STATUS_DECRYPTION_FAILED
;
; MessageText:
;
;  The file decryption attempt failed.
;
STATUS_DECRYPTION_FAILED         = 0C000028Bh

;
; MessageId: STATUS_RANGE_NOT_FOUND
;
; MessageText:
;
;  The specified range could not be found in the range list.
;
STATUS_RANGE_NOT_FOUND           = 0C000028Ch

;
; MessageId: STATUS_NO_RECOVERY_POLICY
;
; MessageText:
;
;  There is no encryption recovery policy configured for this system.
;
STATUS_NO_RECOVERY_POLICY        = 0C000028Dh

;
; MessageId: STATUS_NO_EFS
;
; MessageText:
;
;  The required encryption driver is not loaded for this system.
;
STATUS_NO_EFS                    = 0C000028Eh

;
; MessageId: STATUS_WRONG_EFS
;
; MessageText:
;
;  The file was encrypted with a different encryption driver than is currently loaded.
;
STATUS_WRONG_EFS                 = 0C000028Fh

;
; MessageId: STATUS_NO_USER_KEYS
;
; MessageText:
;
;  There are no EFS keys defined for the user.
;
STATUS_NO_USER_KEYS              = 0C0000290h

;
; MessageId: STATUS_FILE_NOT_ENCRYPTED
;
; MessageText:
;
;  The specified file is not encrypted.
;
STATUS_FILE_NOT_ENCRYPTED        = 0C0000291h

;
; MessageId: STATUS_NOT_EXPORT_FORMAT
;
; MessageText:
;
;  The specified file is not in the defined EFS export format.
;
STATUS_NOT_EXPORT_FORMAT         = 0C0000292h

;
; MessageId: STATUS_FILE_ENCRYPTED
;
; MessageText:
;
;  The specified file is encrypted and the user does not have the ability to decrypt it.
;
STATUS_FILE_ENCRYPTED            = 0C0000293h

;
; MessageId: STATUS_WAKE_SYSTEM
;
; MessageText:
;
;  The system has awoken
;
STATUS_WAKE_SYSTEM               = 40000294h

;
; MessageId: STATUS_WMI_GUID_NOT_FOUND
;
; MessageText:
;
;  The guid passed was not recognized as valid by a WMI data provider.
;
STATUS_WMI_GUID_NOT_FOUND        = 0C0000295h

;
; MessageId: STATUS_WMI_INSTANCE_NOT_FOUND
;
; MessageText:
;
;  The instance name passed was not recognized as valid by a WMI data provider.
;
STATUS_WMI_INSTANCE_NOT_FOUND    = 0C0000296h

;
; MessageId: STATUS_WMI_ITEMID_NOT_FOUND
;
; MessageText:
;
;  The data item id passed was not recognized as valid by a WMI data provider.
;
STATUS_WMI_ITEMID_NOT_FOUND      = 0C0000297h

;
; MessageId: STATUS_WMI_TRY_AGAIN
;
; MessageText:
;
;  The WMI request could not be completed and should be retried.
;
STATUS_WMI_TRY_AGAIN             = 0C0000298h

;
; MessageId: STATUS_SHARED_POLICY
;
; MessageText:
;
;  The policy object is shared and can only be modified at the root
;
STATUS_SHARED_POLICY             = 0C0000299h

;
; MessageId: STATUS_POLICY_OBJECT_NOT_FOUND
;
; MessageText:
;
;  The policy object does not exist when it should
;
STATUS_POLICY_OBJECT_NOT_FOUND   = 0C000029Ah

;
; MessageId: STATUS_POLICY_ONLY_IN_DS
;
; MessageText:
;
;  The requested policy information only lives in the Ds
;
STATUS_POLICY_ONLY_IN_DS         = 0C000029Bh

;
; MessageId: STATUS_VOLUME_NOT_UPGRADED
;
; MessageText:
;
;  The volume must be upgraded to enable this feature
;
STATUS_VOLUME_NOT_UPGRADED       = 0C000029Ch

;
; MessageId: STATUS_REMOTE_STORAGE_NOT_ACTIVE
;
; MessageText:
;
;  The remote storage service is not operational at this time.
;
STATUS_REMOTE_STORAGE_NOT_ACTIVE = 0C000029Dh

;
; MessageId: STATUS_REMOTE_STORAGE_MEDIA_ERROR
;
; MessageText:
;
;  The remote storage service encountered a media error.
;
STATUS_REMOTE_STORAGE_MEDIA_ERROR = 0C000029Eh

;
; MessageId: STATUS_NO_TRACKING_SERVICE
;
; MessageText:
;
;  The tracking (workstation) service is not running.
;
STATUS_NO_TRACKING_SERVICE       = 0C000029Fh

;
; MessageId: STATUS_SERVER_SID_MISMATCH
;
; MessageText:
;
;  The server process is running under a SID different than that required by client.
;
STATUS_SERVER_SID_MISMATCH       = 0C00002A0h

;
; Directory Service specific Errors
;
;
; MessageId: STATUS_DS_NO_ATTRIBUTE_OR_VALUE
;
; MessageText:
;
;  The specified directory service attribute or value does not exist.
;
STATUS_DS_NO_ATTRIBUTE_OR_VALUE  = 0C00002A1h

;
; MessageId: STATUS_DS_INVALID_ATTRIBUTE_SYNTAX
;
; MessageText:
;
;  The attribute syntax specified to the directory service is invalid.
;
STATUS_DS_INVALID_ATTRIBUTE_SYNTAX = 0C00002A2h

;
; MessageId: STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED
;
; MessageText:
;
;  The attribute type specified to the directory service is not defined.
;
STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED = 0C00002A3h

;
; MessageId: STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS
;
; MessageText:
;
;  The specified directory service attribute or value already exists.
;
STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS = 0C00002A4h

;
; MessageId: STATUS_DS_BUSY
;
; MessageText:
;
;  The directory service is busy.
;
STATUS_DS_BUSY                   = 0C00002A5h

;
; MessageId: STATUS_DS_UNAVAILABLE
;
; MessageText:
;
;  The directory service is not available.
;
STATUS_DS_UNAVAILABLE            = 0C00002A6h

;
; MessageId: STATUS_DS_NO_RIDS_ALLOCATED
;
; MessageText:
;
;  The directory service was unable to allocate a relative identifier.
;
STATUS_DS_NO_RIDS_ALLOCATED      = 0C00002A7h

;
; MessageId: STATUS_DS_NO_MORE_RIDS
;
; MessageText:
;
;  The directory service has exhausted the pool of relative identifiers.
;
STATUS_DS_NO_MORE_RIDS           = 0C00002A8h

;
; MessageId: STATUS_DS_INCORRECT_ROLE_OWNER
;
; MessageText:
;
;  The requested operation could not be performed because the directory service is not the master for that type of operation.
;
STATUS_DS_INCORRECT_ROLE_OWNER   = 0C00002A9h

;
; MessageId: STATUS_DS_RIDMGR_INIT_ERROR
;
; MessageText:
;
;  The directory service was unable to initialize the subsystem that allocates relative identifiers.
;
STATUS_DS_RIDMGR_INIT_ERROR      = 0C00002AAh

;
; MessageId: STATUS_DS_OBJ_CLASS_VIOLATION
;
; MessageText:
;
;  The requested operation did not satisfy one or more constraints associated with the class of the object.
;
STATUS_DS_OBJ_CLASS_VIOLATION    = 0C00002ABh

;
; MessageId: STATUS_DS_CANT_ON_NON_LEAF
;
; MessageText:
;
;  The directory service can perform the requested operation only on a leaf object.
;
STATUS_DS_CANT_ON_NON_LEAF       = 0C00002ACh

;
; MessageId: STATUS_DS_CANT_ON_RDN
;
; MessageText:
;
;  The directory service cannot perform the requested operation on the Relatively Defined Name (RDN) attribute of an object.
;
STATUS_DS_CANT_ON_RDN            = 0C00002ADh

;
; MessageId: STATUS_DS_CANT_MOD_OBJ_CLASS
;
; MessageText:
;
;  The directory service detected an attempt to modify the object class of an object.
;
STATUS_DS_CANT_MOD_OBJ_CLASS     = 0C00002AEh

;
; MessageId: STATUS_DS_CROSS_DOM_MOVE_FAILED
;
; MessageText:
;
;  An error occurred while performing a cross domain move operation.
;
STATUS_DS_CROSS_DOM_MOVE_FAILED  = 0C00002AFh

;
; MessageId: STATUS_DS_GC_NOT_AVAILABLE
;
; MessageText:
;
;  Unable to Contact the Global Catalog Server.
;
STATUS_DS_GC_NOT_AVAILABLE       = 0C00002B0h

;
; MessageId: STATUS_DIRECTORY_SERVICE_REQUIRED
;
; MessageText:
;
;  The requested operation requires a directory service, and none was available.
;
STATUS_DIRECTORY_SERVICE_REQUIRED = 0C00002B1h

;
; MessageId: STATUS_REPARSE_ATTRIBUTE_CONFLICT
;
; MessageText:
;
;  The reparse attribute cannot be set as it is incompatible with an existing attribute.
;
STATUS_REPARSE_ATTRIBUTE_CONFLICT = 0C00002B2h

;
; MessageId: STATUS_CANT_ENABLE_DENY_ONLY
;
; MessageText:
;
;  A group marked use for deny only  can not be enabled.
;
STATUS_CANT_ENABLE_DENY_ONLY     = 0C00002B3h

;
; MessageId: STATUS_FLOAT_MULTIPLE_FAULTS
;
; MessageText:
;
;  {EXCEPTION}
;  Multiple floating point faults.
;
STATUS_FLOAT_MULTIPLE_FAULTS     = 0C00002B4h    ; winnt

;
; MessageId: STATUS_FLOAT_MULTIPLE_TRAPS
;
; MessageText:
;
;  {EXCEPTION}
;  Multiple floating point traps.
;
STATUS_FLOAT_MULTIPLE_TRAPS      = 0C00002B5h    ; winnt

;
; MessageId: STATUS_DEVICE_REMOVED
;
; MessageText:
;
;  The device has been removed.
;
STATUS_DEVICE_REMOVED            = 0C00002B6h

;
; MessageId: STATUS_JOURNAL_DELETE_IN_PROGRESS
;
; MessageText:
;
;  The volume change journal is being deleted.
;
STATUS_JOURNAL_DELETE_IN_PROGRESS = 0C00002B7h

;
; MessageId: STATUS_JOURNAL_NOT_ACTIVE
;
; MessageText:
;
;  The volume change journal service is not active.
;
STATUS_JOURNAL_NOT_ACTIVE        = 0C00002B8h

;
; MessageId: STATUS_NOINTERFACE
;
; MessageText:
;
;  The requested interface is not supported.
;
STATUS_NOINTERFACE               = 0C00002B9h

;
; MessageId: STATUS_DS_ADMIN_LIMIT_EXCEEDED
;
; MessageText:
;
;  A directory service resource limit has been exceeded.
;
STATUS_DS_ADMIN_LIMIT_EXCEEDED   = 0C00002C1h

;
; MessageId: STATUS_DRIVER_FAILED_SLEEP
;
; MessageText:
;
;  {System Standby Failed}
;  The driver %hs does not support standby mode. Updating this
;  driver may allow the system to go to standby mode.
;
STATUS_DRIVER_FAILED_SLEEP       = 0C00002C2h

;
; MessageId: STATUS_MUTUAL_AUTHENTICATION_FAILED
;
; MessageText:
;
;  Mutual Authentication failed. The server's password is out of date at the domain controller.
;
STATUS_MUTUAL_AUTHENTICATION_FAILED = 0C00002C3h

;
; MessageId: STATUS_CORRUPT_SYSTEM_FILE
;
; MessageText:
;
;  The system file %1 has become corrupt and has been replaced.
;
STATUS_CORRUPT_SYSTEM_FILE       = 0C00002C4h

;
; MessageId: STATUS_DATATYPE_MISALIGNMENT_ERROR
;
; MessageText:
;
;  {EXCEPTION}
;  Alignment Error
;  A datatype misalignment error was detected in a load or store instruction.
;
STATUS_DATATYPE_MISALIGNMENT_ERROR = 0C00002C5h

;
; MessageId: STATUS_WMI_READ_ONLY
;
; MessageText:
;
;  The WMI data item or data block is read only.
;
STATUS_WMI_READ_ONLY             = 0C00002C6h

;
; MessageId: STATUS_WMI_SET_FAILURE
;
; MessageText:
;
;  The WMI data item or data block could not be changed.
;
STATUS_WMI_SET_FAILURE           = 0C00002C7h

;
; MessageId: STATUS_COMMITMENT_MINIMUM
;
; MessageText:
;
;  {Virtual Memory Minimum Too Low}
;  Your system is low on virtual memory. Windows is increasing the size of your virtual memory paging file.
;  During this process, memory requests for some applications may be denied. For more information, see Help.
;
STATUS_COMMITMENT_MINIMUM        = 0C00002C8h

;
; MessageId: STATUS_REG_NAT_CONSUMPTION
;
; MessageText:
;
;  {EXCEPTION}
;  Register NaT consumption faults.
;  A NaT value is consumed on a non speculative instruction.
;
STATUS_REG_NAT_CONSUMPTION       = 0C00002C9h    ; winnt

;
; MessageId: STATUS_TRANSPORT_FULL
;
; MessageText:
;
;  The medium changer's transport element contains media, which is causing the operation to fail.
;
STATUS_TRANSPORT_FULL            = 0C00002CAh

;
; MessageId: STATUS_DS_SAM_INIT_FAILURE
;
; MessageText:
;
;  Security Accounts Manager initialization failed because of the following error:
;  %hs
;  Error Status: 0x%x.
;  Please click OK to shutdown this system and reboot into Directory Services Restore Mode, check the event log for more detailed information.
;
STATUS_DS_SAM_INIT_FAILURE       = 0C00002CBh

;
; MessageId: STATUS_ONLY_IF_CONNECTED
;
; MessageText:
;
;  This operation is supported only when you are connected to the server.
;
STATUS_ONLY_IF_CONNECTED         = 0C00002CCh

;
; MessageId: STATUS_DS_SENSITIVE_GROUP_VIOLATION
;
; MessageText:
;
;  Only an administrator can modify the membership list of an administrative group.
;
STATUS_DS_SENSITIVE_GROUP_VIOLATION = 0C00002CDh

;
; MessageId: STATUS_PNP_RESTART_ENUMERATION
;
; MessageText:
;
;  A device was removed so enumeration must be restarted.
;
STATUS_PNP_RESTART_ENUMERATION   = 0C00002CEh

;
; MessageId: STATUS_JOURNAL_ENTRY_DELETED
;
; MessageText:
;
;  The journal entry has been deleted from the journal.
;
STATUS_JOURNAL_ENTRY_DELETED     = 0C00002CFh

;
; MessageId: STATUS_DS_CANT_MOD_PRIMARYGROUPID
;
; MessageText:
;
;  Cannot change the primary group ID of a domain controller account.
;
STATUS_DS_CANT_MOD_PRIMARYGROUPID = 0C00002D0h

;
; MessageId: STATUS_SYSTEM_IMAGE_BAD_SIGNATURE
;
; MessageText:
;
;  {Fatal System Error}
;  The system image %s is not properly signed.
;  The file has been replaced with the signed file.
;  The system has been shut down.
;
STATUS_SYSTEM_IMAGE_BAD_SIGNATURE = 0C00002D1h

;
; MessageId: STATUS_PNP_REBOOT_REQUIRED
;
; MessageText:
;
;  Device will not start without a reboot.
;
STATUS_PNP_REBOOT_REQUIRED       = 0C00002D2h

;
; MessageId: STATUS_POWER_STATE_INVALID
;
; MessageText:
;
;  Current device power state cannot support this request.
;
STATUS_POWER_STATE_INVALID       = 0C00002D3h

;
; MessageId: STATUS_DS_INVALID_GROUP_TYPE
;
; MessageText:
;
;  The specified group type is invalid.
;
STATUS_DS_INVALID_GROUP_TYPE     = 0C00002D4h

;
; MessageId: STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN
;
; MessageText:
;
;  In mixed domain no nesting of global group if group is security enabled.
;
STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN = 0C00002D5h

;
; MessageId: STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN
;
; MessageText:
;
;  In mixed domain, cannot nest local groups with other local groups, if the group is security enabled.
;
STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN = 0C00002D6h

;
; MessageId: STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER
;
; MessageText:
;
;  A global group cannot have a local group as a member.
;
STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER = 0C00002D7h

;
; MessageId: STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER
;
; MessageText:
;
;  A global group cannot have a universal group as a member.
;
STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER = 0C00002D8h

;
; MessageId: STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER
;
; MessageText:
;
;  A universal group cannot have a local group as a member.
;
STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER = 0C00002D9h

;
; MessageId: STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER
;
; MessageText:
;
;  A global group cannot have a cross domain member.
;
STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER = 0C00002DAh

;
; MessageId: STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER
;
; MessageText:
;
;  A local group cannot have another cross domain local group as a member.
;
STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER = 0C00002DBh

;
; MessageId: STATUS_DS_HAVE_PRIMARY_MEMBERS
;
; MessageText:
;
;  Can not change to security disabled group because of having primary members in this group.
;
STATUS_DS_HAVE_PRIMARY_MEMBERS   = 0C00002DCh

;
; MessageId: STATUS_WMI_NOT_SUPPORTED
;
; MessageText:
;
;  The WMI operation is not supported by the data block or method.
;
STATUS_WMI_NOT_SUPPORTED         = 0C00002DDh

;
; MessageId: STATUS_INSUFFICIENT_POWER
;
; MessageText:
;
;  There is not enough power to complete the requested operation.
;
STATUS_INSUFFICIENT_POWER        = 0C00002DEh

;
; MessageId: STATUS_SAM_NEED_BOOTKEY_PASSWORD
;
; MessageText:
;
;  Security Account Manager needs to get the boot password.
;
STATUS_SAM_NEED_BOOTKEY_PASSWORD = 0C00002DFh

;
; MessageId: STATUS_SAM_NEED_BOOTKEY_FLOPPY
;
; MessageText:
;
;  Security Account Manager needs to get the boot key from floppy disk.
;
STATUS_SAM_NEED_BOOTKEY_FLOPPY   = 0C00002E0h

;
; MessageId: STATUS_DS_CANT_START
;
; MessageText:
;
;  Directory Service can not start.
;
STATUS_DS_CANT_START             = 0C00002E1h

;
; MessageId: STATUS_DS_INIT_FAILURE
;
; MessageText:
;
;  Directory Services could not start because of the following error:
;  %hs
;  Error Status: 0x%x.
;  Please click OK to shutdown this system and reboot into Directory Services Restore Mode, check the event log for more detailed information.
;
STATUS_DS_INIT_FAILURE           = 0C00002E2h

;
; MessageId: STATUS_SAM_INIT_FAILURE
;
; MessageText:
;
;  Security Accounts Manager initialization failed because of the following error:
;  %hs
;  Error Status: 0x%x.
;  Please click OK to shutdown this system and reboot into Safe Mode, check the event log for more detailed information.
;
STATUS_SAM_INIT_FAILURE          = 0C00002E3h

;
; MessageId: STATUS_DS_GC_REQUIRED
;
; MessageText:
;
;  The requested operation can be performed only on a global catalog server.
;
STATUS_DS_GC_REQUIRED            = 0C00002E4h

;
; MessageId: STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY
;
; MessageText:
;
;  A local group can only be a member of other local groups in the same domain.
;
STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY = 0C00002E5h

;
; MessageId: STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS
;
; MessageText:
;
;  Foreign security principals cannot be members of universal groups.
;
STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS = 0C00002E6h

;
; MessageId: STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED
;
; MessageText:
;
;  Your computer could not be joined to the domain. You have exceeded the maximum number of computer accounts you are allowed to create in this domain. Contact your system administrator to have this limit reset or increased.
;
STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED = 0C00002E7h

;
; MessageId: STATUS_MULTIPLE_FAULT_VIOLATION
;
; MessageText:
;
;  STATUS_MULTIPLE_FAULT_VIOLATION
;
STATUS_MULTIPLE_FAULT_VIOLATION  = 0C00002E8h

;
; MessageId: STATUS_NOT_SUPPORTED_ON_SBS
;
; MessageText:
;
;  This operation is not supported on a Microsoft Small Business Server
;
STATUS_NOT_SUPPORTED_ON_SBS      = 0C0000300h

;
; MessageId: STATUS_WOW_ASSERTION
;
; MessageText:
;
;  WOW Assertion Error.
;
STATUS_WOW_ASSERTION             = 0C0009898h

;
; MessageId: DBG_NO_STATE_CHANGE
;
; MessageText:
;
;  Debugger did not perform a state change.
;
DBG_NO_STATE_CHANGE              = 0C0010001h

;
; MessageId: DBG_APP_NOT_IDLE
;
; MessageText:
;
;  Debugger has found the application is not idle.
;
DBG_APP_NOT_IDLE                 = 0C0010002h

;
; MessageId: RPC_NT_INVALID_STRING_BINDING
;
; MessageText:
;
;  The string binding is invalid.
;
RPC_NT_INVALID_STRING_BINDING    = 0C0020001h

;
; MessageId: RPC_NT_WRONG_KIND_OF_BINDING
;
; MessageText:
;
;  The binding handle is not the correct type.
;
RPC_NT_WRONG_KIND_OF_BINDING     = 0C0020002h

;
; MessageId: RPC_NT_INVALID_BINDING
;
; MessageText:
;
;  The binding handle is invalid.
;
RPC_NT_INVALID_BINDING           = 0C0020003h

;
; MessageId: RPC_NT_PROTSEQ_NOT_SUPPORTED
;
; MessageText:
;
;  The RPC protocol sequence is not supported.
;
RPC_NT_PROTSEQ_NOT_SUPPORTED     = 0C0020004h

;
; MessageId: RPC_NT_INVALID_RPC_PROTSEQ
;
; MessageText:
;
;  The RPC protocol sequence is invalid.
;
RPC_NT_INVALID_RPC_PROTSEQ       = 0C0020005h

;
; MessageId: RPC_NT_INVALID_STRING_UUID
;
; MessageText:
;
;  The string UUID is invalid.
;
RPC_NT_INVALID_STRING_UUID       = 0C0020006h

;
; MessageId: RPC_NT_INVALID_ENDPOINT_FORMAT
;
; MessageText:
;
;  The endpoint format is invalid.
;
RPC_NT_INVALID_ENDPOINT_FORMAT   = 0C0020007h

;
; MessageId: RPC_NT_INVALID_NET_ADDR
;
; MessageText:
;
;  The network address is invalid.
;
RPC_NT_INVALID_NET_ADDR          = 0C0020008h

;
; MessageId: RPC_NT_NO_ENDPOINT_FOUND
;
; MessageText:
;
;  No endpoint was found.
;
RPC_NT_NO_ENDPOINT_FOUND         = 0C0020009h

;
; MessageId: RPC_NT_INVALID_TIMEOUT
;
; MessageText:
;
;  The timeout value is invalid.
;
RPC_NT_INVALID_TIMEOUT           = 0C002000Ah

;
; MessageId: RPC_NT_OBJECT_NOT_FOUND
;
; MessageText:
;
;  The object UUID was not found.
;
RPC_NT_OBJECT_NOT_FOUND          = 0C002000Bh

;
; MessageId: RPC_NT_ALREADY_REGISTERED
;
; MessageText:
;
;  The object UUID has already been registered.
;
RPC_NT_ALREADY_REGISTERED        = 0C002000Ch

;
; MessageId: RPC_NT_TYPE_ALREADY_REGISTERED
;
; MessageText:
;
;  The type UUID has already been registered.
;
RPC_NT_TYPE_ALREADY_REGISTERED   = 0C002000Dh

;
; MessageId: RPC_NT_ALREADY_LISTENING
;
; MessageText:
;
;  The RPC server is already listening.
;
RPC_NT_ALREADY_LISTENING         = 0C002000Eh

;
; MessageId: RPC_NT_NO_PROTSEQS_REGISTERED
;
; MessageText:
;
;  No protocol sequences have been registered.
;
RPC_NT_NO_PROTSEQS_REGISTERED    = 0C002000Fh

;
; MessageId: RPC_NT_NOT_LISTENING
;
; MessageText:
;
;  The RPC server is not listening.
;
RPC_NT_NOT_LISTENING             = 0C0020010h

;
; MessageId: RPC_NT_UNKNOWN_MGR_TYPE
;
; MessageText:
;
;  The manager type is unknown.
;
RPC_NT_UNKNOWN_MGR_TYPE          = 0C0020011h

;
; MessageId: RPC_NT_UNKNOWN_IF
;
; MessageText:
;
;  The interface is unknown.
;
RPC_NT_UNKNOWN_IF                = 0C0020012h

;
; MessageId: RPC_NT_NO_BINDINGS
;
; MessageText:
;
;  There are no bindings.
;
RPC_NT_NO_BINDINGS               = 0C0020013h

;
; MessageId: RPC_NT_NO_PROTSEQS
;
; MessageText:
;
;  There are no protocol sequences.
;
RPC_NT_NO_PROTSEQS               = 0C0020014h

;
; MessageId: RPC_NT_CANT_CREATE_ENDPOINT
;
; MessageText:
;
;  The endpoint cannot be created.
;
RPC_NT_CANT_CREATE_ENDPOINT      = 0C0020015h

;
; MessageId: RPC_NT_OUT_OF_RESOURCES
;
; MessageText:
;
;  Not enough resources are available to complete this operation.
;
RPC_NT_OUT_OF_RESOURCES          = 0C0020016h

;
; MessageId: RPC_NT_SERVER_UNAVAILABLE
;
; MessageText:
;
;  The RPC server is unavailable.
;
RPC_NT_SERVER_UNAVAILABLE        = 0C0020017h

;
; MessageId: RPC_NT_SERVER_TOO_BUSY
;
; MessageText:
;
;  The RPC server is too busy to complete this operation.
;
RPC_NT_SERVER_TOO_BUSY           = 0C0020018h

;
; MessageId: RPC_NT_INVALID_NETWORK_OPTIONS
;
; MessageText:
;
;  The network options are invalid.
;
RPC_NT_INVALID_NETWORK_OPTIONS   = 0C0020019h

;
; MessageId: RPC_NT_NO_CALL_ACTIVE
;
; MessageText:
;
;  There are no remote procedure calls active on this thread.
;
RPC_NT_NO_CALL_ACTIVE            = 0C002001Ah

;
; MessageId: RPC_NT_CALL_FAILED
;
; MessageText:
;
;  The remote procedure call failed.
;
RPC_NT_CALL_FAILED               = 0C002001Bh

;
; MessageId: RPC_NT_CALL_FAILED_DNE
;
; MessageText:
;
;  The remote procedure call failed and did not execute.
;
RPC_NT_CALL_FAILED_DNE           = 0C002001Ch

;
; MessageId: RPC_NT_PROTOCOL_ERROR
;
; MessageText:
;
;  An RPC protocol error occurred.
;
RPC_NT_PROTOCOL_ERROR            = 0C002001Dh

;
; MessageId: RPC_NT_UNSUPPORTED_TRANS_SYN
;
; MessageText:
;
;  The transfer syntax is not supported by the RPC server.
;
RPC_NT_UNSUPPORTED_TRANS_SYN     = 0C002001Fh

;
; MessageId: RPC_NT_UNSUPPORTED_TYPE
;
; MessageText:
;
;  The type UUID is not supported.
;
RPC_NT_UNSUPPORTED_TYPE          = 0C0020021h

;
; MessageId: RPC_NT_INVALID_TAG
;
; MessageText:
;
;  The tag is invalid.
;
RPC_NT_INVALID_TAG               = 0C0020022h

;
; MessageId: RPC_NT_INVALID_BOUND
;
; MessageText:
;
;  The array bounds are invalid.
;
RPC_NT_INVALID_BOUND             = 0C0020023h

;
; MessageId: RPC_NT_NO_ENTRY_NAME
;
; MessageText:
;
;  The binding does not contain an entry name.
;
RPC_NT_NO_ENTRY_NAME             = 0C0020024h

;
; MessageId: RPC_NT_INVALID_NAME_SYNTAX
;
; MessageText:
;
;  The name syntax is invalid.
;
RPC_NT_INVALID_NAME_SYNTAX       = 0C0020025h

;
; MessageId: RPC_NT_UNSUPPORTED_NAME_SYNTAX
;
; MessageText:
;
;  The name syntax is not supported.
;
RPC_NT_UNSUPPORTED_NAME_SYNTAX   = 0C0020026h

;
; MessageId: RPC_NT_UUID_NO_ADDRESS
;
; MessageText:
;
;  No network address is available to use to construct a UUID.
;
RPC_NT_UUID_NO_ADDRESS           = 0C0020028h

;
; MessageId: RPC_NT_DUPLICATE_ENDPOINT
;
; MessageText:
;
;  The endpoint is a duplicate.
;
RPC_NT_DUPLICATE_ENDPOINT        = 0C0020029h

;
; MessageId: RPC_NT_UNKNOWN_AUTHN_TYPE
;
; MessageText:
;
;  The authentication type is unknown.
;
RPC_NT_UNKNOWN_AUTHN_TYPE        = 0C002002Ah

;
; MessageId: RPC_NT_MAX_CALLS_TOO_SMALL
;
; MessageText:
;
;  The maximum number of calls is too small.
;
RPC_NT_MAX_CALLS_TOO_SMALL       = 0C002002Bh

;
; MessageId: RPC_NT_STRING_TOO_LONG
;
; MessageText:
;
;  The string is too long.
;
RPC_NT_STRING_TOO_LONG           = 0C002002Ch

;
; MessageId: RPC_NT_PROTSEQ_NOT_FOUND
;
; MessageText:
;
;  The RPC protocol sequence was not found.
;
RPC_NT_PROTSEQ_NOT_FOUND         = 0C002002Dh

;
; MessageId: RPC_NT_PROCNUM_OUT_OF_RANGE
;
; MessageText:
;
;  The procedure number is out of range.
;
RPC_NT_PROCNUM_OUT_OF_RANGE      = 0C002002Eh

;
; MessageId: RPC_NT_BINDING_HAS_NO_AUTH
;
; MessageText:
;
;  The binding does not contain any authentication information.
;
RPC_NT_BINDING_HAS_NO_AUTH       = 0C002002Fh

;
; MessageId: RPC_NT_UNKNOWN_AUTHN_SERVICE
;
; MessageText:
;
;  The authentication service is unknown.
;
RPC_NT_UNKNOWN_AUTHN_SERVICE     = 0C0020030h

;
; MessageId: RPC_NT_UNKNOWN_AUTHN_LEVEL
;
; MessageText:
;
;  The authentication level is unknown.
;
RPC_NT_UNKNOWN_AUTHN_LEVEL       = 0C0020031h

;
; MessageId: RPC_NT_INVALID_AUTH_IDENTITY
;
; MessageText:
;
;  The security context is invalid.
;
RPC_NT_INVALID_AUTH_IDENTITY     = 0C0020032h

;
; MessageId: RPC_NT_UNKNOWN_AUTHZ_SERVICE
;
; MessageText:
;
;  The authorization service is unknown.
;
RPC_NT_UNKNOWN_AUTHZ_SERVICE     = 0C0020033h

;
; MessageId: EPT_NT_INVALID_ENTRY
;
; MessageText:
;
;  The entry is invalid.
;
EPT_NT_INVALID_ENTRY             = 0C0020034h

;
; MessageId: EPT_NT_CANT_PERFORM_OP
;
; MessageText:
;
;  The operation cannot be performed.
;
EPT_NT_CANT_PERFORM_OP           = 0C0020035h

;
; MessageId: EPT_NT_NOT_REGISTERED
;
; MessageText:
;
;  There are no more endpoints available from the endpoint mapper.
;
EPT_NT_NOT_REGISTERED            = 0C0020036h

;
; MessageId: RPC_NT_NOTHING_TO_EXPORT
;
; MessageText:
;
;  No interfaces have been exported.
;
RPC_NT_NOTHING_TO_EXPORT         = 0C0020037h

;
; MessageId: RPC_NT_INCOMPLETE_NAME
;
; MessageText:
;
;  The entry name is incomplete.
;
RPC_NT_INCOMPLETE_NAME           = 0C0020038h

;
; MessageId: RPC_NT_INVALID_VERS_OPTION
;
; MessageText:
;
;  The version option is invalid.
;
RPC_NT_INVALID_VERS_OPTION       = 0C0020039h

;
; MessageId: RPC_NT_NO_MORE_MEMBERS
;
; MessageText:
;
;  There are no more members.
;
RPC_NT_NO_MORE_MEMBERS           = 0C002003Ah

;
; MessageId: RPC_NT_NOT_ALL_OBJS_UNEXPORTED
;
; MessageText:
;
;  There is nothing to unexport.
;
RPC_NT_NOT_ALL_OBJS_UNEXPORTED   = 0C002003Bh

;
; MessageId: RPC_NT_INTERFACE_NOT_FOUND
;
; MessageText:
;
;  The interface was not found.
;
RPC_NT_INTERFACE_NOT_FOUND       = 0C002003Ch

;
; MessageId: RPC_NT_ENTRY_ALREADY_EXISTS
;
; MessageText:
;
;  The entry already exists.
;
RPC_NT_ENTRY_ALREADY_EXISTS      = 0C002003Dh

;
; MessageId: RPC_NT_ENTRY_NOT_FOUND
;
; MessageText:
;
;  The entry is not found.
;
RPC_NT_ENTRY_NOT_FOUND           = 0C002003Eh

;
; MessageId: RPC_NT_NAME_SERVICE_UNAVAILABLE
;
; MessageText:
;
;  The name service is unavailable.
;
RPC_NT_NAME_SERVICE_UNAVAILABLE  = 0C002003Fh

;
; MessageId: RPC_NT_INVALID_NAF_ID
;
; MessageText:
;
;  The network address family is invalid.
;
RPC_NT_INVALID_NAF_ID            = 0C0020040h

;
; MessageId: RPC_NT_CANNOT_SUPPORT
;
; MessageText:
;
;  The requested operation is not supported.
;
RPC_NT_CANNOT_SUPPORT            = 0C0020041h

;
; MessageId: RPC_NT_NO_CONTEXT_AVAILABLE
;
; MessageText:
;
;  No security context is available to allow impersonation.
;
RPC_NT_NO_CONTEXT_AVAILABLE      = 0C0020042h

;
; MessageId: RPC_NT_INTERNAL_ERROR
;
; MessageText:
;
;  An internal error occurred in RPC.
;
RPC_NT_INTERNAL_ERROR            = 0C0020043h

;
; MessageId: RPC_NT_ZERO_DIVIDE
;
; MessageText:
;
;  The RPC server attempted an integer divide by zero.
;
RPC_NT_ZERO_DIVIDE               = 0C0020044h

;
; MessageId: RPC_NT_ADDRESS_ERROR
;
; MessageText:
;
;  An addressing error occurred in the RPC server.
;
RPC_NT_ADDRESS_ERROR             = 0C0020045h

;
; MessageId: RPC_NT_FP_DIV_ZERO
;
; MessageText:
;
;  A floating point operation at the RPC server caused a divide by zero.
;
RPC_NT_FP_DIV_ZERO               = 0C0020046h

;
; MessageId: RPC_NT_FP_UNDERFLOW
;
; MessageText:
;
;  A floating point underflow occurred at the RPC server.
;
RPC_NT_FP_UNDERFLOW              = 0C0020047h

;
; MessageId: RPC_NT_FP_OVERFLOW
;
; MessageText:
;
;  A floating point overflow occurred at the RPC server.
;
RPC_NT_FP_OVERFLOW               = 0C0020048h

;
; MessageId: RPC_NT_NO_MORE_ENTRIES
;
; MessageText:
;
;  The list of RPC servers available for auto-handle binding has been exhausted.
;
RPC_NT_NO_MORE_ENTRIES           = 0C0030001h

;
; MessageId: RPC_NT_SS_CHAR_TRANS_OPEN_FAIL
;
; MessageText:
;
;  The file designated by DCERPCCHARTRANS cannot be opened.
;
RPC_NT_SS_CHAR_TRANS_OPEN_FAIL   = 0C0030002h

;
; MessageId: RPC_NT_SS_CHAR_TRANS_SHORT_FILE
;
; MessageText:
;
;  The file containing the character translation table has fewer than 512 bytes.
;
RPC_NT_SS_CHAR_TRANS_SHORT_FILE  = 0C0030003h

;
; MessageId: RPC_NT_SS_IN_NULL_CONTEXT
;
; MessageText:
;
;  A null context handle is passed as an [in] parameter.
;
RPC_NT_SS_IN_NULL_CONTEXT        = 0C0030004h

;
; MessageId: RPC_NT_SS_CONTEXT_MISMATCH
;
; MessageText:
;
;  The context handle does not match any known context handles.
;
RPC_NT_SS_CONTEXT_MISMATCH       = 0C0030005h

;
; MessageId: RPC_NT_SS_CONTEXT_DAMAGED
;
; MessageText:
;
;  The context handle changed during a call.
;
RPC_NT_SS_CONTEXT_DAMAGED        = 0C0030006h

;
; MessageId: RPC_NT_SS_HANDLES_MISMATCH
;
; MessageText:
;
;  The binding handles passed to a remote procedure call do not match.
;
RPC_NT_SS_HANDLES_MISMATCH       = 0C0030007h

;
; MessageId: RPC_NT_SS_CANNOT_GET_CALL_HANDLE
;
; MessageText:
;
;  The stub is unable to get the call handle.
;
RPC_NT_SS_CANNOT_GET_CALL_HANDLE = 0C0030008h

;
; MessageId: RPC_NT_NULL_REF_POINTER
;
; MessageText:
;
;  A null reference pointer was passed to the stub.
;
RPC_NT_NULL_REF_POINTER          = 0C0030009h

;
; MessageId: RPC_NT_ENUM_VALUE_OUT_OF_RANGE
;
; MessageText:
;
;  The enumeration value is out of range.
;
RPC_NT_ENUM_VALUE_OUT_OF_RANGE   = 0C003000Ah

;
; MessageId: RPC_NT_BYTE_COUNT_TOO_SMALL
;
; MessageText:
;
;  The byte count is too small.
;
RPC_NT_BYTE_COUNT_TOO_SMALL      = 0C003000Bh

;
; MessageId: RPC_NT_BAD_STUB_DATA
;
; MessageText:
;
;  The stub received bad data.
;
RPC_NT_BAD_STUB_DATA             = 0C003000Ch

;
; MessageId: RPC_NT_CALL_IN_PROGRESS
;
; MessageText:
;
;  A remote procedure call is already in progress for this thread.
;
RPC_NT_CALL_IN_PROGRESS          = 0C0020049h

;
; MessageId: RPC_NT_NO_MORE_BINDINGS
;
; MessageText:
;
;  There are no more bindings.
;
RPC_NT_NO_MORE_BINDINGS          = 0C002004Ah

;
; MessageId: RPC_NT_GROUP_MEMBER_NOT_FOUND
;
; MessageText:
;
;  The group member was not found.
;
RPC_NT_GROUP_MEMBER_NOT_FOUND    = 0C002004Bh

;
; MessageId: EPT_NT_CANT_CREATE
;
; MessageText:
;
;  The endpoint mapper database entry could not be created.
;
EPT_NT_CANT_CREATE               = 0C002004Ch

;
; MessageId: RPC_NT_INVALID_OBJECT
;
; MessageText:
;
;  The object UUID is the nil UUID.
;
RPC_NT_INVALID_OBJECT            = 0C002004Dh

;
; MessageId: RPC_NT_NO_INTERFACES
;
; MessageText:
;
;  No interfaces have been registered.
;
RPC_NT_NO_INTERFACES             = 0C002004Fh

;
; MessageId: RPC_NT_CALL_CANCELLED
;
; MessageText:
;
;  The remote procedure call was cancelled.
;
RPC_NT_CALL_CANCELLED            = 0C0020050h

;
; MessageId: RPC_NT_BINDING_INCOMPLETE
;
; MessageText:
;
;  The binding handle does not contain all required information.
;
RPC_NT_BINDING_INCOMPLETE        = 0C0020051h

;
; MessageId: RPC_NT_COMM_FAILURE
;
; MessageText:
;
;  A communications failure occurred during a remote procedure call.
;
RPC_NT_COMM_FAILURE              = 0C0020052h

;
; MessageId: RPC_NT_UNSUPPORTED_AUTHN_LEVEL
;
; MessageText:
;
;  The requested authentication level is not supported.
;
RPC_NT_UNSUPPORTED_AUTHN_LEVEL   = 0C0020053h

;
; MessageId: RPC_NT_NO_PRINC_NAME
;
; MessageText:
;
;  No principal name registered.
;
RPC_NT_NO_PRINC_NAME             = 0C0020054h

;
; MessageId: RPC_NT_NOT_RPC_ERROR
;
; MessageText:
;
;  The error specified is not a valid Windows RPC error code.
;
RPC_NT_NOT_RPC_ERROR             = 0C0020055h

;
; MessageId: RPC_NT_UUID_LOCAL_ONLY
;
; MessageText:
;
;  A UUID that is valid only on this computer has been allocated.
;
RPC_NT_UUID_LOCAL_ONLY           = 40020056h

;
; MessageId: RPC_NT_SEC_PKG_ERROR
;
; MessageText:
;
;  A security package specific error occurred.
;
RPC_NT_SEC_PKG_ERROR             = 0C0020057h

;
; MessageId: RPC_NT_NOT_CANCELLED
;
; MessageText:
;
;  Thread is not cancelled.
;
RPC_NT_NOT_CANCELLED             = 0C0020058h

;
; MessageId: RPC_NT_INVALID_ES_ACTION
;
; MessageText:
;
;  Invalid operation on the encoding/decoding handle.
;
RPC_NT_INVALID_ES_ACTION         = 0C0030059h

;
; MessageId: RPC_NT_WRONG_ES_VERSION
;
; MessageText:
;
;  Incompatible version of the serializing package.
;
RPC_NT_WRONG_ES_VERSION          = 0C003005Ah

;
; MessageId: RPC_NT_WRONG_STUB_VERSION
;
; MessageText:
;
;  Incompatible version of the RPC stub.
;
RPC_NT_WRONG_STUB_VERSION        = 0C003005Bh

;
; MessageId: RPC_NT_INVALID_PIPE_OBJECT
;
; MessageText:
;
;  The RPC pipe object is invalid or corrupted.
;
RPC_NT_INVALID_PIPE_OBJECT       = 0C003005Ch

;
; MessageId: RPC_NT_INVALID_PIPE_OPERATION
;
; MessageText:
;
;  An invalid operation was attempted on an RPC pipe object.
;
RPC_NT_INVALID_PIPE_OPERATION    = 0C003005Dh

;
; MessageId: RPC_NT_WRONG_PIPE_VERSION
;
; MessageText:
;
;  Unsupported RPC pipe version.
;
RPC_NT_WRONG_PIPE_VERSION        = 0C003005Eh

;
; MessageId: RPC_NT_PIPE_CLOSED
;
; MessageText:
;
;  The RPC pipe object has already been closed.
;
RPC_NT_PIPE_CLOSED               = 0C003005Fh

;
; MessageId: RPC_NT_PIPE_DISCIPLINE_ERROR
;
; MessageText:
;
;  The RPC call completed before all pipes were processed.
;
RPC_NT_PIPE_DISCIPLINE_ERROR     = 0C0030060h

;
; MessageId: RPC_NT_PIPE_EMPTY
;
; MessageText:
;
;  No more data is available from the RPC pipe.
;
RPC_NT_PIPE_EMPTY                = 0C0030061h

;
; MessageId: RPC_NT_INVALID_ASYNC_HANDLE
;
; MessageText:
;
;  Invalid asynchronous remote procedure call handle.
;
RPC_NT_INVALID_ASYNC_HANDLE      = 0C0020062h

;
; MessageId: RPC_NT_INVALID_ASYNC_CALL
;
; MessageText:
;
;  Invalid asynchronous RPC call handle for this operation.
;
RPC_NT_INVALID_ASYNC_CALL        = 0C0020063h

;
; MessageId: RPC_NT_SEND_INCOMPLETE
;
; MessageText:
;
;  Some data remains to be sent in the request buffer.
;
RPC_NT_SEND_INCOMPLETE           = 400200AFh

;
; MessageId: STATUS_ACPI_INVALID_OPCODE
;
; MessageText:
;
;  An attempt was made to run an invalid AML opcode
;
STATUS_ACPI_INVALID_OPCODE       = 0C0140001h

;
; MessageId: STATUS_ACPI_STACK_OVERFLOW
;
; MessageText:
;
;  The AML Interpreter Stack has overflowed
;
STATUS_ACPI_STACK_OVERFLOW       = 0C0140002h

;
; MessageId: STATUS_ACPI_ASSERT_FAILED
;
; MessageText:
;
;  An inconsistent state has occurred
;
STATUS_ACPI_ASSERT_FAILED        = 0C0140003h

;
; MessageId: STATUS_ACPI_INVALID_INDEX
;
; MessageText:
;
;  An attempt was made to access an array outside of its bounds
;
STATUS_ACPI_INVALID_INDEX        = 0C0140004h

;
; MessageId: STATUS_ACPI_INVALID_ARGUMENT
;
; MessageText:
;
;  A required argument was not specified
;
STATUS_ACPI_INVALID_ARGUMENT     = 0C0140005h

;
; MessageId: STATUS_ACPI_FATAL
;
; MessageText:
;
;  A fatal error has occurred
;
STATUS_ACPI_FATAL                = 0C0140006h

;
; MessageId: STATUS_ACPI_INVALID_SUPERNAME
;
; MessageText:
;
;  An invalid SuperName was specified
;
STATUS_ACPI_INVALID_SUPERNAME    = 0C0140007h

;
; MessageId: STATUS_ACPI_INVALID_ARGTYPE
;
; MessageText:
;
;  An argument with an incorrect type was specified
;
STATUS_ACPI_INVALID_ARGTYPE      = 0C0140008h

;
; MessageId: STATUS_ACPI_INVALID_OBJTYPE
;
; MessageText:
;
;  An object with an incorrect type was specified
;
STATUS_ACPI_INVALID_OBJTYPE      = 0C0140009h

;
; MessageId: STATUS_ACPI_INVALID_TARGETTYPE
;
; MessageText:
;
;  A target with an incorrect type was specified
;
STATUS_ACPI_INVALID_TARGETTYPE   = 0C014000Ah

;
; MessageId: STATUS_ACPI_INCORRECT_ARGUMENT_COUNT
;
; MessageText:
;
;  An incorrect number of arguments were specified
;
STATUS_ACPI_INCORRECT_ARGUMENT_COUNT = 0C014000Bh

;
; MessageId: STATUS_ACPI_ADDRESS_NOT_MAPPED
;
; MessageText:
;
;  An address failed to translate
;
STATUS_ACPI_ADDRESS_NOT_MAPPED   = 0C014000Ch

;
; MessageId: STATUS_ACPI_INVALID_EVENTTYPE
;
; MessageText:
;
;  An incorrect event type was specified
;
STATUS_ACPI_INVALID_EVENTTYPE    = 0C014000Dh

;
; MessageId: STATUS_ACPI_HANDLER_COLLISION
;
; MessageText:
;
;  A handler for the target already exists
;
STATUS_ACPI_HANDLER_COLLISION    = 0C014000Eh

;
; MessageId: STATUS_ACPI_INVALID_DATA
;
; MessageText:
;
;  Invalid data for the target was specified
;
STATUS_ACPI_INVALID_DATA         = 0C014000Fh

;
; MessageId: STATUS_ACPI_INVALID_REGION
;
; MessageText:
;
;  An invalid region for the target was specified
;
STATUS_ACPI_INVALID_REGION       = 0C0140010h

;
; MessageId: STATUS_ACPI_INVALID_ACCESS_SIZE
;
; MessageText:
;
;  An attempt was made to access a field outside of the defined range
;
STATUS_ACPI_INVALID_ACCESS_SIZE  = 0C0140011h

;
; MessageId: STATUS_ACPI_ACQUIRE_GLOBAL_LOCK
;
; MessageText:
;
;  The Global system lock could not be acquired
;
STATUS_ACPI_ACQUIRE_GLOBAL_LOCK  = 0C0140012h

;
; MessageId: STATUS_ACPI_ALREADY_INITIALIZED
;
; MessageText:
;
;  An attempt was made to reinitialize the ACPI subsystem
;
STATUS_ACPI_ALREADY_INITIALIZED  = 0C0140013h

;
; MessageId: STATUS_ACPI_NOT_INITIALIZED
;
; MessageText:
;
;  The ACPI subsystem has not been initialized
;
STATUS_ACPI_NOT_INITIALIZED      = 0C0140014h

;
; MessageId: STATUS_ACPI_INVALID_MUTEX_LEVEL
;
; MessageText:
;
;  An incorrect mutex was specified
;
STATUS_ACPI_INVALID_MUTEX_LEVEL  = 0C0140015h

;
; MessageId: STATUS_ACPI_MUTEX_NOT_OWNED
;
; MessageText:
;
;  The mutex is not currently owned
;
STATUS_ACPI_MUTEX_NOT_OWNED      = 0C0140016h

;
; MessageId: STATUS_ACPI_MUTEX_NOT_OWNER
;
; MessageText:
;
;  An attempt was made to access the mutex by a process that was not the owner
;
STATUS_ACPI_MUTEX_NOT_OWNER      = 0C0140017h

;
; MessageId: STATUS_ACPI_RS_ACCESS
;
; MessageText:
;
;  An error occurred during an access to Region Space
;
STATUS_ACPI_RS_ACCESS            = 0C0140018h

;
; MessageId: STATUS_ACPI_INVALID_TABLE
;
; MessageText:
;
;  An attempt was made to use an incorrect table
;
STATUS_ACPI_INVALID_TABLE        = 0C0140019h

;
; MessageId: STATUS_ACPI_REG_HANDLER_FAILED
;
; MessageText:
;
;  The registration of an ACPI event failed
;
STATUS_ACPI_REG_HANDLER_FAILED   = 0C0140020h

;
; MessageId: STATUS_ACPI_POWER_REQUEST_FAILED
;
; MessageText:
;
;  An ACPI Power Object failed to transition state
;
STATUS_ACPI_POWER_REQUEST_FAILED = 0C0140021h

;
; Terminal Server specific Errors
;
;
; MessageId: STATUS_CTX_WINSTATION_NAME_INVALID
;
; MessageText:
;
;  Session name %1 is invalid.
;
STATUS_CTX_WINSTATION_NAME_INVALID = 0C00A0001h

;
; MessageId: STATUS_CTX_INVALID_PD
;
; MessageText:
;
;  The protocol driver %1 is invalid.
;
STATUS_CTX_INVALID_PD            = 0C00A0002h

;
; MessageId: STATUS_CTX_PD_NOT_FOUND
;
; MessageText:
;
;  The protocol driver %1 was not found in the system path.
;
STATUS_CTX_PD_NOT_FOUND          = 0C00A0003h

;
; MessageId: STATUS_CTX_CDM_CONNECT
;
; MessageText:
;
;  The Client Drive Mapping Service Has Connected on Terminal Connection.
;
STATUS_CTX_CDM_CONNECT           = 400A0004h

;
; MessageId: STATUS_CTX_CDM_DISCONNECT
;
; MessageText:
;
;  The Client Drive Mapping Service Has Disconnected on Terminal Connection.
;
STATUS_CTX_CDM_DISCONNECT        = 400A0005h

;
; MessageId: STATUS_CTX_CLOSE_PENDING
;
; MessageText:
;
;  A close operation is pending on the Terminal Connection.
;
STATUS_CTX_CLOSE_PENDING         = 0C00A0006h

;
; MessageId: STATUS_CTX_NO_OUTBUF
;
; MessageText:
;
;  There are no free output buffers available.
;
STATUS_CTX_NO_OUTBUF             = 0C00A0007h

;
; MessageId: STATUS_CTX_MODEM_INF_NOT_FOUND
;
; MessageText:
;
;  The MODEM.INF file was not found.
;
STATUS_CTX_MODEM_INF_NOT_FOUND   = 0C00A0008h

;
; MessageId: STATUS_CTX_INVALID_MODEMNAME
;
; MessageText:
;
;  The modem (%1) was not found in MODEM.INF.
;
STATUS_CTX_INVALID_MODEMNAME     = 0C00A0009h

;
; MessageId: STATUS_CTX_RESPONSE_ERROR
;
; MessageText:
;
;  The modem did not accept the command sent to it.
;  Verify the configured modem name matches the attached modem.
;
STATUS_CTX_RESPONSE_ERROR        = 0C00A000Ah

;
; MessageId: STATUS_CTX_MODEM_RESPONSE_TIMEOUT
;
; MessageText:
;
;  The modem did not respond to the command sent to it.
;  Verify the modem is properly cabled and powered on.
;
STATUS_CTX_MODEM_RESPONSE_TIMEOUT = 0C00A000Bh

;
; MessageId: STATUS_CTX_MODEM_RESPONSE_NO_CARRIER
;
; MessageText:
;
;  Carrier detect has failed or carrier has been dropped due to disconnect.
;
STATUS_CTX_MODEM_RESPONSE_NO_CARRIER = 0C00A000Ch

;
; MessageId: STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE
;
; MessageText:
;
;  Dial tone not detected within required time.
;  Verify phone cable is properly attached and functional.
;
STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE = 0C00A000Dh

;
; MessageId: STATUS_CTX_MODEM_RESPONSE_BUSY
;
; MessageText:
;
;  Busy signal detected at remote site on callback.
;
STATUS_CTX_MODEM_RESPONSE_BUSY   = 0C00A000Eh

;
; MessageId: STATUS_CTX_MODEM_RESPONSE_VOICE
;
; MessageText:
;
;  Voice detected at remote site on callback.
;
STATUS_CTX_MODEM_RESPONSE_VOICE  = 0C00A000Fh

;
; MessageId: STATUS_CTX_TD_ERROR
;
; MessageText:
;
;  Transport driver error
;
STATUS_CTX_TD_ERROR              = 0C00A0010h

;
; MessageId: STATUS_CTX_LICENSE_CLIENT_INVALID
;
; MessageText:
;
;  The client you are using is not licensed to use this system. Your logon request is denied.
;
STATUS_CTX_LICENSE_CLIENT_INVALID = 0C00A0012h

;
; MessageId: STATUS_CTX_LICENSE_NOT_AVAILABLE
;
; MessageText:
;
;  The system has reached its licensed logon limit.
;  Please try again later.
;
STATUS_CTX_LICENSE_NOT_AVAILABLE = 0C00A0013h

;
; MessageId: STATUS_CTX_LICENSE_EXPIRED
;
; MessageText:
;
;  The system license has expired. Your logon request is denied.
;
STATUS_CTX_LICENSE_EXPIRED       = 0C00A0014h

;
; MessageId: STATUS_CTX_WINSTATION_NOT_FOUND
;
; MessageText:
;
;  The specified session cannot be found.
;
STATUS_CTX_WINSTATION_NOT_FOUND  = 0C00A0015h

;
; MessageId: STATUS_CTX_WINSTATION_NAME_COLLISION
;
; MessageText:
;
;  The specified session name is already in use.
;
STATUS_CTX_WINSTATION_NAME_COLLISION = 0C00A0016h

;
; MessageId: STATUS_CTX_WINSTATION_BUSY
;
; MessageText:
;
;  The requested operation cannot be completed because the Terminal Connection is currently busy processing a connect, disconnect, reset, or delete operation.
;
STATUS_CTX_WINSTATION_BUSY       = 0C00A0017h

;
; MessageId: STATUS_CTX_BAD_VIDEO_MODE
;
; MessageText:
;
;  An attempt has been made to connect to a session whose video mode is not supported by the current client.
;
STATUS_CTX_BAD_VIDEO_MODE        = 0C00A0018h

;
; MessageId: STATUS_CTX_GRAPHICS_INVALID
;
; MessageText:
;
;  The application attempted to enable DOS graphics mode.
;  DOS graphics mode is not supported.
;
STATUS_CTX_GRAPHICS_INVALID      = 0C00A0022h

;
; MessageId: STATUS_CTX_NOT_CONSOLE
;
; MessageText:
;
;  The requested operation can be performed only on the system console.
;  This is most often the result of a driver or system DLL requiring direct console access.
;
STATUS_CTX_NOT_CONSOLE           = 0C00A0024h

;
; MessageId: STATUS_CTX_CLIENT_QUERY_TIMEOUT
;
; MessageText:
;
;  The client failed to respond to the server connect message.
;
STATUS_CTX_CLIENT_QUERY_TIMEOUT  = 0C00A0026h

;
; MessageId: STATUS_CTX_CONSOLE_DISCONNECT
;
; MessageText:
;
;  Disconnecting the console session is not supported.
;
STATUS_CTX_CONSOLE_DISCONNECT    = 0C00A0027h

;
; MessageId: STATUS_CTX_CONSOLE_CONNECT
;
; MessageText:
;
;  Reconnecting a disconnected session to the console is not supported.
;
STATUS_CTX_CONSOLE_CONNECT       = 0C00A0028h

;
; MessageId: STATUS_CTX_SHADOW_DENIED
;
; MessageText:
;
;  The request to control another session remotely was denied.
;
STATUS_CTX_SHADOW_DENIED         = 0C00A002Ah

;
; MessageId: STATUS_CTX_WINSTATION_ACCESS_DENIED
;
; MessageText:
;
;  A process has requested access to a session, but has not been granted those access rights.
;
STATUS_CTX_WINSTATION_ACCESS_DENIED = 0C00A002Bh

;
; MessageId: STATUS_CTX_INVALID_WD
;
; MessageText:
;
;  The Terminal Connection driver %1 is invalid.
;
STATUS_CTX_INVALID_WD            = 0C00A002Eh

;
; MessageId: STATUS_CTX_WD_NOT_FOUND
;
; MessageText:
;
;  The Terminal Connection driver %1 was not found in the system path.
;
STATUS_CTX_WD_NOT_FOUND          = 0C00A002Fh

;
; MessageId: STATUS_CTX_SHADOW_INVALID
;
; MessageText:
;
;  The requested session cannot be controlled remotely.
;  This may be because the session is disconnected or does not currently have a user logged on.
;  Also, you cannot control a session remotely from the system console or control the system console remotely.
;  And you cannot remote control your own current session.
;
STATUS_CTX_SHADOW_INVALID        = 0C00A0030h

;
; MessageId: STATUS_CTX_SHADOW_DISABLED
;
; MessageText:
;
;  The requested session is not configured to allow remote control.
;
STATUS_CTX_SHADOW_DISABLED       = 0C00A0031h

;
; MessageId: STATUS_RDP_PROTOCOL_ERROR
;
; MessageText:
;
;  The RDP protocol component %2 detected an error in the protocol stream and has disconnected the client.
;
STATUS_RDP_PROTOCOL_ERROR        = 0C00A0032h

;
; MessageId: STATUS_CTX_CLIENT_LICENSE_NOT_SET
;
; MessageText:
;
;  Your request to connect to this Terminal server has been rejected.
;  Your Terminal Server Client license number has not been entered for this copy of the Terminal Client.
;  Please call your system administrator for help in entering a valid, unique license number for this Terminal Server Client.
;  Click OK to continue.
;
STATUS_CTX_CLIENT_LICENSE_NOT_SET = 0C00A0033h

;
; MessageId: STATUS_CTX_CLIENT_LICENSE_IN_USE
;
; MessageText:
;
;  Your request to connect to this Terminal server has been rejected.
;  Your Terminal Server Client license number is currently being used by another user.
;  Please call your system administrator to obtain a new copy of the Terminal Server Client with a valid, unique license number.
;  Click OK to continue.
;
STATUS_CTX_CLIENT_LICENSE_IN_USE = 0C00A0034h

;
; MessageId: STATUS_PNP_BAD_MPS_TABLE
;
; MessageText:
;
;  A device is missing in the system BIOS MPS table. This device will not be used.
;  Please contact your system vendor for system BIOS update.
;
STATUS_PNP_BAD_MPS_TABLE         = 0C0040035h

;
; MessageId: STATUS_PNP_TRANSLATION_FAILED
;
; MessageText:
;
;  A translator failed to translate resources.
;
STATUS_PNP_TRANSLATION_FAILED    = 0C0040036h

;
; MessageId: STATUS_PNP_IRQ_TRANSLATION_FAILED
;
; MessageText:
;
;  A IRQ translator failed to translate resources.
;
STATUS_PNP_IRQ_TRANSLATION_FAILED = 0C0040037h