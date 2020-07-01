/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:43:22 by donglee           #+#    #+#             */
/*   Updated: 2020/07/01 18:56:49 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int		exit_hook(t_mlx *mlx)
{
	return (error("exit game", mlx));
}
