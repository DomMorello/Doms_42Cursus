#include "../main.h"

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