/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:45:05 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 11:48:27 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_one.h"

/*
**	prints state and checks if someone died.
*/

int		print_msg(t_philo *philo, int state, unsigned long cur)
{
	pthread_mutex_lock(&g_info.msg);
	if (g_info.done)
	{
		pthread_mutex_unlock(&g_info.msg);
		return (TRUE);
	}
	printf("%lu %d", cur - g_info.time, philo->philo_no);
	if (state == S_TAKEN_FORK)
		printf(" has taken a fork\n");
	else if (state == S_EATING)
	{
		printf(" is eating\n");
		philo->last_eat = cur;
	}
	else if (state == S_SLEEPING)
		printf(" is sleeping\n");
	else if (state == S_THINKING)
		printf(" is thinking\n");
	else if (state == S_DIED)
	{
		printf(" died\n");
		g_info.done = 1;
	}
	pthread_mutex_unlock(&g_info.msg);
	return (FALSE);
}

int		err_check(char **argv)
{
	if ((g_info.num_of_philos = ft_atoi(argv[1])) <= 1 ||
		(g_info.time_to_die = ft_atoi(argv[2])) <= 0 ||
		(g_info.time_to_eat = ft_atoi(argv[3])) <= 0 ||
		(g_info.time_to_sleep = ft_atoi(argv[4])) <= 0)
		return (TRUE);
	if (argv[5] && (g_info.must_eat = ft_atoi(argv[5])) <= 0)
		return (TRUE);
	else if (!argv[5])
		g_info.must_eat = -1;
	return (FALSE);
}

int		main(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6) || err_check(argv))
		return (printf("invalid argument\n"));
	if (!(g_philos = malloc(sizeof(t_philo) * g_info.num_of_philos)))
		return (printf("malloc error\n"));
	if (!(g_info.fork = malloc(sizeof(pthread_mutex_t) * g_info.num_of_philos)))
		return (printf("malloc error\n"));
	init_info();
	init_philos();
	clean_info();
	return (0);
}
