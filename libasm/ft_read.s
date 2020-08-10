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
	extern	___error
	section	.text
								;ssize_t fr_read(int fd, void *buf, size_t count)
_ft_read:	mov	rax, 0x02000003	;read syscall number
			syscall				;call the function read
			jc	error			;int freeBSD, if syscall fails carry flag is set to 1 
			ret					;if no error, return rax
			
error:		push	rbx			;to call extern function, you must align stack as much as 16byte
								;'push rbx' will make 8 bytes in stack and 'call ___error' make another 8 byte
			mov		rbx, rax	;if syscall fails, rax has errno. I moved it to tmp register(rbx) to use it later
			call	___error	;this function returns (stored in rax)the address of errno(int *) which is the location of the errno
			mov		[rax], rbx	;since rax is address of the errno, and rbx is errno itself, 
								;put rbx(errno(integer)) to the address of errno([rax](location of errno)).
			mov		rax, -1		;put -1 to rax
			pop		rbx			;clean stack
			ret					;return rax which is -1
