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

// # define K_ESC 53
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2
// # define KEY_W 13
// # define KEY_LEFT 123
// # define KEY_RIGHT 124

typedef struct      s_img
{
	void    *img_ptr;
	int     *data;
	int     size_l;
	int     bpp;
	int     endian;
}                   t_img;

typedef struct		s_game
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	int		mapX;
	int 	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		drawStart;
	int		drawEnd;
	int		lineHeight;
}					t_game;

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_game	game;
}					t_mlx;

# endif 