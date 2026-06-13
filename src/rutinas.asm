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

bits 64
default rel

;===============================================================
; rutinas_linux.asm
; FUNCIONES NASM 64 BITS — BitQuest  (Linux System V ABI)
;
; Convencion System V AMD64:
;   RDI = param 1,  RSI = param 2,  RDX = param 3,  RCX = param 4
;   R8  = param 5
;   RAX = retorno
;===============================================================

;===============================================================
; Funcion: detectar_objeto
; Detecta si un objeto especifico existe en una celda del mapa.
;
; Parametros desde C:
;   RDI       = direccion base del mapa
;   ESI       = numero de columnas
;   EDX       = fila a revisar
;   ECX       = columna a revisar
;   R8B       = caracter objeto a buscar (char)
;
; Retorno:
;   EAX = 1  objeto encontrado en la celda
;   EAX = 0  objeto no encontrado
;===============================================================

global detectar_objeto

section .text

detectar_objeto:
    push rbp
    mov rbp, rsp

    ; calcular indice = fila * columnas + columna
    mov eax, edx
    imul eax, esi
    add eax, ecx

    ; leer celda del mapa en ese indice
    mov r10b, byte [rdi + rax]

    ; comparar celda con el objeto buscado (R8B, ya en registro)
    cmp r10b, r8b
    je .objeto_encontrado

    xor eax, eax
    jmp .fin_detectar

.objeto_encontrado:
    mov eax, 1

.fin_detectar:
    mov rsp, rbp
    pop rbp
    ret

;===============================================================
; Funcion: contar_celdas_libres
; Cuenta cuantas celdas libres (.) existen en el mapa.
;
; Parametros desde C:
;   RDI = direccion base del mapa
;   ESI = total de celdas (3600)
;
; Retorno:
;   RAX = cantidad de celdas libres encontradas
;===============================================================

global contar_celdas_libres

section .text

contar_celdas_libres:
    push rbp
    mov rbp, rsp

    xor rax, rax        ; contador = 0
    xor ecx, ecx        ; indice = 0

.bucle_inicio:
    cmp ecx, esi        ; indice < total_celdas?
    jge .bucle_fin

    mov r10b, byte [rdi + rcx]  ; celda = mapa[indice]
    cmp r10b, '.'               ; es camino libre?
    jne .avanzar_indice

    inc rax             ; contador++

.avanzar_indice:
    inc ecx             ; indice++
    jmp .bucle_inicio

.bucle_fin:
    mov rsp, rbp
    pop rbp
    ret