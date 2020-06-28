/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 00:37:38 by donglee           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/06/28 01:56:59 by marvin           ###   ########.fr       */
=======
/*   Updated: 2020/06/28 19:59:22 by donglee          ###   ########.fr       */
>>>>>>> d2f0a248641aeebd4b390b158602bca4194788f6
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
	int				floor_color;
	int				ceiling_color;
}					t_tex;

typedef struct		s_game
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	int				mapx;
	int				mapy;
	double			side_distx;
	double			side_disty;
	double			delta_distx;
	double			delta_disty;
	double			perp_wall_dist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			camerax;
	double			ray_dirx;
	double			ray_diry;
	int				draw_start;
	int				draw_end;
	int				line_height;
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
	double			spritex;
	double			spritey;
	double			transformx;
	double			transformy;
	double			sprite_screenx;
	int				perp_wall_dist;
	double			dist;
	double			sprite_height;
	double			sprite_width;
	int				draw_startx;
	int				draw_endx;
	int				draw_starty;
	int				draw_endy;
}					t_sprite;

typedef struct		s_map
{
	char			*row;
	struct s_map	*next;
}					t_map;

typedef struct		s_fc
{
	float			ray_dirx0;
	float			ray_diry0;
	float			ray_dirx1;
	float			ray_diry1;
	float			floor_stepx;
	float			floor_stepy;
	float			floorx;
	float			floory;
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
	int				sprite_num;
	int				win_width;
	int				win_height;
}					t_mlx;

# pragma pack(push, 1)

typedef struct		s_bmfh
{
	char			bf_type[2];
	int				bf_size;
	int				bf_reserved;
	int				bf_off_bits;
}					t_bmfh;

typedef struct		s_bmih
{
	int				bi_size;
	int				bi_width;
	int				bi_height;
	char			bi_planes[2];
	char			bi_bit_count[2];
	int				bi_compression;
	int				bi_size_image;
	int				bix_pels_per_meter;
	int				biy_pels_per_meter;
	int				bi_clr_used;
	int				bi_clr_important;
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
void				perform_dda(t_mlx *mlx);
void				set_draw(t_mlx *mlx);
void				set_var(t_mlx *mlx, int i);
void				set_side_dist(t_mlx *mlx);
void				init_game(t_mlx *mlx);
void				check_extension(char const *argv, t_mlx *mlx);
char				*ft_strfromend(char *str, int size);
int					parse_info(char const *argv, t_mlx *mlx);
void				parse_map(t_mlx *mlx);
void				check_sprite(t_mlx *mlx, int mapsizey);
void				input_sprite(t_sprite *sprites, char **map, int mapsizey);
int					count_sprite(char **map, int mapsizey);
void				check_direction(t_mlx *mlx, int mapsizey);
void				input_direction(t_mlx *mlx, char direction, int x, int y);
void				set_playerpos(t_mlx *mlx, double x, double y);
void				set_plane(t_mlx *mlx, double planex, double planey);
void				set_dir(t_mlx *mlx, double dirx, double diry);
void				parse_contents(t_mlx *mlx, int mapsizey);
void				check_updown(int i, int j, t_mlx *mlx);
void				check_border(t_mlx *mlx, int mapsizey);
void				check_rightside(t_mlx *mlx, int mapsizey);
void				move_map_2d(t_mlx *mlx, int mapsizey);
int					get_mapsizey(t_mlx *mlx);
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
int					is_rgbcolor(t_tex *tex, t_mlx *mlx);
int					save_bmp(t_mlx *mlx);
void				move_forback(t_mlx *mlx, double move_speed);
void				move_side(t_mlx *mlx);
void				rotate_right(t_mlx *mlx, double rot_speed);
void				rotate_left(t_mlx *mlx, double rot_speed);
void				input_verline(t_mlx *mlx, int texx, int i);
void				draw_spritey(t_mlx *mlx, t_sprite *sprite,
								int texx, int stripe);

#endif
