#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

//ssize_t ft_write(int fd, const void *buf, size_t count);
size_t ft_strlen(const char *s);

int main(void)
{
	char *s = "faskjdhflahsdflahdslfjhasjkdfbahsbfhlesbasdjklbfasefluiabsldjfbalshjkdbf";
	printf("%lu\n", ft_strlen(s));
	printf("%lu\n", strlen(s));
	//int ret = ft_write(1, "hello", 5);
	//printf("ret:%d\n", ret);
	
	return 0;
}
