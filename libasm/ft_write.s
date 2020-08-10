; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_write.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: donglee <donglee@student.42seoul.k>        +;+  +:+       +;+         ;
;                                                 +;+;+;+;+;+   +;+            ;
;    Created: 2020/08/09 18:59:42 by donglee           ;+;    ;+;              ;
;    Updated: 2020/08/09 18:59:42 by donglee          ;;;   ;;;;;;;;.fr        ;
;                                                                              ;
; **************************************************************************** ;

    global	_ft_write
	extern	___error
    section .text
                                    ;ssize_t ft_write(int fd, const void *buf, size_t count);
_ft_write:  mov     rax, 0x02000004	;write system call number
            syscall					;call write function
            jc		error			;in FreeBSD, if syscall has an error, carry flag sets to 1
			ret

error:		push	rbx
			mov		rbx, rax
			call	___error
			mov		[rax], rbx
			mov		rax, -1			;rax has return value. -1 in error
			pop		rbx
			ret
