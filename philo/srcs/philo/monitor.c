/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:47:46 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/09 10:24:28 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_monitor(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;
	long			last_eat_us_time;
	long			uneaten_us_time;

	while (read_mutex_long(&share->continue_flag))
	{
		last_eat_us_time = read_mutex_long(&philo->last_eat_us_time);
		uneaten_us_time = get_us_time() - last_eat_us_time;
		if ((long)share->death_ms_time * 1000 < uneaten_us_time)
		{
			put_philo_status(philo, share, DIE);
			break ;
		}
		my_usleep(800);
	}
	return (NULL);
}
