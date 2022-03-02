/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 12:28:48 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo, t_share *share)
{
	pthread_mutex_lock(philo->right_fork);
	put_philo_status(philo, share, FORK);
	if (share->philo_num == 1)
	{
		my_usleep((share->death_ms_time + 1) * 1000);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	put_philo_status(philo, share, FORK);
	write_mutex_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT);
	my_usleep(philo->share->eat_ms_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, SLEEP);
	my_usleep(share->sleep_ms_time * 1000);
}

static void	philo_think(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, THINK);
}

void	*loop_philo_routine(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;

	write_mutex_long(&philo->last_eat_us_time, share->start_us_time);
	pthread_create(&philo->dead_monitor_thread, NULL, dead_monitor, philo);
	pthread_detach(philo->dead_monitor_thread);
	if (philo->id % 2 == 1)
		my_usleep(800);
	while (read_mutex_long(&share->continue_flag))
	{
		philo_eat(philo, share);
		philo_sleep(philo, share);
		philo_think(philo, share);
	}
	return (NULL);
}
