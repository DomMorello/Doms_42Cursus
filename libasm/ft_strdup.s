    global  _ft_strdup
    extern  _malloc
    extern  _ft_strlen
    section .text

_ft_strdup: xor     rcx, rcx
            push    rbx
            mov     r8, rdi
            mov     rdi, r8
            call    _ft_strlen
            pop     rbx
            ret

