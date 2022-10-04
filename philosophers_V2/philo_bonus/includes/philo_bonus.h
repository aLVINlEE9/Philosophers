/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:26:25 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 20:18:14 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_data
{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	uint64_t		start_time;
	pid_t			*pid;
	int				all_eat;
	sem_t			*table;
	sem_t			*fork;
	sem_t			*start;
	sem_t			*print;
	struct s_philo	*philo;
}   t_data;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	uint64_t	last_eat_time;
	pthread_t	die_check;
	sem_t		*check_sem;
}	t_philo;

#endif