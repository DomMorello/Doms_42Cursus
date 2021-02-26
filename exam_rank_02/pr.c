#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return len;
}

char *ft_strndup(char *s, int n)
{
	char *ret;

	if ((ret = malloc(sizeof(char) * n + 1)) == NULL)
		return NULL;
	int i = 0;
	while (s[i] && i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return ret;
}

char *ft_strchr(char *s, int c)
{
	char *ret = s;

	while (*ret != c)
	{
		if (!*ret)
			return NULL;
		ret++;
	}
	return ret;
}

char *ft_strjoin(char *s1, char *s2)
{
	char *ret;
	int s1_len = ft_strlen(s1);
	int s2_len = ft_strlen(s2);
	int i = 0;

	if ((ret = malloc(sizeof(char) * (s1_len + s2_len + 1))) == NULL)
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
	static char *save;
	char buf[2];
	int bytes;
	char *tmp;
	char *n_ptr;

	if (!save)
	{
		save = ft_strndup("", 0);
		while ((bytes = read(0, buf, 1) > 0))
		{
			buf[bytes] = 0;
			tmp = save;
			save = ft_strjoin(save, buf);
			free(tmp);
		}
	}
	n_ptr = ft_strchr(save, '\n');
	if (n_ptr)
	{
		*line = ft_strndup(save, n_ptr - save);
		save += n_ptr - save + 1;
		return 1;
	}
	else
	{
		*line = ft_strndup(save, ft_strchr(save, '\0') - save);
		return 0;
	}
}

int main(void)
{
	char *line;
	int ret;

	line = NULL;
	while ((ret = get_next_line(&line)) > 0)
	{
		printf("%d %s\n", ret, line);
		free(line);
		line = NULL;
	}
	printf("%d %s\n", ret, line);
	free(line);
	line = NULL;
	return 0;
}
