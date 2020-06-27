#include "../main.h"

void	rotate_right(t_mlx *mlx, double rotSpeed)
{
	double oldDirX;
	double oldPlaneX;

	if (mlx->game.rotate_r == 1)
	{
		oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(-rotSpeed) -
							mlx->game.dirY * sin(-rotSpeed);
		mlx->game.dirY = oldDirX * sin(-rotSpeed) +
							mlx->game.dirY * cos(-rotSpeed);
		oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(-rotSpeed) -
							mlx->game.planeY * sin(-rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(-rotSpeed) +
							mlx->game.planeY * cos(-rotSpeed);
	}
}

void	rotate_left(t_mlx *mlx, double rotSpeed)
{
	double oldDirX;
	double oldPlaneX;

	if (mlx->game.rotate_l == 1)
	{
		oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(rotSpeed) -
							mlx->game.dirY * sin(rotSpeed);
		mlx->game.dirY = oldDirX * sin(rotSpeed) +
							mlx->game.dirY * cos(rotSpeed);
		oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(rotSpeed) -
							mlx->game.planeY * sin(rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(rotSpeed) +
							mlx->game.planeY * cos(rotSpeed);
	}
}

void	move_side(t_mlx *mlx)
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

void	move_forback(t_mlx *mlx, double moveSpeed)
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