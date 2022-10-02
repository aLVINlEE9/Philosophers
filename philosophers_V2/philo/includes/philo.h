/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:59:21 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/02 19:22:12 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define FREE 30
# define FREE_MAIN_LOCK 31
# define FREE_PHILO 32
# define FREE_FORKS 33
# define FREE_PHILO_LOCK 34

typedef struct s_data
{
    int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_must_eat;
    pthread_mutex_t *main_lock;
    pthread_mutex_t *forks;
    struct s_philo  *philo;
}   t_data;

typedef struct s_philo
{
    int             id;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *philo_lock;
    pthread_t       thread;
    struct s_data   *data;
}   t_philo;

int free_util(t_data *data, int free_type, int idx);

int	args_check(int argc, char **argv);
int init(int argc, char **argv, t_data *data);

int print_error(char *err_str);

int one_philo_case(t_data *data);

int start_thread(t_data *data);

uint64_t	ft_atou64(const char *str);

#endif