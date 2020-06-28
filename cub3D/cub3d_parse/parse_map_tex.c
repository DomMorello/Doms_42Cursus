/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:43:37 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 19:52:15 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int		which_tex(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		return (SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WEST);
	else if (line[0] == 'E' && line[1] == 'A')
		return (EAST);
	else if (line[0] == 'S')
		return (SPRITE);
	else if (line[0] == 'F')
		return (FLOOR);
	else if (line[0] == 'C')
		return (CEILING);
	else if (line[0] == 0 || line[0] == '1' || line[0] == 'R')
		return (PASS);
	else
		return (ERROR);
}

int		input_tex(t_mlx *mlx, int tex, char *line)
{
	int space;
	int i;

	i = 0;
	if (tex != ERROR && tex != PASS)
	{
		if (tex >= 0 && tex <= 3)
			space = 2;
		else
			space = 1;
		while (space--)
			i++;
		while (ft_isspace(line[i]))
			i++;
		if ((mlx->tex[tex].filepath = ft_strdup(&line[i])) == NULL)
			return (error(ERR_MEM, mlx));
	}
	return (TRUE);
}

int		copy_map(t_mlx *mlx, char *line)
{
	int		i;
	t_map	*new;

	i = 0;
	new = NULL;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 0)
		return (PASS);
	if (line[i] != '1')
		return (error(ERR_MAP_SUR, mlx));
	while (line[i])
	{
		if (!is_valid_letter(line[i]))
			return (error(ERR_LETTER, mlx));
		i++;
	}
	if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
		return (error(ERR_MEM, mlx));
	return (TRUE);
}

int		is_valid_letter(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N' ||
		c == 'S' || c == 'W' || c == 'E')
		return (TRUE);
	else if (ft_isspace(c) || c == '\r' || c == '\n')
		return (TRUE);
	return (FALSE);
}

int		ft_lstaddmap_back(t_map **lst, t_map *new, char *row)
{
	t_map *tmp;

	if (lst)
	{
		if ((new = ft_lstnewmap(row)) == NULL)
			return (ERROR);
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
	return (TRUE);
}
