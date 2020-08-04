	global _ft_strlen
	section .text

_ft_strlen:	xor rax, rax				;initializes rax to 0

getlen:		cmp byte [rdi + rax], 0x0	;compares a byte in rdi(first parameter:const char *s) with null(0x0)
			je  done					;if it counters null, jump to done(return rax)
			inc rax						;if not, increase rax: len++
			jmp getlen					;and check again till the pointer reaches null

done:		ret							;return rax
