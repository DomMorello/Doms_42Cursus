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

void	input_width(t_data *data, char **ptr)
{
	int tmp;

	tmp = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		if (**ptr == '*')
		{
			tmp = va_arg(data->ap, int);
			printf("tmp %d\n", tmp);
			/* 버그를 찾았다. 여기서 va_arg를 한 번 불렀으니 두 번 반복하니까 다음으로 넘어가버리는 것이다. ㅈ됐다. ㅅㅂ */
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

void	input_precision(t_data *data, char **ptr)
{
	int tmp;

	tmp = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		if (**ptr == '*')
			tmp = va_arg(data->ap, int);
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

void	input_data(t_data *data, char **ptr)
{
	input_flag(data, ptr);
	input_width(data, ptr);
	if (**ptr == '.')
	{
		(*ptr)++;
		input_precision(data, ptr);
	}
	input_type(data, ptr);
}

void	get_len(t_data *data)
{
	if (data->width == 0)
		data->len += 1;
	if (data->width > 0)
		data->len += data->width;
}

/* 프린트 하는 과정은 똑같은 구조로 데이터를 다 넣고 예외를 처리한 이후에 예외가 없으면 진행 */
// void	print_c(t_data *data, char ret)
// {
// 	if (data->flag[MINUS] == TRUE)
// 	{
// 		write(1, &ret, 1);
// 		while((((data->width)--) - 1) > 0)
// 			write(1, " ", 1);
// 	}
// 	else
// 	{
// 		while ((((data->width)--) - 1) > 0)
// 			write(1, " ", 1);
// 		write(1, &ret, 1);
// 	}
// }

int		exception_c(t_data *data, const char *format)
{
	char ret;
	int idx;

	idx = 0;
	get_len(data);
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

	/* 프린트하는 부분은 같은 구조로 데이터 다 넣고 난 이후에 에러검사 이후에 실시할 예정 */
	// while (*(data->print))
	// {
	// 	if (*(data->print) == '%'정
	// 	{
	// 		ret = va_arg(data->ap, int);
	// 		print_c(data, ret);
	// 		data->print += data->i;
	// 		break ;
	// 	}
	// 	else
	// 	{
	// 		write(1, &*(data->print), 1);
	// 		data->print++;
	// 	}
	// }

int		exception_data(t_data *data, const char *format)
{
	if (data->type == 'c')
		return (exception_c(data, format));
	// if (data->type == 's')
	// 	return (process_s(data));
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

void	print_c(t_data *data, char ret)
{
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

void	print_data(t_data *data, char ret)
{
	if (data->type == 'c')
		print_c(data, ret);
	// if (data->type == 's')
	// 	print_s(data);
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

void	move_to_print(t_data *data)
{
	char ret;

	ret = '\0';
	while (*(data->print))
	{
		if (*(data->print) == '%')
		{
			ret = va_arg(data->ap, int);
			data_init(data);
			data->print++;
			input_data(data, &data->print);
			// printf("type: %c\n", data->type);
			// printf("width: %d\n", data->width);
			print_data(data, ret);
		}
		else
		{
			write(1, &*data->print, 1);
			data->print++;
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
			input_data(data, &data->copy);
			if (exception_data(data, format) == ERROR)
				return (ERROR);
			// printf("flag minus %d\n", data->flag[MINUS]);
			// printf("flag zero %d\n", data->flag[ZERO]);
			// printf("flag width %d\n", data->width);
		}
		else
		{
			data->copy++;
			data->len++;
		}
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
		parse_data(data, format);
		va_end(data->ap);
	}
	free(data);
	return (data->len);
}

int main()
{
	int a = ft_printf("ftt %-*.chello%1c\n", 5, 'a', 'b');
	// int b = printf("lib %-*.chello%-01c\n", 5, 'a', 'b');
	// printf("ft: %d\n", a);
	// printf("lib: %d\n", b);
	return 0;
}