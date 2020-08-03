#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

int main(void)
{
    //int fd = 0;

    //if ((fd = open("./test.txt", O_RDWR)) < 0)
    //{    
    //    printf("error!!! errno: %d\n", errno);
    //    return 0;
    // }
    //int ret = 0;
    //if ((ret = ft_write(fd, "what!", 5)) == -1)
    //{
    //    printf("write error errno: %d\n", errno);
    //    return 0;
    //}
    //close(fd);
	int ret = write(1, "hello", 123456789);
	printf("ret sys:%d\n", ret);
	int ret2 = ft_write(1, "hello", 123456789);
	printf("ret ft:%d\n", ret2);
	return 0;
}
