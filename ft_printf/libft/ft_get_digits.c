#include "libft.h"

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