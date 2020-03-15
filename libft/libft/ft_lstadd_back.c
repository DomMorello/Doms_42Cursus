#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (lst)
	{
		tmp = *lst;
		if (!tmp)
			*lst = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

// int main()
// {
// 	t_list one;
// 	t_list two;
// 	t_list three;
// 	t_list four;
// 	t_list five;

// 	t_list *pone = &one;
// 	t_list *ptwo = &two;
// 	t_list *pthree = &three;
// 	t_list *pfour = &four;
// 	t_list *pfive = &five;

// 	pone->next = ptwo;
// 	ptwo->next = pthree;
// 	pthree->next = pfour;
// 	pfour->next = pfive;
// 	pfive->next = NULL;

// 	return 0;
// }