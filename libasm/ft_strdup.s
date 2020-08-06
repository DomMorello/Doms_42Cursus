    global  _ft_strdup
    extern  _malloc
    extern  _ft_strlen
    section .text

_ft_strdup: xor     rcx, rcx
            push    rbx
            mov     r8, rdi
            mov     rdi, r8
            call    _ft_strlen
			push	r8
			inc		rax
			mov		rdi, rax
			call	_malloc
			cmp		rax, 0x0
			je		error

loop:		cmp		byte [r8 + rcx], 0x0
			je		done
			mov		r9, [r8 + rcx]
			mov		[rax + rcx], r9
			inc		rcx
			jmp		loop

done:		pop		rbx
			pop		r8
			mov		byte [rax + rcx], 0x0
			ret

error:		pop		rbx
			pop		r8
			ret

			
