/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 13:10:20 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	read_cmd_arg(int argc, char **argv, t_share *share)
{
	if (argc <= 4 || argc >= 7)
		return (ERROR);
	share->philo_num = ft_atoi(argv[1]);
	share->ms_time_until_death = ft_atoi(argv[2]);
	share->eating_ms_time = ft_atoi(argv[3]);
	share->sleeping_ms_time = ft_atoi(argv[4]);
	if (argc == 6)
		share->must_eat_num = ft_atoi(argv[5]);
	else
		share->must_eat_num = -1;
	if ((share->philo_num <= 0 || share->philo_num > 1000)
		|| share->ms_time_until_death <= 0
		|| share->eating_ms_time <= 0
		|| share->sleeping_ms_time <= 0
		|| (argc == 6 && share->must_eat_num <= 0))
		return (ERROR);
	return (SUCCESS);
}

static t_status	init_data(t_person **persons, t_share *share)
{
	int		i;

	*persons = malloc(sizeof(t_person) * share->philo_num);
	if (*persons == NULL)
		return (ERROR);
	share->m_forks = malloc(sizeof(pthread_mutex_t) * share->philo_num);
	if (share->m_forks == NULL)
		return (ERROR);
	i = -1;
	while (++i < share->philo_num)
	{
		(*persons)[i].id = i;
		(*persons)[i].share = share;
		(*persons)[i].right_fork = &share->m_forks[i];
		(*persons)[i].left_fork = &share->m_forks[(i + 1) % share->philo_num];
		init_t_mutex_long(&(*persons)[i].last_eat_us_time, 0);
		pthread_mutex_init(&share->m_forks[i], NULL);
	}
	init_t_mutex_long(&share->someone_dead, 0);
	init_t_mutex_long(&share->ate_philo_num, 0);
	return (SUCCESS);
}

static void	wait_philos_thread(t_person *persons, t_share *share)
{
	int		i;

	i = -1;
	while (++i < share->philo_num)
	{
		pthread_join(persons[i].work_thread, NULL);
	}
}

static void	clean_data(t_person *persons, t_share *share)
{
	int		i;

	i = -1;
	while (++i < share->philo_num)
	{
		pthread_mutex_destroy(&persons[i].last_eat_us_time.m);
		pthread_mutex_destroy(&share->m_forks[i]);
	}
	pthread_mutex_destroy(&share->someone_dead.m);
	pthread_mutex_destroy(&share->ate_philo_num.m);
	free(persons);
	free(share->m_forks);
}

int	main(int argc, char **argv)
{
	t_person	*persons;
	t_share		share;

	if (read_cmd_arg(argc, argv, &share) == ERROR)
	{
		ft_putendl_fd(USAGE_MSG, STDERR_FILENO);
		return (1);
	}
	if (init_data(&persons, &share) == ERROR)
	{
		ft_putendl_fd(MALLOC_EMSG, STDERR_FILENO);
		return (1);
	}
	start_philos_thread(persons, &share);
	wait_philos_thread(persons, &share);
	clean_data(persons, &share);
	return (0);
}
