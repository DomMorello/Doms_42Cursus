/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:41:04 by donglee           #+#    #+#             */
/*   Updated: 2020/07/01 15:36:58 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_end_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_map	*ft_lstnewmap(char *content)
{
	t_map *ret;

	if ((ret = (t_map *)malloc(sizeof(ret))) == NULL)
		return (NULL);
	ret->next = NULL;
	ret->row = content;
	return (ret);
}

void	check_updown(int i, int j, t_mlx *mlx)
{
	if (ft_isspace(mlx->map[i - 1][j + 1]))
		error(ERR_MAP_SUR, mlx);
	if ((int)ft_strlen(mlx->map[i + 1]) > j + 1)
	{
		if (ft_isspace(mlx->map[i + 1][j + 1]))
			error(ERR_MAP_SUR, mlx);
	}
	else
		error(ERR_MAP_SUR, mlx);
}

void	parse_contents(t_mlx *mlx, int mapsizey)
{
	int i;
	int j;

	i = 1;
	while (i < mapsizey - 1)
	{
		j = 0;
		while (ft_isspace(mlx->map[i][j]))
			j++;
		while (j < (int)ft_strlen(mlx->map[i]) - 1)
		{
			if (mlx->map[i][j + 1] == '0')
			{
				check_updown(i, j, mlx);
				if (ft_isspace(mlx->map[i][j]) ||
					ft_isspace(mlx->map[i][j + 2]))
					error(ERR_MAP_SUR, mlx);
			}
			j++;
		}
		i++;
	}
}

void	check_rightside(t_mlx *mlx, int mapsizey)
{
	int i;
	int j;

	i = 0;
	while (i < mapsizey)
	{
		j = ft_strlen(mlx->map[i]) - 1;
		while (ft_isspace(mlx->map[i][j]))
			j--;
		if (mlx->map[i][j] != '1')
			error(ERR_MAP_SUR, mlx);
		i++;
	}
}
