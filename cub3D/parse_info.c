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
		if (!(check[0] == '\0' || check[0] == '\r' || check[0] == '\n')) //OS�� ���� �ٸ�����.
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
			free(mlx->tex[i].filepath);
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
	/* ���⼭ �ٷ� xpm�Լ��� ����ؼ� error�� �߻����Ѿ�
		�Ȱ��� filepath�� ���� �� �����ų� �׷� ���ܻ�Ȳ�� ���� �� �ִ�. */
	int space;
	int i;

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
			return (free_tex(mlx, ERROR));
	}
	return (TRUE);
}

int check_tex(t_mlx *mlx)
{
	/* file�� RGB������ ������ ��츦 �������� ���� �߰��ؾߵȴ�. */
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			return (error("Error\ninvalid format"));
		i++;
	}
}

int check_order(t_mlx *mlx, char *line)
{
	int allSet;
	int i;

	i = 0;
	allSet = TRUE;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			allSet = FALSE;
		i++;
	}
	if (!allSet)
		if (line[0] == '1')
			return (error("Error\nmap info must be located at the end of the file"));
	return (TRUE);
}

int parse_line(char *line, t_mlx *mlx)
{
	int i;
	int tex;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if ((check_order(mlx, &line[i])) == ERROR)
		return (ERROR);
	if (line[i] == 'R')
		if ((input_resolution(mlx, &line[i])) == ERROR)
			return (ERROR);
	if ((tex = which_tex(&line[i], mlx)) == ERROR)
		return (error("Error\ninvalid format"));
	if (input_tex(mlx, tex, &line[i]) == ERROR)
		return (ERROR);
	return (TRUE);
}

void init_game(t_mlx *mlx)
{
}

int parse_info(char const *argv, t_mlx *mlx)
{
	int fd;
	char *line;

	init_game(mlx);
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

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	if (argc == 2)
	{
		if (check_extension(argv[1]) == ERROR || parse_info(argv[1], &mlx) == ERROR)
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

	return 0;
}
