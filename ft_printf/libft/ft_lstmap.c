#include "libft.h"

void	*ffunc(void *content)
{
	// printf("ffunc content: %p\n", content);
	return content;
}

void	dfunc(void *content)
{
	int a = 1;
	// printf("dfunc content: %p\n", content);
	if (content)
		a += 1;
}

// t_list  *ft_lstnew(void *content)
// {
// 	t_list *ret;

// 	if ((ret = (t_list *)malloc(sizeof(ret))) == 0)
// 		return (NULL);
// 	ret->next = NULL;
// 	ret->content = content;
// 	return (ret);
// }

// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	if (lst)
// 	{
// 		if (del)
// 			del(lst->content);
// 		free(lst);
// 	}
// }

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list *tmp;

// 	if (lst && *lst && del)
// 	{
// 		while (*lst)
// 		{
// 			tmp = (*lst)->next;
// 			ft_lstdelone(*lst, del);
// 			(*lst) = tmp;
// 		}
// 		*lst = NULL; 
// 	}
// }

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list *tmp;

// 	if (lst)
// 	{
// 		tmp = *lst;
// 		if (!tmp)
// 			*lst = new;
// 		else
// 		{
// 			while (tmp->next)
// 				tmp = tmp->next;
// 			tmp->next = new;
// 		}
// 	}
// }

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ret;
	t_list *node;

	ret = NULL;
	if (lst && f && del)
	{
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

int main()
{
	t_list one;
	t_list two;
	t_list three;

	t_list *pone = &one;
	t_list *ptwo = &two;
	t_list *pthree = &three;

	pone->next = ptwo;
	ptwo->next = pthree;
	pthree->next = NULL;

	printf("pone: %p\n", pone);
	printf("ptwo: %p\n", ptwo);
	printf("pthree: %p\n", pthree);
	void *(*f)(void *) = ffunc;
	void (*del)(void *) = dfunc;

	t_list *result = ft_lstmap(pone, f, del);
	while (result) 
	{
		printf("result: %p\n", result);
		result = result->next;
	}
	printf("result->next: %p\n", result->next);
	return 0;
}
