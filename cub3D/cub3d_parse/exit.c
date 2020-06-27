#include "../main.h"

void clear_map(t_mlx *mlx)
{
	int i;

	i = 0;
	ft_lstmapclear(&mlx->maplst);
	if (mlx->map)
	{
		while (mlx->map[i])
		{
			free(mlx->map[i]);
			mlx->map[i] = NULL;
			i++;
		}
		free(mlx->map);
		mlx->map = NULL;
	}
}

void clear_tex(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath)
		{
			free(mlx->tex[i].filepath);
			mlx->tex[i].filepath = NULL;
		}
		if (mlx->tex[i].img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->tex[i].img_ptr);
		i++;
	}
}

void clear_sprite(t_mlx *mlx)
{
	if (mlx->sprite)
	{
		free(mlx->sprite);
		mlx->sprite = NULL;
	}
}

void clear_window(t_mlx *mlx)
{
	if (mlx->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	}
}

int error(char *str, t_mlx *mlx)
{
	clear_window(mlx);
	clear_sprite(mlx);
	clear_tex(mlx);
	clear_map(mlx);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(ERROR);
	return (ERROR);
}