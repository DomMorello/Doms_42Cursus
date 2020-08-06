#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

// ssize_t ft_write(int fd, const void *buf, size_t count);
// size_t ft_strlen(const char *s);
// char *ft_strcpy(char *dest, const char *src);
//int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_read(int fd, void *buf, size_t count);

int main(void)
{
	int fd = 0;
    if ((fd = open("./test.txt", O_RDONLY)) == -1)
    {
        printf("open error! %d\n", errno);
        close(fd);
        return 0;
    }

    char buf[10] = {0,};
    int ret = 1;

    while ((ret = read(fd, buf, sizeof(buf))) > 0)
    {
        if (errno > 0)
            printf("error! %d\n", errno);
        printf("%s\n", buf);
    }
    close(fd);
	return 0;
}
