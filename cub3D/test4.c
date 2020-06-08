#include <stdio.h>
#include <stdlib.h>
#include "./main.h"

typedef struct s_test
{
	double dist;
	int idx;	
}				t_test;

typedef struct s_all
{
	int a;
	t_test test[5];
	int size;
}				t_all;

void	desc_sort(t_all *all)
{
	int i;
	int j;
	t_test tmp;

	i = 0;
	while (i < all->size)
	{
		j = i;
		while (j < all->size)
		{
			if (all->test[i].dist < all->test[j].dist)
			{
				tmp = all->test[i];
				all->test[i] = all->test[j];
				all->test[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char const *argv[])
{
	// t_mlx mlx;
	// mlx.mlx_ptr = mlx_init();
	// mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Hi");
	// mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	// mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	
	// mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	// mlx_loop(mlx.mlx_ptr);
	// int a = 5;
	// t_mlx mlx;
	// mlx.sprite = test(a);

	// printf("??%d\n", mlx.sprite[0].perpWallDist);
	// printf("??%d\n", mlx.sprite[1].perpWallDist);
	// printf("??%d\n", mlx.sprite[4].perpWallDist);

	return 0;
}
