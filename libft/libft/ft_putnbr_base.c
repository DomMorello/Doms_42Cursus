/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:19:13 by donglee           #+#    #+#             */
/*   Updated: 2020/04/07 18:21:06 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_len(unsigned long nbr, int base_len, int *len)
{
	(*len)++;
	if (nbr >= (unsigned long)base_len)
		get_len(nbr / base_len, base_len, len)
}

static char *save_str(unsigned long nbr, int base_len, char *basie)
{
	unsigned long	remainder;
	unsigned long	quotient;
	int				len;
	char			*ret;

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
	int		base_len;
	char	*ret;

	base_len = 0;
	if (!exception_base(&base_len, base))
		return (NULL);
	if ((ret = save_str(nbr, base_len, base)) == NULL)
		return (NULL);
	return (ret);
}
