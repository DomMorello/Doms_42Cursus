#include "../main.h"

void	draw_fc(t_mlx *mlx, int x, int y)
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

void	get_position(t_mlx *mlx, int y)
{
	int		p;
	float	posZ;
	float	rowDistance;

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

void	draw_floor_ceiling(t_mlx *mlx)
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

int		run_game(t_mlx *mlx)
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
	return (TRUE);
}