/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:09:55 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 20:36:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	transform_sprite(t_mlx *mlx, t_game *game, t_sprite *sprite)
{
	double inv_det;

	sprite->spritex = sprite->x - game->posx;
	sprite->spritey = sprite->y - game->posy;
	inv_det = 1.0 / (game->planex * game->diry - game->dirx * game->planey);
	sprite->transformx = inv_det * (game->diry * sprite->spritex -
						game->dirx * sprite->spritey);
	sprite->transformy = inv_det *
			(-game->planey * sprite->spritex + game->planex * sprite->spritey);
	sprite->sprite_screenx = (int)((mlx->win_width / 2) *
							(1 + sprite->transformx / sprite->transformy));
}

void	cal_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->sprite_height = abs((int)(mlx->win_height / (sprite->transformy)));
	sprite->draw_starty = -sprite->sprite_height / 2 + mlx->win_height / 2;
	if (sprite->draw_starty < 0)
		sprite->draw_starty = 0;
	sprite->draw_endy = sprite->sprite_height / 2 + mlx->win_height / 2;
	if (sprite->draw_endy >= mlx->win_height)
		sprite->draw_endy = mlx->win_height - 1;
	sprite->sprite_width = abs((int)(mlx->win_height / (sprite->transformy)));
	sprite->draw_startx = -sprite->sprite_width / 2 + sprite->sprite_screenx;
	if (sprite->draw_startx < 0)
		sprite->draw_startx = 0;
	sprite->draw_endx = sprite->sprite_width / 2 + sprite->sprite_screenx;
	if (sprite->draw_endx >= mlx->win_width)
		sprite->draw_endx = mlx->win_width - 1;
}

void	draw_spritey(t_mlx *mlx, t_sprite *sprite, int texx, int stripe)
{
	int texy;
	int y;
	int d;
	int color;

	y = sprite->draw_starty;
	while (y < sprite->draw_endy)
	{
		d = (y) * 256 - mlx->win_height * 128 + sprite->sprite_height * 128;
		texy = ((d * TEX_HEIGHT) / sprite->sprite_height) / 256;
		color = mlx->tex[SPRITE].data[TEX_WIDTH * texy + texx];
		if ((color & 0x00FFFFFF) != 0)
			mlx->img.data[stripe + mlx->win_width * y] = color;
		y++;
	}
}

void	draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
	int texx;
	int stripe;

	stripe = sprite->draw_startx;
	while (stripe < sprite->draw_endx)
	{
		texx = (int)(256 * (stripe - (-sprite->sprite_width / 2 +
			sprite->sprite_screenx)) * TEX_WIDTH / sprite->sprite_width) / 256;
		if (sprite->transformy > 0 && stripe > 0 && stripe <
				mlx->win_width && sprite->transformy < mlx->zbuffer[stripe])
			draw_spritey(mlx, sprite, texx, stripe);
		stripe++;
	}
}

void	render_sprite(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->sprite_num)
	{
		mlx->sprite[i].dist = ((mlx->game.posx - mlx->sprite[i].x) *
		(mlx->game.posx - mlx->sprite[i].x) +
		(mlx->game.posy - mlx->sprite[i].y) *
		(mlx->game.posy - mlx->sprite[i].y));
		i++;
	}
	desc_sort(mlx);
	i = 0;
	while (i < mlx->sprite_num)
	{
		transform_sprite(mlx, &mlx->game, &mlx->sprite[i]);
		cal_sprite(mlx, &mlx->sprite[i]);
		draw_sprite(mlx, &mlx->sprite[i]);
		i++;
	}
}
