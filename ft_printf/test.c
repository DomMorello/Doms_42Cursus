#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

int main()
{
	printf("%.s %.1d\n", "abc", 0);
	return 0;
}