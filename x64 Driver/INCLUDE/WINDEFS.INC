
; FASM SOURCE FILE
; http://flatassembler.net

; written by @L.CHEMIST (Andrey A. Meshkov)
; maalchemist@gmail.com
; maa-mail@yandex.ru

; ------------------------------------------------------------------------------

INFINITE               = 0xFFFFFFFF ; Infinite timeout
MAXIMUM_WAIT_OBJECTS   = 64         ; Maximum number of wait objects

; ------------------------------------------------------------------------------

; String Flags.
NORM_IGNORECASE     = 0x00000001 ; ignore case
NORM_IGNORENONSPACE = 0x00000002 ; ignore nonspacing chars
NORM_IGNORESYMBOLS  = 0x00000004 ; ignore symbols
NORM_IGNOREKANATYPE = 0x00010000 ; ignore kanatype
NORM_IGNOREWIDTH    = 0x00020000 ; ignore width

; ------------------------------------------------------------------------------

; Compare String Return Values.

CSTR_LESS_THAN            = 1           ; string 1 less than string 2
CSTR_EQUAL                = 2           ; string 1 equal to string 2
CSTR_GREATER_THAN         = 3           ; string 1 greater than string 2

; ------------------------------------------------------------------------------

; Language IDs.
;
; The following two combinations of primary language ID and
; sublanguage ID have special semantics:
;
;   Primary Language ID   Sublanguage ID      Result
;   -------------------   ---------------     ------------------------
;   LANG_NEUTRAL          SUBLANG_NEUTRAL     Language neutral
;   LANG_NEUTRAL          SUBLANG_DEFAULT     User default language
;   LANG_NEUTRAL          SUBLANG_SYS_DEFAULT System default language
;   LANG_INVARIANT        SUBLANG_NEUTRAL     Invariant locale

; Primary language IDs.

LANG_NEUTRAL                     = 0x00
LANG_INVARIANT                   = 0x7f

LANG_AFRIKAANS                   = 0x36
LANG_ALBANIAN                    = 0x1c
LANG_ARABIC                      = 0x01
LANG_ARMENIAN                    = 0x2b
LANG_ASSAMESE                    = 0x4d
LANG_AZERI                       = 0x2c
LANG_BASQUE                      = 0x2d
LANG_BELARUSIAN                  = 0x23
LANG_BENGALI                     = 0x45
LANG_BULGARIAN                   = 0x02
LANG_CATALAN                     = 0x03
LANG_CHINESE                     = 0x04
LANG_CROATIAN                    = 0x1a
LANG_CZECH                       = 0x05
LANG_DANISH                      = 0x06
LANG_DIVEHI                      = 0x65
LANG_DUTCH                       = 0x13
LANG_ENGLISH                     = 0x09
LANG_ESTONIAN                    = 0x25
LANG_FAEROESE                    = 0x38
LANG_FARSI                       = 0x29
LANG_FINNISH                     = 0x0b
LANG_FRENCH                      = 0x0c
LANG_GALICIAN                    = 0x56
LANG_GEORGIAN                    = 0x37
LANG_GERMAN                      = 0x07
LANG_GREEK                       = 0x08
LANG_GUJARATI                    = 0x47
LANG_HEBREW                      = 0x0d
LANG_HINDI                       = 0x39
LANG_HUNGARIAN                   = 0x0e
LANG_ICELANDIC                   = 0x0f
LANG_INDONESIAN                  = 0x21
LANG_ITALIAN                     = 0x10
LANG_JAPANESE                    = 0x11
LANG_KANNADA                     = 0x4b
LANG_KASHMIRI                    = 0x60
LANG_KAZAK                       = 0x3f
LANG_KONKANI                     = 0x57
LANG_KOREAN                      = 0x12
LANG_KYRGYZ                      = 0x40
LANG_LATVIAN                     = 0x26
LANG_LITHUANIAN                  = 0x27
LANG_MACEDONIAN                  = 0x2f   ; the Former Yugoslav Republic of Macedonia
LANG_MALAY                       = 0x3e
LANG_MALAYALAM                   = 0x4c
LANG_MANIPURI                    = 0x58
LANG_MARATHI                     = 0x4e
LANG_MONGOLIAN                   = 0x50
LANG_NEPALI                      = 0x61
LANG_NORWEGIAN                   = 0x14
LANG_ORIYA                       = 0x48
LANG_POLISH                      = 0x15
LANG_PORTUGUESE                  = 0x16
LANG_PUNJABI                     = 0x46
LANG_ROMANIAN                    = 0x18
LANG_RUSSIAN                     = 0x19
LANG_SANSKRIT                    = 0x4f
LANG_SERBIAN                     = 0x1a
LANG_SINDHI                      = 0x59
LANG_SLOVAK                      = 0x1b
LANG_SLOVENIAN                   = 0x24
LANG_SPANISH                     = 0x0a
LANG_SWAHILI                     = 0x41
LANG_SWEDISH                     = 0x1d
LANG_SYRIAC                      = 0x5a
LANG_TAMIL                       = 0x49
LANG_TATAR                       = 0x44
LANG_TELUGU                      = 0x4a
LANG_THAI                        = 0x1e
LANG_TURKISH                     = 0x1f
LANG_UKRAINIAN                   = 0x22
LANG_URDU                        = 0x20
LANG_UZBEK                       = 0x43
LANG_VIETNAMESE                  = 0x2a

; Sublanguage IDs.
;
; The name immediately following SUBLANG_ dictates which primary
; language ID that sublanguage ID can be combined with to form a
; valid language ID.

SUBLANG_NEUTRAL                  = 0x00    ; language neutral
SUBLANG_DEFAULT                  = 0x01    ; user default
SUBLANG_SYS_DEFAULT              = 0x02    ; system default

SUBLANG_ARABIC_SAUDI_ARABIA      = 0x01    ; Arabic (Saudi Arabia)
SUBLANG_ARABIC_IRAQ              = 0x02    ; Arabic (Iraq)
SUBLANG_ARABIC_EGYPT             = 0x03    ; Arabic (Egypt)
SUBLANG_ARABIC_LIBYA             = 0x04    ; Arabic (Libya)
SUBLANG_ARABIC_ALGERIA           = 0x05    ; Arabic (Algeria)
SUBLANG_ARABIC_MOROCCO           = 0x06    ; Arabic (Morocco)
SUBLANG_ARABIC_TUNISIA           = 0x07    ; Arabic (Tunisia)
SUBLANG_ARABIC_OMAN              = 0x08    ; Arabic (Oman)
SUBLANG_ARABIC_YEMEN             = 0x09    ; Arabic (Yemen)
SUBLANG_ARABIC_SYRIA             = 0x0a    ; Arabic (Syria)
SUBLANG_ARABIC_JORDAN            = 0x0b    ; Arabic (Jordan)
SUBLANG_ARABIC_LEBANON           = 0x0c    ; Arabic (Lebanon)
SUBLANG_ARABIC_KUWAIT            = 0x0d    ; Arabic (Kuwait)
SUBLANG_ARABIC_UAE               = 0x0e    ; Arabic (U.A.E)
SUBLANG_ARABIC_BAHRAIN           = 0x0f    ; Arabic (Bahrain)
SUBLANG_ARABIC_QATAR             = 0x10    ; Arabic (Qatar)
SUBLANG_AZERI_LATIN              = 0x01    ; Azeri (Latin)
SUBLANG_AZERI_CYRILLIC           = 0x02    ; Azeri (Cyrillic)
SUBLANG_CHINESE_TRADITIONAL      = 0x01    ; Chinese (Taiwan)
SUBLANG_CHINESE_SIMPLIFIED       = 0x02    ; Chinese (PR China)
SUBLANG_CHINESE_HONGKONG         = 0x03    ; Chinese (Hong Kong S.A.R., P.R.C.)
SUBLANG_CHINESE_SINGAPORE        = 0x04    ; Chinese (Singapore)
SUBLANG_CHINESE_MACAU            = 0x05    ; Chinese (Macau S.A.R.)
SUBLANG_DUTCH                    = 0x01    ; Dutch
SUBLANG_DUTCH_BELGIAN            = 0x02    ; Dutch (Belgian)
SUBLANG_ENGLISH_US               = 0x01    ; English (USA)
SUBLANG_ENGLISH_UK               = 0x02    ; English (UK)
SUBLANG_ENGLISH_AUS              = 0x03    ; English (Australian)
SUBLANG_ENGLISH_CAN              = 0x04    ; English (Canadian)
SUBLANG_ENGLISH_NZ               = 0x05    ; English (New Zealand)
SUBLANG_ENGLISH_EIRE             = 0x06    ; English (Irish)
SUBLANG_ENGLISH_SOUTH_AFRICA     = 0x07    ; English (South Africa)
SUBLANG_ENGLISH_JAMAICA          = 0x08    ; English (Jamaica)
SUBLANG_ENGLISH_CARIBBEAN        = 0x09    ; English (Caribbean)
SUBLANG_ENGLISH_BELIZE           = 0x0a    ; English (Belize)
SUBLANG_ENGLISH_TRINIDAD         = 0x0b    ; English (Trinidad)
SUBLANG_ENGLISH_ZIMBABWE         = 0x0c    ; English (Zimbabwe)
SUBLANG_ENGLISH_PHILIPPINES      = 0x0d    ; English (Philippines)
SUBLANG_FRENCH                   = 0x01    ; French
SUBLANG_FRENCH_BELGIAN           = 0x02    ; French (Belgian)
SUBLANG_FRENCH_CANADIAN          = 0x03    ; French (Canadian)
SUBLANG_FRENCH_SWISS             = 0x04    ; French (Swiss)
SUBLANG_FRENCH_LUXEMBOURG        = 0x05    ; French (Luxembourg)
SUBLANG_FRENCH_MONACO            = 0x06    ; French (Monaco)
SUBLANG_GERMAN                   = 0x01    ; German
SUBLANG_GERMAN_SWISS             = 0x02    ; German (Swiss)
SUBLANG_GERMAN_AUSTRIAN          = 0x03    ; German (Austrian)
SUBLANG_GERMAN_LUXEMBOURG        = 0x04    ; German (Luxembourg)
SUBLANG_GERMAN_LIECHTENSTEIN     = 0x05    ; German (Liechtenstein)
SUBLANG_ITALIAN                  = 0x01    ; Italian
SUBLANG_ITALIAN_SWISS            = 0x02    ; Italian (Swiss)
; #if _WIN32_WINNT >= 0x0501
; #define SUBLANG_KASHMIRI_SASIA           0x02    // Kashmiri (South Asia)
; #endif
SUBLANG_KASHMIRI_INDIA           = 0x02    ; For app compatibility only
SUBLANG_KOREAN                   = 0x01    ; Korean (Extended Wansung)
SUBLANG_LITHUANIAN               = 0x01    ; Lithuanian
SUBLANG_MALAY_MALAYSIA           = 0x01    ; Malay (Malaysia)
SUBLANG_MALAY_BRUNEI_DARUSSALAM  = 0x02    ; Malay (Brunei Darussalam)
SUBLANG_NEPALI_INDIA             = 0x02    ; Nepali (India)
SUBLANG_NORWEGIAN_BOKMAL         = 0x01    ; Norwegian (Bokmal)
SUBLANG_NORWEGIAN_NYNORSK        = 0x02    ; Norwegian (Nynorsk)
SUBLANG_PORTUGUESE               = 0x02    ; Portuguese
SUBLANG_PORTUGUESE_BRAZILIAN     = 0x01    ; Portuguese (Brazilian)
SUBLANG_SERBIAN_LATIN            = 0x02    ; Serbian (Latin)
SUBLANG_SERBIAN_CYRILLIC         = 0x03    ; Serbian (Cyrillic)
SUBLANG_SPANISH                  = 0x01    ; Spanish (Castilian)
SUBLANG_SPANISH_MEXICAN          = 0x02    ; Spanish (Mexican)
SUBLANG_SPANISH_MODERN           = 0x03    ; Spanish (Spain)
SUBLANG_SPANISH_GUATEMALA        = 0x04    ; Spanish (Guatemala)
SUBLANG_SPANISH_COSTA_RICA       = 0x05    ; Spanish (Costa Rica)
SUBLANG_SPANISH_PANAMA           = 0x06    ; Spanish (Panama)
SUBLANG_SPANISH_DOMINICAN_REPUBLIC = 0x07  ; Spanish (Dominican Republic)
SUBLANG_SPANISH_VENEZUELA        = 0x08    ; Spanish (Venezuela)
SUBLANG_SPANISH_COLOMBIA         = 0x09    ; Spanish (Colombia)
SUBLANG_SPANISH_PERU             = 0x0a    ; Spanish (Peru)
SUBLANG_SPANISH_ARGENTINA        = 0x0b    ; Spanish (Argentina)
SUBLANG_SPANISH_ECUADOR          = 0x0c    ; Spanish (Ecuador)
SUBLANG_SPANISH_CHILE            = 0x0d    ; Spanish (Chile)
SUBLANG_SPANISH_URUGUAY          = 0x0e    ; Spanish (Uruguay)
SUBLANG_SPANISH_PARAGUAY         = 0x0f    ; Spanish (Paraguay)
SUBLANG_SPANISH_BOLIVIA          = 0x10    ; Spanish (Bolivia)
SUBLANG_SPANISH_EL_SALVADOR      = 0x11    ; Spanish (El Salvador)
SUBLANG_SPANISH_HONDURAS         = 0x12    ; Spanish (Honduras)
SUBLANG_SPANISH_NICARAGUA        = 0x13    ; Spanish (Nicaragua)
SUBLANG_SPANISH_PUERTO_RICO      = 0x14    ; Spanish (Puerto Rico)
SUBLANG_SWEDISH                  = 0x01    ; Swedish
SUBLANG_SWEDISH_FINLAND          = 0x02    ; Swedish (Finland)
SUBLANG_URDU_PAKISTAN            = 0x01    ; Urdu (Pakistan)
SUBLANG_URDU_INDIA               = 0x02    ; Urdu (India)
SUBLANG_UZBEK_LATIN              = 0x01    ; Uzbek (Latin)
SUBLANG_UZBEK_CYRILLIC           = 0x02    ; Uzbek (Cyrillic)

; Sorting IDs.

SORT_DEFAULT                     = 0x0     ; sorting default

SORT_JAPANESE_XJIS               = 0x0     ; Japanese XJIS order
SORT_JAPANESE_UNICODE            = 0x1     ; Japanese Unicode order

SORT_CHINESE_BIG5                = 0x0     ; Chinese BIG5 order
SORT_CHINESE_PRCP                = 0x0     ; PRC Chinese Phonetic order
SORT_CHINESE_UNICODE             = 0x1     ; Chinese Unicode order
SORT_CHINESE_PRC                 = 0x2     ; PRC Chinese Stroke Count order
SORT_CHINESE_BOPOMOFO            = 0x3     ; Traditional Chinese Bopomofo order

SORT_KOREAN_KSC                  = 0x0     ; Korean KSC order
SORT_KOREAN_UNICODE              = 0x1     ; Korean Unicode order

SORT_GERMAN_PHONE_BOOK           = 0x1     ; German Phone Book order

SORT_HUNGARIAN_DEFAULT           = 0x0     ; Hungarian Default order
SORT_HUNGARIAN_TECHNICAL         = 0x1     ; Hungarian Technical order

SORT_GEORGIAN_TRADITIONAL        = 0x0     ; Georgian Traditional order
SORT_GEORGIAN_MODERN             = 0x1     ; Georgian Modern order


; A language ID is a 16 bit value which is the combination of a
; primary language ID and a secondary language ID.  The bits are
; allocated as follows:
;
;      +-----------------------+-------------------------+
;      |     Sublanguage ID    |   Primary Language ID   |
;      +-----------------------+-------------------------+
;       15                   10 9                       0   bit


; Language ID creation/extraction macros:
;
;   MAKELANGID    - construct language id from a primary language id and
;                   a sublanguage id.
;   PRIMARYLANGID - extract primary language id from a language id.
;   SUBLANGID     - extract sublanguage id from a language id.

; #define MAKELANGID(p, s)       ((((WORD  )(s)) << 10) | (WORD  )(p))
; #define PRIMARYLANGID(lgid)    ((WORD  )(lgid) & 0x3ff)
; #define SUBLANGID(lgid)        ((WORD  )(lgid) >> 10)

; A locale ID is a 32 bit value which is the combination of a
; language ID, a sort ID, and a reserved area.  The bits are
; allocated as follows:
;
;      +-------------+---------+-------------------------+
;      |   Reserved  | Sort ID |      Language ID        |
;      +-------------+---------+-------------------------+
;       31         20 19     16 15                      0   bit
;
; Locale ID creation/extraction macros:
;
;   MAKELCID            - construct the locale id from a language id and a sort id.
;   MAKESORTLCID        - construct the locale id from a language id, sort id, and sort version.
;   LANGIDFROMLCID      - extract the language id from a locale id.
;   SORTIDFROMLCID      - extract the sort id from a locale id.
;   SORTVERSIONFROMLCID - extract the sort version from a locale id.

NLS_VALID_LOCALE_MASK  = 0x000fffff
;
; #define MAKELCID(lgid, srtid)  ((DWORD)((((DWORD)((WORD  )(srtid))) << 16) |
;                                          ((DWORD)((WORD  )(lgid)))))
; #define MAKESORTLCID(lgid, srtid, ver)                                            
;                                ((DWORD)((MAKELCID(lgid, srtid)) |             
;                                     (((DWORD)((WORD  )(ver))) << 20)))
; #define LANGIDFROMLCID(lcid)   ((WORD  )(lcid))
; #define SORTIDFROMLCID(lcid)   ((WORD  )((((DWORD)(lcid)) >> 16) & 0xf))
; #define SORTVERSIONFROMLCID(lcid)  ((WORD  )((((DWORD)(lcid)) >> 20) & 0xf))

; Default System and User IDs for language and locale.

; #define LANG_SYSTEM_DEFAULT    (MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT))
; #define LANG_USER_DEFAULT      (MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT))

; #define LOCALE_SYSTEM_DEFAULT  (MAKELCID(LANG_SYSTEM_DEFAULT, SORT_DEFAULT))
; #define LOCALE_USER_DEFAULT    (MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT))

; #define LOCALE_NEUTRAL   (MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SORT_DEFAULT))
; #define LOCALE_INVARIANT (MAKELCID(MAKELANGID(LANG_INVARIANT, SUBLANG_NEUTRAL), SORT_DEFAULT))

LANG_SYSTEM_DEFAULT   = LANG_NEUTRAL or (SUBLANG_SYS_DEFAULT shl 10)
LANG_USER_DEFAULT     = LANG_NEUTRAL or (SUBLANG_DEFAULT shl 10)

LOCALE_SYSTEM_DEFAULT = LANG_SYSTEM_DEFAULT or (SORT_DEFAULT shl 16)
LOCALE_USER_DEFAULT   = LANG_USER_DEFAULT or (SORT_DEFAULT shl 16)

LOCALE_NEUTRAL        = (LANG_NEUTRAL or (SUBLANG_NEUTRAL shl 10)) or (SORT_DEFAULT shl 16)
LOCALE_INVARIANT      = (LANG_INVARIANT or (SUBLANG_NEUTRAL shl 10)) or (SORT_DEFAULT shl 16)

; ------------------------------------------------------------------------------

