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

# define ERR_REDOUT "mongshell : syntax error near unexpected token `>'\n"
# define ERR_REDIN "mongshell : syntax error near unexpected token `<'\n"
# define ERR_PIPE "mongshell : syntax error near unexpected token `|'\n"
# define ERR_SEMI "mongshell : syntax error near unexpected token `;'\n"
# define ERR_QUOTE "mongshell : syntax error near '"
# define ERR_DSEMI "mongshell : syntax error near ';;'\n"
# define ERR_NEWL "mongshell : syntax error near unexpected token `newline'\n"



int get_next_line(int fd, char **line);

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

/* lexer add */
void start_bash(char ***cmds);
char ***divide_semicolon(t_token *token);
char ***alloc_cmds(t_token *token, char ***cmds, int len);
void copy_token_to_char(t_token **token, int num_cmd, char **cmds);
int get_num_cmd(t_token **token);
int get_num_cmdline(t_token *token);
int remove_empty_token(t_token *token);
void erase_quote(t_token *token, char quote_type);
void copy_without_quote(char *data, char *new, char quote_type);
void adjust_env_in_dquote(t_token *token);
void copy_env_key(char **token_data);
void search_key_in_env(char *key, char **token_data, int env_idx);
void convert_key_to_env(char *env_content, char **token_data, char *key, int env_idx);
void convert_to_value(char *new, char *env_content, int *i, int *j);
void check_dred_out(t_token *token);
int make_dred_out(t_token *deleted, t_token *prev, int d_red_out);

/* main */
void do_nothing(int signo);
void free_env(void);
void handle_process(char **cmd);
void copy_environ(void);
void handle_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx);
void exec_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx);
void process_pipe(char *cmd[], int *prev_pipe_idx, int pipe_idx);
void handle_cmd(char *token, char *cmd[], int *prev_pipe_idx, int pipe_idx);
void exec_unset(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc);
void delete_env_node(char *token);
void exec_export_np(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc);
int check_update(char *content);
char *get_key(char *content);
void exec_cmd_p(char *cmd[], int *prev_pipe_idx, int pipe_idx);
void parse_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx);
void exec_echo(char *cmd[], int prev_pipe_idx, int pipe_idx);
int get_len(char *cmd[], int prev_pipe_idx, int pipe_idx);
void print_echo(char *cmd[], int start, int end, int option);
void exec_export_p(char *cmd[], int prev_pipe_idx, int pipe_idx);
void print_export(char *line);
void add_dquote(char *new, char *line);
void	sort_export(t_list **list);
void exec_env(char *cmd[], int prev_pipe_idx, int pipe_idx);
int find_env_path(void);
void exec_pwd(char *cmd[], int prev_pipe_idx, int pipe_idx);
void exec_nprocess_built_in(void (*exec_func)(char **, int, int, int), char **cmd, int *prev_pipe_idx, int pipe_idx);
void exec_exit(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc);
void exec_cd(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc);
void dir_to_HOME(char *cmd[], int is_pipe);
char *find_home(void);
void change_dir(char *cmd[], char *dir, int is_pipe);
void update_env(char *cwd, char *key);
int find_pipe(char *cmd[]);
void handle_executable(char *token, char *cmd[], int prev_pipe_idx, int pipe_idx);
char *get_filepath(char *token, char **path);
void		free_2d_char(char **arr);
void cat_filepath(char **ret, char **tmp, char *token);
int search_dir(char *token, char *path);
char **get_path(void);
void exec_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx, char *filepath);
void exec_executable(char *cmd[], int prev_pipe_idx, int pipe_idx, char *filepath);
int get_argc(char *cmd[], int prev_pipe_idx, int pipe_idx);
int is_redirection(char *token);
void process_redirection(char *cmd[], int *prev_pipe_idx, int pipe_idx, int is_process);
void set_pipe_parent();
void set_pipe_child();
void set_red_double_out(char *title);
void set_red_in(char *title, char *token, int is_process);
void set_red_out(char *title);
void print_error_red_in(char *title, int is_process);
void print_err_not_dir(char *dir);
void print_err_no_dir(char *dir);
void do_export(char *token, int prev_pipe_idx);
void parse_to_start(t_token *token);
void do_echo(int start, int end, char *cmd[]);

#endif
