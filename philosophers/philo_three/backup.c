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
	int i;

	i = -1;
//	while (++i < info->num_of_philos)
//	{
//		info->philos[i].philo_no = i + 1;
//		info->philos[i].eat_cnt = 0;
//	}
	info->full_philo = 0;
	info->done = 0;
	info->time = get_time();
	info->enter = sem_open(SEM_ENTER, O_CREAT | O_EXCL, 0777, info->num_of_philos / 2);
	info->msg = sem_open(SEM_MSG, O_CREAT | O_EXCL, 0777, 1);
	sem_unlink(SEM_ENTER);
	sem_unlink(SEM_MSG);
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
		//fork
	}
}

int main(int argc, char const *argv[])
{
	t_info info;

	if (!(argc == 5 || argc == 6) || err_check(argv, &info))
		return (printf("invalid arguments\n"));
	if ((info.philos = (t_philo *)malloc(sizeof(t_philo) * info.num_of_philos)) == NULL)
		return (ERROR);
	init_info(&info);
	init_philos(&info);
	return (TRUE);
}
