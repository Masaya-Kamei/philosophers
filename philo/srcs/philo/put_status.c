/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:45:45 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/14 16:11:38 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_philo_status(
	t_philo *philo, t_share *share, const t_philo_status status)
{
	const char	msgs[5][17]
		= {"has taken a fork", "is eating",
			"is sleeping", "is thinking", "died"};
	long		passed_ms_time;

	pthread_mutex_lock(&share->continue_flag.m);
	if (share->continue_flag.val)
	{
		passed_ms_time = (get_us_time() - share->start_us_time) / 1000;
		printf("%6ld %4d %s\n",
			passed_ms_time, philo->id + !DEBUG_FLAG, msgs[status]);
		if (status == DIE)
			share->continue_flag.val = 0;
	}
	pthread_mutex_unlock(&share->continue_flag.m);
}
