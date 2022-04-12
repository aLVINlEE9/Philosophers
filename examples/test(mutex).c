#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int mails = 0;
pthread_mutex_t mutex;

void	*routine(void *data)
{
	int i = -1;

	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	pthread_t	th1, th2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&th1, NULL, routine, NULL))
		perror("Failed to create thread ");
	if (pthread_create(&th2, NULL, routine, NULL))
		perror("Failed to create thread ");
	if (pthread_join(th1, NULL))
		perror("Failed to join thread ");
	if (pthread_join(th2, NULL))
		perror("Failed to join thread ");
	pthread_mutex_destroy(&mutex);
	printf("%d\n", mails);
}