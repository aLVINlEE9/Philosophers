/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:01:42 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:03:50 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	eat_check(t_philo *philo)
{
	if (philo->data->num_of_must_eat != -1 && philo->eat_count == \
		philo->data->num_of_must_eat)
		return (1);
	else
		return (0);
}

int	dead_check(t_philo *philo)
{
	if (!philo->data->is_dead || !philo->is_done)
		return (0);
	else
		return (1);
}

void	*moniter(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	sem_wait(philo->philo_lock);
	if (philo->is_done)
	{
		if (get_time() - philo->eat_time >= philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%lld %d %s\n", get_time() - philo->data->start_time, \
					philo->id, "died");
			philo->data->is_dead = 0;
			sem_post(philo->data->print);
		}
	}
	sem_post(philo->philo_lock);
}

void	process(t_philo *philo)
{
	if (pthread_create(&philo->moniter, NULL, moniter, (void *)&philo))
		return (print_error("create thread error"));
	if (philo->id % 2)
		usleep(800);
	while (dead_check(philo))
	{
		take_forks(philo);
		philo_eat(philo);
		put_down_forks(philo);
		philo->eat_count++;
		if (eat_check(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
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