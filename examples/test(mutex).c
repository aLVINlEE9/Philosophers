#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int mails = 0;
int nmails = 0;
pthread_mutex_t mutex_1, mutex_2;

void	*routine(void *data)
{
	int i = -1;

	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex_1);
		usleep(1);
		pthread_mutex_lock(&mutex_2);
		mails++;
		nmails++;
		pthread_mutex_unlock(&mutex_1);
		pthread_mutex_unlock(&mutex_2);
	}
}

int main()
{
	pthread_t	th1, th2;

	pthread_mutex_init(&mutex_1, NULL);
	pthread_mutex_init(&mutex_2, NULL);
	if (pthread_create(&th1, NULL, routine, NULL))
		perror("Failed to create thread ");
	if (pthread_create(&th2, NULL, routine, NULL))
		perror("Failed to create thread ");
	if (pthread_join(th1, NULL))
		perror("Failed to join thread ");
	if (pthread_join(th2, NULL))
		perror("Failed to join thread ");
	pthread_mutex_destroy(&mutex_1);
	pthread_mutex_destroy(&mutex_2);
	printf("%d %d\n", mails, nmails);
}