#!/bin/bash
cd libft
make
mv libft.a ../
make fclean
cd ..
gcc main.c ./lexer/*.c libft.a
