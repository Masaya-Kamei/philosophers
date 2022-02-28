/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:47:46 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 08:33:33 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	last_put_philo_status(
	t_philo *philo, t_share *share, const char *status_msg)
{
	long	elapsed_time_in_ms;

	write_mutex_long(&share->continue_flag, 0);
	elapsed_time_in_ms = (get_us_time() - share->start_us_time) / 1000;
	printf("%6ld %4d %s\n", elapsed_time_in_ms, philo->id + 1, status_msg);
}

void	count_eat_num(t_philo *philo, t_share *share)
{
	if (share->must_eat_num == -1)
		return ;
	philo->eat_num++;
	if (philo->eat_num == share->must_eat_num)
		increase_mutex_long(&share->ate_philo_num, 1);
	if (read_mutex_long(&share->ate_philo_num) == share->philo_num)
		last_put_philo_status(philo, share, EAT_MSG);
}

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
			last_put_philo_status(philo, share, DIE_MSG);
			break ;
		}
		my_usleep(20);
	}
	return (NULL);
}
