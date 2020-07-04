/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:43:22 by donglee           #+#    #+#             */
/*   Updated: 2020/07/04 13:23:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Initializes the mlx and parses the information in the file
** related with textures. Converts texture xpm files to images.
*/

void	init_game(t_mlx *mlx)
{
	int		i;
	char	*tmp;

	i = -1;
	init_mlx(mlx);
	while (++i < 7)
	{
		tmp = mlx->tex[i].filepath;
		if (tmp[ft_strlen(tmp) - 1] == '\r' || tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		if ((mlx->tex[i].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
				tmp, &mlx->tex[i].width, &mlx->tex[i].height)) == NULL)
		{
			if (is_rgbcolor(&mlx->tex[i], mlx))
				continue;
			else
				error(ERR_PATH, mlx);
		}
		mlx->tex[i].data = (int *)mlx_get_data_addr(mlx->tex[i].img_ptr,
				&mlx->tex[i].bpp, &mlx->tex[i].size_l, &mlx->tex[i].endian);
	}
}

void	init_null(t_mlx *mlx)
{
	int i;

	i = 0;
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img.img_ptr = NULL;
	while (i < 7)
	{
		mlx->tex[i].filepath = NULL;
		mlx->tex[i].img_ptr = NULL;
		i++;
	}
	mlx->map = NULL;
	mlx->maplst = NULL;
	mlx->sprite = NULL;
}

/*
** If you code like "mlx_hook(mlx->win_ptr, 17, 1L << 17, error, mlx);",
** It will make error on your program when you click the red x button.
** So I made this function of which prototype is "int function(void *param)"
** And it works fine
*/

int		exit_hook(t_mlx *mlx)
{
	return (error("exit game", mlx));
}
