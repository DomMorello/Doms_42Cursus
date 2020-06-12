#include "./main.h"
#include "./gnl/get_next_line.h"

int error(char *str)
{
	write(1, str, ft_strlen(str));
	return (ERROR);
}

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int input_resolution(t_mlx *mlx, char *str)
{
	char **ret;
	int i;

	i = 0;
	while (str[++i])
	{
		if (!(ft_isdigit(str[i]) || ft_isspace(str[i])))
			return (error("Error\ninvalid format"));
	}
	if ((ret = ft_split(&str[1], ' ')) == NULL)
		return (error("Error\nmemory allocation fail"));
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
	i = -1;
	while (ret[++i])
		free(ret[i]);
	free(ret);
	ret = NULL;
}

int parse_line(char *line, t_mlx *mlx)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
			break;
	}
	if (line[i] == 'R')
		input_resolution(mlx, &line[i]);
	// if (line[i] == 'N' && line[i + 1] == 'O')
	// if (line[0] == 'S' && line[1] == 'O')
	// if (line[0] == 'W' && line[1] == 'E')
	// if (line[0] == 'E' && line[1] == 'A')
}

int parse_info(char const *argv)
{
	int fd;
	char *line;
	t_mlx mlx;

	if ((fd = open(argv, O_RDONLY)) == -1)
		return (error("Error\ncannot open the file"));
	while (get_next_line(fd, &line))
	{
		parse_line(line, &mlx);
		free(line);
	}
}

char *ft_strfromend(char *str, int size)
{
	int len;
	int j;
	char *copy;

	if ((copy = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	len = ft_strlen(str);
	j = 0;
	while (size)
	{
		copy[j++] = str[len - size];
		size--;
	}
	copy[j] = '\0';
	return (copy);
}

int check_extension(char const *argv)
{
	char *extension;

	if ((extension = ft_strfromend((char *)argv, 4)) == NULL)
		return (FALSE);
	if (!ft_strncmp(extension, ".cub", 5))
		return (TRUE);
	else
		return (FALSE);
}

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		if (check_extension(argv[1]) == FALSE || parse_info(argv[1]) == ERROR)
			return (ERROR);
	}
	else if (argc == 3)
		/* bmp */

		return 0;
}
