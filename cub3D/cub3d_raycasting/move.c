/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:09:33 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 20:36:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_right(t_mlx *mlx, double rot_speed)
{
	double old_dirx;
	double old_planex;

	if (mlx->game.rotate_r == 1)
	{
		old_dirx = mlx->game.dirx;
		mlx->game.dirx = mlx->game.dirx * cos(-rot_speed) -
							mlx->game.diry * sin(-rot_speed);
		mlx->game.diry = old_dirx * sin(-rot_speed) +
							mlx->game.diry * cos(-rot_speed);
		old_planex = mlx->game.planex;
		mlx->game.planex = mlx->game.planex * cos(-rot_speed) -
							mlx->game.planey * sin(-rot_speed);
		mlx->game.planey = old_planex * sin(-rot_speed) +
							mlx->game.planey * cos(-rot_speed);
	}
}

void	rotate_left(t_mlx *mlx, double rot_speed)
{
	double old_dirx;
	double old_planex;

	if (mlx->game.rotate_l == 1)
	{
		old_dirx = mlx->game.dirx;
		mlx->game.dirx = mlx->game.dirx * cos(rot_speed) -
							mlx->game.diry * sin(rot_speed);
		mlx->game.diry = old_dirx * sin(rot_speed) +
							mlx->game.diry * cos(rot_speed);
		old_planex = mlx->game.planex;
		mlx->game.planex = mlx->game.planex * cos(rot_speed) -
							mlx->game.planey * sin(rot_speed);
		mlx->game.planey = old_planex * sin(rot_speed) +
							mlx->game.planey * cos(rot_speed);
	}
}

void	move_side(t_mlx *mlx)
{
	if (mlx->game.move_r == 1)
	{
		if (mlx->map[(int)(mlx->game.posx + mlx->game.planex * 0.01)]
			[(int)mlx->game.posy] == '0')
			mlx->game.posx += mlx->game.planex * 0.01;
		if (mlx->map[(int)mlx->game.posx]
			[(int)(mlx->game.posy + mlx->game.planey * 0.01)] == '0')
			mlx->game.posy += mlx->game.planey * 0.01;
	}
	if (mlx->game.move_l == 1)
	{
		if (mlx->map[(int)(mlx->game.posx - mlx->game.planex * 0.01)]
			[(int)mlx->game.posy] == '0')
			mlx->game.posx -= mlx->game.planex * 0.01;
		if (mlx->map[(int)mlx->game.posx]
			[(int)(mlx->game.posy - mlx->game.planey * 0.01)] == '0')
			mlx->game.posy -= mlx->game.planey * 0.01;
	}
}

void	move_forback(t_mlx *mlx, double move_speed)
{
	if (mlx->game.move_f == 1)
	{
		if (mlx->map[(int)(mlx->game.posx + mlx->game.dirx * move_speed)]
			[(int)mlx->game.posy] == '0')
			mlx->game.posx += mlx->game.dirx * move_speed;
		if (mlx->map[(int)mlx->game.posx]
			[(int)(mlx->game.posy + mlx->game.diry * move_speed)] == '0')
			mlx->game.posy += mlx->game.diry * move_speed;
	}
	if (mlx->game.move_b == 1)
	{
		if (mlx->map[(int)(mlx->game.posx - mlx->game.dirx * move_speed)]
			[(int)mlx->game.posy] == '0')
			mlx->game.posx -= mlx->game.dirx * move_speed;
		if (mlx->map[(int)mlx->game.posx]
			[(int)(mlx->game.posy - mlx->game.diry * move_speed)] == '0')
			mlx->game.posy -= mlx->game.diry * move_speed;
	}
}
