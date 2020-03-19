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
	// data->len = 0;
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

void	parse_flag(t_data *data)
{
	while (*(data->copy) && is_flag(*(data->copy)))
	{
		if (*(data->copy) == '-')
			data->flag[MINUS] = TRUE;
		if (*(data->copy) == '0')
			data->flag[ZERO] = TRUE;
		(data->copy)++;
	}
}

void	parse_width(t_data *data)
{
	int tmp;

	tmp = 0;
	while (*(data->copy) && (ft_isdigit(*(data->copy)) || *(data->copy) == '*'))
	{
		if (*(data->copy) == '*')
		{
			tmp = va_arg(data->ap, int);
			if (tmp < 0)
			{
				data->flag[MINUS] = TRUE;
				tmp *= (-1);
			}
		}
		else
			tmp = *(data->copy) - '0' + (tmp * 10);
		(data->copy)++;
	}
	data->width = tmp;
}

void	parse_precision(t_data *data)
{
	int tmp;

	tmp = 0;
	while (*(data->copy) && (ft_isdigit(*(data->copy)) || *(data->copy) == '*'))
	{
		if (*(data->copy) == '*')
			tmp = va_arg(data->ap, int);
		else
			tmp = *(data->copy) - '0' + (tmp * 10);
		(data->copy)++;
	}
	data->precision = tmp;
}

int		is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' ||
		c == 'd' || c == 'i' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%')
		return (TRUE);
	return (FALSE);
}

void	parse_type(t_data *data)
{
	if (is_type(*(data->copy)))
		data->type = *(data->copy);
	data->copy++;
}
void	input_data(t_data *data)
{
	parse_flag(data);
	parse_width(data);
	if (*(data->copy) == '.')
	{
		data->copy++;
		parse_precision(data);
	}
	parse_type(data);
}

void	get_len(t_data *data)
{
	if (data->width == 0)
		data->len += 1;
	if (data->width > 0)
		data->len += data->width;
}

int		process_c(t_data *data)
{
	char ret;

	get_len(data);
	if (data->flag[ZERO] == TRUE)
		return (ERROR);
	printf("pre: %d\n", data->precision);
	if (data->precision >= 0)
		return (ERROR);
	ret = va_arg(data->ap, int);
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
	return (TRUE);
}

int		process_data(t_data *data)
{
	if (data->type == 'c')
		return (process_c(data));
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

int		parse_data(t_data *data)
{
	while (*(data->copy))
	{
		if (*(data->copy) == '%')
		{
			data_init(data);
			(data->copy)++;
			input_data(data);
			// printf("flag minus %d\n", data->flag[MINUS]);
			// printf("flag zero %d\n", data->flag[ZERO]);
			// printf("width %d\n", data->width);
			// printf("precision %d\n", data->precision);
			// printf("type %c\n", data->type);

			if (process_data(data) == ERROR)
				return (ERROR);
		}
		else
		{
			write(1, &*(data->copy), 1);
			(data->len)++;
			(data->copy)++;
		}
	}
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
		va_start(data->ap, format);
		parse_data(data);
		va_end(data->ap);
	}
	free(data);
	return (data->len);
}

int main()
{
	int a = ft_printf("ftt %-*.chello%1cwow\n", 0, 'a', 'b');
	int b = printf("lib %-*.chello%1cwow\n", 0, 'a', 'b');
	printf("ft: %d\n", a);
	printf("lib: %d\n", b);
	return 0;
}