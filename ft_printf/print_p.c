/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:43:46 by donglee           #+#    #+#             */
/*   Updated: 2020/04/13 20:54:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//p���� . ������ precision 0 ���� �ؼ� 0�̰� NULL�� ���� 0x�� ������;
int			modify_p_data(t_data *data, char *cpy)
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
			data->precision = 0;
		i++;
	}
	free(check);
	return (TRUE);
}

void	printp_from_haed(t_data *data, char *convert, int gap, int len)
{
	write(1, "0x", 2);
	data->len += 2;
	while (len--)
	{
		write(1, &*convert, 1);
		convert++;
		data->len++;
	}
	while (gap--)
	{
		write(1, " ", 1);
		data->len++;
	}
}

void	printp_from_tail(t_data *data, char   *convert, int gap, int len)
{
	while (gap--)
	{
		write(1, " ", 1);
		data->len++;
	}
	write(1, "0x", 2);
	data->len += 2;
	while (len--)
	{
		write(1, &*convert, 1);
		convert++;
		data->len++;
	}
}

void	printp_body(t_data *data, char *convert, int len)
{
	write(1, "0x", 2);
	data->len += 2;
	while (len--)
	{
		write(1, &*convert, 1);
		convert++;
		data->len++;
	}
}

int			print_p(t_data *data)
{
	unsigned long ret;
	char *convert;
	int len;
	int gap;

	ret = va_arg(data->ap_copy, unsigned long);
	if ((convert = ft_putnbr_base(ret, "0123456789abcdef")) == NULL)
		return (ERROR);
	len = ft_strlen(convert);
	if (data->precision == 0)
		len = 0;	//0x�� ����ϵ��� 
	if (data->width > len)
	{
		gap = data->width - len - 2;
		if (gap < 0)
			gap = 0;	//width�� 2�� �� ���ѷ��� ����.
		if (data->flag[MINUS] == TRUE)
			printp_from_haed(data, convert, gap, len);
		else
			printp_from_tail(data, convert, gap, len);
	}
	else
		printp_body(data, convert, len);
	free(convert);
	return (TRUE);
}
