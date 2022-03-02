/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:31:58 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 11:13:18 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philos_thread(t_philo *philos, t_share *share)
{
	int		i;

	share->start_us_time = get_us_time();
	i = 0;
	while (i < share->philo_num)
	{
		pthread_create(
			&philos[i].routine_thread, NULL, loop_philo_routine, &philos[i]);
		i++;
	}
}

void	wait_philos_thread(t_philo *philos, t_share *share)
{
	int		i;

	i = 0;
	while (i < share->philo_num)
	{
		pthread_join(philos[i].routine_thread, NULL);
		i++;
	}
}
