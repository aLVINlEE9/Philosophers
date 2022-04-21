/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:34 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 17:37:51 by seungsle         ###   ########.fr       */
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

# define ERR_PARSING 10
# define ERR_MALLOC 11
# define ERR_THREAD 12

typedef struct s_data{
	int				philo_num;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo{
	int			id;
	int			l_fork;
	int			r_fork;
	pthread_t	tid;
	t_data		*data;
}	t_philo;

int			init(int argc, char **argv, t_data *data);

int			print_error(int err_type);

uint64_t	ft_atou64(const char *str);

#endif