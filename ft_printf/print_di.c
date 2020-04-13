/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:41:57 by donglee           #+#    #+#             */
/*   Updated: 2020/04/13 16:40:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printd_gap(t_data *data, long long ret, int len)
{
	int gap;

	gap = 0;
	if (data->precision > len)
	{
		if (data->width > data->precision)
			gap = data->width - data->precision;
	}
	else
	{
		if (data->width > len)
			gap = data->width - len;
	}
	if (ret < 0)
		gap--;
	while (gap-- > 0)
	{
		write(1, " ", 1);
		data->len++;
	}
}

void		printd_zero(t_data *data, int len, int *ret)
{
	int gap;
	long long tmp;

	tmp = (long long)*ret;
	if (tmp < 0 && tmp != -2147483648)
	{
		len++;
		write(1, "-", 1);
		data->len++;
		*ret *= -1;
	}	//00-12 이지랄 나는거때문에 추가함. 
	gap = 0;
	if (data->width > len)
		gap = data->width - len;
	while (gap--)
	{
		write(1, "0", 1);
		data->len++;
	}
}

void	printd_nbr(t_data *data, long long ret, int len)
{
	if (data->type == 'u')
		ft_putnbrl_fd((unsigned int)ret, 1);
	else
		ft_putnbrl_fd(ret, 1);
	data->len += len;
}

void	printd_body(t_data *data, int ret, int len)
{
	int			gap;
	long long	tmp;

	tmp = (long long)ret;
	if (tmp < 0)
		data->len++;
	if (data->precision > len)
	{
		gap = data->precision - len;
		if (tmp < 0)
		{
			write(1, "-", 1);
			tmp *= (-1);
		}
		while (gap--)
		{
			write(1, "0", 1);
			data->len++;
		}
	}
	if (ret != 0 || data->precision != 0)
		printd_nbr(data, tmp, len);
}

void	print_di(t_data *data)
{
	int ret;
	int len;

	ret = va_arg(data->ap_copy, int);
	len = ft_get_digits(ret);
	if (ret == 0 && data->precision == 0)
		len = 0;
	if (data->flag[MINUS] == TRUE)
	{
		printd_body(data, ret, len);
		printd_gap(data, ret, len);
	}
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, len, &ret);
		else
			printd_gap(data, ret, len);
		printd_body(data, ret, len);
	}
}
