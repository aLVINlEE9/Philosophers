/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:03:06 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 17:21:10 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(int err_type)
{
	printf("%s", "Error : ");
	if (err_type == ERR_PARSING)
		printf("%s\n", "bad arguments");
	else if (err_type == ERR_MALLOC)
		printf("%s\n", "memory error(failed to malloc)");
	else if (err_type == ERR_THREAD)
		printf("%s\n", "thread error(failed to create thread");
	return (1);
}
