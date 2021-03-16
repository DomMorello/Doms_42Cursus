/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:48:10 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 11:51:02 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_one.h"

void	*monitor(void *arg)
{
	t_philo			*philo;
	unsigned long	cur;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (philo->eat_cnt == g_info.must_eat)
			break ;
		cur = get_time();
		if (g_info.time_to_die < cur - philo->last_eat)
		{
			print_msg(philo, S_DIED, cur);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int		eat(t_philo *philo)
{
	pthread_mutex_lock(&g_info.fork[philo->l_fork]);
	print_msg(philo, S_TAKEN_FORK, get_time());
	pthread_mutex_lock(&g_info.fork[philo->r_fork]);
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_EATING, get_time());
	less_error_sleep(g_info.time_to_eat);
	pthread_mutex_unlock(&g_info.fork[philo->l_fork]);
	pthread_mutex_unlock(&g_info.fork[philo->r_fork]);
	philo->eat_cnt++;
	if (philo->eat_cnt == g_info.must_eat)
	{
		g_info.full_philo++;
		return (TRUE);
	}
	return (FALSE);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	th;

	philo = (t_philo *)arg;
	if (!(philo->philo_no % 2))
		less_error_sleep(1);
	pthread_create(&th, NULL, monitor, philo);
	while (TRUE)
	{
		if (eat(philo))
			break ;
		if (print_msg(philo, S_SLEEPING, get_time()))
			break ;
		less_error_sleep(g_info.time_to_sleep);
		if (print_msg(philo, S_THINKING, get_time()))
			break ;
	}
	pthread_join(th, NULL);
	return (NULL);
}
