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

enum	e_state{
	S_EATING,
	S_TAKEN_FORK,
	S_SLEEPING,
	S_THINKING,
	S_DIED,
	S_FULL
};

struct	s_info;

typedef struct 		s_philo
{
	int 			philo_no;
	int				l_fork;
	int				r_fork;
	int				is_eating;
	int				eat_cnt;
	unsigned long	limit;
	unsigned long 	last_eat;
	struct s_info	*info;
}					t_philo;

typedef struct		s_info
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat_cnt;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
}					t_info;

int ft_atoi(char const *str);

#endif
