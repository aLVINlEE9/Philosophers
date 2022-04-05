/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:49:58 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/05 10:13:51 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	long long	ret;
	long long	p;

	ret = 0;
	p = 1;
	while (*str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			p *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += (p * (*str - '0'));
		str++;
	}
	return ((int)ret);
}

int	valid_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			exit(exception_print("invalid parameter(not a number)"));
	return (ft_atoi(str));
}

void	init_info(int argc, char **argv, t_info *info)
{
	info->number_of_philosophers = valid_check(argv[1]);
	info->time_to_die = valid_check(argv[2]);
	info->time_to_eat = valid_check(argv[3]);
	info->time_to_sleep = valid_check(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = valid_check(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
}

void	parsing(int argc, char **argv, t_info *info)
{
	if (argc == 5 || argc == 6)
		init_info(argc, argv, info);
	else
		exit(exception_print("invalid parameter"));
}
