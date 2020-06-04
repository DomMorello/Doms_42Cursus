#include <stdio.h>
#include "./main.h"

int main(int argc, char const *argv[])
{
	t_mlx mlx;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Hi");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	
	for (size_t i = 0; i < (WIN_WIDTH * WIN_HEIGHT) / 2; i++)
	{
		mlx.img.data[i] = 0xffff00;
	}
	for (size_t i = (WIN_WIDTH * WIN_HEIGHT) / 2; i < (WIN_WIDTH * WIN_HEIGHT); i++)
	{
		mlx.img.data[i] = 0xff00ff;
	}
	
		
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);

	return 0;
}
