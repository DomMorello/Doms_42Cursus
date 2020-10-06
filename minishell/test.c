#include "minishell.h"

extern char **environ;

int g_fd[2];
int g_red_out;

void set_prev_pipe()
{
	close(g_fd[1]);
	dup2(g_fd[0], 0);
	close(g_fd[0]);
}

void set_post_pipe()
{
	close(g_fd[0]);
	dup2(g_fd[1], 1);
	close(g_fd[1]);
}

void set_red_out(char *title)
{
	g_red_out = open(title, O_CREAT | O_RDWR);
	dup2(g_red_out, 1);
	close(g_red_out);
}

int	main(int argc, char *argv[])
{
    //  // execve 이용한 bin 실행파일 구현
	//  char	**new_argv;
	//  char	*command;
	//  char 	*path;
	//  char	*absolute_path;
	//  int	idx;
	
	//  command = strdup(argv[1]);
	//  absolute_path = strdup("/usr/bin/");
	
	//  // 입력받은 명렁어와 절대경로의 문자열을 합침
	//  absolute_path = strcat(absolute_path, command);
	//  new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
	
	//  // 명령어와 이후의 데이터를 이중 포인터에 저장
	//  idx = 0;
	//  while (idx < argc)
	//  {
	//  	new_argv[idx] = argv[idx + 1];
	//  	idx++;
	//  }
	//  new_argv[argc] = NULL;

	//  // 명령어 실행!
	//  if (execve(absolute_path, new_argv, env) == -1)
	//  {
	//  	fprintf(stderr, "error: %s\n", strerror(errno));
	//  	return (1);
	//  }
	//  printf("this is not exec\n");
	
	// ls -al | grep Sep > hello1 | echo hi > hello2
	pipe(g_fd);
	pid_t pid1 = fork();
	if (pid1 == 0)
	{
		set_post_pipe();
		execlp("ls", "ls", "-al", NULL);
	}
	else
	{
		wait(NULL);
	}
	
	set_prev_pipe();

	pipe(g_fd);
	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		set_post_pipe();
		set_red_out("hello1");
		execlp("grep", "grep", "Sep", NULL);
	}
	else
	{
		wait(NULL);
	}

	set_prev_pipe();

	pid_t pid3 = fork();
	if (pid3 == 0)
	{
		set_red_out("hello2");
		execlp("echo", "echo", "hi", NULL);
	}
	else
	{
		wait(NULL);	
	}
	
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
