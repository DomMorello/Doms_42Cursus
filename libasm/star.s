    global start
    section .text
start:
    mov rdx, output
    mov r8, 1
    mov r9, 0
line:
    mov byte [rdx], '*'
    