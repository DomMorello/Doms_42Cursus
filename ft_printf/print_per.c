/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_per.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:45:26 by donglee           #+#    #+#             */
/*   Updated: 2020/04/13 16:40:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_per_head(t_data *data)
{
	write(1, "%", 1);
	data->len++;
	while ((((data->width)--) - 1) > 0)
	{
		write(1, " ", 1);
		data->len++;
	}
}

void	print_per(t_data *data)
{
	if (data->flag[MINUS] == TRUE)
		print_per_head(data);
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, 1, NULL);
		else
		{
			while ((((data->width)--) - 1) > 0)
			{
				write(1, " ", 1);
				data->len++;
			}
		}
		write(1, "%", 1);
		data->len++;
	}
}
