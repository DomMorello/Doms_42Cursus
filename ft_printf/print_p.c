#include "ft_printf.h"

void		printp_from_haed(t_data *data, char *convert, int gap, int len)
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

void		printp_from_tail(t_data *data, char *convert, int gap, int len)
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

void		printp_body(t_data *data, char *convert, int len)
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
	if (data->width > len)
	{
		gap = data->width - len - 2;
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
