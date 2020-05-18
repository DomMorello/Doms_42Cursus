#include "./minilibx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "domMorello");

	int a = 0;
	int b = 0;
	int c = 100;
	int d = 100;

	while (b < 50)
	{
		a = 0;
		d = 100;
		while (a < 100)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, c, d, 0255);
			a++;
			d++;
		}
		c++;
		b++;
	}

	mlx_loop(mlx_ptr);
	return (0);
}