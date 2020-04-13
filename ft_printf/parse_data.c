/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:40:15 by donglee           #+#    #+#             */
/*   Updated: 2020/04/13 21:56:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_data(t_data *data)
{
	if (data->type == 'c')
	{
		if (print_c(data) == ERROR)
			return (ERROR);
	}
	if (data->type == 's')
		print_s(data);
	if (data->type == 'p')
	{
		if (print_p(data) == ERROR)
			return (ERROR);
	}
	if (data->type == 'd' || data->type == 'i')
		print_di(data);
	if (data->type == 'u')
		print_u(data);
	if (data->type == 'x' || data->type == 'X')
	{
		if (print_x(data) == ERROR)
			return (ERROR);
	}
	if (data->type == '%')
		print_per(data);
	return (TRUE);
}

int			modify_ds_data(t_data *data, char *cpy)
{
	char *check;
	int i;

	i = 0;
	if ((check = (char *)malloc(sizeof(char) * (data->i) + 2)) == NULL)
		return (FALSE);
	ft_strlcpy(check, cpy, (data->i + 2));
	while (check[i])
	{
		if (check[i] == '.')
		{
			i++;
			if (is_type(check[i]))
				data->precision = 0;
			if (data->type == 's' && data->flag[ZERO] == TRUE && data->precision < 0)
				break ;
			if (data->type != 's' && data->precision < 0)
				break ;
			data->flag[ZERO] = FALSE;
		}
		i++;
	}
	free(check);
	return (TRUE);
}

int			modify_data(t_data *data, char *cpy)
{
	if (data->type == 'd' || data->type == 's' || data->type == 'u'
		|| data->type == 'x' || data->type == 'X' || data->type == 'i')
	{
		if (!modify_ds_data(data, cpy))
			return (FALSE);
	}
	if (data->type == '%')
	{
		data->precision = -1;
		if (data->flag[MINUS] == TRUE && data->flag[ZERO] == TRUE)
			data->flag[ZERO] = FALSE;
	}
	if (data->type == 'p')
		if (!modify_p_data(data, cpy))
			return (FALSE);
	return (TRUE);
}

int	move_to_print(t_data *data)
{
	char *cpy;

	while (*(data->print))
	{
		if (*(data->print) == '%')
		{
			cpy = data->print;
			data_init(data);
			data->print++;
			input_data(data, &data->print, &data->ap_copy);
			if (!modify_data(data, cpy))
				return (ERROR);
			if (print_data(data) == ERROR)
				return (ERROR);
		}
		else
		{
			write(1, &*data->print, 1);
			data->print++;
			data->len++;
		}
	}
	return (TRUE);
}

int	parse_data(t_data *data, const char *format)
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
		}
		else
			data->copy++;
	}
	if (move_to_print(data) == ERROR)
		return (ERROR);
	return (TRUE);
}
