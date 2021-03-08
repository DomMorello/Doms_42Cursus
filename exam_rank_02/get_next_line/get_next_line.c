#include "./get_next_line.h"

int ft_strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return len;
}

char *ft_strchr(char *s, int c)
{
	char *ret = s;

	while (ret && *ret != c)
	{
		if (!*ret)
			return NULL;
		ret++;
	}
	return ret;
}

char *ft_strdup(char *s)
{
	char *ret;
	int len = ft_strlen(s);
	int i = 0;

	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return NULL;
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return ret;
}

char *ft_substr(char *s, unsigned int start, int len)
{
	char *ret;
	int i = 0;

	if ((ret = malloc(sizeof(char) * len + 1)) == NULL)
		return NULL;
	while (i < len)
		ret[i++] = s[start++];
	ret[i] = 0;
	return ret;

}

char *ft_strjoin(char *s1, char *s2)
{
	char *ret;
	int s1_len = ft_strlen(s1);
	int s2_len = ft_strlen(s2);
	int i = 0;

	if ((ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))) == NULL)
		return NULL;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	while (i - s1_len < s2_len)
	{
		ret[i] = s2[i - s1_len];
		i++;
	}
	ret[i] = 0;
	return ret;
}

int get_next_line(char **line)
{
	char *n_ptr;
	int bytes;
	char buf[1024];
	static char *save;
	char *tmp;

	bytes = 1;
	while(((n_ptr = ft_strchr(save, '\n')) == NULL) && bytes != 0)
	{
		if ((bytes = read(0, buf, 1024)) == -1)
			return (-1);
		buf[bytes] = '\0';
		(save == NULL)? (tmp = ft_strdup(buf)) : (tmp = ft_strjoin(save, buf));
		if (save != NULL)
			free(save);
		save = tmp;
	}
	if(n_ptr != NULL)
	{
		tmp = save;
		*line = ft_substr(save, 0, n_ptr - save);
		save = ft_strdup(n_ptr + 1);
		free(tmp);
		return (1);
	}
	*line = save;
	save = NULL;
	return (0);
}

int main(int argc, char *argv[])
{
	char 	*line;
	int	ret;

	line = NULL;
	while ((ret = get_next_line(&line)) > 0)
	{
		printf("%d %s\n", ret, line);
		free(line);
		line = NULL;
	}
	printf("%d %s\n", ret, line);
	free(line);
	return 0;
}