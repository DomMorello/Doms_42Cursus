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

int	main(int argc, char *argv[])
{
	// test();

	char *line;
	char **cmd;

	get_next_line(0, &line);
	cmd = ft_split(line, ' ');
	
	int stdin1 = dup(0);
	perror("set up stdtin");
	int stdout1 = dup(1);
	perror("set up stdtin");

	int len = 0;
	while (cmd[len])
		len++;
	
	if (len > 2)
		ft_putstr_fd("too many\n", 2);
	else
	{
		struct stat file;
		char buf[100];
		char *cwd;

		if (!stat(cmd[1], &file))
		{
			if (S_ISDIR(file.st_mode))
			{
				chdir(cmd[1]);
				cwd = getcwd(buf, sizeof(buf));
				ft_putstr_fd(cwd, 2);
				ft_putstr_fd("\n", 2);
			}
			else
			{
				ft_putstr_fd("not a dir\n", 2);
			}
		}
		else
		{
			ft_putstr_fd("no such\n", 2);
		}
	}
	dup2(stdin1, 0);
	perror("take back stdtin");
	dup2(stdout1, 1);
	perror("take back stdtin");

    //  // execve �̿��� bin �������� ����
	//  char	**new_argv;
	//  char	*command;
	//  char 	*path;
	//  char	*absolute_path;
	//  int	idx;
	
	//  command = strdup(argv[1]);
	//  absolute_path = strdup("/usr/bin/");
	
	//  // �Է¹��� ����� �������� ���ڿ��� ��ħ
	//  absolute_path = strcat(absolute_path, command);
	//  new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
	
	//  // ��ɾ�� ������ �����͸� ���� �����Ϳ� ����
	//  idx = 0;
	//  while (idx < argc)
	//  {
	//  	new_argv[idx] = argv[idx + 1];
	//  	idx++;
	//  }
	//  new_argv[argc] = NULL;

	//  // ��ɾ� ����!
	//  if (execve(absolute_path, new_argv, env) == -1)
	//  {
	//  	fprintf(stderr, "error: %s\n", strerror(errno));
	//  	return (1);
	//  }
	//  printf("this is not exec\n");
	return (0);
}
