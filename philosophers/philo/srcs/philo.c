/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:07:23 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 02:23:24 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	if (pthread_create(&philo->moniter_tid, NULL, moniter, (void *)(philo)))
		return ((void *)exception_print("thread error\
				(failed to create thread"));
	pthread_detach(&philo->moniter_tid);
	while (philo->info->done_philo < philo->info->num_of_philo)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

int	run_philosopher(t_info *info)
{
	int			i;

	i = -1;
	while (++i < info->num_of_philo)
		if (pthread_create(&info->philos[i].tid, NULL, routine, \
			(void *)(&info->philos[i])))
			return (exception_print("thread error(failed to create thread)"));
	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(&info->philos[i].tid, NULL);
}
