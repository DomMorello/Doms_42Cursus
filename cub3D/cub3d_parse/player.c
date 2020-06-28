/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:42:58 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 19:49:31 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	set_dir(t_mlx *mlx, double dirx, double diry)
{
	mlx->game.dirx = dirx;
	mlx->game.diry = diry;
}

void	set_plane(t_mlx *mlx, double planex, double planey)
{
	mlx->game.planex = planex;
	mlx->game.planey = planey;
}

void	set_playerpos(t_mlx *mlx, double x, double y)
{
	mlx->game.posx = x + 0.5;
	mlx->game.posy = y + 0.5;
}

void	input_direction(t_mlx *mlx, char direction, int x, int y)
{
	if (direction == 'N')
	{
		set_dir(mlx, -1, 0);
		set_plane(mlx, 0, 0.66);
	}
	else if (direction == 'S')
	{
		set_dir(mlx, 1, 0);
		set_plane(mlx, 0, -0.66);
	}
	else if (direction == 'E')
	{
		set_dir(mlx, 0, 1);
		set_plane(mlx, 0.66, 0);
	}
	else if (direction == 'W')
	{
		set_dir(mlx, 0, -1);
		set_plane(mlx, -0.66, 0);
	}
	set_playerpos(mlx, (double)x, (double)y);
}
