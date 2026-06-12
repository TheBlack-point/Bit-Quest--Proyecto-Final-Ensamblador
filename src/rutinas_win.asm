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

;===============================================================
; Funcion: detectar_objeto
; Detecta si un objeto especifico existe en una celda del mapa.
;
; Parametros desde C:
;   RCX       = direccion base del mapa
;   EDX       = numero de columnas
;   R8D       = fila a revisar
;   R9D       = columna a revisar
;   [RSP+40]  = caracter objeto a buscar (char)
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

    ; leer el 5to parametro desde el stack
    ; +8 por el push rbp que desplazo RSP
    movsx r10d, byte [rsp+40]

    ; calcular indice = fila * columnas + columna
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    ; leer celda del mapa en ese indice
    mov r11b, byte [rcx + rax]

    ; comparar celda con el objeto buscado
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
; Cuenta cuantas celdas libres (.) existen en el mapa.
;
; Parametros desde C:
;   RCX = direccion base del mapa
;   EDX = total de celdas (3600)
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
    xor r9d, r9d        ; indice = 0

.bucle_inicio:
    cmp r9d, edx        ; indice < total_celdas?
    jge .bucle_fin

    mov r10b, byte [rcx + r9]   ; celda = mapa[indice]
    cmp r10b, '.'               ; es camino libre?
    jne .avanzar_indice

    inc rax             ; contador++

.avanzar_indice:
    inc r9d             ; indice++
    jmp .bucle_inicio

.bucle_fin:
    mov rsp, rbp
    pop rbp
    ret