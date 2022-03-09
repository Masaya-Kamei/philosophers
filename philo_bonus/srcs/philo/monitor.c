/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:32:24 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/09 10:29:49 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*dead_monitor(void *p)
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
		my_usleep(1000);
	}
	return (NULL);
}
