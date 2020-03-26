#include "libft.h"

int			ft_get_digits(int nbr)
{
	int cnt;
	
	cnt = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		cnt++;
	}
	return (cnt);
}