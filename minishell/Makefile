CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a

SRCS = 	exec_env.c exec_export_p.c handle_executable1.c\
		process_redirection.c exec_cd.c exec_exit.c exec_pwd.c\
		handle_executable2.c parse_cmd.c set_pipe.c exec_echo.c\
		exec_export_np.c exec_unset.c handle_process.c minishell.c\
		print_err.c signal.c ./lexer/adjust_env_in_dquote.c\
		./lexer/char_analyzer.c ./lexer/check_basic_grammar.c\
		./lexer/divide_semicolon.c ./lexer/environ_converter.c\
		./lexer/lexer_tokenizer.c ./lexer/lexer_util.c ./lexer/lexer_util2.c\
		./lexer/quote_dred.c ./lexer/token_issuer.c\
		./lexer/convert_exit_status.c

OBJS = $(SRCS:%.c=%.o)

NAME = minishell

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	cp libft/$(LIBFT) ./
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $(NAME)

clean :
	cd ./libft; make clean
	rm -f $(OBJS)

fclean :
	cd ./libft; make fclean
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f $(LIBFT)

norm :
	norminette ./.c ./.h

re : fclean all