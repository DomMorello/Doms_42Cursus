#include "ft_printf.h"

int			is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' ||
		c == 'd' || c == 'i' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%')
		return (TRUE);
	return (FALSE);
}

int 		is_flag(char c)
{
	if (c == '-' || c == '0')
		return (TRUE);
	return (FALSE);
}

int			is_valid(char c)
{
	if (ft_isdigit(c) || is_flag(c) || c == '.' || c == '*')
		return (TRUE);
	return (FALSE);
}
