#include "minishell.h"

extern char **environ;

int	main(int argc, char *argv[])
{
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
	char *s = "hello";
	s[3] = 'g';
	
	return (0);
}
