#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

// ssize_t ft_write(int fd, const void *buf, size_t count);
// size_t ft_strlen(const char *s);
// char *ft_strcpy(char *dest, const char *src);
// int ft_strcmp(const char *s1, const char *s2);
// ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);
char	*test(void);

int main(void)
{
//	 char *str = "hello world";
//	 char *ret = strdup(str);
//	 printf("lib %s\n", ret);
//
//	 ret[3] = 'a';
//	 printf("lib %s\n", ret);
//
//	 char *s1 = "hello world";
//	 char *r = ft_strdup(s1);
//	 printf("ft %s\n", r);
//
//	 r[3] = 'a';
//	 printf("ft %s\n", r);
	char *s = test();
	printf("%s\n", s);
	return 0;
}
