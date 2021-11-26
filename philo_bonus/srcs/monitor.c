/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:13:07 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 08:49:24 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	everyone_eaten_monitor(t_share *share)
{
	int		i;

	i = -1;
	while (++i < share->philo_num)
		sem_wait(share->s_ate_philo_num);
	exit(0);
}

void	start_monitor_process(t_share *share)
{
	share->eaten_monitor_pid = fork();
	if (share->eaten_monitor_pid < 0)
		exit_with_errout(SYS_EMSG, 1);
	else if (share->eaten_monitor_pid == 0)
	{
		everyone_eaten_monitor(share);
		exit(0);
	}
}
