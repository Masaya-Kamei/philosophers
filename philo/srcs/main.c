/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/19 16:58:54 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	allocate_memory(t_philo **philos, t_share *share)
{
	share->forks = malloc(sizeof(t_fork) * share->philo_num);
	if (share->forks == NULL)
		return (ERROR);
	*philos = malloc(sizeof(t_philo) * share->philo_num);
	if (*philos == NULL)
	{
		free(share->forks);
		return (ERROR);
	}
	return (SUCCESS);
}

static t_status	init_data(t_philo **philos, t_share *share)
{
	int		i;

	if (allocate_memory(philos, share) == ERROR)
		return (ERROR);
	init_safe_long(&share->eaten_philo_num, 0);
	init_safe_long(&share->continue_flag, 1);
	i = 0;
	while (i < share->philo_num)
	{
		pthread_mutex_init(&share->forks[i].real, NULL);
		init_safe_long(&share->forks[i].last_user_id, -1);
		(*philos)[i].id = i;
		(*philos)[i].share = share;
		(*philos)[i].eat_num = 0;
		(*philos)[i].left_fork = &share->forks[i];
		(*philos)[i].right_fork = &share->forks[(i + 1) % share->philo_num];
		init_safe_long(&(*philos)[i].last_eat_us_time, 0);
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
		pthread_mutex_destroy(&share->forks[i].real);
		pthread_mutex_destroy(&share->forks[i].last_user_id.m);
		i++;
	}
	pthread_mutex_destroy(&share->eaten_philo_num.m);
	pthread_mutex_destroy(&share->continue_flag.m);
	free(philos);
	free(share->forks);
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
	start_philos_thread(philos, &share);
	wait_philos_thread(philos, &share);
	clean_data(philos, &share);
	return (0);
}
