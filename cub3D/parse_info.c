#include "./main.h"
#include "./gnl/get_next_line.h"

void ft_lstmapdelone(t_map *node)
{
	if (node)
	{
		free(node->row);
		node->row = NULL;
		free(node);
		node = NULL;
	}
}

void ft_lstmapclear(t_map **lst)
{
	t_map *tmp;

	if (lst && *lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstmapdelone(*lst);
			(*lst) = tmp;
		}
		*lst = NULL;
	}
}

void clear_map(t_mlx *mlx)
{
	int i;

	i = 0;
	ft_lstmapclear(&mlx->maplst);
	if (mlx->map)
	{
		while (mlx->map[i])
		{
			free(mlx->map[i]);
			mlx->map[i] = NULL;
			i++;
		}
		free(mlx->map);
		mlx->map = NULL;
	}
}

void clear_tex(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath)
		{
			free(mlx->tex[i].filepath);
			mlx->tex[i].filepath = NULL;
		}
		if (mlx->tex[i].img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->tex[i].img_ptr);
		i++;
	}
}

void clear_sprite(t_mlx *mlx)
{
	if (mlx->sprite)
	{
		free(mlx->sprite);
		mlx->sprite = NULL;
	}
}

void clear_window(t_mlx *mlx)
{
	if (mlx->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	}
}

int error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (ERROR);
}

int error(char *str, t_mlx *mlx)
{
	clear_window(mlx);
	clear_sprite(mlx);
	clear_tex(mlx);
	clear_map(mlx);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(ERROR);
	return (ERROR);
}

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int free_2d_char(char **ret, int flag)
{
	int i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	ret = NULL;
	return (flag);
}

int input_resolution(t_mlx *mlx, char *str)
{
	char **ret;
	char *check;
	int i;

	i = 0;
	while (str[++i])
		if (!(ft_isdigit(str[i]) || ft_isspace(str[i])))
			return (error_msg(ERR_FORMAT));
	if ((ret = ft_split(&str[1], ' ')) == NULL)
		return (error_msg(ERR_MEM));
	check = ret[2];
	if (check)
		if (!(check[0] == '\0' || check[0] == '\r' || check[0] == '\n'))
			return (free_2d_char(ret, error_msg(ERR_FORMAT)));
	mlx->winWidth = ft_atoi(ret[0]);
	mlx->winHeight = ft_atoi(ret[1]);
	if (mlx->winWidth > MAX_WIN_WIDTH)
		mlx->winWidth = MAX_WIN_WIDTH;
	if (mlx->winWidth < MIN_WIN_WIDTH)
		mlx->winWidth = MIN_WIN_WIDTH;
	if (mlx->winHeight > MAX_WIN_HEIGHT)
		mlx->winHeight = MAX_WIN_HEIGHT;
	if (mlx->winHeight < MIN_WIN_HEIGHT)
		mlx->winHeight = MIN_WIN_HEIGHT;
	return (free_2d_char(ret, TRUE));
}

int which_tex(char *line, t_mlx *mlx)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		return (SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WEST);
	else if (line[0] == 'E' && line[1] == 'A')
		return (EAST);
	else if (line[0] == 'S')
		return (SPRITE);
	else if (line[0] == 'F')
		return (FLOOR);
	else if (line[0] == 'C')
		return (CEILING);
	else if (line[0] == 0 || line[0] == '1' || line[0] == 'R')
		return (PASS);
	else
		return (ERROR);
}

int input_tex(t_mlx *mlx, int tex, char *line)
{
	int space;
	int i;
	char *tmp;

	i = 0;
	if (tex != ERROR && tex != PASS)
	{
		if (tex >= 0 && tex <= 3)
			space = 2;
		else
			space = 1;
		while (space--)
			i++;
		while (ft_isspace(line[i]))
			i++;
		if ((mlx->tex[tex].filepath = ft_strdup(&line[i])) == NULL)
			return (error(ERR_MEM, mlx));
	}
	return (TRUE);
}

void check_tex(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			error(ERR_FORMAT, mlx);
		i++;
	}
}

int allset_filepath(t_mlx *mlx)
{
	int allset;
	int i;

	allset = TRUE;
	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			allset = FALSE;
		i++;
	}
	return (allset);
}

int check_order(t_mlx *mlx, char *line)
{
	if (line[0] == '1' || line[0] == '0')
		error(ERR_ORDER, mlx);
	return (TRUE);
}

t_map *ft_lstnewmap(char *content)
{
	t_map *ret;

	if ((ret = (t_map *)malloc(sizeof(ret))) == NULL)
		return (NULL);
	ret->next = NULL;
	ret->row = content;
	return (ret);
}

int ft_lstaddmap_back(t_map **lst, t_map *new, char *row)
{
	t_map *tmp;

	if (lst)
	{
		if ((new = ft_lstnewmap(row)) == NULL)
			return (ERROR);
		tmp = *lst;
		if (!tmp)
			*lst = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

int is_valid_letter(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N' ||
		c == 'S' || c == 'W' || c == 'E')
		return (TRUE);
	else if (ft_isspace(c) || c == '\r' || c == '\n')
		return (TRUE);
	return (FALSE);
}

int copy_map(t_mlx *mlx, char *line)
{
	int i;
	t_map *new;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 0)
		return (PASS);
	if (line[i] != '1')
		return (error(ERR_MAP_SUR, mlx));
	while (line[i])
	{
		if (!is_valid_letter(line[i]))
			return (error(ERR_LETTER, mlx));
		i++;
	}
	if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
		return (error(ERR_MEM, mlx));
}

int parse_line(char *line, t_mlx *mlx)
{
	int i;
	int tex;

	i = 0;
	if (!allset_filepath(mlx))
	{
		while (ft_isspace(line[i]))
			i++;
		check_order(mlx, &line[i]);
		if (line[i] == 'R')
			if ((input_resolution(mlx, &line[i])) == ERROR)
				return (ERROR);
		if ((tex = which_tex(&line[i], mlx)) == ERROR)
			return (error(ERR_LETTER, mlx));
		if (input_tex(mlx, tex, &line[i]) == ERROR)
			return (ERROR);
	}
	else if (copy_map(mlx, line) == ERROR)
		return (ERROR);
	return (TRUE);
}

void check_lastline(t_mlx *mlx, char *line)
{
	int i;
	t_map *new;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1')
		if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
			error(ERR_MEM, mlx);
}

int get_mapsizeY(t_mlx *mlx)
{
	int len;
	t_map *tmp;

	tmp = mlx->maplst;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void move_map_2d(t_mlx *mlx, int mapsizeY)
{
	int i;
	char *tmp;
	t_map *lst;

	i = 0;
	if ((mlx->map = (char **)malloc(sizeof(char *) * mapsizeY + 1)) == NULL)
		error(ERR_MEM, mlx);
	mlx->map[mapsizeY] = 0;
	lst = mlx->maplst;
	while (lst)
	{
		tmp = lst->row;
		if (tmp[ft_strlen(tmp) - 1] == '\r' || tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		mlx->map[i] = tmp;
		lst = lst->next;
		i++;
	}
}

void check_rightside(t_mlx *mlx, int mapsizeY)
{
	int i;
	int j;

	i = 0;
	while (i < mapsizeY)
	{
		j = ft_strlen(mlx->map[i]) - 1;
		while (ft_isspace(mlx->map[i][j]))
			j--;
		if (mlx->map[i][j] != '1')
			error(ERR_MAP_SUR, mlx);
		i++;
	}
}

void check_border(t_mlx *mlx, int mapsizeY)
{
	int i;

	i = 0;
	while (mlx->map[0][i])
	{
		if (mlx->map[0][i] != '1' && !ft_isspace(mlx->map[0][i]))
			error(ERR_MAP_SUR, mlx);
		i++;
	}
	i = 0;
	while (mlx->map[mapsizeY - 1][i])
	{
		if (mlx->map[mapsizeY - 1][i] != '1' && !ft_isspace(mlx->map[mapsizeY - 1][i]))
			error(ERR_MAP_SUR, mlx);
		i++;
	}
	check_rightside(mlx, mapsizeY);
}

void check_updown(int i, int j, t_mlx *mlx)
{
	if (ft_isspace(mlx->map[i - 1][j + 1]))
		error(ERR_MAP_SUR, mlx);
	if (ft_strlen(mlx->map[i + 1]) > j + 1)
	{
		if (ft_isspace(mlx->map[i + 1][j + 1]))
			error(ERR_MAP_SUR, mlx);
	}
	else
		error(ERR_MAP_SUR, mlx);
}

void parse_contents(t_mlx *mlx, int mapsizeY)
{
	int i;
	int j;

	i = 1;
	while (i < mapsizeY - 1)
	{
		j = 0;
		while (ft_isspace(mlx->map[i][j]))
			j++;
		while (j < ft_strlen(mlx->map[i]) - 1)
		{
			if (mlx->map[i][j + 1] == '0')
			{
				check_updown(i, j, mlx);
				if (ft_isspace(mlx->map[i][j]) ||
					ft_isspace(mlx->map[i][j + 2]))
					error(ERR_MAP_SUR, mlx);
			}
			j++;
		}
		i++;
	}
}

void set_dir(t_mlx *mlx, double dirX, double dirY)
{
	mlx->game.dirX = dirX;
	mlx->game.dirY = dirY;
}

void set_plane(t_mlx *mlx, double planeX, double planeY)
{
	mlx->game.planeX = planeX;
	mlx->game.planeY = planeY;
}

void set_playerpos(t_mlx *mlx, double x, double y)
{
	mlx->game.posX = x + 0.5;
	mlx->game.posY = y + 0.5;
}

void input_direction(t_mlx *mlx, char direction, int x, int y)
{
	if (direction == 'N')
	{
		set_dir(mlx, -1, 0);
		set_plane(mlx, 0, 0.66);
	}
	else if (direction == 'S')
	{
		set_dir(mlx, 1, 0);
		set_plane(mlx, 0, -0.66);
	}
	else if (direction == 'E')
	{
		set_dir(mlx, 0, 1);
		set_plane(mlx, 0.66, 0);
	}
	else if (direction == 'W')
	{
		set_dir(mlx, 0, -1);
		set_plane(mlx, -0.66, 0);
	}
	set_playerpos(mlx, (double)x, (double)y);
}

void check_direction(t_mlx *mlx, int mapsizeY)
{
	int i;
	int j;
	int isPlural;

	i = 0;
	isPlural = 0;
	while (++i < mapsizeY - 1)
	{
		j = 0;
		while (ft_isspace(mlx->map[i][j]))
			j++;
		while (j < ft_strlen(mlx->map[i]) - 1)
		{
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' ||
				mlx->map[i][j] == 'E' || mlx->map[i][j] == 'W')
			{
				input_direction(mlx, mlx->map[i][j], i, j);
				mlx->map[i][j] = '0';
				isPlural++;
			}
			j++;
		}
	}
	if (isPlural != 1)
		error(ERR_PLU, mlx);
}

int count_sprite(char **map, int mapsizeY)
{
	int i;
	int j;
	int spriteNum;

	i = 1;
	spriteNum = 0;
	while (i < mapsizeY - 1)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (map[i][j + 1])
		{
			if (map[i][j + 1] == '2')
				spriteNum++;
			j++;
		}
		i++;
	}
	return (spriteNum);
}

void input_sprite(t_sprite *sprites, char **map, int mapsizeY)
{
	int i;
	int j;
	int idx;

	i = 1;
	idx = 0;
	while (i < mapsizeY)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (map[i][j + 1])
		{
			if (map[i][j + 1] == '2')
			{
				sprites[idx].x = i + 0.5;
				sprites[idx].y = j + 1.5;
				idx++;
			}
			j++;
		}
		i++;
	}
}

void check_sprite(t_mlx *mlx, int mapsizeY)
{
	int spriteNum;
	t_sprite *sprites;

	spriteNum = count_sprite(mlx->map, mapsizeY);
	if ((sprites = (t_sprite *)malloc(sizeof(t_sprite) * spriteNum)) == NULL)
		error(ERR_MEM, mlx);
	input_sprite(sprites, mlx->map, mapsizeY);
	mlx->spriteNum = spriteNum;
	mlx->sprite = sprites;
}

void parse_map(t_mlx *mlx)
{
	int mapsizeY;

	mapsizeY = get_mapsizeY(mlx);
	move_map_2d(mlx, mapsizeY);
	check_direction(mlx, mapsizeY);
	check_border(mlx, mapsizeY);
	parse_contents(mlx, mapsizeY);
	check_sprite(mlx, mapsizeY);
}

int parse_info(char const *argv, t_mlx *mlx)
{
	int fd;
	char *line;

	if ((fd = open(argv, O_RDONLY)) == ERROR)
		error(ERR_OPEN, mlx);
	while (get_next_line(fd, &line))
	{
		if (parse_line(line, mlx) == ERROR)
		{
			free(line);
			return (ERROR);
		}
		free(line);
	}
	check_tex(mlx);
	check_lastline(mlx, line);
	parse_map(mlx);
	free(line);
	close(fd);
	return (TRUE);
}

char *ft_strfromend(char *str, int size)
{
	int len;
	int i;
	char *copy;

	if ((copy = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (size)
	{
		copy[i++] = str[len - size];
		size--;
	}
	copy[i] = '\0';
	return (copy);
}

void check_extension(char const *argv, t_mlx *mlx)
{
	char *extension;

	if ((extension = ft_strfromend((char *)argv, 4)) == NULL)
		error(ERR_MEM, mlx);
	if (ft_strncmp(extension, ".cub", 5))
	{
		free(extension);
		error(ERR_EXT, mlx);
	}
	free(extension);
}

void input_color(t_tex *tex, t_mlx *mlx, char **ret)
{
	int rgb[3];
	int i;
	int color;

	color = 0;
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(ret[i]);
		if (rgb[i] > 255 || rgb[i] < 0)
			error(ERR_RGB, mlx);
		i++;
	}
	color += rgb[0] << 16;
	color += rgb[1] << 8;
	color += rgb[2];
	if (tex == &mlx->tex[FLOOR])
		mlx->tex[FLOOR].floorColor = color;
	if (tex == &mlx->tex[CEILING])
		mlx->tex[CEILING].ceilingColor = color;
	free_2d_char(ret, TRUE);
}

int isRGBcolor(t_tex *tex, t_mlx *mlx)
{
	char **ret;
	int i;
	char *check;

	i = 0;
	while (tex->filepath[i])
	{
		if (!ft_isdigit(tex->filepath[i]) && !ft_isspace(tex->filepath[i]))
			return (FALSE);
		i++;
	}
	if ((ret = ft_split(tex->filepath, ' ')) == NULL)
		error(ERR_MEM, mlx);
	if (check)
	{
		if (!(check[0] == '\0' || check[0] == '\r' || check[0] == '\n'))
		{
			free_2d_char(ret, ERROR);
			error(ERR_FORMAT, mlx);
		}
	}
	input_color(tex, mlx, ret);
	return (TRUE);
}

void init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->winWidth,
									mlx->winHeight, "DomMorello");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->winWidth,
													mlx->winHeight);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
										&mlx->img.size_l, &mlx->img.endian);	
}

void init_game(t_mlx *mlx)
{
	int i;
	char *tmp;

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
			if (isRGBcolor(&mlx->tex[i], mlx))
				continue;
			else
				error(ERR_PATH, mlx);
		}
		mlx->tex[i].data = (int *)mlx_get_data_addr(mlx->tex[i].img_ptr,
				&mlx->tex[i].bpp, &mlx->tex[i].size_l, &mlx->tex[i].endian);
	}
}

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

int save_bmp(t_mlx *mlx)
{
	int fd;
	t_bmfh bmfh;
	t_bmih bmih;

	if ((fd = open("capture.bmp", O_WRONLY | O_CREAT)) == ERROR)
		return (error_msg(ERR_OPEN));
	set_bmfh(&bmfh, mlx);
	set_bmih(&bmih, mlx);
	write(fd, &bmfh, sizeof(bmfh));
	write(fd, &bmih, sizeof(bmih));
	write(fd, mlx->img.data, bmih.biSizeImage);
	close(fd);
	return (TRUE);
}

void mlx_event(t_mlx *mlx)
{
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win_ptr, 17, 1L << 17, error, mlx);
	mlx_loop_hook(mlx->mlx_ptr, run_game, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	if (argv[1])
	{
		check_extension(argv[1], &mlx);
		parse_info(argv[1], &mlx);
		init_game(&mlx);
		if (argv[2])
		{
			if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
			{
				run_game(&mlx);
				save_bmp(&mlx);
			}
			else
				return (error(ERR_ARG, &mlx));
		}
		mlx_event(&mlx);
	}
	else
		return (error(ERR_MAP, &mlx));
	return (0);
}