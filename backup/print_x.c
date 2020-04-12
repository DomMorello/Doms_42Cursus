/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:48:50 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 21:49:27 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printx_body(t_data *data, unsigned int ret, char *convert, int len)
{
	int gap;

	if (data->precision > len)
	{
		gap = data->precision - len;
		while (gap--)
		{
			write(1, "0", 1);
			data->len++;
		}
	}
	if (ret != 0 || data->precision != 0)
	{
		while (*convert)
		{
			write(1, &*convert, 1);
			convert++;
			data->len++;
		}
	}
}

void	print_x_all(t_data *data, unsigned int ret, char *convert, int len)
{
	if (data->flag[MINUS] == TRUE)
	{
		printx_body(data, ret, convert, len);
		printd_gap(data, ret, len);
	}
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, len);
		else
			printd_gap(data, ret, len);
		printx_body(data, ret, convert, len);
	}
}

int		print_x(t_data *data)
{
	unsigned int	ret;
	char			*convert;
	int				len;
	char			*base;

	ret = va_arg(data->ap_copy, unsigned int);
	if (data->type == 'x')
		base = "0123456789abcdef";
	if (data->type == 'X')
		base = "0123456789ABCDEF";
	if ((convert = ft_putnbr_base(ret, base)) == NULL)
		return (ERROR);
	len = ft_strlen(convert);
	if (ret == 0 && data->precision == 0)
		len = 0;
	print_x_all(data, ret, convert, len);
	free(convert);
	return (TRUE);
}
