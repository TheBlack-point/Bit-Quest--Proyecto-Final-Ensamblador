bits 64
default rel

;===============================================================
; rutinas_win.asm
; FUNCIONES NASM 64 BITS — BitQuest (Windows x64 ABI)
;
; Convencion Microsoft x64:
;   RCX = param 1
;   RDX = param 2
;   R8  = param 3
;   R9  = param 4
;   5to parametro en stack
;   RAX = retorno
;===============================================================

global contar_caracteres
global validar_movimiento
global detectar_objeto
global contar_celdas_libres

section .text

;===============================================================
; Funcion: contar_caracteres
;
; RCX = direccion base del mapa
; EDX = total de celdas
; R8B = caracter objetivo a contar
;
; Retorno:
; RAX = cantidad encontrada
;===============================================================

contar_caracteres:
    push rbp
    mov rbp, rsp

    xor rax, rax
    xor r9d, r9d

.bucle_contar:
    cmp r9d, edx
    jge .fin_contar

    mov r10b, byte [rcx + r9]
    cmp r10b, r8b
    jne .avanzar_contar

    inc rax

.avanzar_contar:
    inc r9d
    jmp .bucle_contar

.fin_contar:
    mov rsp, rbp
    pop rbp
    ret


;===============================================================
; Funcion: validar_movimiento
;
; RCX = direccion base del mapa
; EDX = numero de columnas
; R8D = nueva fila
; R9D = nueva columna
;
; Retorno:
; EAX = 1 movimiento valido
; EAX = 0 movimiento bloqueado
;===============================================================

validar_movimiento:
    push rbp
    mov rbp, rsp

    cmp r8d, 0
    jl .mov_bloqueado

    cmp r9d, 0
    jl .mov_bloqueado

    cmp r8d, 60
    jge .mov_bloqueado

    cmp r9d, edx
    jge .mov_bloqueado

    mov eax, r8d
    imul eax, edx
    add eax, r9d

    mov r10b, byte [rcx + rax]

    cmp r10b, '#'
    je .mov_bloqueado

    mov eax, 1
    jmp .fin_validar

.mov_bloqueado:
    xor eax, eax

.fin_validar:
    mov rsp, rbp
    pop rbp
    ret


;===============================================================
; Funcion: detectar_objeto
;
; RCX       = direccion base del mapa
; EDX       = numero de columnas
; R8D       = fila a revisar
; R9D       = columna a revisar
; [RBP+48]  = caracter objeto a buscar
;
; Retorno:
; EAX = 1 objeto encontrado
; EAX = 0 objeto no encontrado
;===============================================================

detectar_objeto:
    push rbp
    mov rbp, rsp

    ; En Windows x64, despues de push rbp:
    ; return address = [rbp+8]
    ; shadow space   = [rbp+16] a [rbp+40]
    ; 5to parametro  = [rbp+48]
    mov r10b, byte [rbp+48]

    mov eax, r8d
    imul eax, edx
    add eax, r9d

    mov r11b, byte [rcx + rax]

    cmp r11b, r10b
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
;
; RCX = direccion base del mapa
; EDX = total de celdas
;
; Retorno:
; RAX = cantidad de celdas libres '.'
;===============================================================

contar_celdas_libres:
    push rbp
    mov rbp, rsp

    xor rax, rax
    xor r9d, r9d

.bucle_libres:
    cmp r9d, edx
    jge .fin_libres

    mov r10b, byte [rcx + r9]
    cmp r10b, '.'
    jne .avanzar_libres

    inc rax

.avanzar_libres:
    inc r9d
    jmp .bucle_libres

.fin_libres:
    mov rsp, rbp
    pop rbp
    ret