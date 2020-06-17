#include "./main.h"
#include <unistd.h>

t_map	*ft_lstnewmap(char *content)
{
	t_map *ret;

	if ((ret = (t_map *)malloc(sizeof(ret))) == 0)
		return (NULL);
	ret->next = NULL;
	ret->row = content;
	return (ret);
}

void	ft_lstaddmap_back(t_map **lst, t_map *new, char *row)
{
	t_map *tmp;

	if (lst)
	{
		if ((new = ft_lstnewmap(row)) == NULL)
			return (NULL);
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

void	func(t_mlx *mlx)
{
	mlx->map.row = "hello";
	t_map *new;
	t_map *lst;

	lst = &mlx->map;

	ft_lstaddmap_back(&lst, new, "world");
	ft_lstaddmap_back(&lst, new, "sex");
}

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	func(&mlx);
	t_map *lst;

	lst = &mlx.map;
	while (lst)
	{
		printf("%s\n", lst->row);
		lst = lst->next;
	}
	
	return 0;
}
