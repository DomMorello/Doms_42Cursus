	global	_test
	extern	_ft_strlen
	extern	_malloc
	section .text

_test:	call	_ft_strlen
		mov		rdi, rax
		push	r8
		call	_malloc
		pop		r8
		ret
