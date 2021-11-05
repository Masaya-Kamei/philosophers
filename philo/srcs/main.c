/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/05 10:09:15 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	read_cmd_arg(int argc, char **argv, t_param *params)
{
	if (argc <= 4 || argc >= 7)
		return (ERROR);
	params->philo_num = ft_atoi(argv[1]);
	params->ms_time_until_death = ft_atoi(argv[2]);
	params->eating_ms_time = ft_atoi(argv[3]);
	params->sleeping_ms_time = ft_atoi(argv[4]);
	if (argc == 6)
		params->must_eat_num = ft_atoi(argv[5]);
	else
		params->must_eat_num = -1;
	if ((params->philo_num <= 1 || params->philo_num > 1000)
		|| params->ms_time_until_death <= 0
		|| params->eating_ms_time <= 0
		|| params->sleeping_ms_time <= 0
		|| (argc == 6 && params->must_eat_num <= 0))
		return (ERROR);
	return (SUCCESS);
}

static t_status	init_data(t_data *d)
{
	int		i;

	d->philos = malloc(sizeof(t_philo) * d->params.philo_num);
	if (d->philos == NULL)
		return (ERROR);
	d->resources.forks = malloc(sizeof(pthread_mutex_t) * d->params.philo_num);
	if (d->resources.forks == NULL)
		return (ERROR);
	i = -1;
	while (++i < d->params.philo_num)
	{
		pthread_mutex_init(&d->resources.forks[i], NULL);
	}
	pthread_mutex_init(&d->resources.output_tty, NULL);
	d->params.death_flag = 0;
	d->params.start_us_time = get_us_time();
	return (SUCCESS);
}

static void	wait_philos_thread(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->params.philo_num)
	{
		pthread_join(d->philos[i].routine_thread, NULL);
	}
}

static void	clean_data(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->params.philo_num)
	{
		pthread_mutex_destroy(&d->resources.forks[i]);
	}
	pthread_mutex_destroy(&d->resources.output_tty);
	free(d->philos);
	free(d->resources.forks);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (read_cmd_arg(argc, argv, &d.params) == ERROR)
	{
		put_usage();
		return (1);
	}
	if (init_data(&d) == ERROR)
	{
		put_errmsg("Malloc Error");
		return (1);
	}
	start_philos_thread(&d);
	wait_philos_thread(&d);
	clean_data(&d);
	return (0);
}
