#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include "./libft/libft.h"

extern char **environ;
t_list *g_env_list;
t_list g_env_head;

// # define GREEN "\033[0;32m"
// # define LIGHT_BLUE "\033[0;34m"
// # define YELLOW "\033[0;33m"
// # define NC "\033[0m"

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PATH "PATH="
# define HOME "HOME="
# define USRBIN "/usr/bin"
# define OLDPWD "OLDPWD="
# define PWD2 "PWD="
# define N_OPTION "-n"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

int get_next_line(int fd, char **line);

/* jipark */

# define BUF_SIZE 1024
/*
** enum STATE represents state of current character when parsing lexer.
*/
enum STATE {
	STATE_NORMAL,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_IN_ENV
};

enum TOKEN_TYPE {
	CHAR_NULL = '\0',
	CHAR_NEWLINE = '\n',
	CHAR_NORMAL = -1,
	CHAR_PIPE = '|',
	CHAR_RED_OUT = '>',
	CHAR_RED_IN = '<',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_TAB = '\t',	//필요해?
	CHAR_ENV = '$',
	TOKEN = -1,
};

typedef struct s_token t_token;
typedef struct s_lexer t_lexer;

/*
** Struct s_token is an element of linked list.
*/

typedef struct s_token
{
	char *data;
	int type;
	int white_space_flag;	//필요해?
	t_token *next;
}				t_token;

/*
** Struct s_lexer contains the first element of token linked list.
*/
typedef struct s_lexer
{
	t_token *token_list;
	int token_counts;
}				t_lexer;

/*
** Struct s_token_status contains iterative index i and j for loop,
** amied to be in accordance with norminette which only accepts four local variables and parameters.
*/
typedef struct s_status
{
	int i; //gnl이나 read로 읽은 문자열 인덱스
	int j; //token 안의 data 문자열에 대한 인덱스
	int state;
	int length;
	char *str;
}				t_status;

/*
** Directory lexer
*/
t_token		*tokenize_lexer(char *str, int length);

int				is_normal_env(char c1, char c2);
int				is_normal_special_char(char c1, char c2);
char			analyze_char_type(char *str, t_status *status);
void			initiate_token(t_token *token, int length);
int				is_end_of_quote(char char_type, char c);

void			adjust_env(t_token *token);

void			handle_prompt(char *buf);
void		initiate_token_status(t_status *status, char *str, int length);

void			examine_end_of_line(t_token *token, t_status *status, char char_type);
int		is_env_exception(t_token *token, t_status *status, char *str, char char_type);
t_token			**convert_list_into_array(t_token *token);
int				check_basic_grammar(t_token *token);
void			free_all_tokens(t_token *token, void (*del)(void *));

int				issue_new_token(t_token *token, t_status *status, int flag, char char_type);
void			add_char_and_change_state(t_token *token, t_status *status, char char_type, int state);

void copy_env_key(char **token_data);
void search_key_in_env(char *key, char **token_data, int env_idx);
void convert_key_to_env(char *env_content, char **token_data, char *key, int env_idx);
void convert_to_value(char *new, char *env_content, int *i, int *j);


#endif
