#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct		s_arg
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat_cnt;
}					t_arg;

typedef struct 		s_philo
{
	int 			philo_no;
	int				l_fork;
	int				r_fork;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	unsigned long	limit;
	unsigned long 	last_eat;
}					t_philo;

typedef struct		s_data
{
	t_arg			*arg;
	t_philo			*philo;
}					t_data;

#endif