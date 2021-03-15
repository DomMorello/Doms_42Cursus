#ifndef PHILO_THREE_H
#define PHILO_THREE_H

#define TRUE 1
#define FALSE 0
#define ERROR -1

#define SEM_ENTER "/enter"
#define SEM_MSG "/msg"

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
	sem_t			*enter;
	sem_t			*msg;
	t_philo			*philos;
}					t_info;

int ft_atoi(char const *s);
unsigned long	get_time(void);
void less_error_sleep(unsigned long input);

#endif
