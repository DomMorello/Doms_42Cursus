#include "./philo_one.h"

#define N 5

int	init_info(t_info *info, int argc, char const *argv[])
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_cnt = ft_atoi(argv[5]);
	else
		info->must_eat_cnt = 0;
	return (TRUE);
}

void	 init_philos(t_info *info)
{
	int i;

	i = 0;
	while (i < info->num_of_philos)
	{
		info->philo[i].philo_no = i;
		info->philo[i].is_eating = 0;
		info->philo[i].l_fork = i;
		info->philo[i].r_fork = (i + 1) % info->num_of_philos;
		info->philo[i].eat_cnt = 0;
		i++;
	}
}

char *get_msg(int state)
{
	if (state == S_EATING)
		return (" is eating\n");
	else if (state == S_TAKEN_FORK)
		return (" has taken a fork\n");
	else if (state == S_SLEEPING)
		return (" is sleeping\n");
	else if (state == S_THINKING)
		return (" is thinking\n");
	else if (state == S_DIED)
		return (" died\n");
	else
		return ("All the philosophers are full\n");
}

int	print_msg(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->info->msg);
	printf("%d%s", philo->philo_no + 1, get_msg(state));
	pthread_mutex_unlock(&philo->info->msg);
}

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
	print_msg(philo, S_TAKEN_FORK);
	pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
	print_msg(philo, S_TAKEN_FORK);
	sleep(1);
}

void put_fork(t_philo *philo)
{
	print_msg(philo, S_SLEEPING);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
}

void *routine(void *philo_v)
{
	t_philo *philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		take_fork(philo);
		//eat();
		put_fork(philo);
	}
	return philo_v;
}

void solution(t_info *info)
{
	int i;
	pthread_t th;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_create(&th, NULL, routine, (void *)&info->philo[i]);
		pthread_detach(th);
		i++;
	}
	while (1)
	{
		;
	}
}

int	init_mutex(t_info *info)
{
	int i;

	i = 0;
	if ((info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_of_philos)) == NULL)
		return (ERROR);
	while (i < info->num_of_philos)
		pthread_mutex_init(&info->forks[i++], NULL);
	pthread_mutex_init(&info->msg, NULL);
	return (TRUE);
}

int	init(t_info *info, int argc, char const *argv[])
{
	init_info(info, argc, argv);
	if ((info->philo = malloc(sizeof(t_philo) * info->num_of_philos)) == NULL)
		return (ERROR);
	init_philos(info);
	init_mutex(info);
	return (TRUE);
}

int main(int argc, char const *argv[])
{
	t_info info;

    if (argc < 5 || argc > 6)
    {
        printf("invalid argument\n");
        return (ERROR);
    }
	if (init(&info, argc, argv) == ERROR)
		return (ERROR);
	solution(&info);
    return 0;
}
