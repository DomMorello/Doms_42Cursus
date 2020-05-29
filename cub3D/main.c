#include "./main.h"
#include <math.h>

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int		init_window(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_WIDTH, "DomMorello");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->game.posX = 22;
	mlx->game.posY = 12;
	mlx->game.dirX = -1;
	mlx->game.dirY = 0;
	mlx->game.planeX = 0;
	mlx->game.planeY = 0.66;
	return 0;
}

int		setSideDist(t_mlx *mlx)
{
	if (mlx->game.rayDirX < 0)
	{
		mlx->game.stepX = -1;
		mlx->game.sideDistX = (mlx->game.posX - mlx->game.mapX) * mlx->game.deltaDistX;
	}
	else
	{
		mlx->game.stepX = 1;
		mlx->game.sideDistX = (mlx->game.mapX + 1.0) * mlx->game.deltaDistX;
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

int		setVar(t_mlx *mlx, int i)
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

int		setDraw(t_mlx *mlx)
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


int		performDDA(t_mlx *mlx)
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
		if (mlx->game.side == 0)
			mlx->game.perpWallDist = (mlx->game.mapX - mlx->game.posX + (1 - mlx->game.stepX) / 2) / mlx->game.rayDirX;
		else
			mlx->game.perpWallDist = (mlx->game.mapY - mlx->game.posY + (1 - mlx->game.stepY) / 2) / mlx->game.rayDirY;
		return setDraw(mlx);
	}
}

int		key_press(int key, t_mlx *mlx)
{
	printf("key: %d\n", key);
	return 0;
}

int		drawVertLine(t_mlx *mlx, int i, int color)
{
	while (mlx->game.drawStart <= mlx->game.drawEnd)
	{
		mlx->img.data[i + WIN_WIDTH * mlx->game.drawStart] = color;
		mlx->game.drawStart++;
	}
	mlx_hook(mlx->mlx_ptr, 2, 1L<<0, key_press, mlx);
}

int		startEngine(t_mlx *mlx)
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

int		start_game(t_mlx *mlx)
{
	init_window(mlx);
	startEngine(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return 0;
}

int main()
{
	/* read map, handle exception */
	t_mlx mlx;
	start_game(&mlx);
	return (0);
}