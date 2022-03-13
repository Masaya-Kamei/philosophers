/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:03:54 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/14 07:46:14 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	put_philo_status(
	t_philo *philo, t_share *share, const t_philo_status status)
{
	const char	msgs[5][17]
		= {"has taken a fork", "is eating",
			"is sleeping", "is thinking", "died"};
	long		passed_time_in_ms;

	sem_wait(share->s_continue);
	passed_time_in_ms = (get_us_time() - share->start_us_time) / 1000;
	printf("%6ld %4d %s\n", passed_time_in_ms, philo->id, msgs[status]);
	if (status == DIE)
	{
		sem_post(share->s_dead_philo_count);
		return ;
	}
	sem_post(share->s_continue);
}
