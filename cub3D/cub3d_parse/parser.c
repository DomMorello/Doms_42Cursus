#include "../main.h"

int		input_resolution(t_mlx *mlx, char *str)
{
	char	**ret;
	char	*check;
	int		i;

	i = 0;
	while (str[++i])
		if (!(ft_isdigit(str[i]) || ft_isspace(str[i])))
			return (error_msg(ERR_FORMAT));
	if ((ret = ft_split(&str[1], ' ')) == NULL)
		return (error_msg(ERR_MEM));
	check = ret[2];
	if (check)
		if (!(check[0] == '\0' || check[0] == '\r' || check[0] == '\n'))
			return (free_2d_char(ret, error_msg(ERR_FORMAT)));
	mlx->winWidth = ft_atoi(ret[0]);
	mlx->winHeight = ft_atoi(ret[1]);
	if (mlx->winWidth > MAX_WIN_WIDTH)
		mlx->winWidth = MAX_WIN_WIDTH;
	if (mlx->winWidth < MIN_WIN_WIDTH)
		mlx->winWidth = MIN_WIN_WIDTH;
	if (mlx->winHeight > MAX_WIN_HEIGHT)
		mlx->winHeight = MAX_WIN_HEIGHT;
	if (mlx->winHeight < MIN_WIN_HEIGHT)
		mlx->winHeight = MIN_WIN_HEIGHT;
	return (free_2d_char(ret, TRUE));
}

int		check_order(t_mlx *mlx, char *line)
{
	if (line[0] == '1' || line[0] == '0')
		error(ERR_ORDER, mlx);
	return (TRUE);
}

int		allset_filepath(t_mlx *mlx)
{
	int allset;
	int i;

	allset = TRUE;
	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			allset = FALSE;
		i++;
	}
	return (allset);
}

int		parse_line(char *line, t_mlx *mlx)
{
	int i;
	int tex;

	i = 0;
	if (!allset_filepath(mlx))
	{
		while (ft_isspace(line[i]))
			i++;
		check_order(mlx, &line[i]);
		if (line[i] == 'R')
			if ((input_resolution(mlx, &line[i])) == ERROR)
				return (ERROR);
		if ((tex = which_tex(&line[i])) == ERROR)
			return (error(ERR_LETTER, mlx));
		if (input_tex(mlx, tex, &line[i]) == ERROR)
			return (ERROR);
	}
	else if (copy_map(mlx, line) == ERROR)
		return (ERROR);
	return (TRUE);
}

int		parse_info(char const *argv, t_mlx *mlx)
{
	int		fd;
	char	*line;

	if ((fd = open(argv, O_RDONLY)) == ERROR)
		error(ERR_OPEN, mlx);
	while (get_next_line(fd, &line))
	{
		if (parse_line(line, mlx) == ERROR)
		{
			free(line);
			return (ERROR);
		}
		free(line);
	}
	check_tex(mlx);
	check_lastline(mlx, line);
	parse_map(mlx);
	free(line);
	close(fd);
	return (TRUE);
}