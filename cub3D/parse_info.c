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

int which_tex(char *line)
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
	else
		return (ERROR);
}

int input_tex(t_mlx *mlx, int tex, char *line)
{
	int space;
	int i;

	i = 0;
	if (tex != ERROR)
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
			return (error("Error\nmemory allocation fail"));
		/* 중간에 에러가 났을 경우 이 부분을 어떻게 free할지 해결해야 한다. */
	}
}

int parse_line(char *line, t_mlx *mlx)
{
	int i;
	int tex;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'R')
		if ((input_resolution(mlx, &line[i])) == ERROR)
			return (ERROR);
	tex = which_tex(&line[i]);
	input_tex(mlx, tex, &line[i]);
	/* init을 통해서 널값 넣어주고 나서 하나라도 널인체로 남아있으면 에러처리 */
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
		parse_line(line, mlx);
		free(line);
	}
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
