/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 01:52:53 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/24 23:17:16 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

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
	sem_t			*fork_sem;
	sem_t			*moniter_sem;
	sem_t			*print_sem;
	sem_t			*stop_sem;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int			id;
	uint64_t	limit_time;
	int			is_done;
	pid_t		pid;
	pthread_t	moniter;
	t_data		*data;
}	t_philo;

int			args_check(int argc, char **argv);
void		init_semaphore(t_data *data);
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
void		*moniter(void *philo_v);
void		routine(t_philo *philo);
int			start_process(t_data *data);

void		delay_time(uint64_t delay_time);
uint64_t	get_time(void);
uint64_t	ft_atou64(const char *str);

#endif