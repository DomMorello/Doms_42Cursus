    global	_ft_strcpy
    section	.text
                                        ;char *ft_strcpy(char *dest, const char *src);
_ft_strcpy: mov rax, rdi                ;copies rdi to rax
            xor rcx, rcx                ;initializes rcx to 0

loop:       cmp byte [rsi + rcx], 0x0   ;checks if the src string reaches null
            je  done                    ;if it reaches to null jump to done
            mov dl, byte [rsi + rcx]    ;r8 is tmp. stores src string's character
										;(error): it was 'mov r8, [rsi + rcx]' but it seemed wrong. 
										;it must be fit when it comes to size(must add 'byte', be stored in dl(1 byte))
            mov byte [rax + rcx], dl    ;and put it to dest string which is rax
            inc rcx                     ;increases counter : i++
            jmp loop                    ;repeat till the src string reaches null
        
done:       mov byte [rax + rcx], 0x0   ;add null at the end of the dest string(rax)
			ret                         ;return dest
