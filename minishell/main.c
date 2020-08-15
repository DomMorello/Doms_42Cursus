#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (TRUE);
	return (FALSE);
}

int parse_line(char *line)
{
	char buf[100];
	int i;
	int ret;
	struct stat file;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'c' && line[i + 1] == 'd' && ft_isspace(line[i + 2]))
	{
		i += 3;
		while (ft_isspace(line[i]))
			i++;
		if ((ret = stat(&line[i], &file)) == -1)
			return -1;
		printf("%d\n", S_ISDIR(file.st_mode));
	}
	else
	{
		printf("command not found : %s\n", &line[i]);
	}
	
	return 1;
}

int main(int argc, char *argv[])
{
	char buf[100];
	int ret;
	char *line;

	ret = 0;
	while (1)
	{
		ft_putstr_fd("\033[31mbash\033[0m\033[32m-\033[0m\033[33m3.2\033[0m$ ", 1);
		if ((ret = get_next_line(0, &line)) < 0)
		{
			printf("gnl error\n");
			exit(0);	
		}
		parse_line(line);
	}
	return 0;
}
