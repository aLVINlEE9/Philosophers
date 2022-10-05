/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:26:25 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 15:33:25 by seungsle         ###   ########.fr       */
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
	int				is_dead;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*main_lock;
	struct s_philo	*philo;
}   t_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	uint64_t		sleep_time;
	uint64_t		eat_time;
	int				eat_count;
	int				is_done;
	uint64_t		last_eat_time;
	pthread_t		moniter;
	sem_t			*philo_lock;
	char			*sem_name;
	struct s_data	*data;
}	t_philo;

int			print_error(char *err_str);

int			start_process(t_data *data);

int			ft_cnt(long long n);
char		*ft_put(char *str, long long n, int len);
char		*ft_itoa(int n);
int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);

int			one_philo_case(uint64_t time);
uint64_t	get_time(void);
int			args_check(int argc, char **argv);
uint64_t	ft_atou64(const char *str);

#endif