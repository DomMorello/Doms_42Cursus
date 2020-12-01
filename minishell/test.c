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

void test1(char *s)
{
	s[1] = 'e';
	char *new = malloc(6);
	if (new == NULL)
	{
		printf("malloc fail\n");
	}
	new[0] = 'h';
	new[1] = 'e';
	new[2] = 'l';
	new[3] = 'l';
	new[4] = 'o';
	new[5] = 0;
	free(s);
	s = ft_strdup(new);
	free(new);
}

int	main(int argc, char *argv[])
{
	// test();
	// int i = 0;
	// signal(SIGINT, sig_handler);
	// while (1)
	// {
	// 	printf("%d\n", i);
	// 	i++;
	// 	sleep(1);
	// }
int i = 100;
while (i--)
{
	char *s = malloc(50);
	ft_bzero(s, 50);
	if (s == NULL)
	{
		printf("malloc fail\n");
	}
	s[0] = 'h';
	s[1] = 'i';
	s[2] = 0;
	test1(s);
	printf("%s\n", s);
}

	return (0);
}
