/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:41:04 by donglee           #+#    #+#             */
/*   Updated: 2020/07/04 13:43:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Checks if the line is the last line of the map info
** All the characters of the last line must be 1 or space 
*/

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

/*
** Makes a new node in the list with the given content as a parameter 
*/

t_map	*ft_lstnewmap(char *content)
{
	t_map *ret;

	if ((ret = (t_map *)malloc(sizeof(ret))) == NULL)
		return (NULL);
	ret->next = NULL;
	ret->row = content;
	return (ret);
}

/*
** The algorithm which checks if the map contents is valid
** if there is a vacant space right above and below 0
** it is not a wall surrounded map that is, returns error 
*/

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

/*
** In the map contents, right side of the map must ends with '1'
** If not, it is not a wall surrounded map 
*/

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
