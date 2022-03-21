/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:04:56 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/21 11:21:53 by mkamei           ###   ########.fr       */
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
		sem_wait(share->s_dead_philo_count);
		exit(EXIT_DEAD);
	}
}

static void	fork_everyone_eaten_monitor_process(t_share *share)
{
	int		i;

	share->everyone_eaten_monitor_pid = fork();
	if (share->everyone_eaten_monitor_pid < 0)
		exit_with_errout(SYS_EMSG);
	else if (share->everyone_eaten_monitor_pid == 0)
	{
		i = 0;
		while (i < share->philo_num)
		{
			sem_wait(share->s_eaten_philo_count);
			i++;
		}
		exit(EXIT_EATEN);
	}
}

void	fork_processes(t_philo *philos, t_share *share)
{
	int		i;

	fork_someone_dead_monitor_process(share);
	fork_everyone_eaten_monitor_process(share);
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

static void	kill_and_waitpid(const pid_t pid)
{
	int		status;

	if (kill(pid, SIGKILL) == -1)
		exit_with_errout(SYS_EMSG);
	if (waitpid(pid, &status, 0) == -1)
		exit_with_errout(SYS_EMSG);
}

void	wait_child_processes(t_philo *philos, t_share *share)
{
	int		i;
	int		status;

	if (waitpid(0, &status, 0) == -1)
		exit_with_errout(SYS_EMSG);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_DEAD)
		kill_and_waitpid(share->everyone_eaten_monitor_pid);
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_EATEN)
		kill_and_waitpid(share->someone_dead_monitor_pid);
	i = 0;
	while (i < share->philo_num)
	{
		kill_and_waitpid(philos[i].routine_pid);
		i++;
	}
}
