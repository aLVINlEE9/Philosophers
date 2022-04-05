/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:49:58 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/05 10:48:22 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	valid_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
	}
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	if (valid_check(argc, argv))
		return (1);
	info->number_of_philosophers = (argv[1]);
	info->time_to_die = argv[2];
	info->time_to_eat = argv[3];
	info->time_to_sleep = argv[4];
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = argv[5];
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}
