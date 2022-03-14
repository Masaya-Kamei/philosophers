/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entire_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:30:34 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/15 08:23:20 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	someone_dead_monitor(t_share *share)
{
	sem_wait(share->s_dead_philo_count);
}

void	everyone_eaten_monitor(t_share *share)
{
	int		i;

	i = 0;
	while (i < share->philo_num)
	{
		sem_wait(share->s_eaten_philo_count);
		i++;
	}
}
