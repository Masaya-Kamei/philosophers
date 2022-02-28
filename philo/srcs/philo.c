/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 08:41:48 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_philo_status(
	t_philo *philo, t_share *share, const char *status_msg)
{
	long	elapsed_time_in_ms;

	if (read_mutex_long(&share->continue_flag))
	{
		elapsed_time_in_ms = (get_us_time() - share->start_us_time) / 1000;
		printf("%6ld %4d %s\n", elapsed_time_in_ms, philo->id + 1, status_msg);
	}
}

static void	philo_eat(t_philo *philo, t_share *share)
{
	pthread_mutex_lock(philo->right_fork);
	put_philo_status(philo, share, FORK_MSG);
	pthread_mutex_lock(philo->left_fork);
	put_philo_status(philo, share, FORK_MSG);
	count_eat_num(philo, share);
	write_mutex_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT_MSG);
	my_usleep(philo->share->eat_ms_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, SLEEP_MSG);
	my_usleep(share->sleep_ms_time * 1000);
}

static void	philo_think(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, THINK_MSG);
}

void	*run_philo_work(void *p)
{
	t_philo *const	philo = p;
	t_share *const	share = philo->share;

	printf("aaa\n");
	pthread_create(&philo->dead_thread, NULL, monitor_if_dead, philo);
	if (philo->id % 2 == 1)
		my_usleep(200);
	while (read_mutex_long(&share->continue_flag))
	{
		philo_eat(philo, share);
		philo_sleep(philo, share);
		philo_think(philo, share);
	}
	pthread_join(philo->dead_thread, NULL);
	return (NULL);
}
