#include "ft_printf.h"

void 		prints_from_head(t_data *data, char *s, int gap)
{
	while (data->precision--)
	{
		write(1, &*s, 1);
		data->len++;
		s++;
	}
	while (gap--)
	{
		write(1, " ", 1);	
		data->len++;
	}
}

void		prints_from_tail(t_data *data, char *s, int gap)
{
	while (gap--)
	{
		write(1, " ", 1);
		data->len++;
	}
	while (data->precision--)
	{		
		write(1, &*s, 1);
		data->len++;
		s++;
	}
}

void		print_s(t_data *data)
{
	char *s;
	int gap;

	gap = 0;
	if (!(s = va_arg(data->ap_copy, char *)))
		s = "(null)";
	if ((int)ft_strlen(s) < data->precision || data->precision == -1)
		data->precision = ft_strlen(s);
	if (data->precision < data->width)
		gap = data->width - data->precision;
	if (data->flag[MINUS] == TRUE)
		prints_from_head(data, s, gap);
	else
		prints_from_tail(data, s, gap);
}
