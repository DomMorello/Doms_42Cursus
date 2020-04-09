/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:37:16 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 21:37:30 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
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
