/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:07:19 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/18 01:23:07 by seungsle         ###   ########.fr       */
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

# define FORK " has taken a fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINKING " is thinking"
# define DIED " died"

typedef struct s_info{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	int				done_philo;
	struct s_philo	*philos;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	print;
}	t_info;

typedef struct s_philo{
	t_info			*info;
	int				position;
	int				l_fork;
	int				r_fork;
	int				routine_times;
	uint64_t		limit;
	pthread_t		moniter;
	pthread_t		tid;
}	t_philo;

size_t		ft_strlen(const char *s);
void		message_print(t_philo *philo, char *type);
int			exception_print(char *str);

int			valid_arg_check(int argc, char **argv);
void		init_philos(t_info *info);
int			init_info(int argc, char **argv, t_info *info);

void		timer(uint64_t time);
uint64_t	get_time(void);
uint64_t	ft_atou64(const char *str);

void		*moniter(void *philo_t);

#endif