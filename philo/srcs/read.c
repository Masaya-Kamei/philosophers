/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:32:45 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 18:36:39 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	atoi_with_check(const char *str, int *nbr)
{
	int		i;
	long	long_nbr;

	i = 0;
	long_nbr = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (ERROR);
		long_nbr = (long_nbr * 10) + str[i] - '0';
		if (long_nbr > INT32_MAX)
			return (ERROR);
		i++;
	}
	if (long_nbr == 0)
		return (ERROR);
	*nbr = long_nbr;
	return (SUCCESS);
}

t_status	read_args_with_check(const int argc, char **argv, t_share *share)
{
	if (argc <= 4 || argc >= 7)
		return (ERROR);
	share->must_eat_num = -1;
	if (atoi_with_check(argv[1], &share->philo_num) == ERROR
		|| atoi_with_check(argv[2], &share->death_ms_time) == ERROR
		|| atoi_with_check(argv[3], &share->eat_ms_time) == ERROR
		|| atoi_with_check(argv[4], &share->sleep_ms_time) == ERROR
		|| (argc == 6
			&& atoi_with_check(argv[5], &share->must_eat_num) == ERROR))
	{
		return (ERROR);
	}
	if ((share->philo_num <= 0 || share->philo_num > 1000)
		|| share->death_ms_time <= 0
		|| share->eat_ms_time <= 0
		|| share->sleep_ms_time <= 0
		|| (argc == 6 && share->must_eat_num <= 0))
	{
		return (ERROR);
	}
	return (SUCCESS);
}
