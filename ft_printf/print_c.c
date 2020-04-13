/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:41:12 by donglee           #+#    #+#             */
/*   Updated: 2020/04/13 21:57:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_c(t_data *data)
{
	unsigned char ret;

	if ((ret = va_arg(data->ap_copy, int)) < 0)
		return (ERROR);
	if (data->flag[MINUS] == TRUE)
	{
		write(1, &ret, 1);
		data->len++;
		while((((data->width)--) - 1) > 0)
		{
			write(1, " ", 1);
			data->len++;
		}
	}
	else
	{
		while ((((data->width)--) - 1) > 0)
		{
			write(1, " ", 1);
			data->len++;
		}
		write(1, &ret, 1);
		data->len++;
	}
	return (TRUE);
}
