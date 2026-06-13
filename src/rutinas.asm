bits 64
default rel

;===============
; rutinas.asm
; FUNCIONES NASM 64 BITS - MI PARTE (BETHOR15)
;
; contar_caracteres
; validar_movimiento
;
; Convencion Linux x64 / System V AMD64:
; RDI = parametro 1
; RSI = parametro 2
; RDX = parametro 3
; RCX = parametro 4
; R8  = parametro 5
; R9  = parametro 6
;===============

global contar_caracteres
global validar_movimiento

section .text

;FASE 1
; Funcion: contar_caracteres
;
; Parametros desde C:
; RDI = direccion base del mapa
; RSI = total de celdas
; DL  = caracter objetivo a contar
;
; Retorno:
; RAX = cantidad encontrada

contar_caracteres:
    push rbp
    mov rbp, rsp

    xor rax, rax        ; contador = 0
    xor r8, r8          ; indice = 0

.bucle_inicio:
    cmp r8, rsi
    jge .bucle_fin

    mov r9b, byte [rdi + r8]
    cmp r9b, dl
    jne .avanzar_indice

    inc rax

.avanzar_indice:
    inc r8
    jmp .bucle_inicio

.bucle_fin:
    mov rsp, rbp
    pop rbp
    ret


;FASE 2
; Funcion: validar_movimiento
;
; Parametros desde C:
; RDI = direccion base del mapa
; RSI = numero de columnas
; RDX = nueva fila
; RCX = nueva columna
;
; Retorno:
; EAX = 1 movimiento valido
; EAX = 0 movimiento bloqueado

validar_movimiento:
    push rbp
    mov rbp, rsp

    ; validar fila negativa
    cmp rdx, 0
    jl .mov_bloqueado

    ; validar columna negativa
    cmp rcx, 0
    jl .mov_bloqueado

    ; validar limite de filas
    cmp rdx, 60
    jge .mov_bloqueado

    ; validar limite de columnas
    cmp rcx, rsi
    jge .mov_bloqueado

    ; indice = fila * columnas + columna
    mov r8, rdx
    imul r8, rsi
    add r8, rcx

    ; leer celda del mapa
    mov r9b, byte [rdi + r8]

    ; si es pared, bloquear
    cmp r9b, '#'
    je .mov_bloqueado

    ; si no es pared, permitir movimiento
    mov eax, 1
    jmp .fin_validar

.mov_bloqueado:
    xor eax, eax

.fin_validar:
    mov rsp, rbp
    pop rbp
    ret