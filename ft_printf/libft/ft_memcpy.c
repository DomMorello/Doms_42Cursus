#include "libft.h"

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *dst_string;
	const unsigned char *src_string;

	src_string = src;
	dst_string = dst;
	while (n--)
		*(dst_string++) = *(src_string++);
	return (dst);
}
