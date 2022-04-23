/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:37:08 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/24 00:59:42 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
												* data->num_of_philo);
	if (data->fork_mutex == NULL)
		return (print_error(ERR_MALLOC));
	data->moniter_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (data->moniter_mutex == NULL)
		return (print_error(ERR_MALLOC));
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (data->print_mutex == NULL)
		return (print_error(ERR_MALLOC));
	data->stop_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (data->stop_mutex == NULL)
		return (print_error(ERR_MALLOC));
	while (++i < data->num_of_philo)
		pthread_mutex_init(data->fork_mutex + 1, NULL);
	pthread_mutex_init(data->moniter_mutex, NULL);
	pthread_mutex_init(data->print_mutex, NULL);
	pthread_mutex_init(data->stop_mutex, NULL);
	return (0);
}

int	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (philo == NULL)
		return (print_error(ERR_MALLOC));
	data->philo = philo;
	while (++i < data->num_of_philo)
	{
		philo->data = data;
		philo->id = i + 1;
		philo->l_fork = i;
		philo->r_fork = (i + 1) % data->num_of_philo;
		philo->is_done = FALSE;
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
	data->fork_mutex = NULL;
	data->print_mutex = NULL;
	data->stop_mutex = NULL;
	data->philo = NULL;
	return (0);
}

int	init(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data = (t_data *)malloc(sizeof(t_data));
		if (data == NULL)
			return (print_error(ERR_MALLOC));
		if (init_data(argc, argv, data))
			return (1);
		if (init_philo(data))
			return (1);
		if (init_mutex(data))
			return (1);
	}
	else
		return (print_error(ERR_ARGS));
	return (0);
}
