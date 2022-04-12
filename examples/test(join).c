#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

void	*routine(void *data)
{
	pid_t pid;
	pthread_t tid;
	int	*n;

	pid = getpid();
	tid = pthread_self();
	n = (int *)data;
	*n *= 10;
	printf("pid : %u, tid : %x\n", (unsigned int)pid, (unsigned int)tid);
	printf("Finished thread execution\n");
	printf("%p\n", n);
	return ((void *)n);
}

int main()
{
	pthread_t	th;
	int	n = 10;
	int *status;

	if (pthread_create(&th, NULL, routine, (void *)&n))
		perror("Failed to create thread ");
	if (pthread_join(th, (void **)&status))
		perror("Failed to join thread");
	routine((void *)&n);
	printf("%p\n", status);
	printf("%d\n", *status);
}