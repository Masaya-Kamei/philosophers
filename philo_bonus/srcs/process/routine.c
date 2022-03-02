/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:04:37 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 10:58:31 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eat(t_philo *philo, t_share *share)
{
	sem_wait(share->s_forks);
	put_philo_status(philo, share, FORK);
	if (share->philo_num == 1)
	{
		my_usleep((share->death_ms_time + 1) * 1000);
		sem_post(share->s_forks);
		return ;
	}
	sem_wait(share->s_forks);
	put_philo_status(philo, share, FORK);
	write_sem_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT);
	my_usleep(philo->share->eat_ms_time * 1000);
	sem_post(share->s_forks);
	sem_post(share->s_forks);
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

void	loop_philo_routine(t_philo *philo, t_share *share)
{
	write_sem_long(&philo->last_eat_us_time, share->start_us_time);
	pthread_create(&philo->dead_monitor_thread, NULL, dead_monitor, philo);
	pthread_detach(philo->dead_monitor_thread);
	if (philo->id % 2 == 1)
		my_usleep(200);
	while (1)
	{
		philo_eat(philo, share);
		philo_sleep(philo, share);
		philo_think(philo, share);
	}
}
