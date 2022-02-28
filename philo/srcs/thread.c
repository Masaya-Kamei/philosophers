/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:31:58 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 08:40:02 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philos_thread(t_philo *philos, const int philo_num)
{
	int		i;

	i = 0;
	while (i < philo_num)
	{
		pthread_create(&philos[i].work_thread, 0, run_philo_work, &philos[i]);
		i++;
	}
}

void	wait_philos_thread(t_philo *philos, const int philo_num)
{
	int		i;

	i = 0;
	while (i < philo_num)
	{
		pthread_join(philos[i].work_thread, 0);
		i++;
	}
}
