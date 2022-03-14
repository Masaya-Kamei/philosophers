/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/14 12:56:05 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	philo_eat(t_philo *philo, t_share *share)
{
	pthread_mutex_lock(philo->left_fork);
	put_philo_status(philo, share, FORK);
	pthread_mutex_lock(philo->right_fork);
	put_philo_status(philo, share, FORK);
	write_mutex_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT);
	my_msleep(philo->share->eat_ms_time);
	if (++philo->eat_num == share->must_eat_num)
	{
		if (increase_mutex_long(&share->ate_philo_num, 1) == share->philo_num)
			write_mutex_long(&share->continue_flag, 0);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, SLEEP);
	my_msleep(share->sleep_ms_time);
}

static void	philo_think(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, THINK);
}

static void	*philo_one_routine(t_philo	*philo, t_share *share)
{
	put_philo_status(philo, share, FORK);
	pthread_join(philo->dead_monitor_thread, NULL);
	return (NULL);
}

void	*loop_philo_routine(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;

	write_mutex_long(&philo->last_eat_us_time, share->start_us_time);
	pthread_create(&philo->dead_monitor_thread, NULL, dead_monitor, philo);
	if (share->philo_num == 1)
		return (philo_one_routine(philo, share));
	if (philo->id % 2 == 0)
		usleep(500);
	while (read_mutex_long(&share->continue_flag))
	{
		philo_eat(philo, share);
		philo_sleep(philo, share);
		philo_think(philo, share);
	}
	pthread_join(philo->dead_monitor_thread, NULL);
	return (NULL);
}
