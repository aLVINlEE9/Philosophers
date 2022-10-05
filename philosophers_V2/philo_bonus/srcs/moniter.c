/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:15:30 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:22:35 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	eat_moniter(t_philo *philo)
{
	sem_wait(philo->philo_lock);
	if (philo->eat_count == philo->data->num_of_must_eat)
	{
		philo->is_done = 0;
		sem_post(philo->philo_lock);
		return (1);
	}
	sem_post(philo->philo_lock);
	return (0);
}

int	dead_moniter(t_philo *philo)
{
	sem_wait(philo->philo_lock);
	if (get_time() - philo->eat_time >= philo->data->time_to_die)
	{
		sem_wait(philo->data->print);
		printf("%lld %d %s\n", get_time() - philo->data->start_time, \
				philo->id, "died");
		philo->data->is_dead = 0;
		sem_post(philo->data->print);
		return (1);
	}
	sem_post(philo->philo_lock);
	return (0);
}

void	*monitering(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		if (dead_moniter(philo))
			break ;
		if (eat_moniter(philo))
			break ;
	}
	return (NULL);
}