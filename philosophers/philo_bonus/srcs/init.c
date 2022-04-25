/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:37:08 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/25 16:44:09 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	args_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_semaphore(t_data *data)
{
	sem_unlink("fork");
	sem_unlink("moniter");
	sem_unlink("print");
	sem_unlink("stop");
	data->fork_sem = sem_open("fork", O_CREAT, 0600, data->num_of_philo);
	data->moniter_sem = sem_open("moniter", O_CREAT, 0600, 1);
	data->print_sem = sem_open("print", O_CREAT, 0600, 1);
	data->stop_sem = sem_open("stop", O_CREAT, 0600, 1);
}

int	init_philo(t_data *data)
{
	int		i;

	i = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (data->philo == NULL)
		return (print_error(ERR_MALLOC));
	while (++i < data->num_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].limit_time = 0;
		data->philo[i].is_done = FALSE;
	}
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (args_check(argc, argv))
		return (print_error(ERR_ARGS));
	data->num_of_philo = ft_atou64(argv[1]);
	if (data->num_of_philo < 2)
		return (print_error(ERR_ARGS));
	data->time_to_die = ft_atou64(argv[2]);
	data->time_to_eat = ft_atou64(argv[3]);
	data->time_to_sleep = ft_atou64(argv[4]);
	if (argc == 6)
		data->num_of_must_eat = ft_atou64(argv[5]);
	else
		data->num_of_must_eat = -1;
	data->start_time = 0;
	data->routine_count = 0;
	data->max_count = data->num_of_must_eat * data->num_of_philo;
	data->fork_sem = NULL;
	data->moniter_sem = NULL;
	data->print_sem = NULL;
	data->stop_sem = NULL;
	data->philo = NULL;
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
		init_semaphore(data);
	}
	else
		return (print_error(ERR_ARGS));
	return (0);
}
