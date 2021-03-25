CC = clang++
CFLAGS = -Wall -Wextra -Werror

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

NAME = replace

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)
	rm -f test.replace

fclean :
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f test.replace

re : fclean all
