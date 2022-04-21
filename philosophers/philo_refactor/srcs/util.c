/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:49:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 23:33:08 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	correct_time(t_philo *philo)
{
	uint64_t	main_thread_time;
	uint64_t	sub_thread_time;

	pthread_mutex_lock(&philo->time_mutex);
	main_thread_time = philo->data->main_time;
	sub_thread_time = get_time();
	if (main_thread_time < sub_thread_time)
		return (main_thread_time);
	else
		return (sub_thread_time);
	pthread_mutex_unlock(&philo->time_mutex);
}

void	delay_time(t_philo *philo, uint64_t time)
{
	uint64_t	limit;

	limit = correct_time(philo) + time;
	while (get_time() < limit)
		usleep(10);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000));
}

uint64_t	ft_atou64(const char *str)
{
	uint64_t	ret;
	uint64_t	p;

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
	return ((uint64_t)ret);
}
