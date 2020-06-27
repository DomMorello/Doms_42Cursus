#include "../main.h"

void	desc_sort(t_mlx *mlx)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < mlx->spriteNum)
	{
		j = i;
		while (j < mlx->spriteNum)
		{
			if (mlx->sprite[i].dist < mlx->sprite[j].dist)
			{
				tmp = mlx->sprite[i];
				mlx->sprite[i] = mlx->sprite[j];
				mlx->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}