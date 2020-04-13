/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:36:50 by donglee           #+#    #+#             */
/*   Updated: 2020/04/13 22:00:46 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			exception_data(t_data *data, const char *format)
{
	if (exception_all((char *)format) == ERROR)
		return (ERROR);
	if (data->type == 'c' || data->type == 'p')
	{
		if (data->flag[ZERO] == TRUE || data->precision != -1)
			return (ERROR);
	}
	if (data->type == 's')
	{
		if (data->flag[ZERO] == TRUE)
			return (ERROR);
	}
	if (data->type == 'd' || data->type == 'i' || data->type == 'u'
		|| data->type == 'x' || data->type == 'X')
	{
		if (data->flag[MINUS] == TRUE && data->flag[ZERO] == TRUE)
			data->flag[ZERO] = FALSE;
	}
	return (TRUE);
}
