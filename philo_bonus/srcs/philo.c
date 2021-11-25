/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/25 11:28:38 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	put_philo_status(
	t_person *person, t_share *share, t_philo_status status)
{
	long		timestamp_in_ms;
	const char	msgs[5][17] = {
		"has taken a fork", "is eating",
		"is sleeping", "is thinking", "is died"};

	sem_wait(share->someone_dead.s);
	if (share->someone_dead.val == 0
		&& read_sem_long(&share->ate_philo_num) != share->philo_num)
	{
		if (status == DIE)
			share->someone_dead.val = 1;
		timestamp_in_ms = get_us_time() / 1000;
		printf("%ld %4d %s\n", timestamp_in_ms, person->id + 1, msgs[status]);
	}
	sem_post(share->someone_dead.s);
}

static void	*check_dead(void *person_ptr)
{
	long			last_eat_us_time;
	long			timelimit;
	t_person *const	person = person_ptr;
	t_share *const	share = person->share;

	while (read_sem_long(&share->someone_dead) == 0
		&& read_sem_long(&share->ate_philo_num) != share->philo_num)
	{
		last_eat_us_time = read_sem_long(&person->last_eat_us_time);
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
	write_sem_long(&person->last_eat_us_time, get_us_time());
	put_philo_status(person, share, EAT);
	my_usleep(person->share->eating_ms_time * 1000);
	sem_post(share->s_forks);
	sem_post(share->s_forks);
}

static void	run_philo_work(t_person *person, t_share *share)
{
	int		eat_count;

	init_sem_long(&person->last_eat_us_time,
		"/last_eat_us_time", share->start_us_time);
	pthread_create(&person->die_thread, NULL, check_dead, person);
	if (person->id % 2 == 1)
		my_usleep(200);
	eat_count = 0;
	while (read_sem_long(&share->someone_dead) == 0
		&& read_sem_long(&share->ate_philo_num) != share->philo_num)
	{
		philo_eat(person, share);
		if (++eat_count == share->must_eat_num)
			increase_sem_long(&share->ate_philo_num, 1);
		put_philo_status(person, share, SLEEP);
		my_usleep(share->sleeping_ms_time * 1000);
		put_philo_status(person, share, THINK);
	}
	pthread_join(person->die_thread, NULL);
	sem_close(person->last_eat_us_time.s);
	sem_unlink("/last_eat_us_time");
	exit(0);
}

void	start_philos_process(t_person *persons, t_share *share)
{
	int		i;

	i = -1;
	while (++i < share->philo_num)
	{
		persons[i].id = i;
		persons[i].work_pid = fork();
		persons[i].share = share;
		if (persons[i].work_pid < 0)
			exit_with_errout(SYS_EMSG, 1);
		else if (persons[i].work_pid == 0)
		{
			run_philo_work(&persons[i], share);
			exit(0);
		}
	}
}
