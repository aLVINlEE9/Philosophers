/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:34 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/24 19:57:01 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define FALSE			0
# define TRUE			1

# define FORK			2
# define EAT			3
# define SLEEP			4
# define THINK			5
# define DIED			6
# define DONE			7

# define ERR_MALLOC		10
# define ERR_CTHREAD	11
# define ERR_ARGS		12

typedef struct s_data
{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	uint64_t		start_time;
	int				routine_count;
	int				max_count;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*moniter_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*stop_mutex;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			l_fork;
	int			r_fork;
	uint64_t	limit_time;
	int			is_done;
	pthread_t	tid;
	pthread_t	moniter;
	t_data		*data;
}	t_philo;

int			args_check(int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philo(t_data *data);
int			init_data(int argc, char **argv, t_data *data);
int			init(int argc, char **argv, t_data *data);

void		philo_take_fork(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_clean_fork(t_philo *philo);
void		philo_sleep_think(t_philo *philo);

int			print_error(int err_type);
void		print_message(t_philo *philo, int msg_type);

void		release_resources(t_data *data);
int			eat_moniter(t_philo *philo);
void		*moniter(void *philo_v);
void		*routine(void *philo_v);
int			start_thread(t_data *data);

void		delay_time(uint64_t delay_time);
uint64_t	get_time(void);
uint64_t	ft_atou64(const char *str);

#endif
