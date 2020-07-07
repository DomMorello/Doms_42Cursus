#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;
	unsigned int	str_len;

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

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;
	size_t	i;

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

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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

char	*ft_strjoindel(char *s1, char *s2)
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

int		is_newline(char *save, char **line)
{
	char	*found;
	size_t	end;
	size_t	len;

	len = 0;
	found = NULL;
	if ((found = ft_strchr(save, '\n')))
	{
		end = found - save;
		len = ft_strlen(found);
		*line = ft_substr(save, 0, end);
		ft_strlcpy(save, (found + 1), (len + 1));
		return (1);
	}
	return (0);
}

int		get_next_line(char **line)
{
	int			bytes_read;
	static char	*save;
	char		buf[10 + 1];

	if (!line)
		return (-1);
	if (save && is_newline(save, line) == 1)
		return (1);
	while ((bytes_read = read(0, buf, 10)) > 0)
	{
		buf[bytes_read] = 0;
		if (!(save = ft_strjoindel(save, buf)))
			return (-1);
		if (is_newline(save, line) == 1)
			return (1);
	}
	if (save)
		*line = ft_strdup(save);
	else if (bytes_read == -1 || bytes_read == 0)
		*line = ft_strdup("");
	ft_strdel(&save);
	return (bytes_read);
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