CC = clang++

CFLAGS = -Wall -Wextra -Werror

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

NAME = realtype

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean :
	rm -f $(OBJS)
	rm -f $(NAME)

re : fclean all
