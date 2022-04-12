#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


# define THREAD_NUM 8
pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;
int m_1 = 50;
int m_2 = 50;

void	*routine(void *data)
{
	// pthread_mutex_lock(&mutex_1);
	// pthread_mutex_lock(&mutex_2);
	if (rand() % 2 == 0)
	{
		pthread_mutex_lock(&mutex_1);
		pthread_mutex_lock(&mutex_2);
	}
	else
	{
		pthread_mutex_lock(&mutex_2);
		pthread_mutex_lock(&mutex_1);
	}
	m_1 += 50;
	m_2 += m_1;
	printf("Increamented m_1 to: %d set m_2 to %d\n", m_1, m_2);
	pthread_mutex_unlock(&mutex_1);
	pthread_mutex_unlock(&mutex_2);
}

int main()
{
	pthread_t th[THREAD_NUM];
	int n = -1;

	pthread_mutex_init(&mutex_1, NULL);
	pthread_mutex_init(&mutex_2, NULL);
	while (++n < THREAD_NUM)
	{
		if (pthread_create(&th[n], NULL, routine, NULL))
			perror("Failed to create thread ");
	}
	n = -1;
	while(++n < THREAD_NUM)
	{
		if (pthread_join(th[n], NULL))
			perror("Failed to join thread ");
	}
	printf("m_1: %d\n", m_1);
	printf("m_2: %d\n", m_2);
	pthread_mutex_destroy(&mutex_1);
	pthread_mutex_destroy(&mutex_2);
}