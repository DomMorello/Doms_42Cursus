#include "./main.h"

void set_side_dist(t_mlx *mlx)
{
	if (mlx->game.rayDirX < 0)
	{
		mlx->game.stepX = -1;
		mlx->game.sideDistX = (mlx->game.posX - mlx->game.mapX) *
								mlx->game.deltaDistX;
	}
	else
	{
		mlx->game.stepX = 1;
		mlx->game.sideDistX = (mlx->game.mapX + 1.0 - mlx->game.posX) *
								mlx->game.deltaDistX;
	}
	if (mlx->game.rayDirY < 0)
	{
		mlx->game.stepY = -1;
		mlx->game.sideDistY = (mlx->game.posY - mlx->game.mapY) *
								mlx->game.deltaDistY;
	}
	else
	{
		mlx->game.stepY = 1;
		mlx->game.sideDistY = (mlx->game.mapY + 1.0 - mlx->game.posY) *
								mlx->game.deltaDistY;
	}
}

void set_var(t_mlx *mlx, int i)
{
	mlx->game.cameraX = 2 * i / (double)mlx->winWidth - 1;
	mlx->game.rayDirX = mlx->game.dirX + mlx->game.planeX * mlx->game.cameraX;
	mlx->game.rayDirY = mlx->game.dirY + mlx->game.planeY * mlx->game.cameraX;
	mlx->game.mapX = (int)mlx->game.posX;
	mlx->game.mapY = (int)mlx->game.posY;
	mlx->game.deltaDistX = (mlx->game.rayDirY == 0) ? 0 :
			((mlx->game.rayDirX == 0) ? 1 : fabs(1 / mlx->game.rayDirX));
	mlx->game.deltaDistY = (mlx->game.rayDirX == 0) ? 0 :
			((mlx->game.rayDirY == 0) ? 1 : fabs(1 / mlx->game.rayDirY));
	mlx->game.hit = 0;
	set_side_dist(mlx);
}

void set_draw(t_mlx *mlx)
{
	mlx->game.lineHeight = (int)(mlx->winHeight / mlx->game.perpWallDist);
	mlx->game.drawStart = -mlx->game.lineHeight / 2 + mlx->winHeight / 2;
	if (mlx->game.drawStart < 0)
		mlx->game.drawStart = 0;
	mlx->game.drawEnd = mlx->game.lineHeight / 2 + mlx->winHeight / 2;
	if (mlx->game.drawEnd >= mlx->winHeight)
		mlx->game.drawEnd = mlx->winHeight - 1;
}

void perform_DDA(t_mlx *mlx)
{
	while (mlx->game.hit == 0)
	{
		if (mlx->game.sideDistX < mlx->game.sideDistY)
		{
			mlx->game.sideDistX += mlx->game.deltaDistX;
			mlx->game.mapX += mlx->game.stepX;
			mlx->game.side = 0;
		}
		else
		{
			mlx->game.sideDistY += mlx->game.deltaDistY;
			mlx->game.mapY += mlx->game.stepY;
			mlx->game.side = 1;
		}
		if (mlx->map[mlx->game.mapX][mlx->game.mapY] == '1')
			mlx->game.hit = 1;
	}
	if (mlx->game.side == 0)
		mlx->game.perpWallDist = (mlx->game.mapX - mlx->game.posX +
			(1 - mlx->game.stepX) / 2) / mlx->game.rayDirX;
	else
		mlx->game.perpWallDist = (mlx->game.mapY - mlx->game.posY +
			(1 - mlx->game.stepY) / 2) / mlx->game.rayDirY;
	set_draw(mlx);
}

int get_side(t_mlx *mlx)
{
	int wall_side;

	if (mlx->game.side == 0 && mlx->game.rayDirX > 0)
		wall_side = NORTH;
	if (mlx->game.side == 0 && mlx->game.rayDirX < 0)
		wall_side = SOUTH;
	if (mlx->game.side == 1 && mlx->game.rayDirY > 0)
		wall_side = EAST;
	if (mlx->game.side == 1 && mlx->game.rayDirY < 0)
		wall_side = WEST;
	return (wall_side);
}

void input_verline(t_mlx *mlx, int texX, int i)
{
	double step;
	double texPos;
	int wallSide;

	step = 1.0 * TEX_HEIGHT / mlx->game.lineHeight;
	texPos = (mlx->game.drawStart - mlx->winHeight / 2 +
				mlx->game.lineHeight / 2) * step;
	wallSide = get_side(mlx);
	while (mlx->game.drawStart < mlx->game.drawEnd)
	{
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		int color = mlx->tex[wallSide].data[TEX_HEIGHT * texY + texX];
		mlx->img.data[i + mlx->winWidth * mlx->game.drawStart] = color;
		mlx->game.drawStart++;
	}
}

void draw_vertline(t_mlx *mlx, int i)
{
	double wallX;
	int texX;

	if (mlx->game.side == 0)
		wallX = mlx->game.posY + mlx->game.perpWallDist * mlx->game.rayDirY;
	else
		wallX = mlx->game.posX + mlx->game.perpWallDist * mlx->game.rayDirX;
	wallX -= floor(wallX);

	texX = (int)(wallX * (double)TEX_WIDTH);
	if (mlx->game.side == 0 && mlx->game.rayDirX > 0)
		texX = TEX_WIDTH - texX - 1;
	if (mlx->game.side == 1 && mlx->game.rayDirY < 0)
		texX = TEX_WIDTH - texX - 1;
	input_verline(mlx, texX, i);
}

void move_forback(t_mlx *mlx, double moveSpeed, double rotSpeed)
{
	if (mlx->game.move_f == 1)
	{
		if (mlx->map[(int)(mlx->game.posX + mlx->game.dirX * moveSpeed)]
			[(int)mlx->game.posY] == '0')
			mlx->game.posX += mlx->game.dirX * moveSpeed;
		if (mlx->map[(int)mlx->game.posX]
			[(int)(mlx->game.posY + mlx->game.dirY * moveSpeed)] == '0')
			mlx->game.posY += mlx->game.dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (mlx->game.move_b == 1)
	{
		if (mlx->map[(int)(mlx->game.posX - mlx->game.dirX * moveSpeed)]
			[(int)mlx->game.posY] == '0')
			mlx->game.posX -= mlx->game.dirX * moveSpeed;
		if (mlx->map[(int)mlx->game.posX]
			[(int)(mlx->game.posY - mlx->game.dirY * moveSpeed)] == '0')
			mlx->game.posY -= mlx->game.dirY * moveSpeed;
	}
}

void move_side(t_mlx *mlx, double moveSpeed, double rotSpeed)
{
	if (mlx->game.move_r == 1)
	{
		if (mlx->map[(int)(mlx->game.posX + mlx->game.planeX * 0.01)]
			[(int)mlx->game.posY] == '0')
			mlx->game.posX += mlx->game.planeX * 0.01;
		if (mlx->map[(int)mlx->game.posX]
			[(int)(mlx->game.posY + mlx->game.planeY * 0.01)] == '0')
			mlx->game.posY += mlx->game.planeY * 0.01;
	}
	if (mlx->game.move_l == 1)
	{
		if (mlx->map[(int)(mlx->game.posX - mlx->game.planeX * 0.01)]
			[(int)mlx->game.posY] == '0')
			mlx->game.posX -= mlx->game.planeX * 0.01;
		if (mlx->map[(int)mlx->game.posX]
			[(int)(mlx->game.posY - mlx->game.planeY * 0.01)] == '0')
			mlx->game.posY -= mlx->game.planeY * 0.01;
	}
}

void rotate_right(t_mlx *mlx, double moveSpeed, double rotSpeed)
{
	double oldDirX;

	if (mlx->game.rotate_r == 1)
	{
		oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(-rotSpeed) -
							mlx->game.dirY * sin(-rotSpeed);
		mlx->game.dirY = oldDirX * sin(-rotSpeed) +
							mlx->game.dirY * cos(-rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(-rotSpeed) -
							mlx->game.planeY * sin(-rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(-rotSpeed) +
							mlx->game.planeY * cos(-rotSpeed);
	}
}

void rotate_left(t_mlx *mlx, double moveSpeed, double rotSpeed)
{
	double oldDirX;

	if (mlx->game.rotate_l == 1)
	{
		oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(rotSpeed) -
							mlx->game.dirY * sin(rotSpeed);
		mlx->game.dirY = oldDirX * sin(rotSpeed) +
							mlx->game.dirY * cos(rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(rotSpeed) -
							mlx->game.planeY * sin(rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(rotSpeed) +
							mlx->game.planeY * cos(rotSpeed);
	}
}

void key_event(t_mlx *mlx)
{
	double moveSpeed;
	double rotSpeed;

	moveSpeed = 0.018;
	rotSpeed = 0.009;
	move_forback(mlx, moveSpeed, rotSpeed);
	move_side(mlx, moveSpeed, rotSpeed);
	rotate_right(mlx, moveSpeed, rotSpeed);
	rotate_left(mlx, moveSpeed, rotSpeed);
}

void get_position(t_mlx *mlx, int y)
{
	int p;
	float posZ;
	float rowDistance;

	p = y - mlx->winHeight / 2;
	posZ = 0.5 * mlx->winHeight;
	rowDistance = posZ / p;
	mlx->fc.floorStepX = rowDistance *
						 (mlx->fc.rayDirX1 - mlx->fc.rayDirX0) / mlx->winWidth;
	mlx->fc.floorStepY = rowDistance *
						 (mlx->fc.rayDirY1 - mlx->fc.rayDirY0) / mlx->winWidth;
	mlx->fc.floorX = mlx->game.posX + rowDistance * mlx->fc.rayDirX0;
	mlx->fc.floorY = mlx->game.posY + rowDistance * mlx->fc.rayDirY0;
}

void draw_fc(t_mlx *mlx, int x, int y)
{
	int tx;
	int ty;
	int color;

	tx = (int)(TEX_WIDTH *
			(mlx->fc.floorX - (int)mlx->fc.floorX)) & (TEX_WIDTH - 1);
	ty = (int)(TEX_HEIGHT *
			(mlx->fc.floorY - (int)mlx->fc.floorY)) & (TEX_HEIGHT - 1);
	mlx->fc.floorX += mlx->fc.floorStepX;
	mlx->fc.floorY += mlx->fc.floorStepY;
	if (mlx->tex[FLOOR].img_ptr != NULL)
		color = mlx->tex[FLOOR].data[TEX_WIDTH * ty + tx];
	else
		color = mlx->tex[FLOOR].floorColor;
	mlx->img.data[x + mlx->winWidth * y] = color;
	if (mlx->tex[CEILING].img_ptr != NULL)
		color = mlx->tex[CEILING].data[TEX_WIDTH * ty + tx];
	else
		color = mlx->tex[CEILING].ceilingColor;
	mlx->img.data[x + mlx->winWidth * (mlx->winHeight - y - 1)] = color;
}

int draw_floor_ceiling(t_mlx *mlx)
{
	int y;
	int x;

	y = 0;
	while (y < mlx->winHeight)
	{
		mlx->fc.rayDirX0 = mlx->game.dirX - mlx->game.planeX;
		mlx->fc.rayDirY0 = mlx->game.dirY - mlx->game.planeY;
		mlx->fc.rayDirX1 = mlx->game.dirX + mlx->game.planeX;
		mlx->fc.rayDirY1 = mlx->game.dirY + mlx->game.planeY;
		get_position(mlx, y);
		x = 0;
		while (x < mlx->winWidth)
		{
			draw_fc(mlx, x, y);
			x++;
		}
		y++;
	}
}

void desc_sort(t_mlx *mlx)
{
	int i;
	int j;
	t_sprite tmp;

	i = 0;
	while (i < mlx->spriteNum)
	{
		j = i;
		while (j < mlx->spriteNum)
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

void transform_sprite(t_mlx *mlx, t_game *game, t_sprite *sprite)
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

void cal_sprite(t_mlx *mlx, t_sprite *sprite)
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

void draw_spriteY(t_mlx *mlx, t_sprite *sprite, int texX, int stripe)
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

int draw_sprite(t_mlx *mlx, t_sprite *sprite)
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

void render_sprite(t_mlx *mlx)
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

int run_game(t_mlx *mlx)
{
	int i;

	i = 0;
	draw_floor_ceiling(mlx);
	if (mlx->game.move_f || mlx->game.move_b || mlx->game.move_r ||
		mlx->game.move_l || mlx->game.rotate_r || mlx->game.rotate_l)
		key_event(mlx);
	while (i < mlx->winWidth)
	{
		set_var(mlx, i);
		perform_DDA(mlx);
		draw_vertline(mlx, i);
		mlx->zbuffer[i] = mlx->game.perpWallDist;
		i++;
	}
	render_sprite(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return 0;
}

int key_press(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->game.move_f = 1;
	if (key == KEY_S)
		mlx->game.move_b = 1;
	if (key == KEY_A)
		mlx->game.move_l = 1;
	if (key == KEY_D)
		mlx->game.move_r = 1;
	if (key == KEY_LEFT)
		mlx->game.rotate_l = 1;
	if (key == KEY_RIGHT)
		mlx->game.rotate_r = 1;
	if (key == KEY_ESC)
		error("exit game", mlx);
}

int key_release(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->game.move_f = 0;
	if (key == KEY_S)
		mlx->game.move_b = 0;
	if (key == KEY_A)
		mlx->game.move_l = 0;
	if (key == KEY_D)
		mlx->game.move_r = 0;
	if (key == KEY_LEFT)
		mlx->game.rotate_l = 0;
	if (key == KEY_RIGHT)
		mlx->game.rotate_r = 0;
}