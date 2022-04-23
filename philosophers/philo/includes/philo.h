/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:34 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/23 20:19:51 by seungsle         ###   ########.fr       */
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

# define ERR_MALLOC		10
# define ERR_CTHREAD	11
# define ERR_ARGS		12

typedef struct s_data
{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_tos_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	*fork_mutex;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			l_fork;
	int			r_fork;
	pthread_t	tid;
	pthread_t	moniter;
	t_data		*data;
}	t_philo;

int			print_error(int err_type);

uint64_t	ft_atou64(const char *str);

#endif
