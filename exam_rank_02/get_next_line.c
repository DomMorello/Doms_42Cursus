#include <unistd.h>
#include <stdlin.h>

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

	while (*ret != c)
	{
		if (!*ret)
			return NULL;
		ret++;
	}
	return ret;
}

char *ft_substr(char *s, int start, int len)
{
	int i = 0;
	char *ret = NULL;

	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return NULL;
	while (i < len && s[i])
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = 0;
	return ret;
}

void ft_strdel(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

char *ft_strdup(char *str)
{
	int len = ft_strlen(str);
	char *ret = NULL;
	int i = 0;

	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return NULL;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return ret;
}

int ft_strlcpy(char *dst, char *src, int size)
{
	int i = 0;
	int s_len = ft_strlen(src);

	if (size == 0)
		return s_len;
	while (i < size -1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return s_len;
}

int is_newline(char *save, char **line)
{
	int end = 0;
	char *found = NULL;
	int len = 0;

	if (found = ft_strchr(save, '\n'))
	{
		end = found - save;
		len = ft_strlen(found);
		*line = ft_substr(save, 0, end);
		ft_strlcpy(save, found + 1, len + 1);
		return 0;
	}
	return 1;

}

char *ft_strjoindel(char *save, char *buf)
{
	char *ret = NULL;
	int len1 = 0;
	int len2 = ft_strlen(buf);
	if (save)
		len1 = ft_strlen(save);
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (save)
	{
		ft_strjoindel(ret, save, len1 + 1);
		ft_strdel(&save);
	}
	ft_strlcpy(ret + len1, buf, len2 + 1)
	return ret;
}

int get_next_line(char **line)
{
	int ret = 0;
	static char *save;
	int buf_size = 10;
	char buf[buf_size + 1];

	if (!line)
		return -1;
	if (save && (is_newline(save, line) == 1))
		return 1;
	while ((ret = read(0, buf, buf_size)) > 0)
	{
		buf[buf_size] = 0;
		save = ft_strjoindel(save, buf);
		
	}

}