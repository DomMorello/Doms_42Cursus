#include "../main.h"

void check_tex(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			error(ERR_FORMAT, mlx);
		i++;
	}
}

void check_lastline(t_mlx *mlx, char *line)
{
	int i;
	t_map *new;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1')
		if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
			error(ERR_MEM, mlx);
}