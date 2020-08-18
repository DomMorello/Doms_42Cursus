#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern char **environ;

int	main(int argc, char *argv[])
{
	char	**new_argv;
	char	*command;
	char 	*path;
	char	*absolute_path;
	int	idx;
	
	command = strdup(argv[1]);

	printf("command = %s\n", command);

	absolute_path = strdup("/bin/");
	
	// 입력받은 명렁어와 절대경로의 문자열을 합침
	absolute_path = strcat(absolute_path, command);

	printf("absolute_path = %s\n", absolute_path);
	
	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
	
	// 명령어와 이후의 데이터를 이중 포인터에 저장
	idx = 0;
	while (idx < argc)
	{
		new_argv[idx] = argv[idx + 1];
		idx++;
	}
	new_argv[argc] = NULL;
	
	// new_argv에 잘 들어갔나 확인
	idx = 0;
	while(new_argv[idx])
	{
		printf("%s\n", new_argv[idx]);
		idx++;
	}
	
	// 명령어 실행!
	if (execve(absolute_path, new_argv, environ) == -1)
	{
		fprintf(stderr, "error: %s\n", strerror(errno));
		return (1);
	}
	printf("this is not exec\n");
	return (0);
}
