    global _ft_writes
    section .text

_ft_writes:  mov     rax, 0x02000004
            push    rdx
            push    rsi
            push    rdi
            syscall