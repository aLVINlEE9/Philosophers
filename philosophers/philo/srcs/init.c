/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:49:58 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/14 16:57:24 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	valid_arg_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (exception_print("bad arguments(not a number)"));
			j++;
		}
	}
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		info->philos[i].info = info;
		info->philos[i].status = THINKING;
		info->philos[i].routine_times = 0;
		info->philos[i].last_eat = 0;
		pthread_mutex_init(&info->philos[i].mutex, NULL);
	}
}

int	init_info(int argc, char **argv, t_info *info)
{
	t_philo	*philos;

	if (valid_arg_check(argc, argv))
		return (1);
	info->num_of_philo = ft_atou64(argv[1]);
	if (info->num_of_philo < 2)
		return (exception_print("bad arguments(number_of_philosophers)"));
	info->time_to_die = ft_atou64(argv[2]);
	info->time_to_eat = ft_atou64(argv[3]);
	info->time_to_sleep = ft_atou64(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atou64(argv[5]);
	else
		info->num_of_must_eat = -1;
	philos = malloc(sizeof(philos) * info->num_of_philo);
	if (philos == NULL)
		return (exception_print("memory error(malloc failed)"));
	info->philos = philos;
	if (init_philos(info))
		return (1);
	return (0);
}
