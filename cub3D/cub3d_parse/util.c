/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:41:39 by donglee           #+#    #+#             */
/*   Updated: 2020/07/04 14:52:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** delete a node from a list 
*/

void	ft_lstmapdelone(t_map *node)
{
	if (node)
	{
		free(node->row);
		node->row = NULL;
		free(node);
		node = NULL;
	}
}

/*
** clear the list of map 
*/

void	ft_lstmapclear(t_map **lst)
{
	t_map *tmp;

	if (lst && *lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstmapdelone(*lst);
			(*lst) = tmp;
		}
		*lst = NULL;
	}
}

/*
** returns -1(ERROR) and outputs the string of 'str'
*/

int		error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (ERROR);
}

int		ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int		free_2d_char(char **ret, int flag)
{
	int i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	ret = NULL;
	return (flag);
}
