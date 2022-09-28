#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


# define THREAD_NUM 8
pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;
pthread_mutex_t stop;
pthread_mutex_t moniter_mutex;
int m_1 = 50;
int m_2 = 50;

void	*moniter(void *data)
{
	pthread_mutex_init(&moniter_mutex, NULL);
	while (1)
	{
		pthread_mutex_lock(&moniter_mutex);
	}
}

void	*routine(void *data)
{
	pthread_t moniter_thread;
	// pthread_mutex_lock(&mutex_1);
	// pthread_mutex_lock(&mutex_2);
	if (pthread_create(&moniter_thread, NULL, moniter, NULL))
		perror("Failed to create thread ");
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
	while (1)
		;
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
	pthread_mutex_init(&stop, NULL);
	pthread_mutex_lock(&stop);
	while (++n < THREAD_NUM)
	{
		if (pthread_create(&th[n], NULL, routine, NULL))
			perror("Failed to create thread ");
		pthread_detach(th[n]);
	}
	pthread_mutex_lock(&stop);
	n = -1;
	// while(++n < THREAD_NUM)
	// {
	// 	if (pthread_join(th[n], NULL))
	// 		perror("Failed to join thread ");
	// }
	printf("m_1: %d\n", m_1);
	printf("m_2: %d\n", m_2);
	pthread_mutex_destroy(&mutex_1);
	pthread_mutex_destroy(&mutex_2);
}