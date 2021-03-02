#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char *ft_strchr(char *s, int c)
{
	if (s == NULL)
		return (0);
	while(*s != c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return (s);
}

char *ft_strdup(char *s)
{
	int i;
	char *ptr;

	if (!(ptr = malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	i = 0;
	while(*s)
		ptr[i++] = *s++;
	ptr[i] = '\0';
	return(ptr);
}

char *ft_substr(char *s, unsigned start, int len)
{
	int i;
	char *ptr;

	if (!(ptr = malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while(i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return(ptr);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i;
	char *ptr;

	if(!(ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	i = 0;
	while (*s1)
		ptr[i++] = *s1++;
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

char ft_puts(char *s)
{
	write(1, s, ft_strlen(s));
}
/*
int get_next_line(char **line)
{
	char *tp;
	int nread;
	char buf[1024];
	static char *str;
	char *temp;

	nread = 1;
	while(((tp = ft_strchr(str, '\n')) == NULL) && nread != 0)
	{
		if ((nread = read(0, buf, 1024)) == -1)
			return (-1);
		buf[nread] = '\0';
		(str == NULL)? (temp = ft_strdup(buf)) : (temp = ft_strjoin(str, buf));
		if (str != NULL)
			free(str);
		str = temp;
	}
	if(tp != NULL)
	{
		temp = str;
		*line = ft_substr(str, 0, tp - str);
		str = ft_strdup(tp + 1);
		free(temp);
		return (1);
	}
	*line = str;
	str = NULL;
	return (0);
}
*/
int get_next_line(int fd, char **line)
{
	char *tp;
	int nread;
	char buf[6];
	static char *str;
	char *temp;

	nread = 1;
	while(((tp = ft_strchr(str, '\n')) == NULL) && nread != 0)
	{
		ft_puts("111");
		if ((nread = read(fd, buf, 5)) == -1)
			return (-1);
		buf[nread] = '\0';
		(str == NULL)? (temp = ft_strdup(buf)) : (temp = ft_strjoin(str, buf));
		ft_puts("temp is");
		ft_puts(temp);
		if (str != NULL)
			free(str);
		str = temp;
		ft_puts("****no new line*****\n");
		ft_puts(str);
		ft_puts("\n");
	}
	if(tp != NULL)
	{
		ft_puts("222");
		temp = str;
		*line = ft_substr(str, 0, tp - str);
		str = ft_strdup(tp + 1);
		ft_puts("****new line*****\n");
		ft_puts(str);
		free(temp);
		return (1);
	}
	*line = str;
	str = NULL;
	return (0);
}
