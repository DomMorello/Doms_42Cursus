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
	info->forks = NULL;
	info->philo = NULL;
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
		info->philo[i].info = info;
		pthread_mutex_init(&info->philo[i].mutex, NULL);
		pthread_mutex_init(&info->philo[i].eat, NULL);
		pthread_mutex_lock(&info->philo[i].eat);
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

void	print_msg(t_philo *philo, int state)
{
	static int died = 0;

	pthread_mutex_lock(&philo->info->msg);
	if (!died)
	{
		printf("%lu\t", get_time() - philo->info->start);
		if (state != S_DIED)
			printf("%d", philo->philo_no + 1);
		if (state >= S_DIED)
			died = 1;	
		printf("%s", get_msg(state));
	}
	pthread_mutex_unlock(&philo->info->msg);
}

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
	print_msg(philo, S_TAKEN_FORK);
	pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
	print_msg(philo, S_TAKEN_FORK);
}

void put_fork(t_philo *philo)
{
	print_msg(philo, S_SLEEPING);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
	usleep(philo->info->time_to_sleep * 1000);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->info->time_to_die;
	print_msg(philo, S_EATING);
	usleep(philo->info->time_to_eat * 1000);
	philo->eat_cnt++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
}

void *monitor(void *philo_v)
{
	t_philo *philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			print_msg(philo, S_DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->info->game_done);
			return (philo_v);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
	return (philo_v);
}

void *routine(void *philo_v)
{
	t_philo *philo;
	pthread_t th;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->info->time_to_die;
	if (pthread_create(&th, NULL, monitor, philo_v))
		return ((void *)0);
	pthread_detach(th);
	while (1)
	{
		take_fork(philo);
		eat(philo);
		put_fork(philo);
		print_msg(philo, S_THINKING);
	}
	return (philo_v);
}

void *monitor_cnt(void *info_v)
{
	t_info *info;
	int i;
	int total;

	info = (t_info *)info_v;
	total = 0;
	while (total < info->must_eat_cnt)
	{
		i = 0;
		while (i < info->num_of_philos)
			pthread_mutex_lock(&info->philo[i].eat);
		total++;
	}
	print_msg(&info->philo[0], S_FULL);
	pthread_mutex_unlock(&info->game_done);
	return (info_v);
}

int solution(t_info *info)
{
	int i;
	pthread_t th;
	void *philo;

	info->start = get_time();
	i = 0;
	if (info->must_eat_cnt > 0)
	{
		if (pthread_create(&th, NULL, monitor_cnt, (void *)info))
			return (ERROR);
		pthread_detach(th);
	}
	while (i < info->num_of_philos)
	{
		philo = (void *)&info->philo[i];
		if (pthread_create(&th, NULL, routine, philo))
			return (ERROR);
		pthread_detach(th);
		usleep(100);
		i++;
	}
	return (TRUE);
}

int	init_mutex(t_info *info)
{
	int i;

	i = 0;
	pthread_mutex_init(&info->game_done, NULL);
	pthread_mutex_lock(&info->game_done);
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
	if (init_mutex(info) == ERROR)
		return (ERROR);
	return (TRUE);
}

void free_info(t_info *info)
{
	int	i;

	if (info->forks)
	{
		i = 0;
		while (i < info->num_of_philos)
			pthread_mutex_destroy(&info->forks[i++]);
		free(info->forks);
	}
	if (info->philo)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			pthread_mutex_destroy(&info->philo[i].mutex);
			pthread_mutex_destroy(&info->philo[i++].eat);
		}
		free(info->philo);
	}
	pthread_mutex_destroy(&info->msg);
	pthread_mutex_destroy(&info->game_done);
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
	{
		free_info(&info);
		printf("fatal error!\n");
		return (ERROR);
	}
	if ((solution(&info)) == ERROR)
	{
		printf("fatal error!\n");
		free_info(&info);
		return (ERROR);
	}
	pthread_mutex_lock(&info.game_done);
	pthread_mutex_unlock(&info.game_done);
	free_info(&info);
    return (0);
}
