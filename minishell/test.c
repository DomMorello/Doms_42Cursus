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

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t src_len;
	size_t i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (*dst)
		dst++;
	while (src[i] && i < dstsize - dst_len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst_len + src_len);
}

int	main(int argc, char *argv[])
{
	// test();

	int red_in;
	int red_out;

	int stdin;
	int stdout;

	stdin = dup(0);
	perror("set up dup");
	stdout = dup(1);
	perror("set up dup");

	red_out = open("./hello1", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	perror("red out open 1");
	dup2(red_out, 1);
	perror("red out dup2");
	close(red_out);

	ft_putstr_fd("what the hell\n", 1);

	dup2(stdin, 0);
	perror("take back dup2");
	dup2(stdout, 1);
	perror("take back dup2");

	red_out = open("./hello1", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	perror("red out open 1");
	dup2(red_out, 1);
	perror("red out dup2");
	close(red_out);

	ft_putstr_fd("heloo!\n", 1);

	dup2(stdin, 0);
	perror("take back dup2");
	dup2(stdout, 1);
	perror("take back dup2");

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
