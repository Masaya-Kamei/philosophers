/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:45:45 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/21 11:55:22 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_philo_status(
	t_philo *philo, t_share *share, const t_philo_status status)
{
	const char	msgs[5][17]
		= {"has taken a fork", "is eating",
			"is sleeping", "is thinking", "died"};
	long		mtime;

	pthread_mutex_lock(&share->continue_flag.m);
	if (share->continue_flag.val)
	{
		mtime = (get_us_time() - PASSED_TM_FLAG * share->start_us_time) / 1000;
		printf("%6ld %4d %s\n", mtime, philo->id + !DEBUG_FLAG, msgs[status]);
		if (status == DIE)
			share->continue_flag.val = 0;
	}
	pthread_mutex_unlock(&share->continue_flag.m);
}
