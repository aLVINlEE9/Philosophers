/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:39:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 01:32:30 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*moniter(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	while (philo->info->done_philo < philo->info->num_of_philo)
	{
		pthread_mutex_lock(&philo->moniter);
		if (get_time() > philo->limit)
		{
			pthread_mutex_unlock(&philo->moniter);
			break ;
		}
		pthread_mutex_unlock(&philo->moniter);
	}
}
