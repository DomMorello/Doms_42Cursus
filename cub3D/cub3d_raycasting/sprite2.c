/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:12:45 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 15:22:43 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
