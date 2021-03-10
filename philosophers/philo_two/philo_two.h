#ifndef PHILO_TWO_H
#define PHILO_TWO_H

#define TRUE 1
#define FALSE 0
#define ERROR -1

#define SEM_ENTER "/enter"
#define SEM_MSG "/msg"

enum	e_state	{
	S_TAKEN_FORK,
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DIED
};

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <stdio.h>

typedef struct		s_info
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;	//num_eat
	unsigned long	time;		//base_time
	int				full_philo;	//eat
	int				done;		//dead
	sem_t			*enter;
	sem_t			*msg;
}               	t_info;

typedef struct 		s_philo
{
	int				philo_no;	//nbr
	int				eat_cnt;	//eat
	unsigned long	last_eat;
	pthread_t		th;			///tid
}					t_philo;

t_info				g_info;
t_philo				*g_philos;

int ft_atoi(char const *s);
void	less_error_sleep(unsigned long input);
unsigned long	get_time(void);

#endif