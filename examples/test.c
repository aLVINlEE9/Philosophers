#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// s

// 쓰레드 함수
// void *test(void *data)
// {
// 	int i;
// 	int a = *(int *)data;

// 	while (1)
// 	{
// 		for (i = 0; i < 10; i++)
// 		{
// 			printf("%d\n", i*a);
// 		}
// 		sleep(10);
// 		break ;
// 	}
	
// 	return (void *)(i * 100);
// 	// printf("Finished thread execution\n");
// }

// int main()
// {
// 	int a = 100;
// 	pthread_t thread_t;
// 	int status;

// 	// 쓰레드를 생성한다. 
// 	pthread_mutex_t mutex;

// 	pthread_mutex_lock(&mutex);
// 	if (pthread_create(&thread_t, NULL, test, (void *)&a))
// 	{
// 		perror("thread create error:");
// 		exit(0);
// 	}
// 	pthread_detach(thread_t);
// 	//  종료되기를 기다린후 
// 	// 쓰레드의 리턴값을 출력한다. 
// 	// pthread_join(thread_t, (void **)&status);
// 	printf("Thread End %d\n", status);
// 	return 1;
// }

void *test(void *data)
{
	pthread_mutex_t *mutex = (pthread_mutex_t *)data;

	if (rand() % 2)
	{
		pthread_mutex_lock(mutex + 0);
		pthread_mutex_lock(mutex + 1);
	}
	else{
		pthread_mutex_lock(mutex + 1);
		pthread_mutex_lock(mutex + 0);
	}
	
	while (1)
	{
		sleep(5);
		printf("%d\n", 10);
		// pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	int i = -1;
	pthread_t thread_t1[3];
	pthread_t thread_t2;
	pthread_mutex_t *fork;
	pthread_mutex_t mutex;

	// pthread_mutex_lock(&mutex);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 2);
	while (++i < 2)
	{
		pthread_mutex_init(fork + i, NULL);
	}
	i = -1;
	while (++i < 3)
	{
		if (pthread_create(&thread_t1[i], NULL, test, (void *)fork))
		{
			perror("thread create error:");
			exit(0);
		}
		pthread_detach(thread_t1[i]);
		usleep(100);
	}
	// pthread_join(&thread_t1, NULL);
	// pthread_mutex_lock(&mutex);
}