#include "minishell.h"

extern char **environ;

int g_fd[2];
int g_red_out;

void test()
{
	//is_pipe true
	/* ������ �ٽ� �� �� ���ø� �ϴ� ������ �ؼ� �����غ��� */
}

int	main(int argc, char *argv[])
{
	// ls -al | grep Sep | wc > hello1 | echo hi > hello2
	test();

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
	
	// ls -al | grep Sep > hello1 | echo hi > hello2
	
	
	/*
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execlp("ls", "ls", "-al", NULL);
		exit(1);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		
		pipe(fd);
		pid_t pid2 = fork();
		if (pid2 == 0)
		{
			close(fd[0]);
			perror("1 close");
			dup2(fd[1], 1);
			perror("2 dup2");
			close(fd[1]);
			perror("3 close");
			execlp("grep", "grep", "Sep", NULL);
			exit(1);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			perror("4 close");
			dup2(fd[0], 0);
			perror("5 dup2");
			close(fd[0]);
			perror("6 close");
			execlp("wc", "wc", NULL);
		}
	}
	*/
	return (0);
}
//execlp("grep", "grep", "Sep", NULL);
//execlp("wc", "wc", NULL);
