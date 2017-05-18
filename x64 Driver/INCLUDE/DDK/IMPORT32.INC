
; FASM SOURCE FILE
; http://flatassembler.net

; modified by @L.CHEMIST (Andrey A. Meshkov)
; maalchemist@gmail.com
; maa-mail@yandex.ru

; ------------------------------------------------------------------------------

; Macroinstructions for making import section (32-bit)

macro library [name,string]
 { forward
    local _label
    if defined name#.redundant
     if ~ name#.redundant
      dd RVA name#.lookup,0,0,RVA _label,RVA name#.address
     end if
    end if
    name#.referred = 1
   common
    dd 0,0,0,0,0
   forward
    if defined name#.redundant
     if ~ name#.redundant
      _label db string,0
             rb RVA $ and 1
     end if
    end if }

macro import name,[label,string]
 { common
    if defined name#.referred
     name#.lookup:
   forward
     if used label
      if string eqtype ''
       local _label
       dd RVA _label
      else
       dd 80000000h + string
      end if
     end if
   common
     if $ > name#.lookup
      name#.redundant = 0
      dd 0
     else
      name#.redundant = 1
     end if
     if ~ defined name#.IAT           ; @L.CHEMIST
     name#.address:
     end if                           ; @L.CHEMIST
   forward
     if used label
      if ~ defined name#.IAT          ; @L.CHEMIST
      if string eqtype ''
       label dd RVA _label
      else
       label dd 80000000h + string
      end if
      end if                          ; @L.CHEMIST
     end if
   common
     if ~ name#.redundant
      dd 0
     end if
   forward
     if used label & string eqtype ''
     name#.#label:                    ; @L.CHEMIST
     _label dw 0
            db string,0
            rb RVA $ and 1
     end if
   common
    end if }

macro api [name] {}

; Import Address Table                ; @L.CHEMIST
macro IAT name,[label]
 { common
    data 12
    name#.IAT:
    name#.address:
   forward
    if used label
     label dd RVA name#.#label
    end if
   common
    dd 0
    end data }
