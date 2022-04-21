/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:54:45 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 20:59:26 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	main_thread_time_updater(t_data *data)
{
	while (1)
	{
		data->now_time = get_time();
		usleep(10);
	}
}

void	*moniter(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	while (1)
	{
		
	}
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
		philo_take_fork(philo);
		philo_eat(philo);
		philo_clean_fork(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

int	start_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philo[i].tid, NULL, routine, \
						(void *)&(data->philo[i])))
			return (print_error(ERR_THREAD));
		pthread_detach(data->philo[i].tid);
	}
	main_thread_time_updater(data);
}
