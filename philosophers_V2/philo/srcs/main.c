/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:59:13 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/03 13:44:52 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	if (start_thread(&data))
		return (1);
	monitering(&data);
	free_util(&data, RELEASE_RESOURCES, data.num_of_philo);
	return (0);
}
