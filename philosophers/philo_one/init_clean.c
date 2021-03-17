/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:46:23 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 11:50:18 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_one.h"

/*
**	sets location of left and right forks.
*/

void	init_info(void)
{
	int		i;

	i = -1;
	while (++i < g_info.num_of_philos)
	{
		pthread_mutex_init(&g_info.fork[i], NULL);
		g_philos[i].philo_no = i + 1;
		g_philos[i].eat_cnt = 0;
		g_philos[i].l_fork = i - 1;
		if (!i)
			g_philos[i].l_fork = g_info.num_of_philos - 1;
		g_philos[i].r_fork = i;
	}
	pthread_mutex_init(&g_info.msg, NULL);
	g_info.full_philo = 0;
	g_info.done = 0;
	g_info.time = get_time();
}

void	init_philos(void)
{
	int		i;

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

void	clean_info(void)
{
	int		i;

	i = -1;
	while (++i < g_info.num_of_philos)
		pthread_mutex_destroy(&g_info.fork[i]);
	pthread_mutex_destroy(&g_info.msg);
	free(g_info.fork);
	free(g_philos);
}
