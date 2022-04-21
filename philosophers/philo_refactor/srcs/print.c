/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:03:06 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 20:45:12 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(int err_type)
{
	printf("%s", "Error : ");
	if (err_type == ERR_PARSING)
		printf("%s\n", "bad arguments");
	else if (err_type == ERR_MALLOC)
		printf("%s\n", "memory error(failed to malloc)");
	else if (err_type == ERR_THREAD)
		printf("%s\n", "thread error(failed to create thread");
	return (1);
}

int	print_message(t_philo *philo, int msg_type)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lldms\t%d\t", get_time() - philo->data->start_time, philo->id);
	if (msg_type == FORK)
		printf("%s\n", "has taken a fork");
	else if (msg_type == EAT)
		printf("%s\n", "is eating");
	else if (msg_type == SLEEP)
		printf("%s\n", "is sleeping");
	else if (msg_type == THINK)
		printf("%s\n", "is thinking");
	else if (msg_type == DIE)
		printf("%s\n", "died");
	pthread_mutex_unlock(&philo->print_mutex);
	return (0);
}
