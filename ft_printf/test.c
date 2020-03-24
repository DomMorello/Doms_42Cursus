#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int is_flag(char c)
{
	if (c == '-' || c == '0')
		return 1;
	return 0;
}

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int is_valid(char c)
{
	if (is_flag(c) || ft_isdigit(c) || c == '*' || c == '.')
		return 1;
	return 0;
}

int		is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' ||
		c == 'd' || c == 'i' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

// int		exception_all1(char **format)
// {
// 	while (**format)
// 	{
// 		if (**format == '%')
// 		{
// 			(*format)++;
// 			while (!is_type(**format))
// 			{
// 				if (!is_valid(**format))
// 					return 0;
// 				while (is_flag(**format))
// 					(*format)++;
// 				if (is_type(**format))
// 					break ;
// 				if (!is_valid(**format))
// 					return 0;
// 				if (**format == '*')
// 				{
// 					(*format)++;
// 					if (is_type(**format))
// 						break ;
// 					if (ft_isdigit(**format) || !is_valid(**format))
// 						return 0;
// 				}
// 				while (ft_isdigit(**format))
// 					(*format)++;
// 				if (is_flag(**format))
// 					return (0);
// 				if (is_type(**format))
// 					break ;
// 				if (**format == '*' || !is_valid(**format))
// 					return 0;
// 				if (**format == '.')
// 				{
// 					(*format)++;
// 					if (is_type(**format))
// 						break ;
// 					if (**format == '.' || !is_valid(**format) || **format == '-')
// 						return 0;
// 					if (**format == '*')
// 					{
// 						(*format)++;
// 						if (is_type(**format))
// 							break ;
// 						if (ft_isdigit(**format) || !is_valid(**format) || **format == '*')
// 							return 0;
// 					}
// 					else
// 					{
// 						while (ft_isdigit(**format))
// 							(*format)++;
// 						if (**format == '*' || is_flag(**format) || **format == '.')
// 							return (0);
// 					}
// 				}
// 				while (ft_isdigit(**format))
// 					(*format)++;
// 				if (is_type(**format))
// 					break ;
// 			}
// 		}
// 		(*format)++;
// 	}
// 	return 1;
// }

// int exception_all(char *format)
// {
// 	if (!exception_all1(&format))
// 		return (-1);
// 	return (1);
// }

int		handle_exception1(char **format)
{
	while (!is_type(**format))
	{
		if (!is_valid(**format))
			return 0;
		while (is_flag(**format))
			(*format)++;
		if (is_type(**format))
			break ;
		if (!is_valid(**format))
			return 0;
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			if (ft_isdigit(**format) || !is_valid(**format))
				return 0;
		}
		while (ft_isdigit(**format))
			(*format)++;
		break ;
	}
	return (1);
}

int		handle_exception2(char **format)
{
	while (!is_type(**format))
	{
		if (is_flag(**format))
			return (0);
		if (is_type(**format))
			break ;
		if (**format == '*' || !is_valid(**format))
			return 0;		
		if (**format == '.')
			(*format)++;
		if (is_type(**format))
			break ;
		break ;
	}
	return (1);
}

int handle_exception3(char **format)
{
	while (!is_type(**format))
	{
		if (**format == '.' || !is_valid(**format) || **format == '-')
			return 0;
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			else
				return (0);
		}
		else
		{
			while (ft_isdigit(**format))
				(*format)++;
			if (**format == '*' || is_flag(**format) || **format == '.')
				return (0);
		}
		break ;
	}
	return (1);
}

int		handle_exception4(char **format)
{
	while (!is_type(**format))
	{
		while (ft_isdigit(**format))
			(*format)++;
		if (is_type(**format))
			break ; 
		break ;
	}
	return (1);
}

int exception_all(char *format)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!handle_exception1(&format))
				return (-1);
			if (!handle_exception2(&format))
				return (-1);
			if (!handle_exception3(&format))
				return (-1);
			if (!handle_exception4(&format))
				return (-1);
		}
		format++;
	}	
	return (1);
}

int main()
{
	int a = exception_all("#@$*!(@#$)!#$*!)#$*!@#*$fasdfajhsdgfhagdkjfg%----7.*c");
	printf("%d\n", a);

	return 0;
}