# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_strcpy.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/06 17:18:24 by donglee           #+#    #+#              #
#    Updated: 2020/08/06 17:19:19 by donglee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

    global	_ft_strcpy
    section	.text
                                        ;char *ft_strcpy(char *dest, const char *src);
_ft_strcpy: mov rax, rdi                ;copies rdi to rax
            xor rcx, rcx                ;initializes rcx to 0

loop:       cmp byte [rsi + rcx], 0x0   ;checks if the src string reaches null
            je  done                    ;if it reaches to null jump to done
            mov r8, [rsi + rcx]         ;r8 is tmp. stores src string's character
            mov [rax + rcx], r8         ;and put it to dest string which is rax
            inc rcx                     ;increases counter : i++
            jmp loop                    ;repeat till the src string reaches null
        
done:       mov byte [rax + rcx], 0x0   ;add null at the end of the dest string(rax)
            ret                         ;return dest
