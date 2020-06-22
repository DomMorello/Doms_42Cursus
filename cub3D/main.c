#include "./main.h"

int setSideDist(t_mlx *mlx)
{
	if (mlx->game.rayDirX < 0)
	{
		mlx->game.stepX = -1;
		mlx->game.sideDistX = (mlx->game.posX - mlx->game.mapX) * mlx->game.deltaDistX;
	}
	else
	{
		mlx->game.stepX = 1;
		mlx->game.sideDistX = (mlx->game.mapX + 1.0 - mlx->game.posX) * mlx->game.deltaDistX;
	}
	if (mlx->game.rayDirY < 0)
	{
		mlx->game.stepY = -1;
		mlx->game.sideDistY = (mlx->game.posY - mlx->game.mapY) * mlx->game.deltaDistY;
	}
	else
	{
		mlx->game.stepY = 1;
		mlx->game.sideDistY = (mlx->game.mapY + 1.0 - mlx->game.posY) * mlx->game.deltaDistY;
	}
	return 0;
}

int setVar(t_mlx *mlx, int i)
{
	mlx->game.cameraX = 2 * i / (double)mlx->winWidth - 1;
	mlx->game.rayDirX = mlx->game.dirX + mlx->game.planeX * mlx->game.cameraX;
	mlx->game.rayDirY = mlx->game.dirY + mlx->game.planeY * mlx->game.cameraX;
	mlx->game.mapX = (int)mlx->game.posX;
	mlx->game.mapY = (int)mlx->game.posY;
	mlx->game.deltaDistX = (mlx->game.rayDirY == 0) ? 0 : ((mlx->game.rayDirX == 0) ? 1 : fabs(1 / mlx->game.rayDirX));
	mlx->game.deltaDistY = (mlx->game.rayDirX == 0) ? 0 : ((mlx->game.rayDirY == 0) ? 1 : fabs(1 / mlx->game.rayDirY));
	mlx->game.hit = 0;
	setSideDist(mlx);
	return 0;
}

void setDraw(t_mlx *mlx)
{
	mlx->game.lineHeight = (int)(mlx->winHeight / mlx->game.perpWallDist);
	mlx->game.drawStart = -mlx->game.lineHeight / 2 + mlx->winHeight / 2;
	if (mlx->game.drawStart < 0)
		mlx->game.drawStart = 0;
	mlx->game.drawEnd = mlx->game.lineHeight / 2 + mlx->winHeight / 2;
	if (mlx->game.drawEnd >= mlx->winHeight)
		mlx->game.drawEnd = mlx->winHeight - 1;
}

int performDDA(t_mlx *mlx)
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
		mlx->game.perpWallDist = (mlx->game.mapX - mlx->game.posX + (1 - mlx->game.stepX) / 2) / mlx->game.rayDirX;
	else
		mlx->game.perpWallDist = (mlx->game.mapY - mlx->game.posY + (1 - mlx->game.stepY) / 2) / mlx->game.rayDirY;
	setDraw(mlx);
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

int drawVertLine(t_mlx *mlx, int i)
{
	double wallX;
	if (mlx->game.side == 0)
		wallX = mlx->game.posY + mlx->game.perpWallDist * mlx->game.rayDirY;
	else
		wallX = mlx->game.posX + mlx->game.perpWallDist * mlx->game.rayDirX;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)TEX_WIDTH);
	if (mlx->game.side == 0 && mlx->game.rayDirX > 0)
		texX = TEX_WIDTH - texX - 1;
	if (mlx->game.side == 1 && mlx->game.rayDirY < 0)
		texX = TEX_WIDTH - texX - 1;

	double step = 1.0 * TEX_HEIGHT / mlx->game.lineHeight;
	double texPos = (mlx->game.drawStart - mlx->winHeight / 2 + mlx->game.lineHeight / 2) * step;

	int wall_side = get_side(mlx);
	while (mlx->game.drawStart < mlx->game.drawEnd)
	{
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		int color = mlx->tex[wall_side].data[TEX_HEIGHT * texY + texX];
		/* shading? */
		mlx->img.data[i + mlx->winWidth * mlx->game.drawStart] = color;
		mlx->game.drawStart++;
	}
}

int key_press(t_mlx *mlx)
{
	double moveSpeed = 0.018; //the constant value is in squares/second
	double rotSpeed = 0.009;  //the constant value is in radians/second
	// move forward if no wall in front of you
	if (mlx->game.move_f == 1)
	{
		if (mlx->map[(int)(mlx->game.posX + mlx->game.dirX * moveSpeed)][(int)mlx->game.posY] == '0')
			mlx->game.posX += mlx->game.dirX * moveSpeed;
		if (mlx->map[(int)mlx->game.posX][(int)(mlx->game.posY + mlx->game.dirY * moveSpeed)] == '0')
			mlx->game.posY += mlx->game.dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (mlx->game.move_b == 1)
	{
		if (mlx->map[(int)(mlx->game.posX - mlx->game.dirX * moveSpeed)][(int)mlx->game.posY] == '0')
			mlx->game.posX -= mlx->game.dirX * moveSpeed;
		if (mlx->map[(int)mlx->game.posX][(int)(mlx->game.posY - mlx->game.dirY * moveSpeed)] == '0')
			mlx->game.posY -= mlx->game.dirY * moveSpeed;
	}
	//move to the right
	if (mlx->game.move_r == 1)
	{
		if (mlx->map[(int)(mlx->game.posX + mlx->game.planeX * 0.01)][(int)mlx->game.posY] == '0')
			mlx->game.posX += mlx->game.planeX * 0.01;
		if (mlx->map[(int)mlx->game.posX][(int)(mlx->game.posY + mlx->game.planeY * 0.01)] == '0')
			mlx->game.posY += mlx->game.planeY * 0.01;
	}
	//rotate to the right
	if (mlx->game.rotate_r == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(-rotSpeed) - mlx->game.dirY * sin(-rotSpeed);
		mlx->game.dirY = oldDirX * sin(-rotSpeed) + mlx->game.dirY * cos(-rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(-rotSpeed) - mlx->game.planeY * sin(-rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(-rotSpeed) + mlx->game.planeY * cos(-rotSpeed);
	}
	//move to the left
	if (mlx->game.move_l == 1)
	{
		if (mlx->map[(int)(mlx->game.posX - mlx->game.planeX * 0.01)][(int)mlx->game.posY] == '0')
			mlx->game.posX -= mlx->game.planeX * 0.01;
		if (mlx->map[(int)mlx->game.posX][(int)(mlx->game.posY - mlx->game.planeY * 0.01)] == '0')
			mlx->game.posY -= mlx->game.planeY * 0.01;
	}
	//rotate to the left
	if (mlx->game.rotate_l == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(rotSpeed) - mlx->game.dirY * sin(rotSpeed);
		mlx->game.dirY = oldDirX * sin(rotSpeed) + mlx->game.dirY * cos(rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(rotSpeed) - mlx->game.planeY * sin(rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(rotSpeed) + mlx->game.planeY * cos(rotSpeed);
	}
	return 0;
}

int draw_floor_ceiling(t_mlx *mlx)
{
	int y;

	y = 0;
	while (y < mlx->winHeight)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = mlx->game.dirX - mlx->game.planeX;
		float rayDirY0 = mlx->game.dirY - mlx->game.planeY;
		float rayDirX1 = mlx->game.dirX + mlx->game.planeX;
		float rayDirY1 = mlx->game.dirY + mlx->game.planeY;
		// Current y position compared to the center of the screen (the horizon)
		int p = y - mlx->winHeight / 2;
		// Vertical position of the camera.
		float posZ = 0.5 * mlx->winHeight;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / mlx->winWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / mlx->winWidth;
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = mlx->game.posX + rowDistance * rayDirX0;
		float floorY = mlx->game.posY + rowDistance * rayDirY0;

		for (int x = 0; x < mlx->winWidth; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)floorX;
			int cellY = (int)floorY;

			// get the texture coordinate from the fractional part
			int tx = (int)(TEX_WIDTH * (floorX - cellX)) & (TEX_WIDTH - 1);
			int ty = (int)(TEX_HEIGHT * (floorY - cellY)) & (TEX_HEIGHT - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			int color;
			// floor
			color = mlx->tex[FLOOR].data[TEX_WIDTH * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			mlx->img.data[x + mlx->winWidth * y] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = mlx->tex[CEILING].data[TEX_WIDTH * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			mlx->img.data[x + mlx->winWidth * (mlx->winHeight - y - 1)] = color;
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

int transform_sprite(t_mlx *mlx, t_game *game, t_sprite *sprite)
{
	double invDet;
	//translate sprite position to relative to camera
	sprite->spriteX = sprite->x - game->posX;
	sprite->spriteY = sprite->y - game->posY;
	//required for correct matrix multiplication
	invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);
	sprite->transformX = invDet * (game->dirY * sprite->spriteX - game->dirX * sprite->spriteY);
	//this is actually the depth inside the screen, that what Z is in 3D
	sprite->transformY = invDet * (-game->planeY * sprite->spriteX + game->planeX * sprite->spriteY);

	sprite->spriteScreenX = (int)((mlx->winWidth / 2) * (1 + sprite->transformX / sprite->transformY));
}

int cal_sprite(t_mlx *mlx, t_sprite *sprite)
{
	//calculate height of the sprite on screen
	//using 'transformY' instead of the real distance prevents fisheye
	sprite->spriteHeight = abs((int)(mlx->winHeight / (sprite->transformY)));
	//calculate lowest and highest pixel to fill in current stripe
	sprite->drawStartY = -sprite->spriteHeight / 2 + mlx->winHeight / 2;
	if (sprite->drawStartY < 0)
		sprite->drawStartY = 0;
	sprite->drawEndY = sprite->spriteHeight / 2 + mlx->winHeight / 2;
	if (sprite->drawEndY >= mlx->winHeight)
		sprite->drawEndY = mlx->winHeight - 1;

	//calculate width of the sprite
	sprite->spriteWidth = abs((int)(mlx->winHeight / (sprite->transformY)));
	sprite->drawStartX = -sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawStartX < 0)
		sprite->drawStartX = 0;
	sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawEndX >= mlx->winWidth)
		sprite->drawEndX = mlx->winWidth - 1;
}

// int draw_sprite(t_mlx *mlx, t_sprite *sprite, double *zbuffer
int draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
	int texX;
	int texY;
	int stripe = sprite->drawStartX;
	//loop through every vertical stripe of the sprite on screen
	while (stripe < sprite->drawEndX)
	{
		texX = (int)(256 * (stripe - (-sprite->spriteWidth / 2 + sprite->spriteScreenX)) * TEX_WIDTH / sprite->spriteWidth) / 256;
		if (sprite->transformY > 0 && stripe > 0 && stripe < mlx->winWidth && sprite->transformY < mlx->zbuffer[stripe])
		{
			int y = sprite->drawStartY;
			while (y < sprite->drawEndY) //for every pixel of the current stripe
			{
				//256 and 128 factors to avoid floats
				int d = (y) * 256 - mlx->winHeight * 128 + sprite->spriteHeight * 128;
				texY = ((d * TEX_HEIGHT) / sprite->spriteHeight) / 256;
				//get current color from the texture
				int color = mlx->tex[SPRITE].data[TEX_WIDTH * texY + texX];
				if ((color & 0x00FFFFFF) != 0)
					mlx->img.data[stripe + mlx->winWidth * y] = color;
				//paint pixel if it isn't black, black is the invisible color
				y++;
			}
		}
		stripe++;
	}
}

int render_sprite(t_mlx *mlx)
{
	int i;

	i = 0;
	for (size_t i = 0; i < mlx->spriteNum; i++)
	{
		mlx->sprite[i].dist = ((mlx->game.posX - mlx->sprite[i].x) * (mlx->game.posX - mlx->sprite[i].x) + (mlx->game.posY - mlx->sprite[i].y) * (mlx->game.posY - mlx->sprite[i].y));
	}
	desc_sort(mlx);
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
	if (mlx->game.move_f || mlx->game.move_b || mlx->game.move_r || mlx->game.move_l || mlx->game.rotate_r || mlx->game.rotate_l)
		key_press(mlx);
	while (i < mlx->winWidth)
	{
		setVar(mlx, i);
		performDDA(mlx);
		drawVertLine(mlx, i);
		mlx->zbuffer[i] = mlx->game.perpWallDist;
		i++;
	}
	render_sprite(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return 0;
}

int key_press2(int key, t_mlx *mlx)
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