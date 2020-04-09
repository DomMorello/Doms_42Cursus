CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = bool.c data_init.c exception_all.c exception_data.c ft_printf.c input_data.c parse_data.c print_c.c print_di.c print_p.c print_per.c \
	   print_s.c print_u.s print_x.c 

OBJS = $(SRCS:%.c=%.o)

NAME = libftprintf.a

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

norm :
	norminette -R CheckForbiddenSourceHeader ./.c ./.h

re : fclean all
