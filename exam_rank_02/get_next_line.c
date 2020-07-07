#include "./get_next_line.h"

int ft_strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

int ft_strlcpy(char *dst, char *src, int size)
{
	int s_len = 0;
	int i = 0;

	s_len = ft_strlen(src);
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

char *ft_strchr(char *str, int c)
{
	char *ret = NULL;

	ret = str;
	while (*ret != c)
	{
		if (!*ret)
			return (NULL);
		ret++;
	}
	return (ret);
}

char *ft_strdup(char *str)
{
	char *ret = NULL;
	int len = 0;
	int i = 0;

	len = ft_strlen(str);
	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char *ft_substr(char *s, int start, int len)
{
	char *ret = NULL;
	int s_len = ft_strlen(s);
	int i = 0;

	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
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

void ft_strdel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

int main()
{
	// char *line = NULL;
	// int ret = 0;

	// while ((ret = get_next_line(&line)) > 0)
	// {
	// 	printf("line:%s\n", line);
	// 	free(line);
	// 	line = NULL;
	// }
	// printf("line:%s\n", line);\
	// free(line);
	// line = NULL;
	// return 0;
}