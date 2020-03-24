#include "ft_printf.h"
#include <string.h>

void	data_init(t_data *data)
{
	data->flag[MINUS] = FALSE;
	data->flag[ZERO] = FALSE;
	data->precision = -1;
	data->type = '\0';
	data->width = 0;
	data->i = 0;
}

int		is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' ||
		c == 'd' || c == 'i' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%')
		return (TRUE);
	return (FALSE);
}

int is_flag(char c)
{
	if (c == '-' || c == '0')
		return (TRUE);
	return (FALSE);
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		is_valid(char c)
{
	if (ft_isdigit(c) || is_flag(c) || c == '.' || c == '*')
		return (TRUE);
	return (FALSE);
}

size_t ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	input_flag(t_data *data, char **ptr)
{
	while ((**ptr) && is_flag((**ptr)))
	{
		if (**ptr == '-')
			data->flag[MINUS] = TRUE;
		if (**ptr == '0')
			data->flag[ZERO] = TRUE;
		(*ptr)++;
	}
}

void	input_width(t_data *data, char **ptr, va_list *list)
{
	int tmp;

	tmp = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		if (**ptr == '*')
		{
			tmp = va_arg(*list, int);
			if (tmp < 0)
			{
				data->flag[MINUS] = TRUE;
				tmp *= (-1);
			}
		}
		else
			tmp = **ptr - '0' + (tmp * 10);
		(*ptr)++;
	}
	data->width = tmp;
}

void	input_precision(t_data *data, char **ptr, va_list *list)
{
	int tmp;

	tmp = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		if (**ptr == '*')
			tmp = va_arg(*list, int);
		else
			tmp = **ptr - '0' + (tmp * 10);
		(*ptr)++;
	}
	data->precision = tmp;
}


void	input_type(t_data *data, char **ptr)
{
	if (is_type(**ptr))
		data->type = **ptr;
	(*ptr)++;
}

void	get_c_len(t_data *data)
{
	if (data->width == 0)
		data->len += 1;
	if (data->width > 0)
		data->len += data->width;
}

void	input_data(t_data *data, char **ptr, va_list *list)
{
	input_flag(data, ptr);
	input_width(data, ptr, list);
	if (**ptr == '.')
	{
		(*ptr)++;
		input_precision(data, ptr, list);
	}
	input_type(data, ptr);
}

int		exception_c(t_data *data, const char *format)
{
	if (data->flag[ZERO] == TRUE)
		return (ERROR);	
	while (*format)
	{
		if (*format == '.')
		{
			format++;
			if (ft_isdigit(*format))
				return (ERROR);
		}
		format++;
	}
	return (TRUE);
}

int		handle_exception1(char **format)
{
	while (!is_type(**format))
	{
		if (!is_valid(**format))
			return (ERROR);
		while (is_flag(**format))
			(*format)++;
		if (is_type(**format))
			break ;
		if (!is_valid(**format))
			return (ERROR);
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			if (ft_isdigit(**format) || !is_valid(**format))
				return (ERROR);
		}
		while (ft_isdigit(**format))
			(*format)++;
		break ;
	}
	return (TRUE);
}

int		handle_exception2(char **format)
{
	while (!is_type(**format))
	{
		if (is_flag(**format))
			return (ERROR);
		if (is_type(**format))
			break ;
		if (**format == '*' || !is_valid(**format))
			return (ERROR);		
		if (**format == '.')
			(*format)++;
		if (is_type(**format))
			break ;
		break ;
	}
	return (TRUE);
}

int 	handle_exception3(char **format)
{
	while (!is_type(**format))
	{
		if (**format == '.' || !is_valid(**format) || **format == '-')
			return (ERROR);
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			else
				return (ERROR);
		}
		else
		{
			while (ft_isdigit(**format))
				(*format)++;
			if (**format == '*' || is_flag(**format) || **format == '.')
				return (ERROR);
		}
		break ;
	}
	return (TRUE);
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
	return (TRUE);
}

int 	exception_all(char *format)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (handle_exception1(&format) == ERROR)
				return (ERROR);
			if (handle_exception2(&format) == ERROR)
				return (ERROR);
			if (handle_exception3(&format) == ERROR)
				return (ERROR);
			if (handle_exception4(&format) == ERROR)
				return (ERROR);
		}
		format++;
	}	
	return (TRUE);
}

int		exception_data(t_data *data, const char *format)
{
	if (exception_all((char *)format) == ERROR)
		return (ERROR);
	if (data->type == 'c')
		return (exception_c(data, format));
	if (data->type == 's')
	{
		if (data->flag[ZERO] == TRUE)
			return (ERROR);
	}
	// if (data->type == 'p')
	// 	return (process_p(data));
	// if (data->type == 'd' || data->type == 'i')
	// 	return (process_di(data));
	// if (data->type == 'u')
	// 	return (process_u(data));
	// if (data->type == 'x')
	// 	return (process_x(data));
	// if (data->type == 'X')
	// 	return (process_X(data));
	// if (data->type == '%')
	// 	return (process_perc(data));
	return (TRUE);
}

void	print_c(t_data *data)
{
	char ret;

	ret = '\0';
	ret = va_arg(data->ap_copy, int);
	if (data->flag[MINUS] == TRUE)
	{
		write(1, &ret, 1);
		while((((data->width)--) - 1) > 0)
			write(1, " ", 1);
	}
	else
	{
		while ((((data->width)--) - 1) > 0)
			write(1, " ", 1);
		write(1, &ret, 1);
	}
}

void 	print_from_head(t_data *data, char *s, int gap)
{
	while (data->precision--)
	{
		write(1, &*s, 1);
		data->len++;
		s++;
	}
	while (gap--)
	{
		write(1, " ", 1);	
		data->len++;
	}
}

void	print_from_tail(t_data *data, char *s, int gap)
{
	while (gap--)
	{
		write(1, " ", 1);
		data->len++;
	}
	while (data->precision--)
	{		
		write(1, &*s, 1);
		data->len++;
		s++;
	}
}

void	print_s(t_data *data)
{
	char *s;
	int gap;

	s = va_arg(data->ap_copy, char *);
	if ((int)ft_strlen(s) < data->precision || data->precision == -1)
		data->precision = ft_strlen(s);
	if (data->precision < data->width)
	{
		gap = data->width - data->precision;
		if (data->flag[MINUS] == TRUE)
			print_from_head(data, s, gap);
		else
			print_from_tail(data, s, gap);
	}
}
void	print_data(t_data *data)
{
	if (data->type == 'c')
		print_c(data);
	if (data->type == 's')
		print_s(data);
	// if (data->type == 'p')
	// 	print_p(data);
	// if (data->type == 'd' || data->type == 'i')
	// 	print_di(data);
	// if (data->type == 'u')
	// 	print_u(data);
	// if (data->type == 'x')
	// 	print_x(data);
	// if (data->type == 'X')
	// 	print_X(data);
	// if (data->type == '%')
	// 	print_perc(data);	
}

void	get_return_val(t_data *data)
{
	if (data->type == 'c')
		get_c_len(data);
	// if (data->type == 'p')
	// 	get_p_len(data);
	// if (data->type == 'd' || data->type == 'i')
	// 	get_d_len(data);
	// if (data->type == 'u')
	// 	get_u_len(data);
	// if (data->type == 'x' || data->type == 'X')
	// 	get_x_len(data);
	// if (data->type == '%')
	// 	get_per_len(data);
}

void	move_to_print(t_data *data)
{
	while (*(data->print))
	{
		if (*(data->print) == '%')
		{
			data_init(data);
			data->print++;
			input_data(data, &data->print, &data->ap_copy);
			get_return_val(data);
			print_data(data);
		}
		else
		{
			write(1, &*data->print, 1);
			data->print++;
			data->len++;
		}
	}
}

int		parse_data(t_data *data, const char *format)
{
	while (*(data->copy))
	{
		if (*(data->copy) == '%')
		{
			data_init(data);
			data->copy++;
			input_data(data, &data->copy, &data->ap);
			if (exception_data(data, format) == ERROR)
				return (ERROR);
			// printf("width: %d\n", data->width);
			// printf("precision: %d\n", data->precision);
			// printf("flag minus: %d\n", data->flag[MINUS]);
			// printf("flag zero: %d\n", data->flag[ZERO]);
			// printf("flag type: %c\n", data->type);
		}
		else
			data->copy++;
	}
	move_to_print(data);
	return (TRUE);
}

int		ft_printf(const char *format, ...)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		return (ERROR);
	data_init(data);
	data->len = 0;
	if (format)
	{
		data->copy = (char *)format;
		data->print = (char *)format;
		va_start(data->ap, format);
		va_copy(data->ap_copy, data->ap);
		if (parse_data(data, format) == ERROR)
		{
			free(data);
			return (ERROR);
		}
		va_end(data->ap);
		va_end(data->ap_copy);
	}
	free(data);
	return (data->len);
}

int main()
{
	char *s1 = "abcde";
	char *s2 = "12345";
	int a = ft_printf("hello %*s world %5.c wow\n", 10, s1, 'b');
	int b = printf("hello %*s world %5.c wow\n", 10, s1, 'b');
	printf("ft: %d lib: %d\n", a, b);
	
	return 0;
}