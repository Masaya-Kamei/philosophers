/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 08:14:57 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/15 08:22:35 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo, t_share *share)
{
	sem_wait(share->s_forks);
	put_philo_status(philo, share, FORK);
	sem_wait(share->s_forks);
	put_philo_status(philo, share, FORK);
	write_sem_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT);
	my_msleep(philo->share->eat_ms_time);
	if (++philo->eat_num == share->must_eat_num)
		sem_post(share->s_eaten_philo_count);
	sem_post(share->s_forks);
	sem_post(share->s_forks);
}

void	philo_sleep(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, SLEEP);
	my_msleep(share->sleep_ms_time);
}

void	philo_think(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, THINK);
}
