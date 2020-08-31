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
