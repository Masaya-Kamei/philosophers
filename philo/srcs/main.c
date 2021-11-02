/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/02 12:57:56 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	err_handling(const char *err_msg, t_status status)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
	return (status);
}

static t_status	read_cmd_arg(int argc, char **argv, t_philo *philo)
{
	if (argc <= 4 || argc >= 7)
		return (err_handling("wrong numbers of arguments", ERROR));
	philo->philo_num = ft_atoi(argv[1]);
	philo->die_time = ft_atoi(argv[2]);
	philo->eat_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_num = ft_atoi(argv[5]);
	else
		philo->eat_num = -1;
	if ((philo->philo_num <= 1 || philo->philo_num > 1000)
		|| philo->die_time <= 0
		|| philo->eat_time <= 0
		|| philo->sleep_time <= 0
		|| (argc == 6 && philo->eat_num <= 0))
		return (ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (read_cmd_arg(argc, argv, &philo) == ERROR)
		return (1);
	return (0);
}
