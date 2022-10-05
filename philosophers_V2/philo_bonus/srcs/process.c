/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:01:42 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:25:27 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	dead_check(t_philo *philo)
{
	if (!philo->data->is_dead || !philo->is_done)
		return (0);
	else
		return (1);
}

void	process(t_philo *philo)
{
	if (pthread_create(&philo->moniter, NULL, monitering, (void *)&philo))
		return (print_error("create thread error"));
	if (philo->id % 2)
		usleep(800);
	while (dead_check(philo))
	{
		take_forks(philo);
		philo_eat(philo);
		put_down_forks(philo);
		philo->eat_count++;
		if (dead_check(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_join(philo->moniter, NULL);
}

int	start_process(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_of_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			process((void *)&data->philo[i]);
		else
			return (print_error("fork error"));
	}
	return (0);
}