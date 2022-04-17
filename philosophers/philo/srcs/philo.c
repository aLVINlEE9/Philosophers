/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:07:23 by seungsle          #+#    #+#             */
/*   Updated: 2022/04/17 16:08:27 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*moniter(void *philo_t)
{
	t_philo	*philo;

	philo = (void *)philo_t;
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork_m[philo->l_fork]);
	message_print(philo, FORK);
	pthread_mutex_lock(&philo->info->fork_m[philo->r_fork]);
	message_print(philo, FORK);
	message_print(philo, EAT);
	timer(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->fork_m[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->fork_m[philo->r_fork]);
}

static void	*routine(void *philo_t)
{
	pthread_t	moniter;
	t_philo		*philo;

	philo = (void *)philo_t;
	if (pthread_create(&moniter, NULL, moniter, (void *)(philo)))
		return (exception_print("thread error(failed to create thread)"));
	pthread_detach(moniter);
	while (1)
	{
		eat(philo);
		message_print(philo, SLEEP);
		timer(philo->info->time_to_sleep);
		message_print(philo, THINKING);
	}
}

static int	run_philosopher(t_info *info)
{
	int			i;
	pthread_t	th;

	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_create(&th, NULL, routine, (void *)(&info->philos[i])))
			return (exception_print("thread error(failed to create thread)"));
		pthread_detach(th);
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (exception_print("bad arguments"));
	if (init_info(argc, argv, &info))
		return (1);
	if (run_philosopher(&info))
		return (1);
}
