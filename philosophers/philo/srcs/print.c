/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/24 01:19:39 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(int err_type)
{
	if (err_type == ERR_MALLOC)
		printf("memory error(failed to malloc)\n");
	else if (err_type == ERR_CTHREAD)
		printf("thread error(failed to create thread\n");
	else if (err_type == ERR_ARGS)
		printf("bad arguments\n");
	return (1);
}

void	print_message(t_philo *philo, int msg_type)
{
	uint64_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->print_mutex);
	if (msg_type == FORK)
		printf("%lldms\t%d\t%s\n", time, philo->id, "has taken a fork");
	if (msg_type == EAT)
		printf("%lldms\t%d\t%s\n", time, philo->id, "is eating");
	if (msg_type == SLEEP)
		printf("%lldms\t%d\t%s\n", time, philo->id, "is sleeping");
	if (msg_type == THINK)
		printf("%lldms\t%d\t%s\n", time, philo->id, "is thinking");
	if (msg_type == DIED)
		printf("%lldms\t%d\t%s\n", time, philo->id, "died");
	if (msg_type == DONE)
		printf("%s\n", "done!");
	if (msg_type != DIED && msg_type != DONE)
		pthread_mutex_unlock(philo->data->print_mutex);
}
