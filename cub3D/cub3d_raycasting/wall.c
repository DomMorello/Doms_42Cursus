/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:12:59 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 15:28:21 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	draw_vertline(t_mlx *mlx, int i)
{
	double	wallx;
	int		texx;

	if (mlx->game.side == 0)
		wallx = mlx->game.posy + mlx->game.perp_wall_dist * mlx->game.ray_diry;
	else
		wallx = mlx->game.posx + mlx->game.perp_wall_dist * mlx->game.ray_dirx;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)TEX_WIDTH);
	if (mlx->game.side == 0 && mlx->game.ray_dirx > 0)
		texx = TEX_WIDTH - texx - 1;
	if (mlx->game.side == 1 && mlx->game.ray_diry < 0)
		texx = TEX_WIDTH - texx - 1;
	input_verline(mlx, texx, i);
}

void	set_draw(t_mlx *mlx)
{
	mlx->game.line_height = (int)(mlx->win_height / mlx->game.perp_wall_dist);
	mlx->game.draw_start = -mlx->game.line_height / 2 + mlx->win_height / 2;
	if (mlx->game.draw_start < 0)
		mlx->game.draw_start = 0;
	mlx->game.draw_end = mlx->game.line_height / 2 + mlx->win_height / 2;
	if (mlx->game.draw_end >= mlx->win_height)
		mlx->game.draw_end = mlx->win_height - 1;
}

void	perform_dda(t_mlx *mlx)
{
	while (mlx->game.hit == 0)
	{
		if (mlx->game.side_distx < mlx->game.side_disty)
		{
			mlx->game.side_distx += mlx->game.delta_distx;
			mlx->game.mapx += mlx->game.stepx;
			mlx->game.side = 0;
		}
		else
		{
			mlx->game.side_disty += mlx->game.delta_disty;
			mlx->game.mapy += mlx->game.stepy;
			mlx->game.side = 1;
		}
		if (mlx->map[mlx->game.mapx][mlx->game.mapy] == '1')
			mlx->game.hit = 1;
	}
	if (mlx->game.side == 0)
		mlx->game.perp_wall_dist = (mlx->game.mapx - mlx->game.posx +
			(1 - mlx->game.stepx) / 2) / mlx->game.ray_dirx;
	else
		mlx->game.perp_wall_dist = (mlx->game.mapy - mlx->game.posy +
			(1 - mlx->game.stepy) / 2) / mlx->game.ray_diry;
	set_draw(mlx);
}

void	set_side_dist(t_mlx *mlx)
{
	if (mlx->game.ray_dirx < 0)
	{
		mlx->game.stepx = -1;
		mlx->game.side_distx = (mlx->game.posx - mlx->game.mapx) *
								mlx->game.delta_distx;
	}
	else
	{
		mlx->game.stepx = 1;
		mlx->game.side_distx = (mlx->game.mapx + 1.0 - mlx->game.posx) *
								mlx->game.delta_distx;
	}
	if (mlx->game.ray_diry < 0)
	{
		mlx->game.stepy = -1;
		mlx->game.side_disty = (mlx->game.posy - mlx->game.mapy) *
								mlx->game.delta_disty;
	}
	else
	{
		mlx->game.stepy = 1;
		mlx->game.side_disty = (mlx->game.mapy + 1.0 - mlx->game.posy) *
								mlx->game.delta_disty;
	}
}

void	set_var(t_mlx *mlx, int i)
{
	mlx->game.camerax = 2 * i / (double)mlx->win_width - 1;
	mlx->game.ray_dirx = mlx->game.dirx + mlx->game.planex * mlx->game.camerax;
	mlx->game.ray_diry = mlx->game.diry + mlx->game.planey * mlx->game.camerax;
	mlx->game.mapx = (int)mlx->game.posx;
	mlx->game.mapy = (int)mlx->game.posy;
	if (mlx->game.ray_diry == 0)
		mlx->game.delta_distx = 0;
	else
		mlx->game.delta_distx = (mlx->game.ray_dirx == 0) ? 1 :
								fabs(1 / mlx->game.ray_dirx);
	if (mlx->game.ray_dirx == 0)
		mlx->game.delta_disty = 0;
	else
		mlx->game.delta_disty = (mlx->game.ray_diry == 0) ? 1 :
								fabs(1 / mlx->game.ray_diry);
	mlx->game.hit = 0;
	set_side_dist(mlx);
}
