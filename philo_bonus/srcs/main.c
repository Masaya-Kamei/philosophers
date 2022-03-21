/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/21 11:35:17 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	allocate_memory(t_philo **philos, t_share *share)
{
	*philos = malloc(sizeof(t_philo) * share->philo_num);
	if (*philos == NULL)
		exit_with_errout(SYS_EMSG);
}

static sem_t	*sem_open_and_unlink(const char *name, const unsigned int value)
{
	sem_t	*s;

	s = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
	if (s == SEM_FAILED)
		exit_with_errout(SYS_EMSG);
	sem_unlink(name);
	return (s);
}

static void	init_data(t_philo **philos, t_share *share)
{
	int			i;
	char		*sem_name;
	const int	philo_num = share->philo_num;

	allocate_memory(philos, share);
	share->s_forks = sem_open_and_unlink("/forks", philo_num);
	share->s_forks_access = sem_open_and_unlink("/access", (philo_num + 1) / 2);
	share->s_continue = sem_open_and_unlink("/continue", 1);
	share->s_dead_philo_count = sem_open_and_unlink("/dead_count", 0);
	share->s_eaten_philo_count = sem_open_and_unlink("/eaten_count", 0);
	i = 0;
	while (i < philo_num)
	{
		(*philos)[i].id = i;
		(*philos)[i].share = share;
		(*philos)[i].eat_num = 0;
		sem_name = create_str_with_id("/last_eat_us_time", (*philos)[i].id);
		init_safe_long(&(*philos)[i].last_eat_us_time, sem_name, 0);
		free(sem_name);
		i++;
	}
}

static void	clean_data(t_philo *philos, t_share *share)
{
	int		i;

	i = 0;
	while (i < share->philo_num)
	{
		sem_close(philos[i].last_eat_us_time.s);
		i++;
	}
	sem_close(share->s_forks);
	sem_close(share->s_forks_access);
	sem_close(share->s_continue);
	sem_close(share->s_dead_philo_count);
	sem_close(share->s_eaten_philo_count);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_share		share;

	read_args_with_check(argc, argv, &share);
	init_data(&philos, &share);
	fork_processes(philos, &share);
	wait_child_processes(philos, &share);
	clean_data(philos, &share);
	return (0);
}
