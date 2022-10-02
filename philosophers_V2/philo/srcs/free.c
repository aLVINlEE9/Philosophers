/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:32:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/02 19:28:57 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_array_philo(t_philo *philo, int idx)
{
	int	i;

	i = -1;
	idx++;
	while (++i < idx)
		free(philo[i].philo_lock);
}

int	free_util(t_data *data, int free_type, int idx)
{
	if (free_type == FREE_PHILO_LOCK)
	{
		free_array_philo(data->philo, idx);
		free_type -= 1;
	}
	if (free_type == FREE_FORKS)
	{
		free(data->forks);
		free_type -= 1;
	}
	if (free_type == FREE_PHILO)
	{
		free(data->philo);
		free_type -= 1;
	}
	if (free_type == FREE_MAIN_LOCK)
	{
		free(data->main_lock);
		free_type -= 1;
	}
	if (free_type == FREE)
		return (1);
	return (1);
}
