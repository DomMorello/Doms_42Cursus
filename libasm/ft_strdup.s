; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strdup.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: donglee </var/mail/donglee>                +;+  +:+       +;+         ;
;                                                 +;+;+;+;+;+   +;+            ;
;    Created: 2020/08/07 15:50:35 by donglee           ;+;    ;+;              ;
;    Updated: 2020/08/07 15:50:35 by donglee          ;;;   ;;;;;;;;.fr        ;
;                                                                              ;
; **************************************************************************** ;

    global  _ft_strdup
    extern  _malloc
    extern  _ft_strlen
    section .text
											;char *ft_strdup(const char *s)
_ft_strdup: xor     rcx, rcx				;initializes rcx to 0(int i = 0)
			mov		rbx, rdi				;stores string s in rbx(tmp) to use it later
            call    _ft_strlen				;the string s will be sent to the first parameter of ft_strlen
			push	rbx						;through ft_strlen, the length of string s will be stored in rax
			inc		rax						;to add null pointer at the end of the string, increases 1(len + 1)
			mov		rdi, rax				;to call malloc, send rax(len + 1) to the fisrt parameter(rdi) of func malloc
			call	_malloc					;if malloc succeeds, (len + 1) byte will be created in the heap memory
			cmp		rax, 0x0				;if malloc fails, null will be stored in rax.
			je		error					;if rax is null, jump to error

loop:		cmp		byte [rbx + rcx], 0x0	;checks if the characters of string s(stored in rbx at line 7) reaches to null 
			je		done					;if it reaches null, jump to done
			mov		r9, [rbx + rcx]			;puts a character of the string s to r9(tmp) 
			mov		[rax + rcx], r9			;and puts the character to result string(rax)
			inc		rcx						;increases the index(i++)
			jmp		loop					;repeat the process till rbx reaches null

done:		pop		rbx						;empty stack
			mov		byte [rax + rcx], 0x0	;add null at the end of the result string(rax)
			ret								;return rax(the pointer of the result string)

error:		pop		rbx						;on error, empty stack
			ret								;and return rax(which will be null)

			
