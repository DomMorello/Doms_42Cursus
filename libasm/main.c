#include <stdio.h>
#include <unistd.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

int main(void)
{
	int a = ft_write(1, "hello", 5);
	printf("ret:%d\n", a);
	printf("hello!!!!\n");
	// int a = write(1, "hello", 24664);
	// printf("ret:%d\n", a);
	return 0;
}
