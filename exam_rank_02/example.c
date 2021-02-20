#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_strndup(char *s, int n)
{
	int	i;
	char	*ret;

	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (s[i] && i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;
	char	*ret;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
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
	ret[i] = '\0';
	return (ret);
}

int	get_next_line(char **line)
{
	static char 	*save;
	char 		buff[2];
	ssize_t		bytes;
	char		*tmp;
	char		*n_ptr;

	if (!save)
	{
		save = ft_strndup("", 0);
		while ((bytes = read(0, buff, 1) > 0))
		{
			buff[bytes] = '\0';
			tmp = save;
			save = ft_strjoin(save, buff);
			free(tmp);
		}
	}
	n_ptr = ft_strchr(save, '\n');
	if (n_ptr)
	{
		*line = ft_strndup(save, n_ptr - save);
		save += n_ptr - save + 1;
		return (1);
	}
	else 
	{
		*line = ft_strndup(save, ft_strchr(save, '\0') - save);
		return (0);
	}
}		

int main(void)
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
}