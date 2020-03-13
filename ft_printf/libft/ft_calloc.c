#include "libft.h"

void *ft_calloc(size_t count, size_t size)
{
	char *result;

	if ((result = (char *)malloc(count * size)) == 0)
		return (NULL);
	ft_bzero(result, count * size);
	return ((void *)result);
}
