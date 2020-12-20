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
	int status;
	siginfo_t sig;
	signal(SIGINT, sig_handler);

	pid_t pid = fork();
	if (pid == 0)
	{
		execlp("cat", "cat", NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			printf("signal!! %d\n", )
	}

    return 0;
}
