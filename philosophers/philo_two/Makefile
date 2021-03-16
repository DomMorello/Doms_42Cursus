CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c util.c routine.c

OBJS = $(SRCS:%.c=%.o)

NAME = phlio_two

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean :
	rm -f $(OBJS)
	rm -f $(NAME)

norm :
	norminette -R CheckForbiddenSourceHeader ./.c ./.h

re : fclean all
