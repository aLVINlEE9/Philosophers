/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:34 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/23 19:29:46 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int			num_of_philo;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_tos_sleep;
	int			num_of_must_eat;
}	t_data;

typedef struct s_philo
{
	
}

#endif
