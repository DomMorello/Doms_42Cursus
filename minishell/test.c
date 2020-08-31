#include "minishell.h"

extern char **environ;

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

	t_list head;
	head.content = "ceiling";
	head.next = NULL;
	t_list *list = &head;

	t_list *p1 = ft_lstnew("abortion");
	ft_lstadd_back(&list, p1);
	t_list *p2 = ft_lstnew("delight");
	ft_lstadd_back(&list, p2);
	t_list *p3 = ft_lstnew("boring");
	ft_lstadd_back(&list, p3);

	int swapped = 1;
	t_list *ptr1;
	t_list *lptr = NULL;

	while (swapped)
	{
		swapped = 0;
		ptr1 = list;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->content, ptr1->next->content, ft_strlen(ptr1->content)) >= 0)
			{
				char *tmp = ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	return (0);
}
