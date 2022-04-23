/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:58:48 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/23 19:58:57 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
