
; FASM SOURCE FILE
; http://flatassembler.net

; written by @L.CHEMIST (Andrey A. Meshkov)
; maalchemist@gmail.com
; maa-mail@yandex.ru

; 32-BIT -----------------------------------------------------------------------

; procall FIX stdcall

; 64-BIT -----------------------------------------------------------------------

; additional STACK FRAME for x64 [E]xternal [P]rocedure [C]alls
  STACK_FRAME_x64_EPC = 0x0100 ; 256B = 8B * 32

; additional STACK FRAME for x64 [L]ocal [P]rocedure [C]alls
  STACK_FRAME_x64_LPC = 0x0100 ; 256B = 8B * 32

  purge invoke
  macro invoke proc, [arg] {
    common
      sub      rsp, STACK_FRAME_x64_EPC
      fastcall [proc], arg
      add      rsp, STACK_FRAME_x64_EPC
  }

  purge procall
  macro procall proc, [arg] {
    common
;     sub      rsp, STACK_FRAME_x64_LPC
      fastcall proc, arg
;     add      rsp, STACK_FRAME_x64_LPC
  }

  cinvoke FIX invoke

; ------------------------------------------------------------------------------
