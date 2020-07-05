/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:12:45 by donglee           #+#    #+#             */
/*   Updated: 2020/07/05 19:36:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Sorts the arrrays of sprites accoding to the distance from player
** so that the near sprite will block the farther one   
*/

void	desc_sort(t_mlx *mlx)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < mlx->sprite_num)
	{
		j = i;
		while (j < mlx->sprite_num)
		{
			if (mlx->sprite[i].dist < mlx->sprite[j].dist)
			{
				tmp = mlx->sprite[i];
				mlx->sprite[i] = mlx->sprite[j];
				mlx->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
