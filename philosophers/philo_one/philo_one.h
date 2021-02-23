#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>


typedef struct		s_arg
{
    int             num_of_philo;	//equals to num_of_forks
    unsigned long	die_time;		//thread 에서 die 되면 바로 프로그램 종료되게끔
    unsigned long	eat_time; 		//이 시간동안 usleep?
    unsigned long	sleep_time;
    int				must_eat;		//이렇게 다 먹으면 종료
}					t_arg;

typedef struct 		s_philo
{
	int				philo_no;
	int				is_dead;		//필요할까?
	t_arg			*arg;			
	int				l_fork;
	int				r_fork;
}					t_philo;

#endif