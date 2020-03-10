#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}


char		*ft_strjoindel(char *s1, char *s2)
{
	char	*ret;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len;

	len_s1 = 0;
	len_s2 = ft_strlen(s2);
	if (s1)
		len_s1 = ft_strlen(s1);
	len = len_s1 + len_s2;
	printf("len_s1: %ld len_s2: %ld len: %ld\n", len_s1, len_s2, len);
	if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(ret, s1, (len_s1 + 1));
		ft_strdel(&s1);
	}
	ft_strlcpy(ret + len_s1, s2, (len_s2 + 1));
	return (ret);
}

int			is_newline(char **save, char **line)
{
	char	*found;
	size_t	end;
	size_t	len;

	len = 0;
	found = NULL;
	if ((found = ft_strchr(*save, '\n')))
	{
		printf("found: %s\n", found);
		printf("save: %s\n", *save);
		end = found - *save;
		printf("end: %ld\n", end);
		len = ft_strlen(found);
		printf("found len: %ld\n", len);
		*line = ft_substr(*save, 0, end);
		ft_strlcpy(*save, (found + 1), (len + 1));
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	int bytes_read;
	static char *save[1024];
	char buffer[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (save[fd] && is_newline(&save[fd], line) == 1)
		return (1);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = 0;
		if (!(save[fd] = ft_strjoindel(save[fd], buffer)))
			return (-1);
		printf("buffer: %s\n", buffer);
		printf("gnl save : %s\n", save[fd]);
		if (is_newline(&save[fd], line) == 1)
			return (1);
	}
	if (save[fd] && *save[fd])
		*line = ft_strdup(save[fd]);
	else if (bytes_read == -1 || bytes_read == 0)
		*line = ft_strdup("");
	ft_strdel(&save[fd]);
	return (bytes_read);
}


static void	print_line(int n, char **line, int ret_value)
{
	printf("Line: %d | %s | Return: %d\n", n, *line, ret_value);
	free(*line);
	*line = NULL;
}

static void	print_eofreached()
{
	printf("\n>> EOF reached\n\n");
}

static void	print_error()
{
	printf("\n/!\\ Error occurred\n\n");
}

static void	test_singlefd(int fd)
{
	char	*line;
	int		n;
	int		ret_value;

	line = NULL;
	n = 1;
	ret_value = 1;
	printf(">> Start test\n\n");
	while (ret_value > 0)
	{
		ret_value = get_next_line(fd, &line);
		print_line(n, &line, ret_value);
		n++;
		free(line);
	}
	if (ret_value == 0)
		print_eofreached();
	if (ret_value == -1)
		print_error();
	close(fd);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	char *line;

	line = 0;
	int i = 0;
	int j = 0;
	if (argc == 1)
		test_singlefd(STDIN_FILENO);
	else if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		while (i < 10)
		{
			get_next_line(fd, &line);
			printf("test1: %s\n", line);
			i++;
		}
		fd2 = open(argv[2], O_RDONLY);
		while (j < 10)
		{
			get_next_line(fd2, &line);
			printf("test2: %s\n", line);
			j++;
		}
		//test_singlefd(fd);
	}
	/* Uncomment to test leaks */
	//system("leaks test_gnl");
	return (0);
}