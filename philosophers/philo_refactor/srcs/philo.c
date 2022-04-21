/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:14:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 21:11:34 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&philo->data->fork_mutex[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->data->fork_mutex[philo->r_fork]);
	print_message(philo, FORK);
	if (philo->id % 2)
		pthread_mutex_lock(&philo->data->fork_mutex[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->data->fork_mutex[philo->l_fork]);
	print_message(philo, FORK);
}

void	philo_eat(t_philo *philo)
{
	print_message(philo, EAT);
	philo->limit_time = get_time() + philo->data->time_to_die;
	philo->is_eating = TRUE;
	delay_time(philo->data->time_to_eat);
}

void	philo_clean_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->r_fork]);
}

void	philo_sleep(t_philo *philo)
{
	print_message(philo, SLEEP);
	delay_time(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_message(philo, THINK);
}
