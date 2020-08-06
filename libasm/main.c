#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

// ssize_t ft_write(int fd, const void *buf, size_t count);
// size_t ft_strlen(const char *s);
// char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);

int main(void)
{
	char *s1 = "";
	char *s2 = "";
	int ret = ft_strcmp(s1, s2);
	printf("%d\n", ret);
	return 0;
}

// int		ft_strcmp(char *s1, char *s2)
// {
// 	int i;

// 	i = 0;
// 	while (s1[i] != '\0' && s2[i] != '\0')
// 	{
// 		if (s1[i] == s2[i])
// 			i++;
// 		if (s1[i] < s2[i] || s1[i] > s2[i])
// 			return (s1[i] - s2[i]);
// 	}
// 	return (0);
// }
