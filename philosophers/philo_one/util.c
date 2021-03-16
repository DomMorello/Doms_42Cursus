/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:51:19 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 11:51:20 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_one.h"

int				ft_atoi(char *str)
{
	int		i;
	int		ret;
	int		sign;

	sign = 1;
	ret = 0;
	i = -1;
	if (str[i + 1] == '-' && i++)
		sign = -1;
	while (str[++i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (-1);
		ret = ret * 10 + (str[i] - '0');
	}
	return (sign * ret);
}

unsigned long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void			less_error_sleep(unsigned long input)
{
	unsigned long	base;
	unsigned long	cur;

	base = get_time();
	while (1)
	{
		cur = get_time();
		if (input < cur - base)
			return ;
		usleep(100);
	}
}
