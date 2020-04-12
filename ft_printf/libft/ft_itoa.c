/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:03:40 by donglee           #+#    #+#             */
/*   Updated: 2020/04/07 18:05:47 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(int n)
{
	int			len;
	long long	tmp;

	if (n < 0)
		tmp = (long long)n * (-1);
	if (n >= 0)
		tmp = (long long)n;
	len = 0;
	while (tmp > 9)
	{
		tmp = tmp / 10;
		len++;
	}
	return (len + 1);
}

static int	alloc_stirng(char **result, int n)
{
	int size;

	size = get_digits(n);
	if (n < 0)
	{
		if ((*result = (char *)malloc(sizeof(char) * size + 2)) == 0)
			return (0);
	}
	if (n >= 0)
	{
		if ((*result = (char *)malloc(sizeof(char) * size + 1)) == 0)
			return (0);
	}
	return (1);
}

char		*ft_itoa(int n)
{
	char		*result;
	int			len;
	long long	tmp;

	if (alloc_stirng(&result, n) == 0)
		return (NULL);
	if (n < 0)
	{
		tmp = (long long)n * (-1);
		len = get_digits(n);
		result[0] = '-';
	}
	if (n >= 0)
	{
		tmp = (long long)n;
		len = get_digits(n) - 1;
	}
	result[len + 1] = 0;
	while (tmp > 9)
	{
		result[len--] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	result[len] = (tmp % 10) + '0';
	return (result);
}
