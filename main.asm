;
; This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
; Aguilar Mena.
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, version 3.
;
; This program is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
; General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program. If not, see <http://www.gnu.org/licenses/>.
;

extern printf

extern square
extern cube
extern print
extern printstr

section .data
format: db "%d",9,"x^2=%2d x^3=%2d", 10, 0
mystring: db "my string"

section .text
    global main

main:
    push rbp                 ; set up stack frame
    mov	rbp, rsp
    ; First part
    mov ebx, 5               ; counter down
    mov r12, 0               ; counter up

    .L1:
        ; call square
        mov rdi, r12
        call square wrt ..plt
        mov r13, rax

        ; call cube
        mov rdi, r12
        call cube wrt ..plt

        ; printf
        mov rdi, format         ; address of format string
        mov rsi, r12            ; entero loop
        mov rdx, r13            ; valor r13 del cuadrado
        mov rcx, rax            ; valor del cubo

        call printf wrt ..plt

        inc r12
        dec rbx                 ; keep counting
        jne .L1

    ; Second part
    mov rbx, 6                  ; size
    mov rdi, rbx                ; primer argumento de la funcion
    pxor xmm0, xmm0

    .L2:
        sub rsp, 8
        cvtsi2sd xmm0, rbx
        movsd [rsp], xmm0

        dec rbx
        jne .L2

    mov rsi, rsp                ; puntero

    call print wrt ..plt

    ; Third Part
    mov rdi, mystring
    call printstr wrt ..plt

    mov rsp, rbp                ;
    pop rbp                     ; restore stack
    xor eax, eax
    ret
