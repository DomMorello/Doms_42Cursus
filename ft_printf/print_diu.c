#include "ft_printf.h"

void		printd_gap(t_data *data, int len)
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
	while (gap--)
	{
		write(1, " ", 1);
		data->len++;
	}
}

void		printd_zero(t_data *data, int len)
{
	int gap;

	gap = 0;
	if (data->width > len)
		gap = data->width - len;
	while (gap--)
	{
		write(1, "0", 1);
		data->len++;
	}
}

void		printd_nbr(t_data *data, int ret, int len)
{
	if (data->type == 'u')
		ft_putnbrl_fd((unsigned int)ret, 1);
	else
		ft_putnbrl_fd(ret, 1);
	data->len += len;
}

void		printd_body(t_data *data, int ret, int len)
{
	int gap;
	long long tmp;

	if (data->precision > len)
	{
		gap = data->precision - len;
		tmp = (long long)ret;
		if (tmp < 0)
		{
			write(1, "-", 1);
			data->len++;
			tmp *= (-1);
		}
		while (gap--)
		{
			write(1, "0", 1);
			data->len++;
		}
	}
	if (ret != 0 || data->precision != 0)
		printd_nbr(data, ret, len);
}

void		print_diu(t_data *data)
{
	int ret;
	int len;

	ret = va_arg(data->ap_copy, int);
	if (data->type == 'd' || data->type == 'i')
		len = ft_get_digits(ret);
	else
		len = ft_get_digits((unsigned int)ret);
	if ((data->type == 'd' || data->type == 'i') && ret < 0)
		len++;
	if (ret == 0 && data->precision == 0)
		len = 0;
	if (data->flag[MINUS] == TRUE)
	{
		printd_body(data, ret, len);
		printd_gap(data, len);
	}
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, len);
		else
			printd_gap(data, len);
		printd_body(data, ret, len);
	}
}
