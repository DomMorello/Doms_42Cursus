# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_strcmp.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/06 17:17:50 by donglee           #+#    #+#              #
#    Updated: 2020/08/06 17:19:11 by donglee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
    
	global	_ft_strcmp
    section	.text
										;int ft_strcmp(const char *s1, const char *s2);
_ft_strcmp: xor rcx, rcx				;initializes rcx to 0(:int i = 0)

loop:		mov al, byte [rdi + rcx]	;al 8 bit = 1 byte(char), a character in the string s1 is stored in al 	
			mov bl, byte [rsi + rcx]	;bl 8 bit = 1 byte(char), a character in the string s2 is sotred in bl
			cmp al, 0x0					;checks if al is null
			je	done					;if it is null jump to done
			cmp bl, 0x0					;checks if bl is null
			je	done					;if it is null jump to done
			cmp al, bl					;if both are not null, checks if they are same
			je	increase       			;if they are same, jump to increase

increase:	inc rcx						;increase rcx (: i++)

check:      mov al, byte [rdi + rcx]	;puts the next character of the string s1 into al
            mov bl, byte [rsi + rcx]	;puts the next character of the string s2 into bl 
            cmp al, bl					;then compares both of them
            jne done					;if they are not identical, jump to done
            jmp loop					;if they are identical, repeat the loop

										;movzx: regarless of size, able to move value in smaller register to larger one, ramaining bits are set to 0
done:       movzx rax, al				;puts al to rax				
            movzx rbx, bl				;puts bl to rbx
            sub rax, rbx				;rax = rax - rbx
            ret							;return rax 
