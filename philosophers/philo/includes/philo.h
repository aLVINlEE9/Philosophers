/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:07:19 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/05 21:16:30 by seungsle         ###   ########.fr       */
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

typedef struct s_info{
	long long	number_of_philosophers;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	number_of_times_each_philosopher_must_eat;
}	t_info;

size_t		ft_strlen(const char *s);
int			exception_print(char *str);

long long	ft_atol(const char *str);
int			valid_arg_check(int argc, char **argv);
int			init_info(int argc, char **argv, t_info *info);
void		parsing(int argc, char **argv, t_info *info);

#endif