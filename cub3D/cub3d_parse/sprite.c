/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:44:25 by donglee           #+#    #+#             */
/*   Updated: 2020/07/06 16:21:05 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** According the map, decides the position of the sprites
*/

void	input_sprite(t_sprite *sprites, char **map, int mapsizey)
{
	int i;
	int j;
	int idx;

	i = 1;
	idx = 0;
	while (i < mapsizey)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (map[i][j + 1])
		{
			if (map[i][j + 1] == '2')
			{
				sprites[idx].x = i + 0.5;
				sprites[idx].y = j + 1.5;
				idx++;
			}
			j++;
		}
		i++;
	}
}

/*
** Counts the number of sprites in the map contents
** This is used to compare distance from the player to the sprites
*/

int		count_sprite(char **map, int mapsizey)
{
	int i;
	int j;
	int sprite_num;

	i = 1;
	sprite_num = 0;
	while (i < mapsizey - 1)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (map[i][j + 1])
		{
			if (map[i][j + 1] == '2')
				sprite_num++;
			j++;
		}
		i++;
	}
	return (sprite_num);
}

void	check_sprite(t_mlx *mlx, int mapsizey)
{
	int			sprite_num;
	t_sprite	*sprites;

	sprite_num = count_sprite(mlx->map, mapsizey);
	if ((sprites = (t_sprite *)malloc(sizeof(t_sprite) * sprite_num)) == NULL)
		error(ERR_MEM, mlx);
	input_sprite(sprites, mlx->map, mapsizey);
	mlx->sprite_num = sprite_num;
	mlx->sprite = sprites;
}
