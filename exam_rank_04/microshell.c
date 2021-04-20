#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define	CD_ERR	"error: cd: bad arguments\n"
#define CD_ERR2	"error: cd: cannot change directory to "
#define	SYS_ERR	"error: fatal\n"
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
    write(2, s, ft_strlen(s));
    return 1;
}

int ft_argvlen(char **argv)
{
    int len = 0;

    while (argv[len])
        len++;
    return len;
}

int is_pipe(char **argv)
{
    int i  = 0;

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

void ft_cd(char **argv)
{
    int i = ft_argvlen(argv);

    if (i != 2)
        err(CD_ERR);
    else if (chdir(argv[1]) < 0)
    {
        err(CD_ERR2);
        err(argv[1]);
        err("\n");
    }
}

void	shell(int argc, char **argv, char **envp, int prev, int *fd_prev)
{
	pid_t	pid;
	int		fd_next[2];
	int		next, status, i;

	if (argc <= 0)
		return ;
	next = is_pipe(argv);
	if (argv[0])
	{
		if (next && pipe(fd_next)<0)
			exit(err(SYS_ERR));
		if (!strncmp(argv[0], "cd", 3))
			ft_cd(argv);
		else if ((pid = fork()) < 0)
			exit(err(SYS_ERR));
		else if (!pid)
		{
			if (prev && dup2(fd_prev[0], 0)<0)
				exit(2);
			if (next && dup2(fd_next[1], 1)<0)
				exit(2);
			if (execve(argv[0], argv, envp) < 0)
			{
				err(EXEC_ERR);
				err(argv[0]);
				err("\n");
				exit(1);
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) < 0)
				exit(err(SYS_ERR));
			if (status == 512)
				exit(err(SYS_ERR));
			if (prev)
				close(fd_prev[0]);
			if (next)
				close(fd_next[1]);
		}
	}
	i = ft_argvlen(argv);
	shell(argc-i-1, argv+i+1, envp, next, fd_next);
}

int main(int argc, char **argv, char **envp)
{
    int fd_prev[2];
    fd_prev[0] = 0;
    fd_prev[1] = 1;
    shell(argc - 1, argv + 1, envp, 0, fd_prev);
    return 0;
}