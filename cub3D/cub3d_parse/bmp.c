/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:38:45 by donglee           #+#    #+#             */
/*   Updated: 2020/07/01 16:49:41 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_bmfh(t_bmfh *bmfh, t_mlx *mlx)
{
	bmfh->bf_type[0] = 'B';
	bmfh->bf_type[1] = 'M';
	bmfh->bf_size = 54 + 4 * mlx->win_width * mlx->win_height;
	bmfh->bf_reserved = 0;
	bmfh->bf_off_bits = 54;
}

void	set_bmih(t_bmih *bmih, t_mlx *mlx)
{
	bmih->bi_size = 40;
	bmih->bi_width = mlx->win_width;
	bmih->bi_height = -mlx->win_height;
	bmih->bi_planes[0] = 1;
	bmih->bi_planes[1] = 0;
	bmih->bi_bit_count[0] = 32;
	bmih->bi_bit_count[1] = 0;
	bmih->bi_compression = 0;
	bmih->bi_size_image = 4 * mlx->win_width * mlx->win_height;
	bmih->bix_pels_per_meter = 0;
	bmih->biy_pels_per_meter = 0;
	bmih->bi_clr_used = 0;
	bmih->bi_clr_important = 0;
}

int		save_bmp(t_mlx *mlx)
{
	int		fd;
	t_bmfh	bmfh;
	t_bmih	bmih;

	if ((fd = open("capture.bmp", O_WRONLY | O_CREAT)) == ERROR)
		return (error_msg(ERR_OPEN));
	set_bmfh(&bmfh, mlx);
	set_bmih(&bmih, mlx);
	write(fd, &bmfh, sizeof(bmfh));
	write(fd, &bmih, sizeof(bmih));
	write(fd, mlx->img.data, bmih.bi_size_image);
	close(fd);
	return (TRUE);
}
