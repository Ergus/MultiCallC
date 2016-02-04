extern printf
        
extern square
extern cube
extern print
        
global main

section .data
format: db "%d",9,"x^2=%2d x^3=%2d", 10, 0
        
section .text
main:
    push rbp                 ; set up stack frame
    mov	rbp, rsp
    ; First part
    mov ebx, 5               ; counter down
    mov r12, 0               ; counter up
        
    L1:
        ; call square
        mov rdi, r12
        call square
        mov r13, rax
        
        ; call cube
        mov rdi, r12
        call cube

        ; printf
        mov rdi, format         ; address of format string
        mov rsi, r12            ; entero loop
        mov rdx, r13            ; valor r13 del cuadrado
        mov rcx, rax            ; valor del cubo

        call printf
        
        inc r12
        dec rbx                 ; keep counting
        jne L1  

    ; Second part
    mov rbx, 6                  ; size
    mov rdi, rbx                ; primer argumento de la funcion
    pxor xmm0, xmm0             
        
    L2:
        sub rsp, 8
        cvtsi2sd xmm0, rbx
        movsd [rsp], xmm0
        
        dec rbx
        jne L2

    mov rsi, rsp                ; puntero 

    call print
        
    mov rsp, rbp                ; 
    pop rbp                     ; restore stack
    xor eax, eax
    ret
