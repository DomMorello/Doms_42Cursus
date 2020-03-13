#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *result;
	unsigned int i;
	unsigned int str_len;

	str_len = ft_strlen(s);
	i = 0;
	if ((result = (char *)malloc(sizeof(char) * len + 1)) == 0)
		return (NULL);
	while (i < len && start < str_len)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = 0;
	return (result);
}
