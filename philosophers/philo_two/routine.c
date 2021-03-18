/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:41:57 by donglee           #+#    #+#             */
/*   Updated: 2021/03/18 10:25:39 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_two.h"

int		eat(t_philo *philo)
{
	sem_wait(g_info.forks);
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_EATING, get_time());
	less_error_sleep(g_info.time_to_eat);
	sem_post(g_info.forks);
	philo->eat_cnt++;
	if (philo->eat_cnt == g_info.must_eat)
	{
		g_info.full_philo++;
		return (TRUE);
	}
	return (FALSE);
}

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

void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	th;

	philo = (t_philo *)arg;
	pthread_create(&th, NULL, monitor, (void *)philo);
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
