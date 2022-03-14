/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 08:01:03 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/15 08:26:04 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo, t_share *share)
{
	t_fork	*use_fork;
	int		nnext_user_id;
	int		i;

	i = 0;
	while (i < 2)
	{
		if ((philo->id + i) % 2 == 0)
		{
			use_fork = philo->left_fork;
			nnext_user_id = philo->id - 1;
		}
		else
		{
			use_fork = philo->right_fork;
			nnext_user_id = philo->id + 1;
		}
		nnext_user_id = (nnext_user_id + share->philo_num) % share->philo_num;
		while (read_mutex_long(&use_fork->next_user_id) != philo->id)
			usleep(500);
		pthread_mutex_lock(&use_fork->real);
		write_mutex_long(&use_fork->next_user_id, nnext_user_id);
		put_philo_status(philo, share, FORK);
		i++;
	}
}

void	philo_eat(t_philo *philo, t_share *share)
{
	take_forks(philo, share);
	write_mutex_long(&philo->last_eat_us_time, get_us_time());
	put_philo_status(philo, share, EAT);
	my_msleep(philo->share->eat_ms_time);
	if (++philo->eat_num == share->must_eat_num)
	{
		if (increase_mutex_long(&share->eaten_philo_num, 1) == share->philo_num)
			write_mutex_long(&share->continue_flag, 0);
	}
	pthread_mutex_unlock(&philo->left_fork->real);
	pthread_mutex_unlock(&philo->right_fork->real);
}

void	philo_sleep(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, SLEEP);
	my_msleep(share->sleep_ms_time);
}

void	philo_think(t_philo *philo, t_share *share)
{
	put_philo_status(philo, share, THINK);
}
