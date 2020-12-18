#include "minishell.h"

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

t_list *g_env_list;
t_list g_env_head;

extern char **environ;

// void copy_environ(void)
// {
// 	int i;
// 	t_list *tmp;

// 	g_env_head.content = ft_strdup(environ[0]);
// 	g_env_head.next = NULL;
// 	g_env_list = &g_env_head;
// 	i = 1;
// 	while (environ[i])
// 	{
// 		tmp = ft_lstnew(ft_strdup(environ[i]));
// 		ft_lstadd_back(&g_env_list, tmp);
// 		i++;
// 	}
// }

void sig_handler(int signo)
{
	printf("hi\n");
	exit(127);
}

int main()
{
	signal(SIGINT, sig_handler);

	int status = 0;
	pid_t pid = fork();
	if (pid == 0)
	{
		printf("hi\n");
		exit(123);
	}
	else if (pid < 0)
	{
		perror("fork err");
	}
	else
	{
		wait(&status);
	}
	printf("test %d\n", status);
	if (WIFEXITED(status))
		printf("normal term %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal signal term %d\n", WTERMSIG(status));
	
    return 0;
}
