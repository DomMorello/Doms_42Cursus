#include "./philo_one.h"

#define N 5

int	init_arg(t_arg *arg, int argc, char const *argv[])
{
	arg->num_of_philos = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->must_eat_cnt = ft_atoi(argv[5]);
	else
		arg->must_eat_cnt = 0;
	return (TRUE);
}

int	 init_philos(t_data *data)
{
	int i;

	i = 0;
	if ((data->philos = (t_philo *)malloc(sizeof(t_philo) * data->arg->num_of_philos)) == NULL)
		return (ERROR);
	while (i < data->arg->num_of_philos)
	{
		data->philos->philo_no = i;
		data->philos->is_eating = 0;
		data->philos->l_fork = i;
		data->philos->r_fork = (i + 1) % data->arg->num_of_philos;
		data->philos->eat_cnt = 0;
		i++;
	}
	return (TRUE);
}

int	init(t_data *data, int argc, char const *argv[])
{
	if ((data->arg = malloc(sizeof(t_arg))) == NULL)
		return (ERROR);
	init_arg(data->arg, argc, argv);
	if (init_philos(data) == ERROR)
	{
		free(data->arg);
		data->arg = NULL;
		return (ERROR);
	}
	return (TRUE);
}

int main(int argc, char const *argv[])
{
	t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("invalid argument\n");
        return (ERROR);
    }
	if (init(&data, argc, argv) == ERROR)
		return (ERROR);
    return 0;
}
