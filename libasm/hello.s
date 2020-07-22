section .text
    global _hello_world

_hello_world :
    mov rax, 0x2000004
    mov rdi, 1
    mov rsi, message
    mov rdx, 13
    syscall
    mov rax, 0x2000001
    mov rdi, 0
    syscall

section .data
    db "Hello, World", 10