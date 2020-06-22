#include "./main.h"
#include "./gnl/get_next_line.h"

int error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
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
			return (error("Error\ninvalid format"));
	if ((ret = ft_split(&str[1], ' ')) == NULL)
		return (error("Error\nmemory allocation fail"));
	check = ret[2];
	if (check)
		if (!(check[0] == '\0' || check[0] == '\r' || check[0] == '\n')) //OS에 따라 다르겠지.
			return (free_2d_char(ret, error("Error\ninalid format")));
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

int free_tex(t_mlx *mlx, int flag)
{
	int i;

	i = 0;
	while (i)
	{
		if (mlx->tex[i].filepath != NULL)
		{
			free(mlx->tex[i].filepath);
			mlx->tex[i].filepath = NULL;
		}
		i++;
	}
	return (flag);
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
			return (free_tex(mlx, error("Error\nmemory allocation fail")));
	}
	return (TRUE);
}

int check_tex(t_mlx *mlx)
{
	/* file에 RGB값으로 들어오는 경우를 생각했을 때를 추가해야된다. */
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			return (error("Error\ninvalid format"));
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
	if (!allset_filepath(mlx))
		if (line[0] == '1')
			return (error("Error\nmap info must be located at the end of the file"));
	return (TRUE);
}

t_map *ft_lstnewmap(char *content)
{
	t_map *ret;

	if ((ret = (t_map *)malloc(sizeof(ret))) == 0)
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
	if (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
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
		return (error("Error\nmap is not entirely surrounded by walls"));
	while (line[i])
	{
		if (!is_valid_letter(line[i]))
			return (error("Error\ninvalid letter is included in the map info"));
		i++;
	}
	if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
		return (error("Error\nmemory allocation fail"));
	//메모리릭 해결해야 한다. 에러났을 경우
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
		if ((check_order(mlx, &line[i])) == ERROR)
			return (ERROR);
		if (line[i] == 'R')
			if ((input_resolution(mlx, &line[i])) == ERROR)
				return (ERROR);
		if ((tex = which_tex(&line[i], mlx)) == ERROR)
			return (error("Error\ninvalid format:invalid letter is included in the file"));
		if (input_tex(mlx, tex, &line[i]) == ERROR)
			return (ERROR);
	}
	else if (copy_map(mlx, line) == ERROR)
		return (ERROR);
	return (TRUE);
}

int check_lastline(t_mlx *mlx, char *line)
{
	int i;
	t_map *new;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1')
		if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
			return (ERROR);
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

int move_map_2d(t_mlx *mlx, int mapsizeY)
{
	int i;
	char *tmp;

	i = 0;
	if ((mlx->map = (char **)malloc(sizeof(char *) * mapsizeY + 1)) == NULL)
		return (error("Error\nmemory allocation fail"));
	mlx->map[mapsizeY] = 0;
	while (mlx->maplst)
	{
		tmp = mlx->maplst->row;
		if (tmp[ft_strlen(tmp) - 1] == '\r' || tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		mlx->map[i] = tmp;
		mlx->maplst = mlx->maplst->next;
		i++;
	}
	return (TRUE);
}

int check_rightside(char **map, int mapsizeY)
{
	int i;
	int j;

	i = 0;
	while (i < mapsizeY)
	{
		j = ft_strlen(map[i]) - 1;
		while (ft_isspace(map[i][j]))
			j--;
		if (map[i][j] != '1')
			return (error("Error\nmap is not entirely surrounded by walls"));
		i++;
	}
	return (TRUE);
}

int check_border(char **map, int mapsizeY)
{
	int i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && !ft_isspace(map[0][i]))
			return (error("Error\nmap is not entirely surrounded by walls"));
		i++;
	}
	i = 0;
	while (map[mapsizeY - 1][i])
	{
		if (map[mapsizeY - 1][i] != '1' && !ft_isspace(map[mapsizeY - 1][i]))
			return (error("Error\nmap is not entirely surrounded by walls"));
		i++;
	}
	if (check_rightside(map, mapsizeY) == ERROR)
		return (ERROR);
	return (TRUE);
}

int check_updown(int i, int j, char **map)
{
	if (ft_isspace(map[i - 1][j + 1]))
		return (error("Error\nmap is not entirely surrounded by walls"));
	if (ft_strlen(map[i + 1]) > j + 1)
	{
		if (ft_isspace(map[i + 1][j + 1]))
			return (error("Error\nmap is not entirely surrounded by walls"));
	}
	else
		return (error("Error\nmap is not entirely surrounded by walls"));
}

int parse_contents(char **map, int mapsizeY)
{
	int i;
	int j;

	i = 1;
	while (i < mapsizeY - 1)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		while (j < ft_strlen(map[i]) - 1)
		{
			if (map[i][j + 1] == '0')
			{
				if (check_updown(i, j, map) == ERROR)
					return (ERROR);
				if (ft_isspace(map[i][j]) || ft_isspace(map[i][j + 2]))
					return (error("Error\nmap is not entirely surrounded by walls"));
			}
			j++;
		}
		i++;
	}
	return (TRUE);
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

int check_direction(t_mlx *mlx, int mapsizeY)
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
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' || mlx->map[i][j] == 'E' || mlx->map[i][j] == 'W')
			{
				input_direction(mlx, mlx->map[i][j], i, j);
				mlx->map[i][j] = '0';
				isPlural++;
			}
			j++;
		}
	}
	if (isPlural != 1)
		return (error("Error\nplayer position must be singular"));
	return (TRUE);
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

void	input_sprite(t_sprite *sprites, char **map, int mapsizeY)
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

int check_sprite(t_mlx *mlx, int mapsizeY)
{
	int spriteNum;
	t_sprite *sprites;

	spriteNum = count_sprite(mlx->map, mapsizeY);
	if ((sprites = (t_sprite *)malloc(sizeof(t_sprite) * spriteNum)) == NULL)
		return (error("Error\nmemory allocation fail"));
	input_sprite(sprites, mlx->map, mapsizeY);
	mlx->spriteNum = spriteNum;
	mlx->sprite = sprites;
	return (TRUE);
}

int parse_map(t_mlx *mlx)
{
	int mapsizeY;

	mapsizeY = get_mapsizeY(mlx);
	if (move_map_2d(mlx, mapsizeY) == ERROR)
		return (ERROR);
	if (check_direction(mlx, mapsizeY) == ERROR)
		return (ERROR);
	if (check_border(mlx->map, mapsizeY) == ERROR)
		return (ERROR);
	if (parse_contents(mlx->map, mapsizeY) == ERROR)
		return (ERROR);
	if (check_sprite(mlx, mapsizeY) == ERROR)
		return (ERROR);
	return (TRUE);
}

int parse_info(char const *argv, t_mlx *mlx)
{
	int fd;
	char *line;

	if ((fd = open(argv, O_RDONLY)) == -1)
		return (error("Error\ncannot open the file"));
	while (get_next_line(fd, &line))
	{
		if (parse_line(line, mlx) == ERROR)
		{
			free(line);
			return (ERROR);
		}
		free(line);
	}
	if (check_tex(mlx) == ERROR)
		return (ERROR);
	if (check_lastline(mlx, line) == ERROR)
		return (ERROR);
	if (parse_map(mlx) == ERROR)
		return (ERROR);
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

int check_extension(char const *argv)
{
	char *extension;

	if ((extension = ft_strfromend((char *)argv, 4)) == NULL)
		return (error("Error\nmemory allocation fail"));
	if (!ft_strncmp(extension, ".cub", 5))
	{
		free(extension);
		return (TRUE);
	}
	free(extension);
	return (error("Error\ninvalid extension"));
}

int init_game(t_mlx *mlx)
{
	int i;
	char *tmp;

	i = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->winWidth, mlx->winHeight, "DomMorello");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->winWidth, mlx->winHeight);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	while (i < 7)
	{
		tmp = mlx->tex[i].filepath;
		if (tmp[ft_strlen(tmp) - 1] == '\r' || tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		if ((mlx->tex[i].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, tmp, &mlx->tex[i].width, &mlx->tex[i].height)) == NULL)
			return (error("Error\nWrong filepath:fail to convert xpm file to image"));
		mlx->tex[i].data = (int *)mlx_get_data_addr(mlx->tex[i].img_ptr, &mlx->tex[i].bpp, &mlx->tex[i].size_l, &mlx->tex[i].endian);
		i++;
	}
}

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	if (argc == 2)
	{
		if (check_extension(argv[1]) == ERROR || parse_info(argv[1], &mlx) == ERROR)
			return (ERROR);
		if (init_game(&mlx) == ERROR)
			return (ERROR);
	}
	else if (argc == 3)
	{
		/* bmp */
	}
	else
	{
		return (error("Error\nneed a map file"));
	}
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press2, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L << 1, key_release, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 17, exit_game, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, run_game, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return 0;
}
