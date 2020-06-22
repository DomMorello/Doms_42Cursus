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
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define PASS 7

enum	e_textures
{
	EAST, WEST, SOUTH, NORTH, CEILING, FLOOR, SPRITE
};

# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

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
	t_map		*maplst;
	char		**map;
	double		zbuffer[MAX_WIN_WIDTH];	//맥스로 놔두면 되지 않을까?
	int			spriteNum;
	int			winWidth;
	int			winHeight;
}					t_mlx;


int key_release(int key, t_mlx *mlx);
int key_press2(int key, t_mlx *mlx);
int run_game(t_mlx *mlx);
int render_sprite(t_mlx *mlx);
int draw_sprite(t_mlx *mlx, t_sprite *sprite);
int cal_sprite(t_mlx *mlx, t_sprite *sprite);
int transform_sprite(t_mlx *mlx, t_game *game, t_sprite *sprite);
void desc_sort(t_mlx *mlx);
int draw_floor_ceiling(t_mlx *mlx);
int key_press(t_mlx *mlx);
int drawVertLine(t_mlx *mlx, int i);
int get_side(t_mlx *mlx);
int performDDA(t_mlx *mlx);
void setDraw(t_mlx *mlx);
int setVar(t_mlx *mlx, int i);
int setSideDist(t_mlx *mlx);
int init_game(t_mlx *mlx);
int check_extension(char const *argv);
char *ft_strfromend(char *str, int size);
int parse_info(char const *argv, t_mlx *mlx);
int parse_map(t_mlx *mlx);
int check_sprite(t_mlx *mlx, int mapsizeY);
void	input_sprite(t_sprite *sprites, char **map, int mapsizeY);
int count_sprite(char **map, int mapsizeY);
int check_direction(t_mlx *mlx, int mapsizeY);
void input_direction(t_mlx *mlx, char direction, int x, int y);
void set_playerpos(t_mlx *mlx, double x, double y);
void set_plane(t_mlx *mlx, double planeX, double planeY);
void set_dir(t_mlx *mlx, double dirX, double dirY);
int parse_contents(char **map, int mapsizeY);
int check_updown(int i, int j, char **map);
int check_border(char **map, int mapsizeY);
int check_rightside(char **map, int mapsizeY);
int move_map_2d(t_mlx *mlx, int mapsizeY);
int get_mapsizeY(t_mlx *mlx);
int check_lastline(t_mlx *mlx, char *line);
int parse_line(char *line, t_mlx *mlx);
int copy_map(t_mlx *mlx, char *line);
int is_valid_letter(char c);
int ft_lstaddmap_back(t_map **lst, t_map *new, char *row);
t_map *ft_lstnewmap(char *content);
int check_order(t_mlx *mlx, char *line);
int allset_filepath(t_mlx *mlx);
int check_tex(t_mlx *mlx);
int input_tex(t_mlx *mlx, int tex, char *line);
int which_tex(char *line, t_mlx *mlx);
int free_tex(t_mlx *mlx, int flag);
int input_resolution(t_mlx *mlx, char *str);
int free_2d_char(char **ret, int flag);
int ft_isspace(char c);
int error(char *str);
int	exit_game(t_mlx *mlx);

# endif 