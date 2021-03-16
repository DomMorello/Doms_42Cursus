/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:04:52 by donglee           #+#    #+#             */
/*   Updated: 2021/03/16 17:16:42 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define SEM_FORKS "/forks"
# define SEM_MSG "/msg"

enum	e_state{
	S_TAKEN_FORK,
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DIED
};

struct s_info;

typedef struct		s_philo
{
	int				philo_no;
	int				eat_cnt;
	unsigned long	last_eat;
	pid_t			pid;
	struct s_info	*info;
}					t_philo;

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
	t_philo			*philos;
}					t_info;

int					print_msg(t_philo *philo, int state, unsigned long cur);
int					err_check(char const *argv[], t_info *info);
int					eat(t_philo *philo);
void				*monitor_th(void *arg);
void				routine(t_philo *philo);
void				monitor_p(t_info *info);
void				init_philos(t_info *info);
void				init_info(t_info *info);
void					kill_process(t_info *info);
int					ft_atoi(char const *s);
unsigned long		get_time(void);
void				less_error_sleep(unsigned long input);

#endif
