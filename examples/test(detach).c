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
	sleep(2);
	printf("pid : %u, tid : %x\n", (unsigned int)pid, (unsigned int)tid);
	printf("Finished thread execution\n");
	pthread_mutex_unlock(mutex);
}

int	main(void)
{
	pthread_t th[3];
	pthread_mutex_t mutex;
	int n = -1;

	pthread_mutex_lock(&mutex);
	while (++n < 3)
	{
		if (pthread_create(&th[n], NULL, routine, (void *)&mutex))
			perror("Failed to create thread ");
		
	}
	n = -1;
	while (1)
	{
		sleep(10);
		printf("%d\n", n);
		break ;
	}
	n = -1;
	while(++n < 3)
	{
		pthread_detach(th[n]);
	}
	// routine((void *)NULL);
	// pthread_exit(0);
	return (0);
}