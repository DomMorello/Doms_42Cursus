/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:57:48 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 13:03:37 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_three.h"

int		kill_process(t_info *info)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
		kill(info->philos[i].pid, SIGKILL);
	return (TRUE);
}

void	init_info(t_info *info)
{
	info->full_philo = 0;
	info->done = 0;
	info->time = get_time();
	info->enter = sem_open(SEM_ENTER, O_CREAT | O_EXCL, 0777,
					info->num_of_philos / 2);
	info->msg = sem_open(SEM_MSG, O_CREAT | O_EXCL, 0777, 1);
	sem_unlink(SEM_ENTER);
	sem_unlink(SEM_MSG);
}

void	init_philos(t_info *info)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		info->philos[i].philo_no = i + 1;
		info->philos[i].eat_cnt = 0;
		info->philos[i].info = info;
		info->philos[i].last_eat = get_time();
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
			routine(&info->philos[i]);
	}
	if (i == info->num_of_philos)
		monitor_p(info);
}
