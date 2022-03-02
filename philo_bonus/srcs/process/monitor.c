/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:32:24 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 18:25:33 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*dead_monitor(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;
	long			last_eat_us_time;
	long			timelimit;

	while (1)
	{
		last_eat_us_time = read_sem_long(&philo->last_eat_us_time);
		timelimit
			= share->death_ms_time * 1000 - (get_us_time() - last_eat_us_time);
		if (timelimit < 0)
		{
			put_philo_status(philo, share, DIE);
			break ;
		}
		my_usleep(20);
	}
	return (NULL);
}
