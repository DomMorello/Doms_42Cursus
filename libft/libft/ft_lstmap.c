#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ret;
	t_list *node;

	if (lst && f && del)
	{
		ret = NULL;
		while (lst)
		{
			if ((node = ft_lstnew(f(lst->content))) == NULL)
			{
				ft_lstclear(&ret, del);
				return (NULL);
			}
			ft_lstadd_back(&ret, node);
			lst = lst->next;
		}
	}
	return (ret);
}
