/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:34 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/21 21:07:59 by seungsle         ###   ########.fr       */
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

# define FALSE 0
# define TRUE 1

# define FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIE 6

# define ERR_PARSING 10
# define ERR_MALLOC 11
# define ERR_THREAD 12

typedef struct s_data{
	int				philo_num;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	uint64_t		start_time;
	uint64_t		now_time;
	pthread_mutex_t	*fork_mutex;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo{
	int				id;
	int				l_fork;
	int				r_fork;
	int				is_eating;
	uint64_t		limit_time;
	pthread_t		tid;
	pthread_t		moniter_tid;
	pthread_mutex_t	print_mutex;
	t_data			*data;
}	t_philo;

int			check_num(int argc, char **argv);
int			init(int argc, char **argv, t_data *data);
void		mutex_init(t_data *data);
int			init_philo(t_data *data);
int			init_data(int argc, char **argv, t_data *data);

void		philo_take_fork(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_clean_fork(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

int			print_error(int err_type);
int			print_message(t_philo *philo, int msg_type);

void		main_thread_time_updater(t_data *data);
void		*moniter(void *philo_t);
void		*routine(void *philo_t);
int			start_thread(t_data *data);

void		delay_time(uint64_t time);
uint64_t	get_time(void);
uint64_t	ft_atou64(const char *str);

#endif