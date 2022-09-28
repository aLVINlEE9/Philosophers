#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

void	*routine(void *data)
{
	pid_t pid;
	pthread_t tid;
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)data;
	pid = getpid();
	tid = pthread_self();
	printf("pid : %u, tid : %x\n", (unsigned int)pid, (unsigned int)tid);
	printf("Finished thread execution\n");
	sleep(5);
	pthread_mutex_unlock(mutex);
}

int main()
{
	pthread_t th[3];
	pthread_mutex_t mutex;
	int i = -1;
	int	n = 10;
	int *status;

	pthread_mutex_lock(&mutex);
	while (++n < 3)
	{
		if (pthread_create(&th[n], NULL, routine, (void *)&mutex))
			perror("Failed to create thread ");
		pthread_detach(th[i]);
	}
	n = -1;
	while(++n < 3)
	{
		if (pthread_join(th[n], NULL))
			perror("Failed to join thread");
	}
	// printf("%p\n", status);
	// printf("%d\n", *status);
}