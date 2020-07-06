#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	get_next_line(char **line)
{
	int fd;
	int ret;
	int buf_xize;
	static char *save = NULL;
	char buf[32];
	
	fd = 0;
	if (!line)
		return (-1);
	while ((ret = read(fd, save, sizeof(buf))) > 0)
	{
		buf[ret] = 0;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	char *line;

	get_next_line(&line);
	return 0;
}
