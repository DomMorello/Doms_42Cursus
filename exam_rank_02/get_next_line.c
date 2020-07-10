#include "./get_next_line.h"

int ft_strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

void ft_stedel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

int ft_strlcpy(char *dst, char *src, int len)
{
	int i = 0;
	int s_len = ft_strlen(src);

	if (len == 0)
		return (s_len);
	while (src[i] && i < len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char *ft_strdup(char *s)
{
	int i = 0;
	int len = ft_strlen(s);
	char *ret = NULL;

	if (ret = (char *)malloc(sizeof(char) * len + 1) == NULL)
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char *ft_strchr(char *s, int c)
{
	
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