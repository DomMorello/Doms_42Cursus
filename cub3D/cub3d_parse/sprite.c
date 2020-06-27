#include "../main.h"

void input_sprite(t_sprite *sprites, char **map, int mapsizeY)
{
	int i;
	int j;
	int idx;

	i = 1;
	idx = 0;
	while (i < mapsizeY)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (map[i][j + 1])
		{
			if (map[i][j + 1] == '2')
			{
				sprites[idx].x = i + 0.5;
				sprites[idx].y = j + 1.5;
				idx++;
			}
			j++;
		}
		i++;
	}
}

int count_sprite(char **map, int mapsizeY)
{
	int i;
	int j;
	int spriteNum;

	i = 1;
	spriteNum = 0;
	while (i < mapsizeY - 1)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (map[i][j + 1])
		{
			if (map[i][j + 1] == '2')
				spriteNum++;
			j++;
		}
		i++;
	}
	return (spriteNum);
}

void check_sprite(t_mlx *mlx, int mapsizeY)
{
	int spriteNum;
	t_sprite *sprites;

	spriteNum = count_sprite(mlx->map, mapsizeY);
	if ((sprites = (t_sprite *)malloc(sizeof(t_sprite) * spriteNum)) == NULL)
		error(ERR_MEM, mlx);
	input_sprite(sprites, mlx->map, mapsizeY);
	mlx->spriteNum = spriteNum;
	mlx->sprite = sprites;
}