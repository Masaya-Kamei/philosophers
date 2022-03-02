/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:04:56 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 14:55:30 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	fork_someone_dead_monitor_process(t_share *share)
{
	share->someone_dead_monitor_pid = fork();
	if (share->someone_dead_monitor_pid < 0)
		exit_with_errout(SYS_EMSG);
	else if (share->someone_dead_monitor_pid == 0)
	{
		someone_dead_monitor(share);
		exit(EXIT_DEAD);
	}
}

static void	fork_everyone_ate_monitor_process(t_share *share)
{
	share->everyone_ate_monitor_pid = fork();
	if (share->everyone_ate_monitor_pid < 0)
		exit_with_errout(SYS_EMSG);
	else if (share->everyone_ate_monitor_pid == 0)
	{
		everyone_ate_monitor(share);
		exit(EXIT_ATE);
	}
}

void	fork_processes(t_philo *philos, t_share *share)
{
	int		i;

	fork_someone_dead_monitor_process(share);
	fork_everyone_ate_monitor_process(share);
	share->start_us_time = get_us_time();
	i = 0;
	while (i < share->philo_num)
	{
		philos[i].routine_pid = fork();
		if (philos[i].routine_pid < 0)
			exit_with_errout(SYS_EMSG);
		else if (philos[i].routine_pid == 0)
		{
			loop_philo_routine(&philos[i], share);
			exit(0);
		}
		i++;
	}
}

void	wait_child_processes(t_philo *philos, t_share *share)
{
	int		i;
	int		status;

	if (waitpid(0, &status, 0) == -1)
		exit_with_errout(SYS_EMSG);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_DEAD)
		kill(share->everyone_ate_monitor_pid, SIGKILL);
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_ATE)
		kill(share->someone_dead_monitor_pid, SIGKILL);
	i = 0;
	while (i < share->philo_num)
	{
		kill(philos[i].routine_pid, SIGKILL);
		i++;
	}
}
