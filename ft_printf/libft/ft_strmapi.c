#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;
	int				len;

	if (s && f)
	{
		i = 0;
		len = ft_strlen(s);
		if ((result = (char *)malloc(sizeof(char) * len + 1)) == 0)
			return (NULL);
		while (s[i])
		{
			result[i] = f(i, s[i]);
			i++;
		}
		result[i] = 0;
		return (result);
	}
	return (NULL);
}
