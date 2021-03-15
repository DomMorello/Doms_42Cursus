#include "./philo_three.h"

int err_check(char const *argv[], t_info *info)
{
	if ((info->num_of_philos = ft_atoi(argv[1])) <= 1 ||
		(info->time_to_die = ft_atoi(argv[2])) <= 0 ||
		(info->time_to_eat = ft_atoi(argv[3])) <= 0 ||
		(info->time_to_sleep = ft_atoi(argv[4])) <= 0)
		return (TRUE);
	if (argv[5] && (info->must_eat = ft_atoi(argv[5])) <= 0)
		return (TRUE);
	else if (!argv[5])
		info->must_eat = -1;
	return (FALSE);
}

void init_info(t_info *info)
{
	info->full_philo = 0;
	info->done = 0;
	info->time = get_time();
	info->enter = sem_open(SEM_ENTER, O_CREAT | O_EXCL, 0777, info->num_of_philos / 2);
	info->msg = sem_open(SEM_MSG, O_CREAT | O_EXCL, 0777, 1);
	sem_unlink(SEM_ENTER);
	sem_unlink(SEM_MSG);
}

int print_msg(t_philo *philo, int state, unsigned long cur)
{
	sem_wait(philo->info->msg);
	if (philo->info->done)
	{
		sem_post(philo->info->msg);
		return (TRUE);
	}
	printf("%lu %d", cur - philo->info->time, philo->philo_no);
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
		philo->info->done = 1;
	}
	sem_post(philo->info->msg);
	return (FALSE);
}

int eat(t_philo *philo)
{
	sem_wait(philo->info->enter);
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_TAKEN_FORK, get_time());
	print_msg(philo, S_EATING, get_time());
	less_error_sleep(philo->info->time_to_eat);
	sem_post(philo->info->enter);
	philo->eat_cnt++;
	if (philo->eat_cnt == philo->info->must_eat)
	{
		philo->info->full_philo++;
		return (TRUE);
	}
	return (FALSE);
}

void *monitor_th(void *arg)
{
	t_philo *philo;
	unsigned long cur;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (philo->eat_cnt == philo->info->must_eat)
			break ;
		cur = get_time();
		if (philo->info->time_to_die < cur - philo->last_eat)
		{
			print_msg(philo, S_DIED, cur);
			exit(TRUE);
		}
		usleep(1000);
	}
	return (NULL);
}

void routine(t_philo *philo)
{
	pthread_t th;

	pthread_create(&th, NULL, monitor_th, (void *)philo);
	while (TRUE)
	{
		if (eat(philo))
			break ;
		if (print_msg(philo, S_SLEEPING, get_time()))
			break ;
		less_error_sleep(philo->info->time_to_sleep);
		if (print_msg(philo, S_THINKING, get_time()))
			break ;
	}
	pthread_join(th, NULL);
}

int kill_process(t_info *info)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
		kill(info->philos[i].pid, SIGKILL);
	return (TRUE);
}

void monitor_p(t_info *info)
{
	int stat;
	int i;
	int full_cnt;

	full_cnt = 0;
	while (TRUE)
	{
		i = -1;
		while (++i < info->num_of_philos)
		{
			waitpid(info->philos[i].pid, &stat, WNOHANG);
			if (stat == 256)
				break ;
			if (stat == FALSE && ++full_cnt && full_cnt == info->num_of_philos)
				break ;
		}
		if (i != info->num_of_philos)
		{
			kill_process(info);
			break ;
		}
	}
}

void init_philos(t_info *info)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		info->philos[i].philo_no = i + 1;
		info->philos[i].eat_cnt = 0;
		info->philos[i].info = info;
		info->philos[i].last_eat = get_time();
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
			routine(&info->philos[i]);
	}
	if (i == info->num_of_philos)
		monitor_p(info);
}

int main(int argc, char const *argv[])
{
	t_info info;
	int stat;

	if (!(argc == 5 || argc == 6) || err_check(argv, &info))
		return (printf("invalid arguments\n"));
	if ((info.philos = (t_philo *)malloc(sizeof(t_philo) * info.num_of_philos)) == NULL)
		return (ERROR);
	init_info(&info);
	init_philos(&info);
	sem_close(info.enter);
	sem_close(info.msg);
	free(info.philos);
	return (TRUE);
}
