/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:48:54 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 16:49:51 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
		ft_putnbr_fd(num / 10, fd);
	tmp = (num % 10) + '0';
	write(fd, &tmp, 1);
}
