#include "libft.h"

t_list  *ft_lstnew(void *content)
{
	t_list *ret;

	// ret = NULL;
	if ((ret = (t_list *)malloc(sizeof(ret))) == 0)
		return (NULL);
	// ret->next = NULL;
	// if (!content)
		// ret->content = NULL;
	// else
		ret->content = content;
	return (ret);
}

int main()
{
	t_list *test;
	int a = 3;
	int *ptr = &a;
	test = ft_lstnew(NULL);
	printf("test: %p\n", test->content);
	return 0;
}