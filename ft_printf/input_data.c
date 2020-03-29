#include "ft_printf.h"

void		input_flag(t_data *data, char **ptr)
{
	while ((**ptr) && is_flag((**ptr)))
	{
		if (**ptr == '-')
			data->flag[MINUS] = TRUE;
		if (**ptr == '0')
			data->flag[ZERO] = TRUE;
		(*ptr)++;
		data->i++;
	}
}

void		input_width(t_data *data, char **ptr, va_list *list)
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
		data->i++;
	}
	data->width = tmp;
}

void		input_precision(t_data *data, char **ptr, va_list *list)
{
	int tmp;
	int flag;

	tmp = 0;
	flag = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		flag = 1;
		if (**ptr == '*')
			tmp = va_arg(*list, int);
		else
			tmp = **ptr - '0' + (tmp * 10);
		(*ptr)++;
		data->i++;
	}
	if (flag == 1)
		data->precision = tmp;
}

void		input_type(t_data *data, char **ptr)
{
	if (is_type(**ptr))
		data->type = **ptr;
	(*ptr)++;
	data->i++;
}

void		input_data(t_data *data, char **ptr, va_list *list)
{
	input_flag(data, ptr);
	input_width(data, ptr, list);
	if (**ptr == '.')
	{
		(*ptr)++;
		data->i++;
		input_precision(data, ptr, list);
	}
	input_type(data, ptr);
}
