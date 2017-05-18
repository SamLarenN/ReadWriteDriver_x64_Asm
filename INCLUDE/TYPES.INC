
; FASM SOURCE FILE
; http://flatassembler.net

; Data Types

; written by @L.CHEMIST (Andrey A. Meshkov)
; maalchemist@gmail.com
; maa-mail@yandex.ru

; ------------------------------------------------------------------------------

; Tomasz Grysztar

; macro typedef type, base
; { struc type [v] \{ \common . base v \}
;   macro type [v] \{ \common base v \} }

; typedef long, dd
; typedef DWORD, long

; macro typedef statement
; { match base type, statement
;   \{ struc type [v] \\{ \\common . base v \\}
;      macro type [v] \\{ \common base v \\} \} }

; typedef dd long
; typedef long DWORD

; ------------------------------------------------------------------------------

macro TYPEDEF type, base {
  restruc type
  purge type

  struc type [v] \{ \common . base v \}
  macro type [v] \{ \common base v \}

  virtual at 0
  local label, sizeof
    label type ?
    sizeof = $ - label
    sizeof.#type = sizeof
    SIZEOF.#type = sizeof
    SizeOf.#type = sizeof
  end virtual
}

macro _TYPEDEF_WIN64 TYPE, BASE64, BASE32 {
  TYPEDEF TYPE, BASE32
  match =TRUE, _WIN64 \{ TYPEDEF TYPE, BASE64 \}
}

macro TYPEDEF_WIN64 TYPE, BASE64, BASE32 {
  match =TRUE,  _WIN64 \{ TYPEDEF TYPE, BASE64 \}
  match =FALSE, _WIN64 \{ TYPEDEF TYPE, BASE32 \}
}

macro TYPEDEF_X64 TYPE, BASE64, BASE32 {
  match =TRUE,  _X64 \{ TYPEDEF TYPE, BASE64 \}
  match =FALSE, _X64 \{ TYPEDEF TYPE, BASE32 \}
}

macro _TYPEDEF_UNICODE TYPE, WBASE, ABASE {
  TYPEDEF TYPE, ABASE
  match =TRUE, UNICODE \{ TYPEDEF TYPE, WBASE \}
}

macro TYPEDEF_UNICODE TYPE, WBASE, ABASE {
  match =TRUE,  UNICODE \{ TYPEDEF TYPE, WBASE \}
  match =FALSE, UNICODE \{ TYPEDEF TYPE, ABASE \}
}

; ------------------------------------------------------------------------------

macro VIRTDEF vtype, type {
  virtual at 0
    vtype type ?
  end virtual
}

; ------------------------------------------------------------------------------

macro PADDING x64, x86 {
  match =TRUE,  _X64 \{ rept x64 \\{ db ? \\} \}
  match =FALSE, _X64 \{ rept x86 \\{ db ? \\} \}
}

; ------------------------------------------------------------------------------

TYPEDEF bool, db

TYPEDEF char, db
TYPEDEF signed_char, db
TYPEDEF unsigned_char, db

TYPEDEF __int8, db
TYPEDEF signed__int8, db
TYPEDEF unsigned__int8, db

TYPEDEF wchar_t, dw

TYPEDEF short, dw
TYPEDEF signed_short, dw
TYPEDEF unsigned_short, dw

TYPEDEF __int16, dw
TYPEDEF signed__int16, dw
TYPEDEF unsigned__int16, dw

TYPEDEF int, dd
TYPEDEF signed_int, dd
TYPEDEF unsigned_int, dd

TYPEDEF long, dd
TYPEDEF signed_long, dd
TYPEDEF unsigned_long, dd

TYPEDEF __int32, dd
TYPEDEF signed__int32, dd
TYPEDEF unsigned__int32, dd

TYPEDEF __int64, dq
TYPEDEF signed__int64, dq
TYPEDEF unsigned__int64, dq
TYPEDEF long_long, __int64

TYPEDEF float, dd
TYPEDEF double, dq
TYPEDEF long_double, double

TYPEDEF_WIN64 void, dq, dd

TYPEDEF_WIN64 size_t, unsigned__int64, unsigned_int

; ------------------------------------------------------------------------------

; Platform SDK: Windows API
; Windows Data Types

; ------------------------------------------------------------------------------

TYPEDEF BOOL, int
; Boolean variable (should be TRUE or FALSE).
; This type is declared in WinDef.h as follows:
; typedef int BOOL;

TYPEDEF BYTE, unsigned_char
; Byte (8 bits).
; This type is declared in WinDef.h as follows:
; typedef unsigned char BYTE;

TYPEDEF CHAR, char
; 8-bit Windows (ANSI) character.
; For more information, see <Character Sets Used By Fonts>.
; This type is declared in WinNT.h as follows:
; typedef char CHAR;

TYPEDEF DWORD, unsigned_long
; 32-bit unsigned integer.
; This type is declared in WinDef.h as follows:
; typedef unsigned long DWORD;
 
TYPEDEF DWORD32, unsigned_int
; 32-bit unsigned integer.
; This type is declared in BaseTsd.h as follows:
; typedef unsigned int DWORD32;
 
TYPEDEF DWORD64, unsigned__int64
; 64-bit unsigned integer.
; This type is declared in BaseTsd.h as follows:
; typedef unsigned __int64 DWORD64;
 
TYPEDEF FLOAT, float
; Floating-point variable.
; This type is declared in WinDef.h as follows:
; typedef float FLOAT;
 
TYPEDEF_WIN64 HALF_PTR, int, short
; Half the size of a pointer.
; Use within a structure that contains a pointer and two small fields.
; This type is declared in Basetsd.h as follows:
; #ifdef _WIN64
;  typedef int HALF_PTR;
; #else
;  typedef short HALF_PTR;
; #endif
 
TYPEDEF HFILE, int
; Handle to a file opened by OpenFile, not CreateFile.
; This type is declared in WinDef.h as follows:
; typedef int HFILE;
 
TYPEDEF INT, int
; 32-bit signed integer.
; This type is declared in WinDef.h as follows:
; typedef int INT;

TYPEDEF_WIN64 INT_PTR, __int64, int
; Signed integer type for pointer precision.
; Use when casting a pointer to an integer to perform pointer arithmetic.
; This type is declared in BaseTsd.h as follows:
; #if defined(_WIN64)
;  typedef __int64 INT_PTR;
; #else
;  typedef int INT_PTR;
; #endif
 
TYPEDEF INT32, signed_int
; 32-bit signed integer.
; This type is declared in BaseTsd.h as follows:
; typedef signed int INT32;
 
TYPEDEF INT64, signed__int64
; 64-bit signed integer.
; This type is declared in BaseTsd.h as follows:
; typedef signed __int64 INT64;
 
TYPEDEF LONG, long
; 32-bit signed integer.
; This type is declared in WinNT.h as follows:
; typedef long LONG;
 
TYPEDEF LONGLONG, __int64
; 64-bit signed integer.
; This type is declared in WinNT.h as follows:
; #if !defined(_M_IX86)
;  typedef __int64 LONGLONG;
; #else
;  typedef double LONGLONG;
; #endif

TYPEDEF_WIN64 LONG_PTR, __int64, long
; Signed long type for pointer precision.
; Use when casting a pointer to a long to perform pointer arithmetic.
; This type is declared in BaseTsd.h as follows:
; #if defined(_WIN64)
;  typedef __int64 LONG_PTR;
; #else
;  typedef long LONG_PTR;
; #endif
 
TYPEDEF LONG32, signed_int
; 32-bit signed integer.
; This type is declared in BaseTsd.h as follows:
; typedef signed int LONG32;
 
TYPEDEF LONG64, __int64
; 64-bit signed integer.
; This type is declared in BaseTsd.h as follows:
; typedef __int64 LONG64;
 
TYPEDEF PVOID, void
; Pointer to any type.
; This type is declared in WinNT.h as follows:
; typedef void *PVOID;
 
TYPEDEF SHORT, short
; Short integer (16 bits).
; This type is declared in WinNT.h as follows:
; typedef short SHORT;
 
TYPEDEF UCHAR, unsigned_char
; Unsigned CHAR.
; This type is declared in WinDef.h as follows:
; typedef unsigned char UCHAR;

TYPEDEF_WIN64 UHALF_PTR, unsigned_int, unsigned_short
; Unsigned HALF_PTR.
; Use within a structure that contains a pointer and two small fields.
; This type is declared in Basetsd.h as follows:
; #ifdef _WIN64
;  typedef unsigned int UHALF_PTR;
; #else
;  typedef unsigned short UHALF_PTR;
; #endif
 
TYPEDEF UINT, unsigned_int
; Unsigned INT.
; This type is declared in WinDef.h as follows:
; typedef unsigned int UINT;
 
TYPEDEF_WIN64 UINT_PTR, unsigned__int64, unsigned_int
; Unsigned INT_PTR.
; This type is declared in BaseTsd.h as follows:
; #if defined(_WIN64)
;  typedef unsigned __int64 UINT_PTR;
; #else
;  typedef unsigned int UINT_PTR;
; #endif
 
TYPEDEF UINT32, unsigned_int
; Unsigned INT32.
; This type is declared in BaseTsd.h as follows:
; typedef unsigned int UINT32;
 
TYPEDEF UINT64, unsigned__int64
; Unsigned INT64.
; This type is declared in BaseTsd.h as follows:
; typedef usigned __int64 UINT64;
 
TYPEDEF ULONG, unsigned_long
; Unsigned LONG.
; This type is declared in WinDef.h as follows:
; typedef unsigned long ULONG;
 
TYPEDEF ULONGLONG, unsigned__int64
; 64-bit unsigned integer.
; This type is declared in WinNT.h as follows:
; #if !defined(_M_IX86)
;  typedef unsigned __int64 ULONGLONG;
; #else
;  typedef double ULONGLONG
; #endif

TYPEDEF_WIN64 ULONG_PTR, unsigned__int64, unsigned_long
; Unsigned LONG_PTR.
; This type is declared in BaseTsd.h as follows:
; #if defined(_WIN64)
;  typedef unsigned __int64 ULONG_PTR;
; #else
;  typedef unsigned long ULONG_PTR;
; #endif
 
TYPEDEF ULONG32, unsigned_int
; Unsigned LONG32.
; This type is declared in BaseTsd.h as follows:
; typedef unsigned int ULONG32;
 
TYPEDEF ULONG64, unsigned__int64
; Unsigned LONG64.
; This type is declared in BaseTsd.h as follows:
; typedef unsigned __int64 ULONG64;
 
TYPEDEF USHORT, unsigned_short
; Unsigned SHORT.
; This type is declared in WinDef.h as follows:
; typedef unsigned short USHORT;
 
TYPEDEF WCHAR, wchar_t
; 16-bit Unicode character.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef wchar_t WCHAR;

; ????
; WINAPI
; Calling convention for system functions.
; This type is declared in WinDef.h as follows:
; #define WINAPI __stdcall
 
TYPEDEF WORD, unsigned_short
; 16-bit unsigned integer.
; This type is declared in WinDef.h as follows:
; typedef unsigned short WORD;

; ------------------------------------------------------------------------------

TYPEDEF HANDLE, PVOID
; Handle to an object.
; This type is declared in WinNT.h as follows:
; typedef PVOID HANDLE;
 
TYPEDEF HICON, HANDLE
; Handle to an icon.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HICON;
 
; ------------------------------------------------------------------------------

TYPEDEF ATOM, WORD
; Atom. For more information, see Atoms.
; This type is declared in WinDef.h as follows:
; typedef WORD ATOM;

TYPEDEF BOOLEAN, BYTE
; Boolean variable (should be TRUE or FALSE).
; This type is declared in WinNT.h as follows:
; typedef BYTE BOOLEAN;

; ????
; CALLBACK
; Calling convention for callback functions.
; This type is declared in WinDef.h as follows:
; #define CALLBACK __stdcall

TYPEDEF COLORREF, DWORD
; Red, green, blue (RGB) color value (32 bits).
; See <COLORREF> for information on this type.
; This type is declared in WinDef.h as follows:
; typedef DWORD COLORREF;

; ????
; CONST
; Variable whose value is to remain constant during execution.
; This type is declared in WinDef.h as follows:
; #define CONST const
 
TYPEDEF DWORDLONG, ULONGLONG
; 64-bit unsigned integer.
; This type is declared in WinNT.h as follows:
; typedef ULONGLONG DWORDLONG;
 
TYPEDEF DWORD_PTR, ULONG_PTR
; Unsigned long type for pointer precision.
; Use when casting a pointer to a long type to perform pointer arithmetic.
; (Also commonly used for general 32-bit parameters that have been extended to 64 bits in 64-bit Windows.)
; This type is declared in BaseTsd.h as follows:
; typedef ULONG_PTR DWORD_PTR;
 
TYPEDEF HACCEL, HANDLE
; Handle to an accelerator table.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HACCEL;

TYPEDEF HBITMAP, HANDLE
; Handle to a bitmap.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HBITMAP;
 
TYPEDEF HBRUSH, HANDLE
; Handle to a brush.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HBRUSH;
 
TYPEDEF HCOLORSPACE, HANDLE
; Handle to a color space.
; This type is declared in WinDef.h as follows:
; #if(WINVER >= 0x0400)
;  typedef HANDLE HCOLORSPACE;
; #endif
 
TYPEDEF HCONV, HANDLE
; Handle to a dynamic data exchange (DDE) conversation.
; This type is declared in Ddeml.h as follows:
; typedef HANDLE HCONV;
 
TYPEDEF HCONVLIST, HANDLE
; Handle to a DDE conversation list.
; This type is declared in Ddeml.h as follows:
; typedef HANDLE HCONVLIST;
 
TYPEDEF HCURSOR, HICON
; Handle to a cursor.
; This type is declared in WinDef.h as follows:
; typedef HICON HCURSOR;
 
TYPEDEF HDC, HANDLE
; Handle to a device context (DC).
; This type is declared in WinDef.h as follows:
; typedef HANDLE HDC;
 
TYPEDEF HDDEDATA, HANDLE
; Handle to DDE data.
; This type is declared in Ddeml.h as follows:
; typedef HANDLE HDDEDATA;
 
TYPEDEF HDESK, HANDLE
; Handle to a desktop.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HDESK;
 
TYPEDEF HDROP, HANDLE
; Handle to an internal drop structure.
; This type is declared in ShellApi.h as follows:
; typedef HANDLE HDROP;
 
TYPEDEF HDWP, HANDLE
; Handle to a deferred window position structure.
; This type is declared in WinUser.h as follows:
; typedef HANDLE HDWP;
 
TYPEDEF HENHMETAFILE, HANDLE
; Handle to an enhanced metafile.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HENHMETAFILE;
 
TYPEDEF HFONT, HANDLE
; Handle to a font.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HFONT;
 
TYPEDEF HGDIOBJ, HANDLE
; Handle to a GDI object.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HGDIOBJ;
 
TYPEDEF HGLOBAL, HANDLE
; Handle to a global memory block.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HGLOBAL;
 
TYPEDEF HHOOK, HANDLE
; Handle to a hook.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HHOOK;
 
TYPEDEF HINSTANCE, HANDLE
; Handle to an instance.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HINSTANCE;
 
TYPEDEF HKEY, HANDLE
; Handle to a registry key.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HKEY;
 
TYPEDEF HKL, HANDLE
; Input locale identifier.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HKL;
 
TYPEDEF HLOCAL, HANDLE
; Handle to a local memory block.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HLOCAL;
 
TYPEDEF HMENU, HANDLE
; Handle to a menu.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HMENU;
 
TYPEDEF HMETAFILE, HANDLE
; Handle to a metafile.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HMETAFILE;
 
TYPEDEF HMODULE, HINSTANCE
; Handle to a module. The value is the base address of the module.
; This type is declared in WinDef.h as follows:
; typedef HINSTANCE HMODULE;
 
TYPEDEF HMONITOR, HANDLE
; Handle to a display monitor.
; This type is declared in WinDef.h as follows:
; if(WINVER >= 0x0500) typedef HANDLE HMONITOR;
 
TYPEDEF HPALETTE, HANDLE
; Handle to a palette.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HPALETTE;
 
TYPEDEF HPEN, HANDLE
; Handle to a pen.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HPEN;
 
TYPEDEF HRESULT, LONG
; Return code used by interfaces. It is zero upon success and nonzero to represent an error code or status information.
; This type is declared in WinNT.h as follows:
; typedef LONG HRESULT;
 
TYPEDEF HRGN, HANDLE
; Handle to a region.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HRGN;
 
TYPEDEF HRSRC, HANDLE
; Handle to a resource.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HRSRC;
 
TYPEDEF HSZ, HANDLE
; Handle to a DDE string.
; This type is declared in Ddeml.h as follows:
; typedef HANDLE HSZ;
 
TYPEDEF HWINSTA, HANDLE
; Handle to a window station.
; This type is declared in WinDef.h as follows:
; typedef HANDLE WINSTA;
 
TYPEDEF HWND, HANDLE
; Handle to a window.
; This type is declared in WinDef.h as follows:
; typedef HANDLE HWND;
 
TYPEDEF LANGID, WORD
; Language identifier. For more information, see Locales.
; This type is declared in WinNT.h as follows:
; typedef WORD LANGID;
 
TYPEDEF LCID, DWORD
; Locale identifier. For more information, see Locales.
; This type is declared in WinNT.h as follows:
; typedef DWORD LCID;
 
TYPEDEF LCTYPE, DWORD
; Locale information type.
; For a list, see Locale and Language Information.
; This type is declared in WinNls.h as follows:
; typedef DWORD LCTYPE;
 
TYPEDEF LGRPID, DWORD
; Language group identifier.
; For a list, see EnumLanguageGroupLocales.
; This type is declared in WinNls.h as follows:
; typedef DWORD LGRPID;
 
TYPEDEF LPARAM, LONG_PTR
; Message parameter.
; This type is declared in WinDef.h as follows:
; typedef LONG_PTR LPARAM;
 
TYPEDEF LPBOOL, PVOID
; Pointer to a BOOL.
; This type is declared in WinDef.h as follows:
; typedef BOOL far *LPBOOL;
 
TYPEDEF LPBYTE, PVOID
; Pointer to a BYTE.
; This type is declared in WinDef.h as follows:
; typedef BYTE far *LPBYTE;
 
TYPEDEF LPCOLORREF, PVOID
; Pointer to a COLORREF value.
; This type is declared in WinDef.h as follows:
; typedef DWORD *LPCOLORREF;
 
TYPEDEF LPCSTR, PVOID
; Pointer to a constant null-terminated string of 8-bit Windows (ANSI) characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef __nullterminated CONST CHAR *LPCSTR;

TYPEDEF_UNICODE LPCTSTR, LPCWSTR, LPCSTR
; An LPCWSTR if UNICODE is defined, an LPCSTR otherwise.
; This type is declared in WinNT.h as follows:
; #ifdef UNICODE
;  typedef LPCWSTR LPCTSTR;
; #else
;  typedef LPCSTR LPCTSTR;
; #endif
 
TYPEDEF LPCVOID, PVOID
; Pointer to a constant of any type.
; This type is declared in WinDef.h as follows:
; typedef CONST void *LPCVOID;
 
TYPEDEF LPCWSTR, PVOID
; Pointer to a constant null-terminated string of 16-bit Unicode characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef CONST WCHAR *LPCWSTR;
 
TYPEDEF LPDWORD, PVOID
; Pointer to a DWORD.
; This type is declared in WinDef.h as follows:
; typedef DWORD *LPDWORD;
 
TYPEDEF LPHANDLE, PVOID
; Pointer to a HANDLE.
; This type is declared in WinDef.h as follows:
; typedef HANDLE *LPHANDLE;
 
TYPEDEF LPINT, PVOID
; Pointer to an INT.
; This type is declared in WinDef.h as follows:
; typedef int *LPINT;
 
TYPEDEF LPLONG, PVOID
; Pointer to a LONG.
; This type is declared in WinDef.h as follows:
; typedef long *LPLONG;
 
TYPEDEF LPSTR, PVOID
; Pointer to a null-terminated string of 8-bit Windows (ANSI) characters. For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef CHAR *LPSTR;

TYPEDEF_UNICODE LPTSTR, LPWSTR, LPSTR
; An LPWSTR if UNICODE is defined, an LPSTR otherwise.
; This type is declared in WinNT.h as follows:
; #ifdef UNICODE
;  typedef LPWSTR LPTSTR;
; #else
;  typedef LPSTR LPTSTR;
; #endif
 
TYPEDEF LPVOID, PVOID
; Pointer to any type.
; This type is declared in WinDef.h as follows:
; typedef void *LPVOID;
 
TYPEDEF LPWORD, PVOID
; Pointer to a WORD.
; This type is declared in WinDef.h as follows:
; typedef WORD *LPWORD;
 
TYPEDEF LPWSTR, PVOID
; Pointer to a null-terminated string of 16-bit Unicode characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef WCHAR *LPWSTR;
 
TYPEDEF LRESULT, LONG_PTR
; Signed result of message processing.
; This type is declared in WinDef.h as follows:
; typedef LONG_PTR LRESULT;
 
TYPEDEF PBOOL, PVOID
; Pointer to a BOOL.
; This type is declared in WinDef.h as follows:
; typedef BOOL *PBOOL;
 
TYPEDEF PBOOLEAN, PVOID
; Pointer to a BOOL.
; This type is declared in WinNT.h as follows:
; typedef BOOLEAN *PBOOLEAN;
 
TYPEDEF PBYTE, PVOID
; Pointer to a BYTE.
; This type is declared in WinDef.h as follows:
; typedef BYTE *PBYTE;
 
TYPEDEF PCHAR, PVOID
; Pointer to a CHAR.
; This type is declared in WinNT.h as follows:
; typedef CHAR *PCHAR;
 
TYPEDEF PCSTR, PVOID
; Pointer to a constant null-terminated string of 8-bit Windows (ANSI) characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef CONST CHAR *PCSTR;
 
TYPEDEF_UNICODE PCTSTR, LPCWSTR, LPCSTR
; A PCWSTR if UNICODE is defined, a PCSTR otherwise.
; This type is declared in WinNT.h as follows:
; #ifdef UNICODE
;  typedef LPCWSTR PCTSTR;
; #else
;  typedef LPCSTR PCTSTR;
; #endif
 
TYPEDEF PCWSTR, PVOID
; Pointer to a constant null-terminated string of 16-bit Unicode characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef CONST WCHAR *PCWSTR;
 
TYPEDEF PDWORD, PVOID
; Pointer to a DWORD.
; This type is declared in WinDef.h as follows:
; typedef DWORD *PDWORD;
 
TYPEDEF PDWORDLONG, PVOID
; Pointer to a DWORDLONG.
; This type is declared in WinNT.h as follows:
; typedef DWORDLONG *PDWORDLONG;
 
TYPEDEF PDWORD_PTR, PVOID
; Pointer to a DWORD_PTR.
; This type is declared in BaseTsd.h as follows:
; typedef DWORD_PTR *PDWORD_PTR;
 
TYPEDEF PDWORD32, PVOID
; Pointer to a DWORD32.
; This type is declared in BaseTsd.h as follows:
; typedef DWORD32 *PDWORD32;
 
TYPEDEF PDWORD64, PVOID
; Pointer to a DWORD64.
; This type is declared in BaseTsd.h as follows:
; typedef DWORD64 *PDWORD64;
 
TYPEDEF PFLOAT, PVOID
; Pointer to a FLOAT.
; This type is declared in WinDef.h as follows:
; typedef FLOAT *PFLOAT;

TYPEDEF_WIN64 PHALF_PTR, PVOID, PVOID
; Pointer to a HALF_PTR.
; This type is declared in Basetsd.h as follows:
; #ifdef _WIN64
;  typedef HALF_PTR *PHALF_PTR;
; #else
;  typedef HALF_PTR *PHALF_PTR;
; #endif
 
TYPEDEF PHANDLE, PVOID
; Pointer to a HANDLE.
; This type is declared in WinNT.h as follows:
; typedef HANDLE *PHANDLE;
 
TYPEDEF PHKEY, PVOID
; Pointer to an HKEY.
; This type is declared in WinDef.h as follows:
; typedef HKEY *PHKEY;
 
TYPEDEF PINT, PVOID
; Pointer to an INT.
; This type is declared in WinDef.h as follows:
; typedef int *PINT;
 
TYPEDEF PINT_PTR, PVOID
; Pointer to an INT_PTR.
; This type is declared in BaseTsd.h as follows:
; typedef INT_PTR *PINT_PTR;
 
TYPEDEF PINT32, PVOID
; Pointer to an INT32.
; This type is declared in BaseTsd.h as follows:
; typedef INT32 *PINT32;
 
TYPEDEF PINT64, PVOID
; Pointer to an INT64.
; This type is declared in BaseTsd.h as follows:
; typedef INT64 *PINT64;
 
TYPEDEF PLCID, PVOID
; Pointer to an LCID.
; This type is declared in WinNT.h as follows:
; typedef PDWORD PLCID;
 
TYPEDEF PLONG, PVOID
; Pointer to a LONG.
; This type is declared in WinNT.h as follows:
; typedef LONG *PLONG;
 
TYPEDEF PLONGLONG, PVOID
; Pointer to a LONGLONG.
; This type is declared in WinNT.h as follows:
; typedef LONGLONG *PLONGLONG;
 
TYPEDEF PLONG_PTR, PVOID
; Pointer to a LONG_PTR.
; This type is declared in BaseTsd.h as follows:
; typedef LONG_PTR *PLONG_PTR;
 
TYPEDEF PLONG32, PVOID
; Pointer to a LONG32.
; This type is declared in BaseTsd.h as follows:
; typedef LONG32 *PLONG32;
 
TYPEDEF PLONG64, PVOID
; Pointer to a LONG64.
; This type is declared in BaseTsd.h as follows:
; typedef LONG64 *PLONG64;

; ????
; POINTER_32
; 32-bit pointer.
; On a 32-bit system, this is a native pointer.
; On a 64-bit system, this is a truncated 64-bit pointer.
; This type is declared in BaseTsd.h as follows:
; #if defined(_WIN64)
; #define POINTER_32 __ptr32
; #else
; #define POINTER32
; #endif

; ????
; POINTER_64
; 64-bit pointer.
; On a 64-bit system, this is a native pointer.
; On a 32-bit system, this is a sign-extended 32-bit pointer.
; Note that it is not safe to assume the state of the high pointer bit.
; This type is declared in BaseTsd.h as follows:
; #define POINTER_64 __ptr64
 
TYPEDEF PSHORT, PVOID
; Pointer to a SHORT.
; This type is declared in WinNT.h as follows:
; typedef SHORT *PSHORT;
 
TYPEDEF PSIZE_T, PVOID
; Pointer to a SIZE_T.
; This type is declared in BaseTsd.h as follows:
; typedef SIZE_T *PSIZE_T;
 
TYPEDEF PSSIZE_T, PVOID
; Pointer to a SSIZE_T.
; This type is declared in BaseTsd.h as follows:
; typedef SSIZE_T *PSSIZE_T;
 
TYPEDEF PSTR, PVOID
; Pointer to a null-terminated string of 8-bit Windows (ANSI) characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef CHAR *PSTR;
 
TYPEDEF PTBYTE, PVOID
; Pointer to a TBYTE.
; This type is declared in WinNT.h as follows:
; typedef TBYTE *PTBYTE;
 
TYPEDEF PTCHAR, PVOID
; Pointer to a TCHAR.
; This type is declared in WinNT.h as follows:
; typedef TCHAR *PTCHAR;
 
TYPEDEF_UNICODE PTSTR, LPWSTR, LPSTR
; A PWSTR if UNICODE is defined, a PSTR otherwise.
; This type is declared in WinNT.h as follows:
; #ifdef UNICODE
;  typedef LPWSTR PTSTR;
; #else
;  typedef LPSTR PTSTR;
; #endif
 
TYPEDEF PUCHAR, PVOID
; Pointer to a UCHAR.
; This type is declared in WinDef.h as follows:
; typedef UCHAR *PUCHAR;

TYPEDEF_WIN64 PUHALF_PTR, PVOID, PVOID
; Pointer to a UHALF_PTR.
; This type is declared in Basetsd.h as follows:
; #ifdef _WIN64
;  typedef UHALF_PTR *PUHALF_PTR;
; #else
;  typedef UHALF_PTR *PUHALF_PTR;
; #endif
 
TYPEDEF PUINT, PVOID
; Pointer to a UINT.
; This type is declared in WinDef.h as follows:
; typedef UINT *PUINT;
 
TYPEDEF PUINT_PTR, PVOID
; Pointer to a UINT_PTR.
; This type is declared in BaseTsd.h as follows:
; typedef UINT_PTR *PUINT_PTR;
 
TYPEDEF PUINT32, PVOID
; Pointer to a UINT32.
; This type is declared in BaseTsd.h as follows:
; typedef UINT32 *PUINT32;
 
TYPEDEF PUINT64, PVOID
; Pointer to a UINT64.
; This type is declared in BaseTsd.h as follows:
; typedef UINT64 *PUINT64;
 
TYPEDEF PULONG, PVOID
; Pointer to a ULONG.
; This type is declared in WinDef.h as follows:
; typedef ULONG *PULONG;
 
TYPEDEF PULONGLONG, PVOID
; Pointer to a ULONGLONG.
; This type is declared in WinDef.h as follows:
; typedef ULONGLONG *PULONGLONG;
 
TYPEDEF PULONG_PTR, PVOID
; Pointer to a ULONG_PTR.
; This type is declared in BaseTsd.h as follows:
; typedef ULONG_PTR *PULONG_PTR;
 
TYPEDEF PULONG32, PVOID
; Pointer to a ULONG32.
; This type is declared in BaseTsd.h as follows:
; typedef ULONG32 *PULONG32;
 
TYPEDEF PULONG64, PVOID
; Pointer to a ULONG64.
; This type is declared in BaseTsd.h as follows:
; typedef ULONG64 *PULONG64;
 
TYPEDEF PUSHORT, PVOID
; Pointer to a USHORT.
; This type is declared in WinDef.h as follows:
; typedef USHORT *PUSHORT;
 
TYPEDEF PWCHAR, PVOID
; Pointer to a WCHAR.
; This type is declared in WinNT.h as follows:
; typedef WCHAR *PWCHAR;
 
TYPEDEF PWORD, PVOID
; Pointer to a WORD.
; This type is declared in WinDef.h as follows:
; typedef WORD *PWORD;
 
TYPEDEF PWSTR, PVOID
; Pointer to a null- terminated string of 16-bit Unicode characters.
; For more information, see Character Sets Used By Fonts.
; This type is declared in WinNT.h as follows:
; typedef WCHAR *PWSTR;
 
TYPEDEF SC_HANDLE, HANDLE
; Handle to a service control manager database.
; For more information, see SCM Handles.
; This type is declared in WinSvc.h as follows:
; typedef HANDLE SC_HANDLE;
 
TYPEDEF SC_LOCK, LPVOID
; Lock to a service control manager database.
; For more information, see SCM Handles.
; This type is declared in WinSvc.h as follows:
; typedef LPVOID SC_LOCK;
 
TYPEDEF SERVICE_STATUS_HANDLE, HANDLE
; Handle to a service status value. For more information, see SCM Handles.
; This type is declared in WinSvc.h as follows:
; typedef HANDLE SERVICE_STATUS_HANDLE;
 
TYPEDEF SIZE_T, ULONG_PTR
; The maximum number of bytes to which a pointer can point.
; Use for a count that must span the full range of a pointer.
; This type is declared in BaseTsd.h as follows:
; typedef ULONG_PTR SIZE_T;
 
TYPEDEF SSIZE_T, LONG_PTR
; Signed SIZE_T.
; This type is declared in BaseTsd.h as follows:
; typedef LONG_PTR SSIZE_T;

TYPEDEF_UNICODE TBYTE, WCHAR, CHAR
; A WCHAR if UNICODE is defined, a CHAR otherwise.
; This type is declared in WinNT.h as follows:
; #ifdef UNICODE
;  typedef WCHAR TBYTE;
; #else
;  typedef unsigned char TBYTE;
; #endif
 
TYPEDEF_UNICODE TCHAR, WCHAR, CHAR
; A WCHAR if UNICODE is defined, a CHAR otherwise.
; This type is declared in WinNT.h as follows:
; #ifdef UNICODE
;  typedef WCHAR TCHAR;
; #else
;  typedef char TCHAR;
; #endif
 
TYPEDEF USN, LONGLONG
; Update sequence number (USN).
; This type is declared in WinNT.h as follows:
; typedef LONGLONG USN;

; ????
; VOID
; Any type.
; This type is declared in WinNT.h as follows:
; #define VOID void
 
TYPEDEF WPARAM, UINT_PTR
; Message parameter.
; This type is declared in WinDef.h as follows:
; typedef UINT_PTR WPARAM;

; ------------------------------------------------------------------------------

; //
; // Thread affinity.
; //

; typedef ULONG_PTR KAFFINITY;
; typedef KAFFINITY *PKAFFINITY;

TYPEDEF KAFFINITY, ULONG_PTR
TYPEDEF PKAFFINITY, PVOID

; ------------------------------------------------------------------------------

TYPEDEF_WIN64 enum, dq, dd

TYPEDEF QWORD, dq

TYPEDEF POINTER, PVOID
TYPEDEF PPCHAR, PVOID

; TYPEDEF_WIN64 REG_A, dq, dd
; TYPEDEF_WIN64 REG_B, dq, dd
; TYPEDEF_WIN64 REG_C, dq, dd
; TYPEDEF_WIN64 REG_D, dq, dd
; TYPEDEF_WIN64 REG_BP, dq, dd
; TYPEDEF_WIN64 REG_SP, dq, dd
; TYPEDEF_WIN64 REG_SI, dq, dd
; TYPEDEF_WIN64 REG_DI, dq, dd

TYPEDEF_WIN64 T_CPU_REG, dq, dd
TYPEDEF_WIN64 T_BUFFER_SIZE, dq, dd

TYPEDEF_WIN64 T_PRINTF_ARG, dq, dd

TYPEDEF T_8BIT, db
TYPEDEF P_8BIT, PVOID

TYPEDEF T_16BIT, dw
TYPEDEF P_16BIT, PVOID

TYPEDEF T_32BIT, dd
TYPEDEF P_32BIT, PVOID

TYPEDEF T_64BIT, dq
TYPEDEF P_64BIT, PVOID

; ------------------------------------------------------------------------------
