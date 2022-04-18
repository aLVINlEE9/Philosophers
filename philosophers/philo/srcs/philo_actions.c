/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:51:47 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 14:19:56 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_fork(t_philo *philo)
{
	if (philo->position % 2)
		pthread_mutex_lock(&(philo->info->fork_m[philo->l_fork]));
	else
		pthread_mutex_lock(&(philo->info->fork_m[philo->r_fork]));
	message_print(philo, FORK);
	if (philo->position % 2)
		pthread_mutex_lock(&(philo->info->fork_m[philo->r_fork]));
	else
		pthread_mutex_lock(&(philo->info->fork_m[philo->l_fork]));
	message_print(philo, FORK);
}

void	philo_eat(t_philo *philo)
{
	message_print(philo, EAT);
	philo->limit = get_time() + philo->info->time_to_die;
	timer(philo->info->time_to_eat);
	philo->routine_times++;
	if (philo->routine_times == philo->info->num_of_must_eat)
		philo->info->done_philo++;
	pthread_mutex_unlock(&(philo->info->fork_m[philo->l_fork]));
	pthread_mutex_unlock(&(philo->info->fork_m[philo->r_fork]));
}

void	philo_sleep(t_philo *philo)
{
	message_print(philo, SLEEP);
	timer(philo->info->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	message_print(philo, THINKING);
}
