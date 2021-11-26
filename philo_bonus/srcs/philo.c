/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 13:12:09 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	put_philo_status(
	t_person *person, t_share *share, t_philo_status status)
{
	const char	msgs[5][17] = {
		"has taken a fork", "is eating",
		"is sleeping", "is thinking", "is died"};
	// long		timestamp_in_ms;

	// timestamp_in_ms = get_us_time() / 1000;
	// printf("%ld %4d %s\n", get_us_time() / 1000, person->id + 1, msgs[status]);
	sem_wait(share->s_someone_dead);
	printf("%ld %4d %s\n", (get_us_time() - share->start_us_time) / 1000, person->id + 1, msgs[status]);
	if (status == DIE)
		exit(0);
	else
		sem_post(share->s_someone_dead);
}

static void	*check_dead(void *person_ptr)
{
	long			last_eat_us_time;
	long			timelimit;
	t_person *const	person = person_ptr;
	t_share *const	share = person->share;

	while (1)
	{
		last_eat_us_time = read_t_sem_long(&person->last_eat_us_time);
		timelimit = share->ms_time_until_death * 1000
			- (get_us_time() - last_eat_us_time);
		if (timelimit < 0)
		{
			put_philo_status(person, share, DIE);
			break ;
		}
		my_usleep(20);
	}
	return (NULL);
}

static void	philo_eat(t_person *person, t_share *share)
{
	sem_wait(share->s_forks);
	put_philo_status(person, share, FORK);
	sem_wait(share->s_forks);
	put_philo_status(person, share, FORK);
	write_t_sem_long(&person->last_eat_us_time, get_us_time());
	put_philo_status(person, share, EAT);
	my_usleep(person->share->eating_ms_time * 1000);
	sem_post(share->s_forks);
	sem_post(share->s_forks);
}

static void	run_philo_work(t_person *person, t_share *share)
{
	int		eat_count;

	write_t_sem_long(&person->last_eat_us_time, share->start_us_time);
	pthread_create(&person->die_thread, NULL, check_dead, person);
	if (person->id % 2 == 1)
		my_usleep(500);
	eat_count = 0;
	while (1)
	{
		philo_eat(person, share);
		if (++eat_count == share->must_eat_num)
			sem_post(share->s_ate_philo_num);
		put_philo_status(person, share, SLEEP);
		my_usleep(share->sleeping_ms_time * 1000);
		put_philo_status(person, share, THINK);
	}
	pthread_join(person->die_thread, NULL);
	exit(0);
}

void	start_philos_process(t_person *persons, t_share *share)
{
	int		i;

	share->start_us_time = get_us_time();
	i = -1;
	while (++i < share->philo_num)
	{
		persons[i].work_pid = fork();
		if (persons[i].work_pid < 0)
			exit_with_errout(SYS_EMSG, 1);
		else if (persons[i].work_pid == 0)
		{
			run_philo_work(&persons[i], share);
			exit(0);
		}
	}
}
