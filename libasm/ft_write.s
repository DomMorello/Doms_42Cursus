; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_write.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: marvin <marvin@student.42.fr>              +;+  +:+       +;+         ;
;                                                 +;+;+;+;+;+   +;+            ;
;    Created: 2020/08/09 18:59:42 by donglee           ;+;    ;+;              ;
;    Updated: 2020/08/10 19:09:13 by marvin           ;;;   ;;;;;;;;.fr        ;
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

error:		push	rbx             ;to call extern function, you must align stack as much as 16byte
                                    ;'push rbx' will make 8 bytes in stack and 'call ___error' make another 8 byte
            mov		rbx, rax        ;if syscall fails, rax has errno. I moved it to tmp register(rbx) to use it later
			call	___error        ;this function returns (stored in rax)the address of errno(int *) which is the location of the errno
			mov		[rax], rbx      ;since rax is address of the errno, and rbx is errno itself, 
                                    ;put rbx(errno(integer)) to the address of errno([rax](location of errno)).
			mov		rax, -1			;put -1 to rax
			pop		rbx             ;clean stack
			ret                     ;return rax which is -1
