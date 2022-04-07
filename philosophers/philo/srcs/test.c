/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:11:32 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/07 17:33:31 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*t_func(void *data)
{
	char	a[10000];
	static int	num;

	num = *((int *)data);
	printf("Thread Start\n");
	sleep(5);
	printf("Thread End\n");
	return ((void *)&num);
}

int	main(void)
{
	pthread_t p_thread;
	int thr_id;
	int status;
	int	a;

	a = 100;
	printf("Before Thread\n");
	thr_id = pthread_create(&p_thread, NULL, t_func, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	// pthread_detach(p_thread);
	pause();
	return (0);
}