#include "libft.h"

void *ft_memset(void *b, int c, size_t len)
{
	unsigned char *string;

	string = (unsigned char *)b;
	while (len--)
		*(string++) = (unsigned char)c;
	return (b);
}
