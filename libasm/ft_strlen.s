; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strlen.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: donglee <donglee@student.42seoul.k>        +;+  +:+       +;+         ;
;                                                 +;+;+;+;+;+   +;+            ;
;    Created: 2020/08/09 18:59:30 by donglee           ;+;    ;+;              ;
;    Updated: 2020/08/09 18:59:30 by donglee          ;;;   ;;;;;;;;.fr        ;
;                                                                              ;
; **************************************************************************** ;

	global	_ft_strlen
	section .text
										;size_t ft_strlen(const char *s);
_ft_strlen:	xor rax, rax				;initializes rax to 0

getlen:		cmp byte [rdi + rax], 0x0	;compares a byte in rdi(first parameter:const char *s) with null(0x0)
			je  done					;if it counters null, jump to done(return rax)
			inc rax						;if not, increase rax: len++
			jmp getlen					;and check again till the pointer reaches null

done:		ret							;return rax
