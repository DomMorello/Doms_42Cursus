#include "ft_printf.h"

void		printu_body(t_data *data, unsigned int ret, int len)
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
		printd_nbr(data, ret, len);
}

void		print_u(t_data *data)
{
	unsigned int ret;
	int len;

	ret = va_arg(data->ap_copy, unsigned int);
	len = ft_get_digits((unsigned int)ret);
	if (ret == 0 && data->precision == 0)
		len = 0;
	if (data->flag[MINUS] == TRUE)
	{
		printu_body(data, (unsigned int)ret, len);
		printd_gap(data, ret, len);
	}
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, len);
		else
			printd_gap(data, ret, len);
		printu_body(data, (unsigned int)ret, len);
	}
}
