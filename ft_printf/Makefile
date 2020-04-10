CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =	bool.c data_init.c exception_all.c exception_data.c \
		ft_printf.c input_data.c parse_data.c print_c.c print_di.c \
		print_p.c print_per.c print_s.c print_u.c print_x.c \

OBJS = $(SRCS:%.c=%.o)

NAME = libftprintf.a

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS) ft_printf.h
	@make -C libft
	cp libft/libft.a ./$(NAME)
	$(CC) $(CFLAGS) -c $(SRCS)
	@ar rsc $(NAME) $(OBJS)

clean :
	cd ./libft; make clean
	rm -f $(OBJS)

fclean :
	cd ./libft; make fclean
	rm -f $(OBJS)
	rm -f $(NAME)

norm :
	norminette -R CheckForbiddenSourceHeader ./.c ./.h

re : fclean all
