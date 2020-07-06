/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:41:21 by donglee           #+#    #+#             */
/*   Updated: 2020/07/06 16:26:40 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Inputs resolution info from the file to the varaibles in the struct
** If it exceed the valid range it will be adjusted
** to the maximum(minimum) value
*/

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
	mlx->win_width = ft_atoi(ret[0]);
	mlx->win_height = ft_atoi(ret[1]);
	if (mlx->win_width > MAX_WIN_WIDTH)
		mlx->win_width = MAX_WIN_WIDTH;
	if (mlx->win_width < MIN_WIN_WIDTH)
		mlx->win_width = MIN_WIN_WIDTH;
	if (mlx->win_height > MAX_WIN_HEIGHT)
		mlx->win_height = MAX_WIN_HEIGHT;
	if (mlx->win_height < MIN_WIN_HEIGHT)
		mlx->win_height = MIN_WIN_HEIGHT;
	return (free_2d_char(ret, TRUE));
}

/*
** If the map info is located between other elements like R, NO, S etc,
** the program returns error
** map info must be end of the file.
*/

void	check_order(t_mlx *mlx, char *line)
{
	if (line[0] == '1' || line[0] == '0')
		error(ERR_ORDER, mlx);
}

/*
** Checks if the texture's filepath is fully defined
** If it isn't, returns false otherwise true
** This is used to make sure map info is located in the end of the file.
** Only after all the texture's filepath is fully defined it reads map info.
*/

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
	else
		copy_map(mlx, line);
	return (TRUE);
}

/*
** opens and reads the file and input the information in the file
** to the proper variables in the structs.
** At the same time, it checks whether the file has errors in it
*/

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
