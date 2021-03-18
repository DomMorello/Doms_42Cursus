/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:53:20 by donglee           #+#    #+#             */
/*   Updated: 2021/03/18 10:24:43 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <stdio.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define SEM_FORKS "/forks"
# define SEM_MSG "/msg"

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
	sem_t			*forks;
	sem_t			*msg;
}					t_info;

typedef struct		s_philo
{
	int				philo_no;
	int				eat_cnt;
	unsigned long	last_eat;
	pthread_t		th;
}					t_philo;

t_info				g_info;
t_philo				*g_philos;

int					err_check(char const *argv[]);
int					print_msg(t_philo *philo, int state, unsigned long cur);
void				init_info(void);
void				init_philos(void);
int					eat(t_philo *philo);
void				*monitor(void *arg);
void				*routine(void *arg);
int					ft_atoi(char const *s);
void				less_error_sleep(unsigned long input);
unsigned long		get_time(void);

#endif
