/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:41:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/23 19:47:37 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(int err_type)
{
	if (err_type == ERR_MALLOC)
		printf("memory error(failed to malloc)\n");
	else if (err_type == ERR_CTHREAD)
		printf("thread error(failed to create thread\n");
	else if (err_type == ERR_ARGS)
		printf("bad arguments\n");
	return (1);
}
