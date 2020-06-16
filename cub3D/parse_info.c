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
			return (error("Error\ninvalid format:unavailable letter included in the file"));
		if (input_tex(mlx, tex, &line[i]) == ERROR)
			return (ERROR);
	}
	else
	{
		
	}
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
			return (error("Error\nfail to convert xpm file to image"));
		mlx->tex[i].data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
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
		for (int i = 0; i < 7; i++)
		{
			printf("%d\n", mlx.tex[i].filepath[ft_strlen(mlx.tex[i].filepath) - 1]);
		}
	}
	else if (argc == 3)
	{
		/* bmp */
	}
	else
	{
		return (error("Error\nneed a map file"));
	}
	mlx_loop(mlx.mlx_ptr);
	return 0;
}
