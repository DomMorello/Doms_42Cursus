#include "libft.h"

void *ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dst_string;
	unsigned char *src_string;

	dst_string = (unsigned char *)dst;
	src_string = (unsigned char *)src;
	while (n--)
	{
		*dst_string = *src_string;
		if (*src_string == (unsigned char)c)
			return ((void *)dst_string + 1);
		dst_string++;
		src_string++;
	}
	return (NULL);
}
