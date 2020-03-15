#include "libft.h"

int ft_lstsize(t_list *lst)
{
	int len;

	len = 0;
	if (lst)
	{
		while (lst)
		{
			lst = lst->next;
			len++;
		}
	}
	return (len);
}
