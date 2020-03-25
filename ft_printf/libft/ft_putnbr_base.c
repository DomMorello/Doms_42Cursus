#include "libft.h"

static void	print_num(unsigned long nbr, int base_len, char *base, int *cnt)
{
	(*cnt)++;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= (-1);
	}
	if (nbr >= (unsigned long)base_len)
		print_num(nbr / base_len, base_len, base, cnt);
	write(1, &base[nbr % base_len], 1);
}

int		ft_putnbr_base(unsigned long nbr, char *base)
{
	int base_len;
	int i;
	int j;
	int cnt;

	cnt = 0;
	base_len = 0;
	while (base[base_len])
	{
		if (base[base_len] == '+' || base[base_len] == '-')
			return (-1);
		base_len++;
	}
	if (base_len < 2)
		return (-1);
	i = -1;
	while (++i < base_len)
	{
		j = i;
		while (++j < base_len)
			if (base[i] == base[j])
				return (-1);
	}
	print_num(nbr, base_len, base, &cnt);
	return (cnt);
}