/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:59:19 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 16:46:59 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_three.h"

int		err_check(char const *argv[], t_info *info)
{
	if ((info->num_of_philos = ft_atoi(argv[1])) <= 1 ||
		(info->time_to_die = ft_atoi(argv[2])) <= 0 ||
		(info->time_to_eat = ft_atoi(argv[3])) <= 0 ||
		(info->time_to_sleep = ft_atoi(argv[4])) <= 0)
		return (TRUE);
	if (argv[5] && (info->must_eat = ft_atoi(argv[5])) <= 0)
		return (TRUE);
	else if (!argv[5])
		info->must_eat = -1;
	return (FALSE);
}

/*
**	Prints state and checks if someone died
*/

int		print_msg(t_philo *philo, int state, unsigned long cur)
{
	sem_wait(philo->info->msg);
	if (philo->info->done)
	{
		sem_post(philo->info->msg);
		return (TRUE);
	}
	printf("%lu %d", cur - philo->info->time, philo->philo_no);
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
		philo->info->done = 1;
	}
	sem_post(philo->info->msg);
	return (FALSE);
}

int		main(int argc, char const *argv[])
{
	t_info	info;

	if (!(argc == 5 || argc == 6) || err_check(argv, &info))
		return (printf("invalid arguments\n"));
	if ((info.philos = (t_philo *)malloc(sizeof(t_philo)
		* info.num_of_philos)) == NULL)
		return (ERROR);
	init_info(&info);
	init_philos(&info);
	sem_close(info.forks);
	sem_close(info.msg);
	free(info.philos);
	return (TRUE);
}
