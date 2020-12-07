#include "minishell.h"

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

t_list *g_env_list;
t_list g_env_head;

extern char **environ;

void set_red_in(char *title)
{
	g_red_in_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_in_fd, 0);
	close(g_red_in_fd);
}

void set_red_out(char *title)
{
	g_red_out_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_out_fd, 1);
	close(g_red_out_fd);
}

void test()
{
	// grep Sep < hello1 | wc > hello2
	pipe(g_pipe_fd);

	pid_t pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		close(g_pipe_fd[0]);
		dup2(g_pipe_fd[1], 1);
		close(g_pipe_fd[1]);
		set_red_in("./hello");
		execlp("grep", "grep", "Sep", NULL);
	}
	else
	{
		close(g_pipe_fd[1]);
		dup2(g_pipe_fd[0], 0);
		close(g_pipe_fd[0]);
		set_red_out("./hello1");
		execlp("wc", "wc", NULL);
	}
}

void copy_environ(void)
{
	int i;
	t_list *tmp;

	g_env_head.content = ft_strdup(environ[0]);
	g_env_head.next = NULL;
	g_env_list = &g_env_head;
	i = 1;
	while (environ[i])
	{
		tmp = ft_lstnew(ft_strdup(environ[i]));
		ft_lstadd_back(&g_env_list, tmp);
		i++;
	}
}

void sig_handler(int signo)
{
	printf("worked!\n");
	exit(1);
}

void print_token(t_token *token)
{
	t_token *tmp = token;

	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}

t_token *add_back(t_token *token, char *data)
{
	t_token *tmp = token;

	while (tmp->next)
		tmp = tmp->next;
	t_token *new = malloc(sizeof(t_token));
	new->data = ft_strdup(data);
	new->next = NULL;
	tmp->next = new;
}

void remove_if(t_token *token)
{
	t_token *tmp = token;
	t_token *prev;

	while (tmp)
	{
		if (!strcmp(tmp->data, "three"))
		{
			prev->next = tmp->next;
			free(tmp->data);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void make_dred_out(t_token *deleted, t_token *prev)
{
	prev->next = deleted->next;
	free(prev->data);
	prev->data = ft_strdup(">>");
	free(deleted->data);
	free(deleted);
}

void check_dred_out(t_token *token)
{
	t_token *tmp;
	t_token *tmp2;
	t_token *prev;
	int d_red_out;
	
	tmp = token;
	tmp2 = token;
	d_red_out = FALSE;
	while (tmp2)
	{
		tmp = tmp2;
		while (tmp)
		{
			if (!ft_strncmp(tmp->data, ">", ft_strlen(">")))
				d_red_out = TRUE;
			prev = tmp;
			tmp = tmp->next;
			if (tmp && d_red_out && !ft_strncmp(tmp->data, ">", ft_strlen(">")))
			{
				prev->next = tmp->next;
				free(prev->data);
				prev->data = ft_strdup(">>");
				free(tmp->data);
				free(tmp);
				break ;
			}
			d_red_out = FALSE;
		}
		tmp2 = tmp2->next;
	}
}
// 1p >tp >t 2p > > 3 > > 4 > > 5 > > 6

int main()
{
	t_token *token = malloc(sizeof(t_token));
	token->data = ft_strdup("one");
	token->next = NULL;

	add_back(token, "two");
	add_back(token, "three");
	add_back(token, "four");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, "five");
	add_back(token, "five");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, ">");
	add_back(token, ">");
	add_back(token, "five");
	add_back(token, "three");
	add_back(token, ">");
	add_back(token, ">");
	add_back(token, "five");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, ">");
	add_back(token, ">");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, ">");
	add_back(token, ">");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, "three");
	add_back(token, "five");
	add_back(token, ">");
	add_back(token, ">");
	add_back(token, "three");
	add_back(token, "five");
	// check_dred_out(token);
	// remove_if(token);
	print_token(token);
    return 0;
}
