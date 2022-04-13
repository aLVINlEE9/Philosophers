/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:07:19 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/13 17:59:08 by seungsle         ###   ########.fr       */
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

typedef enum e_status{
	EAT = 1,
	SLEEP,
	THINKING
}	t_status;

typedef struct s_info{
	int			num_of_philo;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			num_of_must_eat;
}	t_info;

typedef struct	s_philo{
	t_info			info;
	t_status		status;
	int				r_times;
	uint64_t		last_eat;
	pthread_mutex_t	mutex;
}	t_philo;

size_t		ft_strlen(const char *s);
int			exception_print(char *str);

long long	ft_atol(const char *str);
int			valid_arg_check(int argc, char **argv);
int			init_info(int argc, char **argv, t_info *info);
void		parsing(int argc, char **argv, t_info *info);

#endif