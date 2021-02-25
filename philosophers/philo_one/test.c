#include "./philo_one.h"

typedef struct s_test
{
	int id;
	pthread_mutex_t *forks;
}				t_test;

void *routine(void *arg)
{
}

int main(int argc, char const *argv[])
{
	t_test philo;

	int i = 0;

	while (i < 3)
	{
		philo.forks = malloc(sizeof(pthread_mutex_t) * 3);
		pthread_mutex_init(&philo.forks[i], NULL);
		i++;
	}
	
    return 0;
}
