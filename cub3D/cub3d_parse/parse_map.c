#include "../main.h"

void check_border(t_mlx *mlx, int mapsizeY)
{
	int i;

	i = 0;
	while (mlx->map[0][i])
	{
		if (mlx->map[0][i] != '1' && !ft_isspace(mlx->map[0][i]))
			error(ERR_MAP_SUR, mlx);
		i++;
	}
	i = 0;
	while (mlx->map[mapsizeY - 1][i])
	{
		if (mlx->map[mapsizeY - 1][i] != '1' &&
			!ft_isspace(mlx->map[mapsizeY - 1][i]))
			error(ERR_MAP_SUR, mlx);
		i++;
	}
	check_rightside(mlx, mapsizeY);
}

void check_direction(t_mlx *mlx, int mapsizeY)
{
	int i;
	int j;
	int isPlural;

	i = 0;
	isPlural = 0;
	while (++i < mapsizeY - 1)
	{
		j = 0;
		while (ft_isspace(mlx->map[i][j]))
			j++;
		while (j < ft_strlen(mlx->map[i]) - 1)
		{
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' ||
				mlx->map[i][j] == 'E' || mlx->map[i][j] == 'W')
			{
				input_direction(mlx, mlx->map[i][j], i, j);
				mlx->map[i][j] = '0';
				isPlural++;
			}
			j++;
		}
	}
	if (isPlural != 1)
		error(ERR_PLU, mlx);
}

void move_map_2d(t_mlx *mlx, int mapsizeY)
{
	int i;
	char *tmp;
	t_map *lst;

	i = 0;
	if ((mlx->map = (char **)malloc(sizeof(char *) * mapsizeY + 1)) == NULL)
		error(ERR_MEM, mlx);
	mlx->map[mapsizeY] = 0;
	lst = mlx->maplst;
	while (lst)
	{
		tmp = lst->row;
		if (tmp[ft_strlen(tmp) - 1] == '\r' || tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		mlx->map[i] = tmp;
		lst = lst->next;
		i++;
	}
}

int get_mapsizeY(t_mlx *mlx)
{
	int len;
	t_map *tmp;

	tmp = mlx->maplst;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void parse_map(t_mlx *mlx)
{
	int mapsizeY;

	mapsizeY = get_mapsizeY(mlx);
	move_map_2d(mlx, mapsizeY);
	check_direction(mlx, mapsizeY);
	check_border(mlx, mapsizeY);
	parse_contents(mlx, mapsizeY);
	check_sprite(mlx, mapsizeY);
}

