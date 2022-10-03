/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:32:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/03 13:50:33 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	join_array_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			print_error("join error");
	}
	return (data->num_of_philo);
}

int	free_array_philo(t_data *data, int idx)
{
	int	i;

	i = -1;
	while (++i < idx)
	{
		if (pthread_mutex_destroy(data->philo[i].philo_lock))
			print_error("mutex destroy error");
		free(data->philo[i].philo_lock);
	}
	return (data->num_of_philo);
}

int	free_array_fork(t_data *data, int idx)
{
	int i;

	i = -1;
	while (++i < idx)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			print_error("mutex destroy error");
	}
	free(data->forks);
	return (data->num_of_philo);
}

int	free_util(t_data *data, int free_type, int idx)
{
	if (free_type == RELEASE_RESOURCES)
	{
		idx = join_array_philo(data);
		free_type -= 1;
	}
	if (free_type == FREE_PHILO_LOCK)
	{
		idx = free_array_philo(data, idx);
		free_type -= 1;
	}
	if (free_type == FREE_FORKS)
	{
		idx = free_array_fork(data, idx);
		free_type -= 1;
	}
	if (free_type == FREE_PHILO)
	{
		free(data->philo);
		pthread_mutex_destroy(data->main_lock);
		free_type -= 1;
	}
	if (free_type == FREE_MAIN_LOCK)
		free(data->main_lock);
	return (1);
}
