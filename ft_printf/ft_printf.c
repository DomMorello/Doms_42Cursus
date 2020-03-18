#include "ft_printf.h"
#include <string.h>

void	data_init(t_data *data)
{
	data->flag[MINUS] = 0;
	data->flag[ZERO] = 0;
	data->precision = -1;
	data->type = '\0';
	data->width = 0;
	data->i = 0;
	data->len = 0;
}

int is_flag(char c)
{
	if (c == '-' || c == '0')
		return (1);
	return (0);
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
			data->flag[MINUS] = 1;
		if (*(data->copy) == '0')
			data->flag[ZERO] = 1;
		(data->copy)++;
		(data->i)++;
	}
	// printf("i: %d\n", data->i);
}

// void	parse_width(t_data *data)
// {
// 	while (*(data->copy) && is_digit(*(data->copy)))
// 	{
		
// 		(data->copy)++;
// 	}
// }

void	input_data(t_data *data)
{
	parse_flag(data);
	data->copy += data->i;
	// parse_width(data);
	// parse_precision(data);
	// parse_type(data);
}	

void	parse_data(t_data *data)
{
	while (*(data->copy))
	{
		if (*(data->copy) == '%')
		{
			(data->copy)++;
			input_data(data);
		}
		else
		{
			write(1, &*(data->copy), 1);
			(data->copy)++;
		}
	}
}

int		ft_printf(const char *format, ...)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		return (-1);
	data_init(data);
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
	ft_printf("hello %----d hello22222 %d\n", 34, 3);
	return 0;
}