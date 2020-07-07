#include "./get_next_line.h"

void ft_strdel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

int ft_strlen(char *s)
{
	int len = 0;
	
	while (s[len])
		len++;
	return (len);
}

char *ft_strdup(char *s)
{
	char *ret = NULL;
	int len = 0;
	int i = 0;

	len = ft_strlen(s);
	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return ret;
}

int ft_strlcpy(char *dst, char *src, int size)
{
	char *ret = NULL;
	int i = 0;
	int s_len = 0;

	s_len = ft_strlen(src);
	while (src[s_len])
		s_len++;
	if (size == 0)
		return (s_len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (s_len);
}

char *ft_strjoindel(char *save, char *buf)
{
	char *ret = NULL;
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
	return (ret);
}

char *ft_substr(char *s, int start, int len)
{
	char *ret = NULL;
	int s_len = 0;
	int i = 0;

	s_len = ft_strlen(s);
	if ((ret = (char *)malloc(sizeof(char) * s_len + 1)) == NULL)
		return (NULL);
	while (i < len && start < s_len)
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = 0;
	return (ret);
}

char *ft_strchr(char *save, int c)
{
	char *ret = NULL;

	ret = save;
	while (*ret != c)
	{
		if (!*ret)
			return (NULL);
		ret++;
	}
	return (ret);
}

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

int get_next_line(char **line)
{
	int fd = 0;
	static char *save = NULL;
	char buf[10 + 1];
	int ret = 0;

	if (!line)
		return (-1);
	if (save && is_newline(save, line))
		return (1);	
	while ((ret = read(fd, buf, 10)) > 0)
	{
		buf[ret] = 0;
		if (!(save = ft_strjoindel(save, buf)))
			return (-1);
		if (is_newline(save, line))
			return 1;
	}
	if (save)
		*line = ft_strdup(save);
	else if (ret == -1 || ret == 0)
		*line = ft_strdup("");
	ft_strdel(&save);
	return (ret);
}

int main()
{
	char *line;
	int ret;

	while ((ret = get_next_line(&line)) > 0)
	{
		printf("ret: %d line:%s\n", ret, line);
		free(line);
		line = NULL;
	}
	printf("ret: %d line:%s\n", ret, line);
	free(line);
	line = NULL;
	return 0;
}