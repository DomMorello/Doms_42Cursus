    global  _ft_strdup
    extern  _malloc
    extern  _ft_strlen
    section .text

_ft_strdup: xor     rcx, rcx
			mov		rbx, rdi
            call    _ft_strlen
			push	rbx
			inc		rax
			mov		rdi, rax
			call	_malloc
			cmp		rax, 0x0
			je		error

loop:		cmp		byte [rbx + rcx], 0x0
			je		done
			mov		r9, [rbx + rcx]
			mov		[rax + rcx], r9
			inc		rcx
			jmp		loop

done:		pop		rbx
			mov		byte [rax + rcx], 0x0
			ret

error:		pop		rbx
			ret

			
