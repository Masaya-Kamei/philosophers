/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 13:10:09 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_philo_status(
	t_person *person, t_share *share, t_philo_status status)
{
	long		timestamp_in_ms;
	const char	msgs[5][17] = {
		"has taken a fork", "is eating",
		"is sleeping", "is thinking", "is died"};

	pthread_mutex_lock(&share->someone_dead.m);
	if (share->someone_dead.val == 0
		&& read_t_mutex_long(&share->ate_philo_num) != share->philo_num)
	{
		if (status == DIE)
			share->someone_dead.val = 1;
		timestamp_in_ms = get_us_time() / 1000;
		printf("%ld %4d %s\n", timestamp_in_ms, person->id + 1, msgs[status]);
	}
	pthread_mutex_unlock(&share->someone_dead.m);
}

static void	*check_dead(void *p)
{
	long			last_eat_us_time;
	long			timelimit;
	t_person *const	person = p;
	t_share *const	share = person->share;

	while (read_t_mutex_long(&share->someone_dead) == 0
		&& read_t_mutex_long(&share->ate_philo_num) != share->philo_num)
	{
		last_eat_us_time = read_t_mutex_long(&person->last_eat_us_time);
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
	pthread_mutex_lock(person->right_fork);
	put_philo_status(person, share, FORK);
	pthread_mutex_lock(person->left_fork);
	put_philo_status(person, share, FORK);
	write_t_mutex_long(&person->last_eat_us_time, get_us_time());
	put_philo_status(person, share, EAT);
	my_usleep(person->share->eating_ms_time * 1000);
	pthread_mutex_unlock(person->right_fork);
	pthread_mutex_unlock(person->left_fork);
}

static void	*run_philo_work(void *p)
{
	int				eat_count;
	t_person *const	person = p;
	t_share *const	share = person->share;

	write_t_mutex_long(&person->last_eat_us_time, share->start_us_time);
	pthread_create(&person->die_thread, NULL, check_dead, person);
	if (person->id % 2 == 1)
		my_usleep(200);
	eat_count = 0;
	while (read_t_mutex_long(&share->someone_dead) == 0
		&& read_t_mutex_long(&share->ate_philo_num) != share->philo_num)
	{
		philo_eat(person, share);
		if (++eat_count == share->must_eat_num)
			increase_t_mutex_long(&share->ate_philo_num, 1);
		put_philo_status(person, share, SLEEP);
		my_usleep(share->sleeping_ms_time * 1000);
		put_philo_status(person, share, THINK);
	}
	pthread_join(person->die_thread, NULL);
	return (NULL);
}

void	start_philos_thread(t_person *persons, t_share *share)
{
	int		i;

	share->start_us_time = get_us_time();
	i = -1;
	while (++i < share->philo_num)
	{
		pthread_create(
			&persons[i].work_thread, NULL, run_philo_work, &persons[i]);
	}
}
