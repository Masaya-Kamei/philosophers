/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:47:46 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 15:19:53 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_if_dead(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;
	long			last_eat_us_time;
	long			timelimit;

	while (read_mutex_long(&share->continue_flag))
	{
		last_eat_us_time = read_mutex_long(&philo->last_eat_us_time);
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
