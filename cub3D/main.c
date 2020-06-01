#include "./main.h"

int worldMap[mapWidth][mapHeight] =
	{
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
		{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
		{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
		{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
		{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
		{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
		{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

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
	mlx->game.cameraX = 2 * i / (double)WIN_WIDTH - 1;
	mlx->game.rayDirX = mlx->game.dirX + mlx->game.planeX * mlx->game.cameraX;
	mlx->game.rayDirY = mlx->game.dirY + mlx->game.planeY * mlx->game.cameraX;
	mlx->game.mapX = (int)mlx->game.posX;
	mlx->game.mapY = (int)mlx->game.posY;
	mlx->game.deltaDistX = fabs(1 / mlx->game.rayDirX);
	mlx->game.deltaDistY = fabs(1 / mlx->game.rayDirY);
	mlx->game.hit = 0;
	setSideDist(mlx);
	return 0;
}

int setDraw(t_mlx *mlx)
{
	mlx->game.lineHeight = (int)(WIN_HEIGHT / mlx->game.perpWallDist);
	mlx->game.drawStart = -mlx->game.lineHeight / 2 + WIN_HEIGHT / 2;
	if (mlx->game.drawStart < 0)
		mlx->game.drawStart = 0;
	mlx->game.drawEnd = mlx->game.lineHeight / 2 + WIN_HEIGHT / 2;
	if (mlx->game.drawEnd >= WIN_HEIGHT)
		mlx->game.drawEnd = WIN_HEIGHT - 1;
	if (worldMap[mlx->game.mapX][mlx->game.mapY] == 1)
		return 0xFF0000;
	else if (worldMap[mlx->game.mapX][mlx->game.mapY] == 2)
		return 0x00FF00;
	else if (worldMap[mlx->game.mapX][mlx->game.mapY] == 3)
		return 0x0000FF;
	else if (worldMap[mlx->game.mapX][mlx->game.mapY] == 4)
		return 0xFFFFFF;
	else
		return 0xFFEB5A;
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
		if (worldMap[mlx->game.mapX][mlx->game.mapY] > 0)
			mlx->game.hit = 1;
	}
	if (mlx->game.side == 0)
		mlx->game.perpWallDist = (mlx->game.mapX - mlx->game.posX + (1 - mlx->game.stepX) / 2) / mlx->game.rayDirX;
	else
		mlx->game.perpWallDist = (mlx->game.mapY - mlx->game.posY + (1 - mlx->game.stepY) / 2) / mlx->game.rayDirY;
	return setDraw(mlx);
}

int drawVertLine(t_mlx *mlx, int i, int color)
{
	// while (mlx->game.drawStart < mlx->game.drawEnd)
	// {
	// 	mlx->img.data[i + WIN_WIDTH * mlx->game.drawStart] = color;
	// 	mlx->game.drawStart++;
	// }
	int a = 50;
	int b = 50;
	void *xpm_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/mossy.xpm", &a, &b);
	int texNum = worldMap[mlx->game.mapX][mlx->game.mapY] - 1;
	double wallX;
	if (mlx->game.side == 0)
		wallX = mlx->game.posY + mlx->game.perpWallDist * mlx->game.rayDirY;
	else
		wallX = mlx->game.posX + mlx->game.perpWallDist * mlx->game.rayDirX;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)TEX_WIDTH);
	if (mlx->game.side == 0 && mlx->game.rayDirX > 0)
		texX = TEX_WIDTH - texX - 1;
	if (mlx->game.side == 1 && mlx->game.rayDirX < 0)
		texX = TEX_WIDTH - texX - 1;

	double step = 1.0 * TEX_HEIGHT / mlx->game.lineHeight;
	double texPos = (mlx->game.drawStart - WIN_HEIGHT / 2 + mlx->game.lineHeight / 2) * step;
	for (int y = mlx->game.drawStart; y < mlx->game.drawStart; y++)
	{
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, xpm_ptr, 0, 0);
		texPos += step;
	}
}

int raycast(t_mlx *mlx)
{
	int i;
	int color;

	i = 0;
	while (i++ < WIN_WIDTH)
	{
		setVar(mlx, i);
		color = performDDA(mlx);
		if (mlx->game.side == 1)
			color = color / 2;
		drawVertLine(mlx, i, color);
	}
	return 0;
}

int run_game(t_mlx *mlx)
{
	raycast(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

int key_press(int key, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);

	double moveSpeed = 0.3; //the constant value is in squares/second
	double rotSpeed = 0.05; //the constant value is in radians/second
	//move forward if no wall in front of you
	if (key == 65362)
	{
		printf("Moving forward\n");
		if (worldMap[(int)(mlx->game.posX + mlx->game.dirX * moveSpeed)][(int)mlx->game.posY] == 0)
			mlx->game.posX += mlx->game.dirX * moveSpeed;
		if (worldMap[(int)mlx->game.posX][(int)(mlx->game.posY + mlx->game.dirY * moveSpeed)] == 0)
			mlx->game.posY += mlx->game.dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == 65364)
	{
		printf("Moving backward\n");
		if (worldMap[(int)(mlx->game.posX - mlx->game.dirX * moveSpeed)][(int)mlx->game.posY] == 0)
			mlx->game.posX -= mlx->game.dirX * moveSpeed;
		if (worldMap[(int)mlx->game.posX][(int)(mlx->game.posY - mlx->game.dirY * moveSpeed)] == 0)
			mlx->game.posY -= mlx->game.dirY * moveSpeed;
	}
	//rotate to the right
	if (key == 65363)
	{
		printf("turning right\n");
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(-rotSpeed) - mlx->game.dirY * sin(-rotSpeed);
		mlx->game.dirY = oldDirX * sin(-rotSpeed) + mlx->game.dirY * cos(-rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(-rotSpeed) - mlx->game.planeY * sin(-rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(-rotSpeed) + mlx->game.planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (key == 65361)
	{
		printf("turning left\n");
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

int initial_setting(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "DomMorello");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->game.posX = 22;
	mlx->game.posY = 12;
	mlx->game.dirX = -1;
	mlx->game.dirY = 0;
	mlx->game.planeX = 0;
	mlx->game.planeY = 0.66;
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_loop_hook(mlx->mlx_ptr, run_game, mlx);
	mlx_loop(mlx->mlx_ptr);
	return 0;
}

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	/* parsing map info */
	initial_setting(&mlx);
	return 0;
}
