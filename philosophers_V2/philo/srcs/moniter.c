/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:33:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 19:22:54 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_moniter(t_data *data, int cnt)
{
	if (cnt == data->num_of_philo)
	{
		pthread_mutex_lock(data->main_lock);
		data->is_dead = 0;
		pthread_mutex_unlock(data->main_lock);
	}
}

void	dead_moniter(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_lock);
	if (philo->is_done)
	{
		if (get_time() - philo->eat_time >= philo->data->time_to_die)
		{
			pthread_mutex_lock(philo->data->main_lock);
			printf("%lld %d %s\n", get_time() - philo->data->start_time, \
					philo->id, "died");
			philo->data->is_dead = 0;
			pthread_mutex_unlock(philo->data->main_lock);
		}
	}
	pthread_mutex_unlock(philo->philo_lock);
}

void	monitering(t_data *data)
{
	int		i;
	int		cnt;

	while (data->is_dead)
	{
		i = 0;
		cnt = 0;
		while (i < data->num_of_philo && data->is_dead)
		{
			dead_moniter(&data->philo[i]);
			pthread_mutex_lock(data->philo[i].philo_lock);
			if (data->philo[i].is_done == 0)
				cnt++;
			pthread_mutex_unlock(data->philo[i].philo_lock);
			i++;
		}
		eat_moniter(data, cnt);
	}
}
