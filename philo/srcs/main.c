/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 10:44:35 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	read_args_with_check(int argc, char **argv, t_share *share)
{
	if (argc <= 4 || argc >= 7)
		return (ERROR);
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
		return (ERROR);
	return (SUCCESS);
}

static t_status	allocate_memory_to_data(t_philo **philos, t_share *share)
{
	int		i;

	share->m_forks = malloc(sizeof(pthread_mutex_t) * share->philo_num);
	if (share->m_forks == NULL)
		return (ERROR);
	*philos = malloc(sizeof(t_philo) * share->philo_num);
	if (*philos == NULL)
	{
		free(share->m_forks);
		return (ERROR);
	}
	return (SUCCESS);
}

static t_status	init_data(t_philo **philos, t_share *share)
{
	int			i;

	if (allocate_memory_to_data(philos, share) == ERROR)
		return (ERROR);
	share->ate_philo_num = 0;
	init_mutex_long(&share->continue_flag, 1);
	i = 0;
	while (i < share->philo_num)
	{
		(*philos)[i].id = i;
		(*philos)[i].share = share;
		(*philos)[i].eat_num = 0;
		(*philos)[i].right_fork = &share->m_forks[i];
		(*philos)[i].left_fork = &share->m_forks[(i + 1) % share->philo_num];
		init_mutex_long(&(*philos)[i].last_eat_us_time, 0);
		pthread_mutex_init(&share->m_forks[i], NULL);
		i++;
	}
	return (SUCCESS);
}

static void	clean_data(t_philo *philos, t_share *share)
{
	int		i;

	i = 0;
	while (i < share->philo_num)
	{
		pthread_mutex_destroy(&philos[i].last_eat_us_time.m);
		pthread_mutex_destroy(&share->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&share->continue_flag.m);
	free(philos);
	free(share->m_forks);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_share		share;

	if (read_args_with_check(argc, argv, &share) == ERROR)
	{
		ft_putendl_fd(USAGE_MSG, STDERR_FILENO);
		return (1);
	}
	if (init_data(&philos, &share) == ERROR)
	{
		ft_putendl_fd(MALLOC_EMSG, STDERR_FILENO);
		return (1);
	}
	start_philos_thread(philos, share.philo_num);
	wait_philos_thread(philos, share.philo_num);
	clean_data(philos, &share);
	return (0);
}
