bits 64
default rel

;===============================================================
; rutinas_win.asm
; FUNCIONES NASM 64 BITS — BitQuest  (Windows x64 ABI)
;
; Convencion Microsoft x64:
;   RCX = param 1,  RDX = param 2,  R8 = param 3,  R9 = param 4
;   5to param y siguientes en stack: [RSP+32], [RSP+40], ...
;   RAX = retorno
;   Shadow space de 32 bytes reservado por el caller antes del call
;===============================================================