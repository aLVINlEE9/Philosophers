/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:29:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 16:55:06 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(int argc, char **argv, t_data *data)
{
	if (args_check(argc, argv))
		return (print_error("bad arguments"));
	data->num_of_philo = ft_atou64(argv[1]);
	data->time_to_die = ft_atou64(argv[2]);
	data->time_to_eat = ft_atou64(argv[3]);
	data->time_to_sleep = ft_atou64(argv[4]);
	data->num_of_must_eat = -1;
	data->is_dead = 1;
	if (argc == 6)
		data->num_of_must_eat = ft_atou64(argv[5]);
	if (data->num_of_philo < 1)
		return (print_error("bad arguments"));
	if (data->num_of_philo == 1)
		return (one_philo_case(data->time_to_die));
	data->main_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->main_lock)
		return (print_error("malloc error") && \
				free_util(data, FREE_MAIN_LOCK, FREE, -1));
	if (pthread_mutex_init(data->main_lock, NULL))
		return (print_error("mutex init error") && \
				free_util(data, FREE_MAIN_LOCK, DESTROY, -1));
	return (0);
}

int	init_forks(t_data *data)
{
	int				i;

	i = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
					* data->num_of_philo);
	if (!data->forks)
		return (print_error("malloc error") && \
				free_util(data, FREE_FORKS, FREE, -1));
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (print_error("mutex init error") && \
					free_util(data, FREE_FORKS, DESTROY, i));
	return (0);
}

int	create_philo(t_data *data)
{
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (print_error("malloc error") && \
				free_util(data, FREE_PHILO, FREE, -1));
	if (init_forks(data))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int				i;

	i = -1;
	if (create_philo(data))
		return (1);
	while (++i < data->num_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].eat_time = 0;
		data->philo[i].sleep_time = 0;
		data->philo[i].eat_count = 0;
		data->philo[i].is_done = 1;
		data->philo[i].l_fork = &data->forks[(i + 1) % data->num_of_philo];
		data->philo[i].r_fork = &data->forks[i];
		data->philo[i].philo_lock = \
				(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data->philo[i].philo_lock)
			return (print_error("malloc error") && \
					free_util(data, FREE_PHILO_LOCK, FREE, i));
		if (pthread_mutex_init(data->philo[i].philo_lock, NULL))
			return (print_error("mutex error") && \
					free_util(data, FREE_PHILO_LOCK, DESTROY, i));
		data->philo[i].data = data;
	}
	return (0);
}

int	init(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		if (init_data(argc, argv, data))
			return (1);
		if (init_philo(data))
			return (1);
	}
	else
		return (print_error("bad arguments"));
	return (0);
}
