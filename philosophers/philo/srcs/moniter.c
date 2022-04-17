/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:39:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 02:22:08 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*moniter(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	while (philo->info->done_philo < philo->info->num_of_philo)
	{
		pthread_mutex_lock(&philo->info->moniter);
		if (get_time() > philo->limit)
		{
			message_print(philo, DIED);
			pthread_mutex_unlock(&philo->info->moniter);
			break ;
		}
		pthread_mutex_unlock(&philo->info->moniter);
	}
	return ((void *)0);
}
