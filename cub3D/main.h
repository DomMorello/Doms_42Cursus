/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 00:37:38 by donglee           #+#    #+#             */
/*   Updated: 2020/06/28 01:08:00 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./minilibx_linux/mlx.h"

# define MIN_WIN_WIDTH 320
# define MIN_WIN_HEIGHT 240
# define MAX_WIN_WIDTH 1280
# define MAX_WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define ERR_MEM "Error\nmemory allocation fail"
# define ERR_ARG "Error\nwrong arguements"
# define ERR_MAP "Error\nneed a map file"
# define ERR_OPEN "Error\ncan't open the file"
# define ERR_PATH "Error\nwrong filepath:fail to convert xpm file to image"
# define ERR_FORMAT "Error\ninvalid format"
# define ERR_RGB "Error\nwrong RGB color value"
# define ERR_EXT "Error\ninvalid extension"
# define ERR_PLU "Error\nplayer position must be singular"
# define ERR_MAP_SUR "Error\nmap is not entirely surrounded by walls"
# define ERR_LETTER "Error\ninvalid letter is included in the file"
# define ERR_ORDER "Error\nmap info must be located at the end of the file"
# define ERR_TOOMANY "Error\ntoo many arguements"

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define PASS 7

# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

enum				e_textures
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
	SPRITE,
	CEILING,
	FLOOR
};

typedef struct		s_img
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_tex
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				width;
	int				height;
	char			*filepath;
	int				floorColor;
	int				ceilingColor;
}					t_tex;

typedef struct		s_game
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	int				mapX;
	int				mapY;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int				stepX;
	int				stepY;
	int				hit;
	int				side;
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	int				drawStart;
	int				drawEnd;
	int				lineHeight;
	int				move_f;
	int				move_b;
	int				move_r;
	int				move_l;
	int				rotate_r;
	int				rotate_l;
}					t_game;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			spriteX;
	double			spriteY;
	double			transformX;
	double			transformY;
	double			spriteScreenX;
	int				perpWallDist;
	double			dist;
	double			spriteHeight;
	double			spriteWidth;
	int				drawStartX;
	int				drawEndX;
	int				drawStartY;
	int				drawEndY;
}					t_sprite;

typedef struct		s_map
{
	char			*row;
	struct s_map	*next;
}					t_map;

typedef struct		s_fc
{
	float			rayDirX0;
	float			rayDirY0;
	float			rayDirX1;
	float			rayDirY1;
	float			floorStepX;
	float			floorStepY;
	float			floorX;
	float			floorY;
}					t_fc;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_game			game;
	t_tex			tex[7];
	t_sprite		*sprite;
	t_map			*maplst;
	t_fc			fc;
	char			**map;
	double			zbuffer[MAX_WIN_WIDTH];
	int				spriteNum;
	int				winWidth;
	int				winHeight;
}					t_mlx;

# pragma pack(push, 1)

typedef struct		s_bmfh
{
	char			bfType[2];
	int				bfSize;
	int				bfReserved;
	int				bfOffBits;
}					t_bmfh;

typedef struct		s_bmih
{
	int				biSize;
	int				biWidth;
	int				biHeight;
	char			biPlanes[2];
	char			biBitCount[2];
	int				biCompression;
	int				biSizeImage;
	int				biXPelsPerMeter;
	int				biYPelsPerMeter;
	int				biClrUsed;
	int				biClrImportant;
}					t_bmih;

# pragma pack(pop)

void				init_mlx(t_mlx *mlx);
int					key_release(int key, t_mlx *mlx);
int					key_press(int key, t_mlx *mlx);
int					run_game(t_mlx *mlx);
void				render_sprite(t_mlx *mlx);
void				draw_sprite(t_mlx *mlx, t_sprite *sprite);
void				cal_sprite(t_mlx *mlx, t_sprite *sprite);
void				transform_sprite(t_mlx *mlx, t_game *game,
										t_sprite *sprite);
void				desc_sort(t_mlx *mlx);
void				draw_floor_ceiling(t_mlx *mlx);
void				key_event(t_mlx *mlx);
void				draw_vertline(t_mlx *mlx, int i);
int					get_side(t_mlx *mlx);
void				perform_DDA(t_mlx *mlx);
void				set_draw(t_mlx *mlx);
void				set_var(t_mlx *mlx, int i);
void				set_side_dist(t_mlx *mlx);
void				init_game(t_mlx *mlx);
void				check_extension(char const *argv, t_mlx *mlx);
char				*ft_strfromend(char *str, int size);
int					parse_info(char const *argv, t_mlx *mlx);
void				parse_map(t_mlx *mlx);
void				check_sprite(t_mlx *mlx, int mapsizeY);
void				input_sprite(t_sprite *sprites, char **map, int mapsizeY);
int					count_sprite(char **map, int mapsizeY);
void				check_direction(t_mlx *mlx, int mapsizeY);
void				input_direction(t_mlx *mlx, char direction, int x, int y);
void				set_playerpos(t_mlx *mlx, double x, double y);
void				set_plane(t_mlx *mlx, double planeX, double planeY);
void				set_dir(t_mlx *mlx, double dirX, double dirY);
void				parse_contents(t_mlx *mlx, int mapsizeY);
void				check_updown(int i, int j, t_mlx *mlx);
void				check_border(t_mlx *mlx, int mapsizeY);
void				check_rightside(t_mlx *mlx, int mapsizeY);
void				move_map_2d(t_mlx *mlx, int mapsizeY);
int					get_mapsizeY(t_mlx *mlx);
void				check_lastline(t_mlx *mlx, char *line);
int					parse_line(char *line, t_mlx *mlx);
int					copy_map(t_mlx *mlx, char *line);
int					is_valid_letter(char c);
int					ft_lstaddmap_back(t_map **lst, t_map *new, char *row);
t_map				*ft_lstnewmap(char *content);
int					check_order(t_mlx *mlx, char *line);
int					allset_filepath(t_mlx *mlx);
void				check_tex(t_mlx *mlx);
int					input_tex(t_mlx *mlx, int tex, char *line);
int					which_tex(char *line);
int					input_resolution(t_mlx *mlx, char *str);
int					free_2d_char(char **ret, int flag);
int					ft_isspace(char c);
int					error_msg(char *str);
int					error(char *str, t_mlx *mlx);
int					exit_game(t_mlx *mlx);
void				clear_map(t_mlx *mlx);
void				input_color(t_tex *tex, t_mlx *mlx, char **ret);
void				ft_lstmapclear(t_map **lst);
void				ft_lstmapdelone(t_map *node);
int					isRGBcolor(t_tex *tex, t_mlx *mlx);
int					save_bmp(t_mlx *mlx);
void				move_forback(t_mlx *mlx, double moveSpeed);
void				move_side(t_mlx *mlx);
void				rotate_right(t_mlx *mlx, double rotSpeed);
void				rotate_left(t_mlx *mlx, double rotSpeed);
void				input_verline(t_mlx *mlx, int texX, int i);
void				draw_spriteY(t_mlx *mlx, t_sprite *sprite,
								int texX, int stripe);

#endif
