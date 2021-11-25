/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/25 10:28:33 by mkamei           ###   ########.fr       */
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
	*persons = malloc(sizeof(t_person) * share->philo_num);
	if (*persons == NULL)
		exit_with_errout(SYS_EMSG, 1);
	share->s_forks
		= sem_open("/forks", O_CREAT, S_IRWXU, share->philo_num);
	if (share->s_forks == SEM_FAILED)
		exit_with_errout(SYS_EMSG, 1);
	init_sem_long(&share->someone_dead, "/someone_dead", 0);
	init_sem_long(&share->ate_philo_num, "/ate_philo_num", 0);
	share->start_us_time = get_us_time();
}

static void	wait_philos_process(t_person *persons, t_share *share)
{
	int		i;
	int		status;

	i = -1;
	while (++i < share->philo_num)
	{
		if (waitpid(persons[i].work_pid, &status, 1) == -1)
			exit_with_errout(SYS_EMSG, 1);
	}
}

static void	clean_data(t_person *persons, t_share *share)
{
	sem_close(share->s_forks);
	sem_close(share->someone_dead.s);
	sem_close(share->ate_philo_num.s);
	sem_unlink("/forks");
	sem_unlink("/someone_dead");
	sem_unlink("/ate_philo_num");
	free(persons);
}

int	main(int argc, char **argv)
{
	t_person	*persons;
	t_share		share;

	read_cmd_arg(argc, argv, &share);
	init_data(&persons, &share);
	start_philos_process(persons, &share);
	wait_philos_process(persons, &share);
	clean_data(persons, &share);
	return (0);
}
