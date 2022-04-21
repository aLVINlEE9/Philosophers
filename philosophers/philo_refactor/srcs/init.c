/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:49:35 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 21:08:13 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
	}
}

void	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		pthread_mutex_init(&data->philo[i].print_mutex, NULL);
	}
}

int	init_philo(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (data->philo == NULL)
		return (print_error(ERR_MALLOC));
	i = -1;
	while (++i < data->philo_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->philo_num;
		data->philo[i].is_eating = FALSE;
		data->philo[i].limit_time = 0;
		data->philo[i].data = data;
	}
}

int	init_data(int argc, char **argv, t_data *data)
{
	if ((argc == 5 || argc == 6) && check_num(argc, argv))
	{
		data->philo_num = ft_atou64(argv[1]);
		if (data->philo_num < 2)
			return (print_error(ERR_PARSING));
		data->time_to_die = ft_atou64(argv[2]);
		data->time_to_eat = ft_atou64(argv[3]);
		data->time_to_sleep = ft_atou64(argv[4]);
		if (argc == 6)
			data->num_of_must_eat = ft_atou64(argv[5]);
		else
			data->num_of_must_eat = -1;
	}
	else
		return (print_error(ERR_PARSING));
	data->start_time = 0;
	data->now_time = 0;
	data->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
					* data->philo_num);
	if (data->fork_mutex == NULL)
		return (print_error(ERR_MALLOC));
	data->philo = NULL;
	return (0);
}

int	init(int argc, char **argv, t_data *data)
{
	if (init_data(argc, argv, data))
		return (1);
	if (init_philo(data))
		return (1);
	mutex_init(data);
	return (0);
}
