bits 64
default rel

;===============
; rutinas.asm
; FUNCIONES NASM 64 BITS - MI PARTE (BETHOR15)
;
; contar_caracteres
; validar_movimiento
;
; Convencion Windows x64:
; RCX = parametro 1
; RDX = parametro 2
; R8  = parametro 3
; R9  = parametro 4
;===============

global contar_caracteres
global validar_movimiento

section .text

;FASE 1
; Funcion: contar_caracteres
; Sirve para contar cuantas veces aparece un caracter dentro del mapa.
;
; Parametros desde C:
; RCX = direccion base del mapa
; EDX = total de celdas
; R8B = caracter objetivo a contar
;
; Retorno:
; RAX = cantidad encontrada

contar_caracteres:
    push rbp
    mov rbp, rsp

    xor rax, rax
    xor r9d, r9d

.bucle_inicio:
    cmp r9d, edx
    jge .bucle_fin

    mov r10b, byte [rcx + r9]
    cmp r10b, r8b
    jne .avanzar_indice

    inc rax

.avanzar_indice:
    inc r9d
    jmp .bucle_inicio

.bucle_fin:
    mov rsp, rbp
    pop rbp
    ret


;FASE 2
; Funcion: validar_movimiento
; Revisa si el jugador puede moverse a una celda.
; Si la celda contiene '#', el movimiento se bloquea.
;
; Parametros desde C:
; RCX = direccion base del mapa
; EDX = numero de columnas
; R8D = nueva fila
; R9D = nueva columna
;
; Retorno:
; EAX = 1 movimiento valido
; EAX = 0 movimiento bloqueado

validar_movimiento:
    push rbp
    mov rbp, rsp

    ; validar fila negativa
    cmp r8d, 0
    jl .mov_bloqueado

    ; validar columna negativa
    cmp r9d, 0
    jl .mov_bloqueado

    ; validar limite de filas
    cmp r8d, 60
    jge .mov_bloqueado

    ; validar limite de columnas
    cmp r9d, edx
    jge .mov_bloqueado

    ; indice = fila * columnas + columna
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    ; leer celda del mapa
    mov r10b, byte [rcx + rax]

    ; si es pared, bloquear
    cmp r10b, '#'
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