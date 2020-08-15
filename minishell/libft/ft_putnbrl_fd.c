/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:50:08 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 16:51:11 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrl_fd(long long n, int fd)
{
	char		tmp;
	long long	num;

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
