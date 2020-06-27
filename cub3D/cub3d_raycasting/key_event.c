#include "../main.h"

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