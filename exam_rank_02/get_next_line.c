#include "./get_next_line.h"

int is_newline(char *save, char **line)
{
	char *found = NULL;
	int end = 0;
	int len = 0;

	if ((found = ft_strchr(save, '\n')))
	{
		end = found - save;
		len = ft_strlen(found);
		*line = ft_substr(save, 0, end);
		ft_strlcpy(save, found + 1, len + 1);
		return 1;
	}
	return 0;
}

char *ft_strjoindel(char *save, char *buf)
{
	char *ret  = NULL;
	int len1 = 0;
	int len2 = ft_strlen(buf);
	if (save)
		len1 = ft_strlen(save);
	if ((ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1))) == NULL)
		return (NULL);
	if (save)
	{
		ft_strlcpy(ret, save, len1 + 1);
		ft_strdel(&save);
	}
	ft_strlcpy(ret + len1, buf, len2 + 1);
	return ret;
}

int get_next_line(char **line)
{
	int buf_size = 10;
	char buf[buf_size + 1];
	int ret = 0;
	static char *save = NULL;

	if (!line)
		return -1;
	if (save && is_newline(save, line) == 1)
		return 1;
	while ((ret = read(0, buf, buf_size)) > 0)
	{
		buf[buf_size] = 0;
		if (!(save = ft_strjoindel(save, buf)))
			return -1;
		if (is_newline(save, line) == 1)
			return 1;
	}
	if (save)
		*line = ft_strdup(save);
	else if (ret == -1 || ret == 0)
		*line = ft_strdup("");
	ft_strdel(&save);
	return ret;
}

int main()
{
	char *line = NULL;
	int ret = 0;

	while ((ret = get_next_line(&line)) > 0)
	{
		printf("line:%s\n", line);
		free(line);
		line = NULL;
	}
	printf("line:%s\n", line);
	free(line);
	line = NULL;
	return 0;
}