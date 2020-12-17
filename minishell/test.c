#include "minishell.h"

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

t_list *g_env_list;
t_list g_env_head;

extern char **environ;

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

char *alloc_new()
{
	char *new;

	new = malloc(6);
	new[6] = 0;
	return new;
}

void make_new(char *new)
{
	new[0] = 'w';
	new[1] = 'o';
	new[2] = 'r';
	new[3] = 'l';
	new[4] = 'd';
}

void test1(char *s)
{
	char *new;

	new = alloc_new();
	make_new(new);
	free(new);
}

int main()
{
	// signal(SIGINT, sig_handler);
	char *s = malloc(6);
	s[0] = 'h';
	s[1] = 'e';
	s[2] = 'l';
	s[3] = 'l';
	s[4] = 'o';
	s[5] = 0;

	test1(s);
	free(s);
	while (1)
	{
		;
	}
	// int status = 0;
	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	execlp("cat", "cat", NULL);
	// }
	// else if (pid < 0)
	// {
	// 	perror("fork err");
	// }
	// else
	// {
	// 	wait(&status);
	// }
	// printf("test %d\n", status);
	// if (WIFEXITED(status))
	// 	printf("normal term %d\n", WEXITSTATUS(status));
	// else if (WIFSIGNALED(status))
	// 	printf("abnormal signal term %d\n", WTERMSIG(status));
	
    return 0;
}
