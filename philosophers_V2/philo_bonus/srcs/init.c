/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:18:32 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 20:27:57 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int init_sem(t_data *data)
{
    sem_unlink("table");
	sem_unlink("fork");
	sem_unlink("start");
	sem_unlink("print");
    data->table = sem_open("table", O_CREAT, 0644, data->num_of_philo);
	data->fork = sem_open("fork", O_CREAT, 0644, data->num_of_philo);
	data->start = sem_open("start", O_CREAT, 0644, 1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
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
	if (argc == 6)
		data->num_of_must_eat = ft_atou64(argv[5]);
	if (data->num_of_philo < 1)
		return (print_error("bad arguments"));
	if (data->num_of_philo == 1)
		return (one_philo_case(data->time_to_die));
	init_sem(data);
    data->pid = (pid_t *)malloc(sizeof(pid_t) * data->num_of_philo);
    if (!data->pid)
        return (print_error("malloc error"));
    data->philo = NULL;
	return (0);
}

int init_philo(t_data *data)
{
    data->philo = (t_philo *)malloc(sizeof(t_philo) * )
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
