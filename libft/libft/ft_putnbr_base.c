#include "libft.h"

static void	print_num(long nbr, int base_len, char *base)
{
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= (-1);
	}
	if (nbr >= base_len)
		print_num(nbr / base_len, base_len, base);
	write(1, &base[nbr % base_len], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int base_len;
	int i;
	int j;

	base_len = 0;
	while (base[base_len])
	{
		if (base[base_len] == '+' || base[base_len] == '-')
			return ;
		base_len++;
	}
	if (base_len < 2)
		return ;
	i = -1;
	while (++i < base_len)
	{
		j = i;
		while (++j < base_len)
			if (base[i] == base[j])
				return ;
	}
	print_num((long)nbr, base_len, base);
}