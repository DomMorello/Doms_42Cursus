# ifndef MAIN_H
# define MAIN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "./minilibx_linux/mlx.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define ERROR -1

#define mapWidth 24
#define mapHeight 24

enum	e_direction
{
	EAST, WEST, SOUTH, NORTH, CEILING, FLOOR, SPRITE
};

// # define K_ESC 53
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct      s_img
{
	void    *img_ptr;
	int     *data;
	int     size_l;
	int     bpp;
	int     endian;
}                   t_img;

typedef struct		s_tex
{
	void	*img_ptr;
	int		*data;
	int     size_l;
	int     bpp;
	int     endian;
	int		width;
	int		height;
	char	*filepath;
}					t_tex;

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
	int		move_f;
	int		move_b;
	int		move_r;
	int		move_l;
	int		rotate_r;
	int		rotate_l;
}					t_game;

typedef struct	s_sprite
{
	int			idx;
	double		x;
	double		y;
	double		spriteX;
	double		spriteY;
	double		transformX;
	double		transformY;
	double		spriteScreenX;
	int			perpWallDist;
	double		dist;
	double		spriteHeight;
	int			drawStartX;
	int			drawEndX;
	int			drawStartY;
	int			drawEndY;
	double		spriteWidth;
}				t_sprite;

typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_game		game;
	t_tex		tex[7];
	t_sprite	*sprite;
	double		zbuffer[WIN_WIDTH];
	int			spriteNum;
}					t_mlx;

# endif 