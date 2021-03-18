/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:42:26 by donglee           #+#    #+#             */
/*   Updated: 2021/03/18 10:25:18 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_two.h"

void	init_info(void)
{
	int i;

	i = -1;
	while (++i < g_info.num_of_philos)
	{
		g_philos[i].philo_no = i + 1;
		g_philos[i].eat_cnt = 0;
	}
	g_info.full_philo = 0;
	g_info.done = 0;
	g_info.time = get_time();
	g_info.forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0777,
					g_info.num_of_philos / 2);
	g_info.msg = sem_open(SEM_MSG, O_CREAT | O_EXCL, 0777, 1);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MSG);
}

void	init_philos(void)
{
	int i;

	i = -1;
	while (++i < g_info.num_of_philos)
	{
		g_philos[i].last_eat = get_time();
		pthread_create(&g_philos[i].th, NULL, routine, &g_philos[i]);
	}
	i = -1;
	while (++i < g_info.num_of_philos)
		pthread_join(g_philos[i].th, NULL);
}
