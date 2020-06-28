/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:13:34 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 20:36:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_side(t_mlx *mlx)
{
	int wall_side;

	if (mlx->game.side == 0 && mlx->game.ray_dirx > 0)
		wall_side = NORTH;
	if (mlx->game.side == 0 && mlx->game.ray_dirx < 0)
		wall_side = SOUTH;
	if (mlx->game.side == 1 && mlx->game.ray_diry > 0)
		wall_side = EAST;
	if (mlx->game.side == 1 && mlx->game.ray_diry < 0)
		wall_side = WEST;
	return (wall_side);
}

void	input_verline(t_mlx *mlx, int texx, int i)
{
	double	step;
	double	tex_pos;
	int		wall_side;
	int		texy;
	int		color;

	step = 1.0 * TEX_HEIGHT / mlx->game.line_height;
	tex_pos = (mlx->game.draw_start - mlx->win_height / 2 +
				mlx->game.line_height / 2) * step;
	wall_side = get_side(mlx);
	while (mlx->game.draw_start < mlx->game.draw_end)
	{
		texy = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = mlx->tex[wall_side].data[TEX_HEIGHT * texy + texx];
		mlx->img.data[i + mlx->win_width * mlx->game.draw_start] = color;
		mlx->game.draw_start++;
	}
}
