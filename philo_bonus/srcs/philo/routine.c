/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:04:37 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/14 07:38:01 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eat(t_philo *philo, t_share *share)
{
	sem_wait(share->s_forks);
	put_philo_status(philo, share, FORK);
	sem_wait(share->s_forks);
	put_philo_status(philo, share, FORK);
	write_sem_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT);
	my_msleep(philo->share->eat_ms_time);
	if (++philo->eat_num == share->must_eat_num)
		sem_post(share->s_ate_philo_count);
	sem_post(share->s_forks);
	sem_post(share->s_forks);
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

static void	philo_one_routine(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, FORK);
	pthread_join(philo->dead_monitor_thread, NULL);
}

void	loop_philo_routine(t_philo *philo, t_share *share)
{
	write_sem_long(&philo->last_eat_us_time, share->start_us_time);
	pthread_create(&philo->dead_monitor_thread, NULL, dead_monitor, philo);
	if (share->philo_num == 1)
		return (philo_one_routine(philo, share));
	if (philo->id % 2 == 0)
		my_usleep(800);
	while (1)
	{
		philo_eat(philo, share);
		philo_sleep(philo, share);
		philo_think(philo, share);
	}
	pthread_join(philo->dead_monitor_thread, NULL);
}
