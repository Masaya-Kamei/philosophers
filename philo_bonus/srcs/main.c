/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 13:14:47 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	read_cmd_arg(int argc, char **argv, t_share *share)
{
	if (argc <= 4 || argc >= 7)
		exit_with_errout(USAGE_MSG, 1);
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
		exit_with_errout(USAGE_MSG, 1);
}

static void	init_data(t_person **persons, t_share *share)
{
	const int	oflag = O_CREAT | O_EXCL;
	int			i;
	char		*sem_name;

	share->s_forks = my_sem_open("/forks", oflag, S_IRWXU, share->philo_num);
	share->s_ate_philo_num = my_sem_open("/ate_philo_num", oflag, S_IRWXU, 0);
	share->s_someone_dead = my_sem_open("/someone_dead", oflag, S_IRWXU, 1);
	*persons = malloc(sizeof(t_person) * share->philo_num);
	if (*persons == NULL)
		exit_with_errout(SYS_EMSG, 1);
	i = -1;
	while (++i < share->philo_num)
	{
		(*persons)[i].id = i;
		(*persons)[i].share = share;
		sem_name = create_str_with_id("/last_eat_us_time", (*persons)[i].id);
		init_t_sem_long(&(*persons)[i].last_eat_us_time, sem_name, 0);
		free(sem_name);
	}
}

static void	wait_child_process(t_person *persons, t_share *share)
{
	int		i;
	int		status;

	if (waitpid(0, &status, 0) == -1)
		exit_with_errout(SYS_EMSG, 1);
	i = -1;
	while (++i < share->philo_num)
		kill(persons[i].work_pid, SIGKILL);
	kill(share->eaten_monitor_pid, SIGKILL);
}

static void	clean_data(t_person *persons, t_share *share)
{
	int		i;

	i = -1;
	while (++i < share->philo_num)
		sem_close(persons[i].last_eat_us_time.s);
	sem_close(share->s_forks);
	sem_close(share->s_ate_philo_num);
	sem_close(share->s_someone_dead);
	free(persons);
}

int	main(int argc, char **argv)
{
	t_person	*persons;
	t_share		share;

	read_cmd_arg(argc, argv, &share);
	init_data(&persons, &share);
	start_philos_process(persons, &share);
	start_monitor_process(&share);
	wait_child_process(persons, &share);
	clean_data(persons, &share);
	return (0);
}
