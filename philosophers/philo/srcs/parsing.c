/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:49:58 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/05 20:36:17 by seungsle         ###   ########.fr       */
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
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (exception_print("bad arguments(not a number)"));
	}
	return (0);
}

int	valid_num_check(int argc, t_info *info)
{
	if (info->number_of_philosophers < 2)
		return (exception_print("bad arguments(number_of_philosophers)"));
	if (info->time_to_die < 0)
		return (exception_print("bad arguments(time_to_die)"));
	if (info->time_to_eat < 0)
		return (exception_print("bad arguments(time_to_eat)"));
	if (info->time_to_sleep < 0)
		return (exception_print("bad arguments(time_to_sleep)"));
	if (argc == 6 && info->number_of_times_each_philosopher_must_eat < 1)
		return (exception_print("bad arguments\
(number_of_times_each_philosopher_must_eat)"));
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	if (valid_arg_check(argc, argv))
		return (1);
	info->number_of_philosophers = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	if (valid_num_check(argc, info))
		return (1);
	return (0);
}
