/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:18:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:45:07 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	print_error(char *err_str)
{
	printf("error : %s\n", err_str);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(argc, argv, &data))
		return (1);
	if (start_process(&data))
		return (1);
	if (end_process(&data))
		return (1);
	return (0);
}
