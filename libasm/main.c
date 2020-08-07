#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

ssize_t ft_write(int fd, const void *buf, size_t count);
size_t ft_strlen(const char *s);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);

int main(void)
{
    char *s = "hello";
    char *r = strdup(s);
    printf("%s\n", r);
    r[7] = 'g';
    printf("%s\n", r);

    char *s1 = "hello";
    char *r1 = ft_strdup(s1);
    printf("%s\n", r1);
    r[7] = 'g';
    printf("%s\n", r1);
    return 0;
}
