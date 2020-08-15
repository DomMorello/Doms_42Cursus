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

void parse_line(char *line)
{
			
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
