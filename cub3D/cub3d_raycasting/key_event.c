#include "../main.h"

int		key_press(int key, t_mlx *mlx)
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
	return (TRUE);
}

int		key_release(int key, t_mlx *mlx)
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
	return (TRUE);
}

void	key_event(t_mlx *mlx)
{
	double moveSpeed;
	double rotSpeed;

	moveSpeed = 0.018;
	rotSpeed = 0.009;
	move_forback(mlx, moveSpeed);
	move_side(mlx);
	rotate_right(mlx, rotSpeed);
	rotate_left(mlx, rotSpeed);
}