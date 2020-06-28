/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorCeiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:08:58 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 20:36:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_fc(t_mlx *mlx, int x, int y)
{
	int tx;
	int ty;
	int color;

	tx = (int)(TEX_WIDTH *
			(mlx->fc.floorx - (int)mlx->fc.floorx)) & (TEX_WIDTH - 1);
	ty = (int)(TEX_HEIGHT *
			(mlx->fc.floory - (int)mlx->fc.floory)) & (TEX_HEIGHT - 1);
	mlx->fc.floorx += mlx->fc.floor_stepx;
	mlx->fc.floory += mlx->fc.floor_stepy;
	if (mlx->tex[FLOOR].img_ptr != NULL)
		color = mlx->tex[FLOOR].data[TEX_WIDTH * ty + tx];
	else
		color = mlx->tex[FLOOR].floor_color;
	mlx->img.data[x + mlx->win_width * y] = color;
	if (mlx->tex[CEILING].img_ptr != NULL)
		color = mlx->tex[CEILING].data[TEX_WIDTH * ty + tx];
	else
		color = mlx->tex[CEILING].ceiling_color;
	mlx->img.data[x + mlx->win_width * (mlx->win_height - y - 1)] = color;
}

void	get_position(t_mlx *mlx, int y)
{
	int		p;
	float	posz;
	float	row_distance;

	p = y - mlx->win_height / 2;
	posz = 0.5 * mlx->win_height;
	row_distance = posz / p;
	mlx->fc.floor_stepx = row_distance *
						 (mlx->fc.ray_dirx1 - mlx->fc.ray_dirx0) / mlx->win_width;
	mlx->fc.floor_stepy = row_distance *
						 (mlx->fc.ray_diry1 - mlx->fc.ray_diry0) / mlx->win_width;
	mlx->fc.floorx = mlx->game.posx + row_distance * mlx->fc.ray_dirx0;
	mlx->fc.floory = mlx->game.posy + row_distance * mlx->fc.ray_diry0;
}

void	draw_floor_ceiling(t_mlx *mlx)
{
	int y;
	int x;

	y = 0;
	while (y < mlx->win_height)
	{
		mlx->fc.ray_dirx0 = mlx->game.dirx - mlx->game.planex;
		mlx->fc.ray_diry0 = mlx->game.diry - mlx->game.planey;
		mlx->fc.ray_dirx1 = mlx->game.dirx + mlx->game.planex;
		mlx->fc.ray_diry1 = mlx->game.diry + mlx->game.planey;
		get_position(mlx, y);
		x = 0;
		while (x < mlx->win_width)
		{
			draw_fc(mlx, x, y);
			x++;
		}
		y++;
	}
}

int		run_game(t_mlx *mlx)
{
	int i;

	i = 0;
	draw_floor_ceiling(mlx);
	if (mlx->game.move_f || mlx->game.move_b || mlx->game.move_r ||
		mlx->game.move_l || mlx->game.rotate_r || mlx->game.rotate_l)
		key_event(mlx);
	while (i < mlx->win_width)
	{
		set_var(mlx, i);
		perform_dda(mlx);
		draw_vertline(mlx, i);
		mlx->zbuffer[i] = mlx->game.perp_wall_dist;
		i++;
	}
	render_sprite(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (TRUE);
}
