    global _ft_strcpy
    section .text

_ft_strcpy: mov rax, rdi
            xor rcx, rcx

loop:       cmp byte [rax + rcx], 0x0
            je  done
            mov r8, [rsi + rcx]
            mov [rax + rcx], r8
            inc rcx
            jmp loop
        
done:       mov byte [rax + rcx], 0x0
            ret