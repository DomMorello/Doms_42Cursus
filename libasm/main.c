#include <stdio.h>
#include <unistd.h>

// ssize_t ft_write(int fd, const void *buf, size_t count);

int main(void)
{
    write(1, "hello", 5);
	return 0;
}
