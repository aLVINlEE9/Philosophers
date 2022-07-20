/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 23:15:17 by seungsle          #+#    #+#             */
/*   Updated: 2022/05/03 00:43:00 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	release_resources(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->fork_mutex[i]);
	pthread_mutex_destroy(data->moniter_mutex);
	pthread_mutex_destroy(data->print_mutex);
	pthread_mutex_destroy(data->stop_mutex);
	free(data->fork_mutex);
	free(data->moniter_mutex);
	free(data->print_mutex);
	free(data->stop_mutex);
}

int	eat_moniter(t_philo *philo)
{
	pthread_mutex_lock(philo->data->moniter_mutex);
	if (philo->data->num_of_must_eat != -1 && \
		philo->data->max_count <= philo->data->routine_count)
	{
		philo->is_done = TRUE;
		print_message(philo, DONE);
		pthread_mutex_unlock(philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->moniter_mutex);
	return (0);
}

void	*moniter(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(philo->data->moniter_mutex);
		if (get_time() > philo->limit_time)
		{
			philo->is_done = TRUE;
			print_message(philo, DIED);
			pthread_mutex_unlock(philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->data->moniter_mutex);
	}
	return ((void *)0);
}

void	*routine(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	philo->limit_time = philo->data->start_time + philo->data->time_to_die;
	if (pthread_create(&philo->moniter, NULL, moniter, (void *)philo))
	{
		print_error(ERR_CTHREAD);
		return ((void *)0);
	}
	pthread_detach(philo->moniter);
	while (1)
	{
		if (philo->is_done == TRUE)
			break ;
		philo_take_fork(philo);
		philo_eat(philo);
		if (eat_moniter(philo))
			break ;
		philo_clean_fork(philo);
		philo_sleep_think(philo);
	}
	return ((void *)0);
}

int	start_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	pthread_mutex_lock(data->stop_mutex);
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&data->philo[i].tid, NULL, routine, \
							(void *)&data->philo[i]))
			return (print_error(ERR_CTHREAD));
		pthread_detach(data->philo[i].tid);
		usleep(100);
	}
	pthread_mutex_lock(data->stop_mutex);
	release_resources(data);
	return (0);
}
