/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:47:45 by donglee           #+#    #+#             */
/*   Updated: 2021/03/18 10:25:27 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_two.h"

int		err_check(char const *argv[])
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

int		print_msg(t_philo *philo, int state, unsigned long cur)
{
	sem_wait(g_info.msg);
	if (g_info.done)
	{
		sem_post(g_info.msg);
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
	sem_post(g_info.msg);
	return (FALSE);
}

int		main(int argc, char const *argv[])
{
	if (!(argc == 5 || argc == 6) || err_check(argv))
		return (printf("invalid arguments\n"));
	if ((g_philos = malloc(sizeof(t_philo) * g_info.num_of_philos)) == NULL)
		return (printf("malloc error\n"));
	init_info();
	init_philos();
	sem_close(g_info.forks);
	sem_close(g_info.msg);
	free(g_philos);
	return (FALSE);
}
