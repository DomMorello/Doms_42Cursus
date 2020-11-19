#include "minishell.h"

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

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

t_list *g_env;
t_list head;

void copy_env(void)
{
	head.content = "hello";
	head.next = NULL;
	g_env = &head;

	t_list *tmp = ft_lstnew("world");
	ft_lstadd_back(&g_env, tmp);
}

void print_env(void)
{
	t_list *test = g_env;
	while (test)
	{
		printf("%s\n", (char *)test->content);
		test = test->next;
	}
}

void exec_export(void)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		t_list *tmp = ft_lstnew("what");
		ft_lstadd_back(&g_env, tmp);
		printf("child!!\n");
		print_env();
		exit(-1);
	}
	else
	{
		wait(NULL);
	}
}


char *get_key(char *content)
{
	int i;
	int key_len;
	char *ret;

	i = 0;
	key_len = 0;
	ret = NULL;
	while (content[i])
	{
		if (content[i] == '=')
		{
			key_len = i;
			break ;
		}
		i++;
	}
	ret = (char *)malloc(sizeof(char) * key_len + 1);
	ft_strlcpy(ret, content, key_len + 1);
	printf("ret: %s\n", ret);
}

int	main(int argc, char *argv[])
{
	// test();
	char *s = "hello=world";
	get_key(s);

	return (0);
}
