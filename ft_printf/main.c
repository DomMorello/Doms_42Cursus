#include "ft_printf.h"

size_t ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
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

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
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

/* - 0 둘 다 올수 있다 ㅅㅂ. tester  원격에서 pull해야된다.  */
int main()
{
    int a = 3;
    unsigned int b = 123;
    char *c = "abc";
    char d = 'd';
    unsigned int e = 543;
    ft_printf("%d %i %u %s %c %x %% \n", a, a, b,c,d,e);
    return 0;
}