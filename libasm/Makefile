CC = gcc
FLAGS = nasm -f macho64
SRCS = ft_read.s ft_strcmp.s ft_strcpy.s ft_strdup.s ft_strlen.s ft_write.s
OBJS = ft_read.o ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strlen.o ft_write.o
NAME = libasm.a

all: $(NAME)

$(NAME): $(OBJS)
	$(FLAGS) $(OBJS)
	ar rs $(NAME) $(OBJS)

test: 

clean:
	rm OBJS

fclean: clean
	rm OBJS

re:
