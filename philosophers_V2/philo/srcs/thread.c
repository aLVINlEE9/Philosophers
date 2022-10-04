/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:28:46 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 19:20:39 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat_check(t_philo *philo)
{
	if (philo->eat_count == philo->data->num_of_must_eat)
	{
		pthread_mutex_lock(philo->philo_lock);
		philo->is_done = 0;
		pthread_mutex_unlock(philo->philo_lock);
		return (1);
	}
	return (0);
}

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(philo->data->main_lock);
	if (!philo->data->is_dead)
	{
		pthread_mutex_unlock(philo->data->main_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->data->main_lock);
	return (1);
}

void	*thread(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	if (philo->id % 2)
		usleep(800);
	while (dead_check(philo))
	{
		take_forks(philo);
		philo_eat(philo);
		put_down_forks(philo);
		philo->eat_count++;
		if (eat_check(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_of_philo)
	{
		data->philo[i].eat_time = get_time();
		if (pthread_create(&data->philo[i].thread, NULL, thread, \
						(void *)&data->philo[i]))
			return (print_error("create thread error"));
	}
	return (0);
}