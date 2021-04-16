#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CD_BAD "error: cd: bas arguments\n"
#define CD_FAIL "error: cd: cannot change direcotry to "
#define SYS_ERR "error: fatal\n"
#define EXEC_ERR "error: cannot execute "

int ft_strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return len;
}

int err(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return 1;
}

int is_pipe(char **argv)
{
	int i = 0;

	while (argv[i])
	{
		if (!strncmp(argv[i], "|", 2))
		{
			argv[i] = NULL;
			return 1;
		}
		else if (!strncmp(argv[i], ";", 2))
		{
			argv[i] = NULL;
			return 0;
		}
		i++;
	}
	return 0;
}

int ft_argvlen(char **argv)
{
	int i = 0;
	
	while (argv[i])
		i++;
	return i;
}

void cd(char **input)
{
	int i = ft_argvlen(input);

	if (i != 2)
		err(CD_BAD);
	else if (chdir(input[1]) < 0)
	{
		err(CD_FAIL);
		err(input[1]);
		err("\n");
	}
}

void shell(int argc, char **input, char **envp, int prev, int *fd)
{
	pid_t pid;
	int fd_next[2];
	int next, status, i;

	if (argc <= 0)
		return ;
	next = is_pipe(input);
	if (input[0])
	{
		if (next && pipe(fd_next) < 0)
			exit(err(SYS_ERR));
		if (!strncmp(input[0], "cd", 3))
			cd(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;

	shell(argc - 1, argv + 1, envp, 0, fd);
	
	return 0;
}
