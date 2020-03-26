#include "libft.h"

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
		ft_putnbr_fd(num / 10, fd);
	tmp = (num % 10) + '0';
	write(fd, &tmp, 1);
}