#include "./philo_two.h"

int err_check(char const *argv[])
{
    if ((g_info.num_of_philos = ft_atoi(argv[1])) <= 1 ||
        (g_info.time_to_die = ft_atoi(argv[2])) <= 0 ||
        (g_info.time_to_eat = ft_atoi(argv[3])) <= 0 ||
        (g_info.time_to_sleep = ft_atoi(argv[4])) <= 0)
        return (TRUE);
    if (argv[5] && (g_info.must_eat = ft_atoi(argv[5])) <= 0)
        return (TRUE);
    else if (!argv[5])
        g_info.must_eat = -1;
    return (FALSE);
}

void init_info(void)
{
    int i;

    i = -1;
    while (++i < g_info.num_of_philos)
    {
        g_philos[i].philo_no = i + 1;
        g_philos[i].eat_cnt = 0;
    }
    g_info.full_philo = 0;
    g_info.done = 0;
    g_info.time = get_time();
    g_info.enter = sem_open(SEM_ENTER, O_CREAT | O_EXCL, 0777, g_info.num_of_philos / 2);
    g_info.msg = sem_open(SEM_MSG, O_CREAT | O_EXCL, 0777, 1);
    sem_unlink(SEM_ENTER);
    sem_unlink(SEM_MSG);
}

int print_msg(t_philo *philo, int state, unsigned long cur)
{
	sem_wait(g_info.msg);
	if (g_info.done)
	{
		sem_post(g_info.msg);
		return (TRUE);
	}
	printf("%lu %d", cur - g_info.time, philo->philo_no);
	if (state == S_TAKEN_FORK)
		printf(" has taken a fork\n");
	else if (state == S_EATING)
	{
		printf(" is eating\n");
		philo->last_eat = cur;
	}
	else if (state == S_SLEEPING)
		printf(" is sleeping\n");
	else if (state == S_THINKING)
		printf(" is thinking\n");
	else if (state == S_DIED)
	{
		printf(" died\n");
		g_info.done = 1;
	}
	sem_post(g_info.msg);
	return (FALSE);
}

int	eat(t_philo *philo)
{
	sem_wait(g_info.enter);
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_EATING, get_time());
	less_error_sleep(g_info.time_to_eat);
	sem_post(g_info.enter);
	philo->eat_cnt++;
	if (philo->eat_cnt == g_info.must_eat)
	{
		g_info.full_philo++;
		return (TRUE);
	}
	return (FALSE);
}

void *monitor(void *arg)
{
	t_philo *philo;
	unsigned long cur;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->eat_cnt == g_info.must_eat)
			break ;
		cur = get_time();
		if (g_info.time_to_die < cur - philo->last_eat)
		{
			print_msg(philo, S_DIED, cur);
			return (NULL);
		}
		less_error_sleep(1);
	}
	return (NULL);
}

void *routine(void *arg)
{
    t_philo *philo;
    pthread_t th;

    philo = (t_philo *)arg;
    pthread_create(&th, NULL, monitor, (void *)philo);
    while (1)
    {
        if (eat(philo))
            break ;
        if (print_msg(philo, S_SLEEPING, get_time()))
            break ;
        less_error_sleep(g_info.time_to_sleep);
        if (print_msg(philo, S_THINKING, get_time()))
            break ;
    }
    pthread_join(th, NULL);
    return (NULL);
}

void init_philos(void)
{
    int i;

    i = -1;
    while (++i < g_info.num_of_philos)
    {
       g_philos[i].last_eat = get_time();
       pthread_create(&g_philos[i].th, NULL, routine, &g_philos[i]); 
    }
    i = -1;
    while (++i < g_info.num_of_philos)
        pthread_join(g_philos[i].th, NULL);
}

int main(int argc, char const *argv[])
{
    if (!(argc == 5 || argc == 6) || err_check(argv))
        return (printf("invalid arguments\n"));
    if ((g_philos = malloc(sizeof(t_philo) * g_info.num_of_philos)) == NULL)
        return (printf("malloc error\n"));
    init_info();
    init_philos();
    sem_close(g_info.enter);
    sem_close(g_info.msg);
    free(g_philos);
    return 0;
}