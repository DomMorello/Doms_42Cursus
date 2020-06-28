/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:42:20 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 19:48:45 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	check_border(t_mlx *mlx, int mapsizey)
{
	int i;

	i = 0;
	while (mlx->map[0][i])
	{
		if (mlx->map[0][i] != '1' && !ft_isspace(mlx->map[0][i]))
			error(ERR_MAP_SUR, mlx);
		i++;
	}
	i = 0;
	while (mlx->map[mapsizey - 1][i])
	{
		if (mlx->map[mapsizey - 1][i] != '1' &&
			!ft_isspace(mlx->map[mapsizey - 1][i]))
			error(ERR_MAP_SUR, mlx);
		i++;
	}
	check_rightside(mlx, mapsizey);
}

void	check_direction(t_mlx *mlx, int mapsizey)
{
	int i;
	int j;
	int is_plural;

	i = 0;
	is_plural = 0;
	while (++i < mapsizey - 1)
	{
		j = 0;
		while (ft_isspace(mlx->map[i][j]))
			j++;
		while (j < (int)ft_strlen(mlx->map[i]) - 1)
		{
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' ||
				mlx->map[i][j] == 'E' || mlx->map[i][j] == 'W')
			{
				input_direction(mlx, mlx->map[i][j], i, j);
				mlx->map[i][j] = '0';
				is_plural++;
			}
			j++;
		}
	}
	if (is_plural != 1)
		error(ERR_PLU, mlx);
}

void	move_map_2d(t_mlx *mlx, int mapsizey)
{
	int		i;
	char	*tmp;
	t_map	*lst;

	i = 0;
	if ((mlx->map = (char **)malloc(sizeof(char *) * mapsizey + 1)) == NULL)
		error(ERR_MEM, mlx);
	mlx->map[mapsizey] = 0;
	lst = mlx->maplst;
	while (lst)
	{
		tmp = lst->row;
		if (tmp[ft_strlen(tmp) - 1] == '\r' || tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		mlx->map[i] = tmp;
		lst = lst->next;
		i++;
	}
}

int		get_mapsizey(t_mlx *mlx)
{
	int		len;
	t_map	*tmp;

	tmp = mlx->maplst;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	parse_map(t_mlx *mlx)
{
	int mapsizey;

	mapsizey = get_mapsizey(mlx);
	move_map_2d(mlx, mapsizey);
	check_direction(mlx, mapsizey);
	check_border(mlx, mapsizey);
	parse_contents(mlx, mapsizey);
	check_sprite(mlx, mapsizey);
}
