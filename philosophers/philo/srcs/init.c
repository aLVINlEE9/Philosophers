/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:49:58 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 01:23:23 by seungsle         ###   ########.fr       */
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

void	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		info->philos[i].info = info;
		info->philos[i].position = i + 1;
		info->philos[i].r_fork = i + 1;
		info->philos[i].l_fork = (i + 2) % info->num_of_philo;
		info->philos[i].routine_times = 0;
		info->philos[i].limit = 0;
		pthread_mutex_init(&info->philos[i].moniter, NULL);
	}
}

int	init_info_sub(t_info *info)
{
	t_philo			*philos;
	pthread_mutex_t	*fork_m;
	int				i;

	i = -1;
	philos = (t_philo *)malloc(sizeof(philos) * info->num_of_philo);
	if (philos == NULL)
		return (exception_print("memory error(failed to malloc)"));
	info->philos = philos;
	fork_m = (pthread_mutex_t *)malloc(sizeof(fork_m) * info->num_of_philo);
	if (fork_m == NULL)
		return (exception_print("memory error(failed to malloc"));
	info->fork_m = fork_m;
	while (++i < info->num_of_philo)
		pthread_mutex_init(&info->fork_m[i], NULL);
	pthread_mutex_init(&info->print, NULL);
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
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
	info->done_philo = 0;
	if (init_info_sub(info))
		return (1);
	init_philos(info);
	return (0);
}
