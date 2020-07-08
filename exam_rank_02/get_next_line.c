#include "./get_next_line.h"

int ft_strlen(char *s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char *ft_strchr(char *s, int c)
{
	char *result;

	result = (char *)s;
	while (*result != c)
	{
		if (!*result)
			return (NULL);
		result++;
	}
	return (result);
}

char *ft_substr(char *s, int start, int len)
{
	char *result;
	int i;
	int str_len;

	str_len = ft_strlen(s);
	i = 0;
	if ((result = (char *)malloc(sizeof(char) * len + 1)) == 0)
		return (NULL);
	while (i < len && start < str_len)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = 0;
	return (result);
}

char *ft_strdup(char *s1)
{
	char *result;
	int len;
	int i;

	i = 0;
	len = ft_strlen(s1);
	if ((result = (char *)malloc(sizeof(char) * len + 1)) == 0)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

void ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

int ft_strlcpy(char *dst, char *src, int dstsize)
{
	int src_len;
	int i;

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
	char *ret = NULL;
	int len1 = 0;
	int len2 = 0;

	len2 = ft_strlen(buf);
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

int get_next_line(char **line)
{
	static char *save = NULL;
	int buf_size = 10;
	char buf[buf_size + 1];
	int ret = 0;

	if (!line)
		return (-1);
	if (save && is_newline(save, line))
		return (1);
	while ((ret = read(0, buf, buf_size)) > 0)
	{
		buf[ret] = 0;
		if (!(save = ft_strjoindel(save, buf)))
			return (-1);
		if (is_newline(save, line))
			return (1);
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