#include "ft_printf.h"
#include <string.h>

void		data_init(t_data *data)
{
	data->flag[MINUS] = FALSE;
	data->flag[ZERO] = FALSE;
	data->precision = -1;
	data->type = '\0';
	data->width = 0;
	data->i = 0;
}

static void	get_len(unsigned long nbr, int base_len, int *len)
{
	(*len)++;
	if (nbr >= (unsigned long)base_len)
		get_len(nbr / base_len, base_len, len);
}

static char *save_str(unsigned long nbr, int base_len, char *base)
{
	unsigned long remainder;
	unsigned long quotient;
	int len;
	char *ret;

	len = 0;
	get_len(nbr, base_len, &len);
	if ((ret = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	ret[len] = '\0';
	if (nbr == 0)
		ret[0] = '0';
	while (nbr != 0)
	{
		remainder = nbr % base_len;
		quotient = nbr / base_len;
		nbr = quotient;
		ret[--len] = base[remainder];
	}
	return (ret);
}

static int	exception_base(int *base_len, char *base)
{
	int i;
	int j;

	while (base[*base_len])
	{
		if (base[*base_len] == '+' || base[*base_len] == '-')
			return (0);
		(*base_len)++;
	}
	if (*base_len < 2)
		return (0);
	i = -1;
	while (++i < *base_len)
	{
		j = i;
		while (++j < *base_len)
			if (base[i] == base[j])
				return (0);
	}
	return (1);
}

char		*ft_putnbr_base(unsigned long nbr, char *base)
{
	int base_len;
	char *ret;

	base_len = 0;
	if (!exception_base(&base_len, base))
		return (NULL);
	if ((ret = save_str(nbr, base_len, base)) == NULL)
		return (NULL);
	return (ret);
}

int			is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' ||
		c == 'd' || c == 'i' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%')
		return (TRUE);
	return (FALSE);
}

int 		is_flag(char c)
{
	if (c == '-' || c == '0')
		return (TRUE);
	return (FALSE);
}

int 		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			is_valid(char c)
{
	if (ft_isdigit(c) || is_flag(c) || c == '.' || c == '*')
		return (TRUE);
	return (FALSE);
}

size_t 		ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void 		ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void		input_flag(t_data *data, char **ptr)
{
	while ((**ptr) && is_flag((**ptr)))
	{
		if (**ptr == '-')
			data->flag[MINUS] = TRUE;
		if (**ptr == '0')
			data->flag[ZERO] = TRUE;
		(*ptr)++;
		data->i++;
	}
}

void		input_width(t_data *data, char **ptr, va_list *list)
{
	int tmp;

	tmp = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		if (**ptr == '*')
		{
			tmp = va_arg(*list, int);
			if (tmp < 0)
			{
				data->flag[MINUS] = TRUE;
				tmp *= (-1);
			}
		}
		else
			tmp = **ptr - '0' + (tmp * 10);
		(*ptr)++;
		data->i++;
	}
	data->width = tmp;
}

void		input_precision(t_data *data, char **ptr, va_list *list)
{
	int tmp;
	int flag;

	tmp = 0;
	flag = 0;
	while (**ptr && (ft_isdigit(**ptr) || **ptr == '*'))
	{
		flag = 1;
		if (**ptr == '*')
			tmp = va_arg(*list, int);
		else
			tmp = **ptr - '0' + (tmp * 10);
		(*ptr)++;
		data->i++;
	}
	if (flag == 1)
		data->precision = tmp;
}


void		input_type(t_data *data, char **ptr)
{
	if (is_type(**ptr))
		data->type = **ptr;
	(*ptr)++;
	data->i++;
}

void		input_data(t_data *data, char **ptr, va_list *list)
{
	input_flag(data, ptr);
	input_width(data, ptr, list);
	if (**ptr == '.')
	{
		(*ptr)++;
		data->i++;
		input_precision(data, ptr, list);
	}
	input_type(data, ptr);
}

int			handle_exception1(char **format)
{
	while (!is_type(**format))
	{
		if (!is_valid(**format))
			return (ERROR);
		while (is_flag(**format))
			(*format)++;
		if (is_type(**format))
			break ;
		if (!is_valid(**format))
			return (ERROR);
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			if (ft_isdigit(**format) || !is_valid(**format))
				return (ERROR);
		}
		while (ft_isdigit(**format))
			(*format)++;
		break ;
	}
	return (TRUE);
}

int			handle_exception2(char **format)
{
	while (!is_type(**format))
	{
		if (is_flag(**format))
			return (ERROR);
		if (is_type(**format))
			break ;
		if (**format == '*' || !is_valid(**format))
			return (ERROR);		
		if (**format == '.')
			(*format)++;
		if (is_type(**format))
			break ;
		break ;
	}
	return (TRUE);
}

int 		handle_exception3(char **format)
{
	while (!is_type(**format))
	{
		if (**format == '.' || !is_valid(**format) || **format == '-')
			return (ERROR);
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			else
				return (ERROR);
		}
		else
		{
			while (ft_isdigit(**format))
				(*format)++;
			if (**format == '*' || is_flag(**format) || **format == '.')
				return (ERROR);
		}
		break ;
	}
	return (TRUE);
}

int			handle_exception4(char **format)
{
	while (!is_type(**format))
	{
		while (ft_isdigit(**format))
			(*format)++;
		if (is_type(**format))
			break ; 
		break ;
	}
	return (TRUE);
}

int 		exception_all(char *format)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (handle_exception1(&format) == ERROR)
				return (ERROR);
			if (handle_exception2(&format) == ERROR)
				return (ERROR);
			if (handle_exception3(&format) == ERROR)
				return (ERROR);
			if (handle_exception4(&format) == ERROR)
				return (ERROR);
		}
		format++;
	}	
	return (TRUE);
}

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
			return (ERROR);
	}
	return (TRUE);
}

int			print_c(t_data *data)
{
	char ret;

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

int			ft_get_digits(long long nbr)
{
	int cnt;
	
	cnt = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		cnt++;
	}
	return (cnt);
}

void 		ft_putnbrl_fd(long long n, int fd)
{
	char tmp;
	long long num;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = (long long)n * (-1);		
	}
	if (n >= 0)
		num = (long long)n;
	if (num > 9)
		ft_putnbrl_fd(num / 10, fd);
	tmp = (num % 10) + '0';
	write(fd, &tmp, 1);
}

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

void		printx_body(t_data *data, unsigned int ret, char *convert, int len)
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

void 		print_x_all(t_data *data, unsigned int ret, char *convert, int len)
{
	if (data->flag[MINUS] == TRUE)
	{
		printx_body(data, ret, convert, len);
		printd_gap(data, len);
	}
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, len);
		else
			printd_gap(data, len);
		printx_body(data, ret, convert, len);
	}
}

int			print_x(t_data *data)
{
	unsigned int ret;
	char *convert;
	int len;
	int gap;
	char *base;

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

void		print_per_head(t_data *data)
{
	write(1, "%", 1);
	data->len++;
	while((((data->width)--) - 1) > 0)
	{
		write(1, " ", 1);
		data->len++;
	}
}

void		print_per(t_data *data)
{
	if (data->flag[MINUS] == TRUE)
		print_per_head(data);
	else
	{
		if (data->flag[ZERO] == TRUE)
			printd_zero(data, 1);
		else
		{
			while((((data->width)--) - 1) > 0)
			{
				write(1, " ", 1);
				data->len++;
			}				
		}
		write(1, "%", 1);
		data->len++;
	}
}

int			print_data(t_data *data)
{
	if (data->type == 'c')
	{
		if (print_c(data) == ERROR)
			return (ERROR);
	}
	if (data->type == 's')
		print_s(data);
	if (data->type == 'p')
	{
		if (print_p(data) == ERROR)
			return (ERROR);
	}
	if (data->type == 'd' || data->type == 'i' || data->type == 'u')
		print_diu(data);
	if (data->type == 'x' || data->type == 'X')
	{
		if (print_x(data) == ERROR)
			return (ERROR);
	}
	if (data->type == '%')
		print_per(data);
	return (TRUE);
}

size_t 		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

int			modify_ds_data(t_data *data, char *cpy)
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
		{
			data->flag[ZERO] = FALSE;
			i++;
			if (check[i] == '0' || is_type(check[i]))
				data->precision = 0;
		}
		i++;
	}
	free(check);
	return (TRUE);
}

int			modify_data(t_data *data, char *cpy)
{
	if (data->type == 'd' || data->type == 's' || data->type == 'u'
		|| data->type == 'x' || data->type == 'X')
	{
		if (!modify_ds_data(data, cpy))
			return (FALSE);
	}
	if (data->type == '%')
	{
		data->precision = -1;
		if (data->flag[MINUS] == TRUE && data->flag[ZERO] == TRUE)
			data->flag[ZERO] = FALSE;
	}
	return (TRUE);
}

int			move_to_print(t_data *data)
{
	char *cpy;

	while (*(data->print))
	{
		if (*(data->print) == '%')
		{
			cpy = data->print;
			data_init(data);
			data->print++;
			input_data(data, &data->print, &data->ap_copy);
			if (!modify_data(data, cpy))
				return (ERROR);
			if (print_data(data) == ERROR)
				return (ERROR);
		}
		else
		{
			write(1, &*data->print, 1);
			data->print++;
			data->len++;
		}
	}
	return (TRUE);
}

int			parse_data(t_data *data, const char *format)
{
	while (*(data->copy))
	{
		if (*(data->copy) == '%')
		{
			data_init(data);
			data->copy++;
			input_data(data, &data->copy, &data->ap);
			if (exception_data(data, format) == ERROR)
				return (ERROR);
		}
		else
			data->copy++;
	}
	if (move_to_print(data) == ERROR)
		return (ERROR);
	return (TRUE);
}

int			ft_printf(const char *format, ...)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		return (ERROR);
	data_init(data);
	data->len = 0;
	if (format)
	{
		data->copy = (char *)format;
		data->print = (char *)format;
		va_start(data->ap, format);
		va_copy(data->ap_copy, data->ap);
		if (parse_data(data, format) == ERROR)
		{
			free(data);
			return (ERROR);
		}
		va_end(data->ap);
		va_end(data->ap_copy);
	}
	free(data);
	return (data->len);
}

int main()
{
	int t = 3;
	int g = 5;
	int k = 0;
	int j = 123;
	unsigned int r = 132543532;
	char *s1 = "abcde";
	// char *s2 = "12345";
	int a = ft_printf("hello %*.s world %5c wow %.p fuck %06d %.d %i %-10.6X %4%yo\n", 10, s1, 'b', &t, g, k, j, r);
	printf("ft: %d\n",a);
	int b = printf("hello %*.s world %5c wow %.p fuck %06d %.d %i %-10.6X %4%yo\n", 10, s1, 'b', &t, g, k, j, r);
	printf("lib: %d\n", b);

	return 0;
}