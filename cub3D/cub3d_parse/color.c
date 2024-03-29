/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:43:10 by donglee           #+#    #+#             */
/*   Updated: 2020/07/06 16:21:32 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** RGB color value is seperately stored in the array of int rgb[3]
** So they must be converted to a single variable int color.
** With bit operation below, the three r,g,b colors can be one integer value.
*/

void	input_color(t_tex *tex, t_mlx *mlx, char **ret)
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
		mlx->tex[FLOOR].floor_color = color;
	if (tex == &mlx->tex[CEILING])
		mlx->tex[CEILING].ceiling_color = color;
	free_2d_char(ret, TRUE);
}

/*
** If the line is "F 234 23 53" then its filapath is "234 23 53".
** The fucntion will check if it is a valid format of rgb color.
*/

int		is_rgbcolor(t_tex *tex, t_mlx *mlx)
{
	char	**ret;
	int		i;
	char	*check;

	i = 0;
	check = NULL;
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
