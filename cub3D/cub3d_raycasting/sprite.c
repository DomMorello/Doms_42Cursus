/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:09:55 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 01:12:33 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	transform_sprite(t_mlx *mlx, t_game *game, t_sprite *sprite)
{
	double invDet;

	sprite->spriteX = sprite->x - game->posX;
	sprite->spriteY = sprite->y - game->posY;
	invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);
	sprite->transformX = invDet * (game->dirY * sprite->spriteX -
						game->dirX * sprite->spriteY);
	sprite->transformY = invDet *
			(-game->planeY * sprite->spriteX + game->planeX * sprite->spriteY);
	sprite->spriteScreenX = (int)((mlx->winWidth / 2) *
							(1 + sprite->transformX / sprite->transformY));
}

void	cal_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->spriteHeight = abs((int)(mlx->winHeight / (sprite->transformY)));
	sprite->drawStartY = -sprite->spriteHeight / 2 + mlx->winHeight / 2;
	if (sprite->drawStartY < 0)
		sprite->drawStartY = 0;
	sprite->drawEndY = sprite->spriteHeight / 2 + mlx->winHeight / 2;
	if (sprite->drawEndY >= mlx->winHeight)
		sprite->drawEndY = mlx->winHeight - 1;
	sprite->spriteWidth = abs((int)(mlx->winHeight / (sprite->transformY)));
	sprite->drawStartX = -sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawStartX < 0)
		sprite->drawStartX = 0;
	sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawEndX >= mlx->winWidth)
		sprite->drawEndX = mlx->winWidth - 1;
}

void	draw_spriteY(t_mlx *mlx, t_sprite *sprite, int texX, int stripe)
{
	int texY;
	int y;
	int d;
	int color;

	y = sprite->drawStartY;
	while (y < sprite->drawEndY)
	{
		d = (y) * 256 - mlx->winHeight * 128 + sprite->spriteHeight * 128;
		texY = ((d * TEX_HEIGHT) / sprite->spriteHeight) / 256;
		color = mlx->tex[SPRITE].data[TEX_WIDTH * texY + texX];
		if ((color & 0x00FFFFFF) != 0)
			mlx->img.data[stripe + mlx->winWidth * y] = color;
		y++;
	}
}

void	draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
	int texX;
	int stripe;

	stripe = sprite->drawStartX;
	while (stripe < sprite->drawEndX)
	{
		texX = (int)(256 * (stripe - (-sprite->spriteWidth / 2 +
			sprite->spriteScreenX)) * TEX_WIDTH / sprite->spriteWidth) / 256;
		if (sprite->transformY > 0 && stripe > 0 && stripe <
				mlx->winWidth && sprite->transformY < mlx->zbuffer[stripe])
			draw_spriteY(mlx, sprite, texX, stripe);
		stripe++;
	}
}

void	render_sprite(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->spriteNum)
	{
		mlx->sprite[i].dist = ((mlx->game.posX - mlx->sprite[i].x) *
		(mlx->game.posX - mlx->sprite[i].x) +
		(mlx->game.posY - mlx->sprite[i].y) *
		(mlx->game.posY - mlx->sprite[i].y));
		i++;
	}
	desc_sort(mlx);
	i = 0;
	while (i < mlx->spriteNum)
	{
		transform_sprite(mlx, &mlx->game, &mlx->sprite[i]);
		cal_sprite(mlx, &mlx->sprite[i]);
		draw_sprite(mlx, &mlx->sprite[i]);
		i++;
	}
}
