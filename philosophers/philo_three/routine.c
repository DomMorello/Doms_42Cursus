/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:58:46 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 16:46:50 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_three.h"

int		eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_EATING, get_time());
	less_error_sleep(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	philo->eat_cnt++;
	if (philo->eat_cnt == philo->info->must_eat)
	{
		philo->info->full_philo++;
		return (TRUE);
	}
	return (FALSE);
}

/*
**	A thread that monitors each processes.
**	checks if the philosopher has eaten must_eat times
**	and has died.
**	when the monitor thread found the philosopher died,
**	the process that contains this thread exits returning TRUE. 
*/

void	*monitor_th(void *arg)
{
	t_philo			*philo;
	unsigned long	cur;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (philo->eat_cnt == philo->info->must_eat)
			break ;
		cur = get_time();
		if (philo->info->time_to_die < cur - philo->last_eat)
		{
			print_msg(philo, S_DIED, cur);
			exit(TRUE);
		}
		less_error_sleep(1);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_t th;

	pthread_create(&th, NULL, monitor_th, (void *)philo);
	while (TRUE)
	{
		if (eat(philo))
			break ;
		if (print_msg(philo, S_SLEEPING, get_time()))
			break ;
		less_error_sleep(philo->info->time_to_sleep);
		if (print_msg(philo, S_THINKING, get_time()))
			break ;
	}
	pthread_join(th, NULL);
	exit(FALSE);
}

/*
**	Only main process(parent process) comes in this function.
**	Doesn't wait child processes by using WNOHANG.
**	when a child process exits,
**	reads the exit status(stat) and decides what to do.
**	if a child process exits returning FALSE,
**	it means the philosopher is full.
**	Otherwise, it means the philosopher died(stat == 256).
**	when a philosopher died, kills all the remaining processes.
*/

void	monitor_p(t_info *info)
{
	int stat;
	int i;
	int full_cnt;

	full_cnt = 0;
	while (TRUE)
	{
		i = -1;
		while (++i < info->num_of_philos)
		{
			waitpid(info->philos[i].pid, &stat, WNOHANG);
			if (stat == 256)
				break ;
			if (stat == FALSE && ++full_cnt && full_cnt == info->num_of_philos)
				break ;
		}
		if (i != info->num_of_philos)
		{
			kill_process(info);
			break ;
		}
	}
}
