/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:38:45 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 01:39:18 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	set_bmfh(t_bmfh *bmfh, t_mlx *mlx)
{
	bmfh->bfType[0] = 'B';
	bmfh->bfType[1] = 'M';
	bmfh->bfSize = 54 + 4 * mlx->winWidth * mlx->winHeight;
	bmfh->bfReserved = 0;
	bmfh->bfOffBits = 54;
}

void	set_bmih(t_bmih *bmih, t_mlx *mlx)
{
	bmih->biSize = 40;
	bmih->biWidth = mlx->winWidth;
	bmih->biHeight = -mlx->winHeight;
	bmih->biPlanes[0] = 1;
	bmih->biPlanes[1] = 0;
	bmih->biBitCount[0] = 32;
	bmih->biBitCount[1] = 0;
	bmih->biCompression = 0;
	bmih->biSizeImage = 4 * mlx->winWidth * mlx->winHeight;
	bmih->biXPelsPerMeter = 0;
	bmih->biYPelsPerMeter = 0;
	bmih->biClrUsed = 0;
	bmih->biClrImportant = 0;
}

int		save_bmp(t_mlx *mlx)
{
	int		fd;
	t_bmfh	bmfh;
	t_bmih	bmih;

	if ((fd = open("../capture.bmp", O_WRONLY | O_CREAT)) == ERROR)
		return (error_msg(ERR_OPEN));
	set_bmfh(&bmfh, mlx);
	set_bmih(&bmih, mlx);
	write(fd, &bmfh, sizeof(bmfh));
	write(fd, &bmih, sizeof(bmih));
	write(fd, mlx->img.data, bmih.biSizeImage);
	close(fd);
	return (TRUE);
}
