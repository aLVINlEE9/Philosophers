/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 23:15:17 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/24 23:18:34 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	release_resources(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		kill(data->philo[i].pid, SIGKILL);
	sem_close(data->fork_sem);
	sem_close(data->moniter_sem);
	sem_close(data->print_sem);
	sem_close(data->stop_sem);
	free(data->philo);
}

void	*moniter(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		sem_wait(philo->data->moniter_sem);
		if (get_time() > philo->limit_time)
		{
			print_message(philo, DIED);
			sem_post(philo->data->stop_sem);
			break ;
		}
		sem_post(philo->data->moniter_sem);
		sem_wait(philo->data->moniter_sem);
		if (philo->data->num_of_must_eat != -1 && \
			philo->data->max_count <= philo->data->routine_count)
		{
			print_message(philo, DONE);
			sem_post(philo->data->stop_sem);
			break ;
		}
		sem_post(philo->data->moniter_sem);
	}
	return ((void *)0);
}

void	routine(t_philo *philo)
{
	philo->limit_time = philo->data->start_time + philo->data->time_to_die;
	if (pthread_create(&philo->moniter, NULL, moniter, (void *)philo))
		print_error(ERR_CTHREAD);
	pthread_detach(philo->moniter);
	while (1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_clean_fork(philo);
		philo_sleep_think(philo);
	}
}

int	start_process(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	sem_wait(data->stop_sem);
	while (++i < data->num_of_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
		{
			routine(&data->philo[i]);
			exit(0);
		}
		usleep(100);
	}
	sem_wait(data->stop_sem);
	release_resources(data);
	return (0);
}
