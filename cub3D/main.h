# ifndef MAIN_H
# define MAIN_H

#include <math.h>
#include <stdio.h>
#include "./minilibx_linux/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

#define mapWidth 24
#define mapHeight 24
// #define screenWidth 640
// #define screenHeight 480

typedef struct      s_img
{
	void    *img_ptr;
	int     *data;
	int     size_l;
	int     bpp;
	int     endian;
}                   t_img;

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}					t_mlx;

# endif 