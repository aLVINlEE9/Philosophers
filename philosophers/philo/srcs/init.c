/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:37:08 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/23 20:16:10 by seungsle         ###   ########.fr       */
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
			if (argv[i][j] < 'a' || argv[i][j] > 'z')
				return (1);
			j++;
		}
		i++;
	}
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
	}
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
	data->time_tos_sleep = ft_atou64(argv[4]);
	if (argc == 6)
		data->num_of_must_eat = ft_atou64(argv[5]);
	else
		data->num_of_must_eat = -1;
	data->philo = NULL;
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
	}
	else
		return (print_error(ERR_ARGS));
	return (0);
}
