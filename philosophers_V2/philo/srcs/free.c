/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:32:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 17:11:57 by seungsle         ###   ########.fr       */
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

int	free_array_philo(t_data *data, int idx, int df_type)
{
	int	i;
	int	idx_d;

	i = -1;
	idx_d = idx;
	if (df_type == DESTROY)
		idx_d -= 1;
	while (++i < idx_d)
		if (pthread_mutex_destroy(data->philo[i].philo_lock))
			print_error("mutex destroy error");
	i = -1;
	while (++i < idx)
		free(data->philo[i].philo_lock);
	return (data->num_of_philo);
}

int	free_array_fork(t_data *data, int idx, int df_type)
{
	int	i;

	i = -1;
	if (df_type == FREE)
		return (data->num_of_philo);
	else
	{
		while (++i < idx)
		{
			if (pthread_mutex_destroy(&data->forks[i]))
				print_error("mutex destroy error");
		}
		free(data->forks);
	}
	return (data->num_of_philo);
}

int	free_util(t_data *data, int free_type, int df_type, int idx)
{
	if (free_type == RELEASE_RESOURCES)
	{
		idx = join_array_philo(data);
		free_type -= 1;
	}
	if (free_type == FREE_PHILO_LOCK)
	{
		idx = free_array_philo(data, idx, df_type);
		free_type -= 1;
	}
	if (free_type == FREE_FORKS)
	{
		idx = free_array_fork(data, idx, df_type);
		free_type -= 1;
	}
	if (free_type == FREE_PHILO)
	{
		pthread_mutex_destroy(data->main_lock);
		free_type -= 1;
	}
	if (free_type == FREE_MAIN_LOCK)
		if (df_type == DESTROY || df_type == ALL)
			free(data->main_lock);
	return (1);
}
