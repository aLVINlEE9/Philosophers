/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:59:21 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/04 16:53:27 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define DESTROY 20
# define FREE 30
# define FREE_MAIN_LOCK 31
# define FREE_PHILO 32
# define FREE_FORKS 33
# define FREE_PHILO_LOCK 34
# define RELEASE_RESOURCES 35
# define ALL 40

typedef struct s_data
{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
	int				is_dead;
	uint64_t		start_time;
	pthread_mutex_t	*main_lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				eat_count;
	int				is_done;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*philo_lock;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;
int			join_array_philo(t_data *data);
int			free_array_philo(t_data *data, int idx, int df_type);
int			free_array_fork(t_data *data, int idx, int df_type);

int			free_util(t_data *data, int free_type, int df_type, int idx);

int			init_data(int argc, char **argv, t_data *data);
int			init_forks(t_data *data);
int			create_philo(t_data *data);
int			init_philo(t_data *data);
int			init(int argc, char **argv, t_data *data);

int			print_error(char *err_str);

void		eat_moniter(t_data *data, int cnt);
void		dead_moniter(t_philo *philo);
void		monitering(t_data *data);


int			one_philo_case(uint64_t time);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		take_forks(t_philo *philo);

int			eat_check(t_philo *philo);

int			dead_check(t_philo *philo);
void		*thread(void *philo_v);
int			start_thread(t_data *data);

uint64_t	get_time(void);
int			args_check(int argc, char **argv);
uint64_t	ft_atou64(const char *str);

#endif