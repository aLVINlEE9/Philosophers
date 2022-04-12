#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

void	*routine(void *data)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	sleep(2);
	printf("pid : %u, tid : %x\n", (unsigned int)pid, (unsigned int)tid);
	printf("Finished thread execution\n");
}

int	main(void)
{
	pthread_t th[3];
	int n = -1;

	while (++n < 3)
	{
		if (pthread_create(&th[n], NULL, routine, (void *)NULL))
			perror("Failed to create thread ");
		pthread_detach(th[n]);
	}
	n = -1;
	while(++n < 3)
	{
		if (pthread_join(th[n], NULL))
			perror("Failed to join thread ");
	}
	// routine((void *)NULL);
	// pthread_exit(0);
	return (0);
}