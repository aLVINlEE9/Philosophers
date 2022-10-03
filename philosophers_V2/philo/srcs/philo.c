/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:46:19 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/03 12:36:03 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	one_philo_case(t_data *data)
{
	
	return (1);
}

void	think(t_philo *philo)
{
	if (dead_check(philo))
	{
		printf("%lldms\t%d\t%s\n", get_time() - philo->data->start_time, \
				philo->id, "is thinking");
	}
}

void	sleep(t_philo *philo)
{
	u_int64_t	sleep_start;
	
	if (dead_check(philo))
	{
		sleep_start = get_time();
		printf("%lldms\t%d\t%s\n", get_time() - philo->data->start_time, \
				philo->id, "is sleeping");
		while (get_time() - sleep_start >= philo->data->time_to_sleep)
			usleep(100);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_lock);
	philo->eat_time = get_time();
	pthread_mutex_unlock(philo->philo_lock);
	if (dead_check(philo))
	{
		printf("%lldms\t%d\t%s\n", get_time() - philo->data->start_time, \
				philo->id, "is eating");
		while (get_time() - philo->eat_time >= philo->data->time_to_eat)
			usleep(100);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (dead_check(philo))
	{
		printf("%lldms\t%d\t%s\n", get_time() - philo->data->start_time, \
				philo->id, "has taken a fork");
	}
	else
		return ;
	pthread_mutex_lock(philo->r_fork);
	if (dead_check(philo))
	{
		printf("%lldms\t%d\t%s\n", get_time() - philo->data->start_time, \
				philo->id, "has taken a fork");
	}
	else
		return ;
}