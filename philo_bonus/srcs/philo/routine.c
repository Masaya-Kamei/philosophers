/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:04:37 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/15 08:21:34 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*dead_monitor(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;
	long			last_eat_us_time;
	long			uneaten_us_time;

	while (1)
	{
		last_eat_us_time = read_sem_long(&philo->last_eat_us_time);
		uneaten_us_time = get_us_time() - last_eat_us_time;
		if ((long)share->death_ms_time * 1000 < uneaten_us_time)
		{
			put_philo_status(philo, share, DIE);
			break ;
		}
		usleep(800);
	}
	return (NULL);
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
	if (philo->id % 2 == 1)
		usleep(500);
	while (1)
	{
		philo_eat(philo, share);
		philo_sleep(philo, share);
		philo_think(philo, share);
	}
	pthread_join(philo->dead_monitor_thread, NULL);
}
