/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:07:23 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 14:01:30 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_exit(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&info->fork_m[i]);
	i = -1;
	pthread_mutex_destroy(&info->moniter);
	pthread_mutex_destroy(&info->print);
	free(info->philos);
	free(info->fork_m);
}

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
			philo->info->num_of_philo = 0;
			break ;
		}
		pthread_mutex_unlock(&philo->info->moniter);
	}
	return ((void *)0);
}

void	*routine(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	if (pthread_create(&philo->moniter_tid, NULL, moniter, (void *)(philo)))
	{
		exception_print("thread errorfailed to create thread");
		return ((void *)0);
	}
	pthread_detach(philo->moniter_tid);
	while (philo->info->done_philo < philo->info->num_of_philo)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
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
		pthread_join(info->philos[i].tid, NULL);
	free_exit(info);
	return (0);
}
