#include "minishell.h"

extern char **environ;

int g_fd[2];
int g_red_out;

void set_pipe(int *is_pipe)
{
	if (pipe(g_fd) != -1)
		*is_pipe = 1;
	// perror("pipe err");
}

void set_red_out(char *title)
{
	g_red_out = open(title, O_CREAT | O_RDWR);
	dup2(g_red_out, 1);
	close(g_red_out);
}

void set_pipe_child()
{
	close(g_fd[0]);
	dup2(g_fd[1], 1);
	close(g_fd[1]);
}

void set_pipe_parent()
{
	close(g_fd[1]);
	dup2(g_fd[0], 0);
	close(g_fd[0]);
}

void exec_cmd(int *is_pipe, char *cmd, char *opt)
{
	pid_t pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		if (*is_pipe)
			set_pipe_child();
		// redirection true
		if (!strcmp(cmd, "wc"))
			set_red_out("hello2");	// > hello2
		if (!strcmp(cmd, "echo"))
			set_red_out("hello3");	// > hello3
		execlp(cmd, cmd, opt, NULL);
	}
	else
	{
		if (*is_pipe)
			set_pipe_parent();
	}
	*is_pipe = 0;
}

void test()
{
	int is_pipe;

	is_pipe = 0;
	//is_pipe true
	set_pipe(&is_pipe);
	exec_cmd(&is_pipe, "ls", "-al");	//ls -al |
	
	set_pipe(&is_pipe);
	exec_cmd(&is_pipe, "grep", "Sep"); //grep Sep |

	set_pipe(&is_pipe);
	exec_cmd(&is_pipe, "wc", NULL);	//wc

	exec_cmd(&is_pipe, "echo", "hi");
	// find redirection between pipes: true
	// set_red_out("hello1");
	// set_red_out("hello2");
}

int	main(int argc, char *argv[])
{
	// ls -al | grep Sep | wc > hello1 > hello2 | echo hi > hello3
	test();

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
	return (0);
}
