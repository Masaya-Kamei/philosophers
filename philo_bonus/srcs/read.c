/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:08:01 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/09 10:34:36 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_status	atoi_with_check(const char *str, int *nbr)
{
	int		i;
	long	long_nbr;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	long_nbr = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (ERROR);
		long_nbr = (long_nbr * 10) + str[i] - '0';
		if ((str[0] != '-' && long_nbr > INT32_MAX)
			|| (str[0] == '-' && - long_nbr < INT32_MIN))
			return (ERROR);
		i++;
	}
	if (str[0] == '-')
		long_nbr *= -1;
	*nbr = long_nbr;
	return (SUCCESS);
}

void	read_args_with_check(const int argc, char **argv, t_share *share)
{
	if (argc <= 4 || argc >= 7)
		exit_with_errout(USAGE_MSG);
	share->must_eat_num = -1;
	if (atoi_with_check(argv[1], &share->philo_num) == ERROR
		|| atoi_with_check(argv[2], &share->death_ms_time) == ERROR
		|| atoi_with_check(argv[3], &share->eat_ms_time) == ERROR
		|| atoi_with_check(argv[4], &share->sleep_ms_time) == ERROR
		|| (argv[5] && atoi_with_check(argv[5], &share->must_eat_num) == ERROR))
	{
		exit_with_errout(USAGE_MSG);
	}
	if ((share->philo_num <= 0 || share->philo_num > 1000)
		|| share->death_ms_time <= 0
		|| share->eat_ms_time <= 0
		|| share->sleep_ms_time <= 0
		|| (argv[5] && share->must_eat_num <= 0))
	{
		exit_with_errout(USAGE_MSG);
	}
}
