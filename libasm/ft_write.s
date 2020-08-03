    global _ft_write
    section .text

_ft_write:  mov     rax, 0x02000004	; write system call number
            syscall					; call write function
            jc		error			; in FreeBSD, if syscall has an error, carry flag sets to 1
			ret

error:		mov		rax, -1			; rax has return value. -1 in error
			ret
