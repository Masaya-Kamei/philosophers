/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:42:16 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/09 10:14:26 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_us_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	my_usleep(const long us_time)
{
	const long	finish_us_time = us_time + get_us_time();
	long		left_time;

	left_time = us_time;
	while (left_time > 0)
	{
		usleep(left_time / 2);
		left_time = finish_us_time - get_us_time();
	}
}

void	my_msleep(const long ms_time)
{
	my_usleep(ms_time * 1000);
}
