# ifndef MAIN_H
# define MAIN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./minilibx_linux/mlx.h"

# define MIN_WIN_WIDTH 320
# define MIN_WIN_HEIGHT 240
# define MAX_WIN_WIDTH 1280
# define MAX_WIN_HEIGHT 720
# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define PASS 7

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
	// 이 부분은 t_img를 이용해서 바꾸자. 
	int		width;
	int		height;
	char	*filepath;
}					t_tex;

//t_game ==> t_ray 로 바꾸자.
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
	double		spriteWidth;
	int			drawStartX;
	int			drawEndX;
	int			drawStartY;
	int			drawEndY;
}				t_sprite;

typedef struct		s_map
{
	// int		mapWidth;
	// int		mapEhight;
	char 			*row;
	struct s_map	*next;
}					t_map;

//mlx->game으로 바꾸자.
typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_game		game;
	t_tex		tex[7];
	t_sprite	*sprite;
	t_map		map;
	double		zbuffer[MAX_WIN_WIDTH];	//맥스로 놔두면 되지 않을까?
	int			spriteNum;
	int			winWidth;
	int			winHeight;
}					t_mlx;

# endif 