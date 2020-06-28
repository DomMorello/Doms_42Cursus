/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:43:22 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 20:35:48 by marvin           ###   ########.fr       */
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
