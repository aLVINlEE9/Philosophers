/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:03:57 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:31:02 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_think(t_philo *philo)
{
	if (dead_check(philo))
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "is thinking");
		if (philo->data->num_of_philo % 2)
			while (get_time() - philo->sleep_time <= \
					(uint64_t)philo->data->num_of_philo * 2 && \
					dead_check(philo))
				usleep(100);
	}
}

void	philo_sleep(t_philo *philo)
{	
	if (dead_check(philo))
	{
		philo->sleep_time = get_time();
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "is sleeping");
		while (get_time() - philo->sleep_time <= philo->data->time_to_sleep && \
				dead_check(philo))
			usleep(100);
	}
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->philo_lock);
	philo->eat_time = get_time();
	sem_post(philo->philo_lock);
	if (dead_check(philo))
	{
		sem_wait(philo->data->print);
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "is eating");
		sem_post(philo->data->print);
		while (get_time() - philo->eat_time <= philo->data->time_to_eat && \
				dead_check(philo))
			usleep(100);
	}
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->fork);
	if (dead_check(philo))
	{
		sem_wait(philo->data->print);
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "has taken a fork");
		sem_post(philo->data->print);
	}
	else
		return ;
	sem_wait(philo->data->fork);
	if (dead_check(philo))
	{
		sem_wait(philo->data->print);
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "has taken a fork");
		sem_post(philo->data->print);
	}
	else
		return ;
}
