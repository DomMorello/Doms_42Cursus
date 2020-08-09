; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_read.s                                          :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: donglee <donglee@student.42seoul.k>        +;+  +:+       +;+         ;
;                                                 +;+;+;+;+;+   +;+            ;
;    Created: 2020/08/09 18:58:27 by donglee           ;+;    ;+;              ;
;    Updated: 2020/08/09 18:58:27 by donglee          ;;;   ;;;;;;;;.fr        ;
;                                                                              ;
; **************************************************************************** ;

	global	_ft_read
	section	.text
								;ssize_t fr_read(int fd, void *buf, size_t count)
_ft_read:	mov	rax, 0x02000003	;read syscall number
			syscall				;call the function read
			jc	error			;int freeBSD, if syscall fails carry flag is set to 1 
			ret					;if no error, return rax
			
error:		mov	rax, -1			;if error, return -1
			ret	
