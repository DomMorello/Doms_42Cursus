#include "minishell.h"

extern char **environ;

char *test(char *s)
{
	char *ret = malloc(sizeof(char) * 10);
	int i = 10;
	while (i--)
	{
		ret[i] = 'a';
	}
	return ret;
}

char *test2(char *s)
{
	char *ret = malloc(sizeof(char) * 14);
	int i = 14;
	while (i--)
	{
		ret[i] = 'b';
	}
	return ret;
}

int	main(int argc, char *argv[])
{
	char *s = "hello";
	s = test(s);
	s = test2(s);
	free(s);
	while (1)
	{
		;
	}
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
