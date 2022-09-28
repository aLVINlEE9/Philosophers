/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 23:33:47 by seungsle          #+#    #+#             */
/*   Updated: 2022/09/28 17:40:23 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_take_fork(t_philo *philo)
{
	if (philo->data->num_of_philo == 1)
	{
		sem_wait(philo->data->fork_sem);
		print_message(philo, FORK);
		while (!philo->is_done)
			usleep(1000);
		sem_post(philo->data->fork_sem);
	}
	else
	{
		sem_wait(philo->data->fork_sem);
		print_message(philo, FORK);
		sem_wait(philo->data->fork_sem);
		print_message(philo, FORK);
	}
}

void	philo_eat(t_philo *philo)
{
	print_message(philo, EAT);
	philo->limit_time = get_time() + philo->data->time_to_die;
	delay_time(philo->data->time_to_eat);
	if (philo->data->num_of_must_eat != -1)
		philo->data->routine_count++;
}

void	philo_clean_fork(t_philo *philo)
{
	sem_post(philo->data->fork_sem);
	sem_post(philo->data->fork_sem);
}

void	philo_sleep_think(t_philo *philo)
{
	print_message(philo, SLEEP);
	delay_time(philo->data->time_to_sleep);
	print_message(philo, THINK);
}
