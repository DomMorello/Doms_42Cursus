    global _ft_strcmp
    section .text

_ft_strcmp: xor rcx, rcx

loop:       cmp byte [rdi + rcx], 0x0
            je  done
            cmp byte [rsi + rcx], 0x0
            je  done
            mov al, byte [rdi + rcx]
            mov bl, byte [rsi + rcx]
            cmp al, bl
            je  increase

increase:   inc rcx

check:      mov al, byte [rdi + rcx]
            mov bl, byte [rsi + rcx]
            cmp al, bl
            jne done
            jmp loop

done:       movzx rax, al
            movzx rbx, bl
            sub rax, rbx
            ret