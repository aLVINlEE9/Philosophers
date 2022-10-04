/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:46:19 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 19:20:31 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	one_philo_case(uint64_t time)
{
	printf("%d %d has taken a fork\n", 0, 1);
	usleep(time * 1000);
	printf("%lld %d died\n", time, 1);
	return (1);
}

void	philo_think(t_philo *philo)
{
	if (dead_check(philo))
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "is thinking");
		if (philo->data->num_of_philo % 2)
			while (get_time() - philo->sleep_time <= \
					(uint64_t)philo->data->num_of_philo * 2 && dead_check(philo))
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
		while (get_time() - philo->sleep_time <= philo->data->time_to_sleep && dead_check(philo))
			usleep(100);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_lock);
	philo->eat_time = get_time();
	pthread_mutex_unlock(philo->philo_lock);
	if (dead_check(philo))
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "is eating");
		while (get_time() - philo->eat_time <= philo->data->time_to_eat && dead_check(philo))
			usleep(100);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (dead_check(philo))
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "has taken a fork");
	}
	else
		return ;
	pthread_mutex_lock(philo->r_fork);
	if (dead_check(philo))
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "has taken a fork");
	}
	else
		return ;
}