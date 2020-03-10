#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
	char *result;
	size_t i;
	
	result = (char *)s;
	i = 0;
	while (result[i])
		i++;
	while (result[i] != c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (&result[i]);
}
