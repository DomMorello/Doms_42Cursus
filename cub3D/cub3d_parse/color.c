#include "../main.h"

void input_color(t_tex *tex, t_mlx *mlx, char **ret)
{
	int rgb[3];
	int i;
	int color;

	color = 0;
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(ret[i]);
		if (rgb[i] > 255 || rgb[i] < 0)
			error(ERR_RGB, mlx);
		i++;
	}
	color += rgb[0] << 16;
	color += rgb[1] << 8;
	color += rgb[2];
	if (tex == &mlx->tex[FLOOR])
		mlx->tex[FLOOR].floorColor = color;
	if (tex == &mlx->tex[CEILING])
		mlx->tex[CEILING].ceilingColor = color;
	free_2d_char(ret, TRUE);
}

int isRGBcolor(t_tex *tex, t_mlx *mlx)
{
	char **ret;
	int i;
	char *check;

	i = 0;
	while (tex->filepath[i])
	{
		if (!ft_isdigit(tex->filepath[i]) && !ft_isspace(tex->filepath[i]))
			return (FALSE);
		i++;
	}
	if ((ret = ft_split(tex->filepath, ' ')) == NULL)
		error(ERR_MEM, mlx);
	if (check)
	{
		if (!(check[0] == '\0' || check[0] == '\r' || check[0] == '\n'))
		{
			free_2d_char(ret, ERROR);
			error(ERR_FORMAT, mlx);
		}
	}
	input_color(tex, mlx, ret);
	return (TRUE);
}