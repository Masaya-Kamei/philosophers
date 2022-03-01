/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:45:45 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 15:50:00 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_routine_end(
	t_philo *philo, t_share *share, const t_philo_status status)
{
	if (status == EAT)
	{
		if (++philo->eat_num == share->must_eat_num)
		{
			if (++share->ate_philo_num == share->philo_num)
				return (1);
		}
	}
	else if (status == DIE)
		return (1);
	return (0);
}

void	put_philo_status(
	t_philo *philo, t_share *share, const t_philo_status status)
{
	const char	msgs[5][17]
		= {"has taken a fork", "is eating",
			"is sleeping", "is thinking", "is died"};
	long		passed_time_in_ms;

	pthread_mutex_lock(&share->continue_flag.m);
	if (share->continue_flag.val)
	{
		passed_time_in_ms = (get_us_time() - share->start_us_time) / 1000;
		printf("%6ld %4d %s\n", passed_time_in_ms, philo->id + 1, msgs[status]);
		if (check_routine_end(philo, share, status))
			share->continue_flag.val = 0;
	}
	pthread_mutex_unlock(&share->continue_flag.m);
}
