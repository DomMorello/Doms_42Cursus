#include "./philo_one.h"

pthread_mutex_t mutex;
pthread_mutex_t game;

void *monitor(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&game);
		sleep(1);
		pthread_mutex_unlock(&game);
	}
}

void *routine(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		printf("hihi\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	return arg;
}

int main(void)
{
	pthread_t th;

	pthread_create(&th, NULL, monitor, NULL);
	pthread_mutex_init(&game, NULL);
	int i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 3)
	{
		pthread_create(&th, NULL, routine, NULL);
		pthread_detach(th);
		i++;
	}
	pthread_mutex_lock(&game);
	pthread_mutex_unlock(&game);

	return 0;
}
