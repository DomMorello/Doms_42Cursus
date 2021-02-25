#include "./philo_one.h"

void *routine(void *arg)
{
	int *a = (int *)arg;

	while (1)
	{
		printf("hi %d\n", *a);
		sleep(1);
	}
	return (void *)a;
}

int main(int argc, char const *argv[])
{
    pthread_t th;

	int i = 0;
	while (i < 3)
	{
		pthread_create(&th, NULL, routine, (void *)&i);
		pthread_detach(th);
		i++;
	}
	while (1)
	{
		;
	}
    return 0;
}
