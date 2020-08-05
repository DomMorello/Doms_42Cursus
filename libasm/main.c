#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

//ssize_t ft_write(int fd, const void *buf, size_t count);
// size_t ft_strlen(const char *s);
char *ft_strcpy(char *dest, const char *src);

int main(void)
{
	char *s = "adfadfadfafds!!";
	char d[6] = "world";
	ft_strcpy(d, s);
	printf("%s\n", d);
	return 0;
}
