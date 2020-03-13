#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s1_str;
	unsigned char *s2_str;
	size_t i;

	s1_str = (unsigned char *)s1;
	s2_str = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*s1_str++ != *s2_str++) 
			return ((*(s1_str - 1)) > (*(s2_str - 1)) ? 1 : -1);
		i++;
	}
	return (0);
}
