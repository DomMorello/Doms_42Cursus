	global _ft_strlen
	section .text

_ft_strlen:	xor	rax, rax
			mov	rsi, rdi
			push rsi
			jmp	getlen

getlen:		mov	al, BYTE [rsi]
			cmp al, 0x0
			inc	rsi
			jne	getlen
			pop rsi
			ret
			
