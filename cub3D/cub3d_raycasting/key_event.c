/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:09:19 by donglee           #+#    #+#             */
/*   Updated: 2020/07/01 16:31:29 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		key_press(int key, t_mlx *mlx)
{
	if (key == MAC_KEY_W)
		mlx->game.move_f = 1;
	if (key == MAC_KEY_S)
		mlx->game.move_b = 1;
	if (key == MAC_KEY_A)
		mlx->game.move_l = 1;
	if (key == MAC_KEY_D)
		mlx->game.move_r = 1;
	if (key == MAC_KEY_LEFT)
		mlx->game.rotate_l = 1;
	if (key == MAC_KEY_RIGHT)
		mlx->game.rotate_r = 1;
	if (key == MAC_KEY_ESC)
		error("exit game", mlx);
	return (TRUE);
}

int		key_release(int key, t_mlx *mlx)
{
	if (key == MAC_KEY_W)
		mlx->game.move_f = 0;
	if (key == MAC_KEY_S)
		mlx->game.move_b = 0;
	if (key == MAC_KEY_A)
		mlx->game.move_l = 0;
	if (key == MAC_KEY_D)
		mlx->game.move_r = 0;
	if (key == MAC_KEY_LEFT)
		mlx->game.rotate_l = 0;
	if (key == MAC_KEY_RIGHT)
		mlx->game.rotate_r = 0;
	return (TRUE);
}

void	key_event(t_mlx *mlx)
{
	double move_speed;
	double rot_speed;

	move_speed = 0.06;
	rot_speed = 0.024;
	move_forback(mlx, move_speed);
	move_side(mlx);
	rotate_right(mlx, rot_speed);
	rotate_left(mlx, rot_speed);
}
