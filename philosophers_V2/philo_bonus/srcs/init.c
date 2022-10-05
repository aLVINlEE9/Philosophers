/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:18:32 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:33:34 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int init_sem(t_data *data)
{
	int	i;

	i = -1;
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("main_lock");
	data->fork = sem_open("fork", O_CREAT, 0644, data->num_of_philo);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->main_lock = sem_open("main_lock", O_CREAT, 0644, 1);
	while (++i < data->num_of_philo)
	{
		sem_unlink(data->philo[i].sem_name);
		data->philo[i].philo_lock = sem_open(data->philo[i].sem_name, \
										O_CREAT, 0644, data->num_of_philo);
	}
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (args_check(argc, argv))
		return (print_error("bad arguments"));
	data->num_of_philo = ft_atou64(argv[1]);
	data->time_to_die = ft_atou64(argv[2]);
	data->time_to_eat = ft_atou64(argv[3]);
	data->time_to_sleep = ft_atou64(argv[4]);
	data->num_of_must_eat = -1;
	data->start_time = 0;
	data->is_dead = 0;
	if (argc == 6)
		data->num_of_must_eat = ft_atou64(argv[5]);
	if (data->num_of_philo < 1)
		return (print_error("bad arguments"));
	if (data->num_of_philo == 1)
		return (one_philo_case(data->time_to_die));
    data->philo = NULL;
	return (0);
}

int init_philo(t_data *data)
{
	int	i;

	i = -1;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (print_error("malloc error"));
	while (++i < data->num_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].sleep_time = 0;
		data->philo[i].eat_time = 0;
		data->philo[i].eat_count = 0;
		data->philo[i].is_done = 1;
		data->philo[i].last_eat_time = 0;
		data->philo[i].sem_name = ft_strjoin("philo_lock_", ft_itoa(i));
		data->philo[i].data = data;
	}
}

int	init(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		if (init_data(argc, argv, data))
			return (1);
		if (init_philo(data))
			return (1);
		if (init_sem(data))
			return (1);
	}
	else
		return (print_error("bad arguments"));
	return (0);
}
