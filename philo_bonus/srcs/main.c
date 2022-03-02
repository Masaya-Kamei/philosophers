/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 11:34:59 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	read_args_with_check(int argc, char **argv, t_share *share)
{
	if (argc <= 4 || argc >= 7)
		exit_with_errout(USAGE_MSG);
	share->philo_num = ft_atoi(argv[1]);
	share->death_ms_time = ft_atoi(argv[2]);
	share->eat_ms_time = ft_atoi(argv[3]);
	share->sleep_ms_time = ft_atoi(argv[4]);
	if (argc == 6)
		share->must_eat_num = ft_atoi(argv[5]);
	else
		share->must_eat_num = -1;
	if ((share->philo_num <= 0 || share->philo_num > 1000)
		|| share->death_ms_time <= 0
		|| share->eat_ms_time <= 0
		|| share->sleep_ms_time <= 0
		|| (argc == 6 && share->must_eat_num <= 0))
		exit_with_errout(USAGE_MSG);
}

static void	allocate_memory_to_data(t_philo **philos, t_share *share)
{
	*philos = malloc(sizeof(t_philo) * share->philo_num);
	if (*philos == NULL)
		exit_with_errout(SYS_EMSG);
}

static void	init_data(t_philo **philos, t_share *share)
{
	int			i;
	char		*sem_name;

	allocate_memory_to_data(philos, share);
	share->s_forks = sem_open_unlink("/forks", share->philo_num);
	share->s_continue = sem_open_unlink("/continue", 1);
	share->s_dead_philo_count = sem_open_unlink("/dead_count", 0);
	share->s_ate_philo_count = sem_open_unlink("/ate_count", 0);
	i = 0;
	while (i < share->philo_num)
	{
		(*philos)[i].id = i;
		(*philos)[i].share = share;
		(*philos)[i].eat_num = 0;
		sem_name = create_str_with_id("/last_eat_us_time", (*philos)[i].id);
		init_sem_long(&(*philos)[i].last_eat_us_time, sem_name, 0);
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
	sem_close(share->s_continue);
	sem_close(share->s_dead_philo_count);
	sem_close(share->s_ate_philo_count);
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
