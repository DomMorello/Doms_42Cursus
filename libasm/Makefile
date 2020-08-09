CC = gcc
FLAGS = nasm -f macho64
SRCS = ft_read.s ft_strcmp.s ft_strcpy.s ft_strdup.s ft_strlen.s ft_write.s
OBJS = $(SRCS:.s=.o)
NAME = libasm.a
TEST = test

%.o: %.s
	$(FLAGS) $<

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm *.o

fclean: clean
	rm $(NAME)
	rm $(TEST)

$(TEST): main.c
	$(CC) -o $@ $? $(NAME)

re: fclean all
