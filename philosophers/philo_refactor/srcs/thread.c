/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:54:45 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/22 15:25:41 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_resources(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->stop_mutex);
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		pthread_mutex_destroy(&data->philo[i].moniter_mutex);
		pthread_mutex_destroy(&data->philo[i].print_mutex);
		pthread_mutex_destroy(&data->philo[i].eat_mutex);
		pthread_mutex_destroy(&data->philo[i].time_mutex);
	}
	free(data->fork_mutex);
	free(data->philo);
}

void	*moniter(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	while (1)
	{
		if (philo->is_eating == TRUE && \
			get_time() > philo->limit_time)
		{
			philo->is_dead = TRUE;
			philo->data->is_dead = TRUE;
			pthread_mutex_lock(&philo->moniter_mutex);
			print_message(philo, DIE);
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
	}
	return ((void *)0);
}

void	*routine(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	if (pthread_create(&philo->moniter_tid, NULL, moniter, (void *)philo))
	{
		print_error(ERR_THREAD);
		return ((void *)0);
	}
	pthread_detach(philo->moniter_tid);
	while (1)
	{
		if (philo->is_dead == TRUE)
			break ;
		philo_take_fork(philo);
		philo_eat(philo);
		if (philo_eat_check(philo))
			break ;
		philo_clean_fork(philo);
		philo_sleep_and_think(philo);
	}
	return ((void *)0);
}

int	start_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	pthread_mutex_lock(&data->stop_mutex);
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philo[i].tid, NULL, routine, \
						(void *)&(data->philo[i])))
			return (print_error(ERR_THREAD));
		pthread_detach(data->philo[i].tid);
	}
	pthread_mutex_lock(&data->stop_mutex);
	free_resources(data);
	return (0);
}
