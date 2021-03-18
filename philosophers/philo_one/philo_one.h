/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:50:47 by donglee           #+#    #+#             */
/*   Updated: 2021/03/18 10:03:41 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define TRUE 1
# define FALSE 0

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>

enum	e_state	{
	S_TAKEN_FORK,
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DIED
};

typedef struct		s_info
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;

	unsigned long	time;
	int				full_philo;
	int				done;
	pthread_mutex_t	*fork;
	pthread_mutex_t	msg;
}					t_info;

typedef struct		s_philo
{
	int				philo_no;
	int				l_fork;
	int				r_fork;
	int				eat_cnt;
	unsigned long	last_eat;
	pthread_t		th;
}					t_philo;

t_info				g_info;
t_philo				*g_philos;

void				*routine(void *philo);
void				*monitor(void *philo);
void				clean_info(void);
void				less_error_sleep(unsigned long time);
void				init_philos(void);
void				init_info(void);
int					ft_atoi(char const *str);
int					err_check(char **argv);
int					print_msg(t_philo *philo, int msg, unsigned long cur);
int					eat(t_philo *philo);
unsigned long		get_time(void);

#endif
