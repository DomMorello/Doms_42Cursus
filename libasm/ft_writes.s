    global _ft_write
    section .text

_ft_write:  mov     rax, 0x02000004
            push    rdx
            push    rsi
            push    rdi
            syscall