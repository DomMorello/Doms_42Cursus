#include "get_next_line.h"


size_t ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char *ft_strchr(const char *s, int c)
{
	char *result;

	result = (char *)s;
	while (*result != c)
	{
		if (!*result)
			return (NULL);
		result++;
	}
	return (result);
}

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

char *ft_strdup(const char *s1)
{
	char *result;
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(s1);
	if ((result = (char *)malloc(sizeof(char) * len + 1)) == 0)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

void				ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}
