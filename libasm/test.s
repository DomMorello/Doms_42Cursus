	global	_test
	extern 	_malloc
	section .text

_test:	mov		rbx, 5h
		push	rbx			;push rbx essentail! align stack!
		mov		rdi, rbx
		call	_malloc
		mov		dword [rax], 68h
		inc		rax
		mov		dword [rax], 65h
		inc		rax
		mov		dword [rax], 6ch
		inc		rax
		mov		dword [rax], 6fh
		dec		rax
		dec		rax
		dec		rax
		pop		rbx
		ret

