CC = clang++
CFLAGS = -Wall -Wextra -Werror

SRCS = Convert.cpp main.cpp

OBJS = $(SRCS:%.cpp=%.o)

NAME = convert

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