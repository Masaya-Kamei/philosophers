/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/06 12:22:20 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_philo_status(t_person *person, const char *status_msg)
{
	int		elapsed_ms_time;

	pthread_mutex_lock(&person->share->m_dead);
	if (person->share->someone_dead == 0)
	{
		if (person->dead_flag)
			person->share->someone_dead = 1;
		elapsed_ms_time = (get_us_time() - person->share->start_us_time) / 1000;
		printf("%6d ms %4d %s\n", elapsed_ms_time, person->id + 1, status_msg);
	}
	pthread_mutex_unlock(&person->share->m_dead);
}

static void	*check_dead(void *p)
{
	t_person	*person;
	long		timelimit;

	person = p;
	while (1)
	{
		pthread_mutex_lock(&person->m_last_eat);
		timelimit = person->share->ms_time_until_death * 1000
			- (get_us_time() - person->last_eat_us_time);
		pthread_mutex_unlock(&person->m_last_eat);
		if (timelimit < 0)
		{
			person->dead_flag = 1;
			put_philo_status(person, DIE_MSG);
			break ;
		}
		my_usleep(timelimit);
	}
	return (NULL);
}

static void	philo_eat(t_person *person)
{
	pthread_mutex_lock(person->right_fork);
	put_philo_status(person, FORK_MSG);
	pthread_mutex_lock(person->left_fork);
	put_philo_status(person, FORK_MSG);
	pthread_mutex_lock(&person->m_last_eat);
	person->last_eat_us_time = get_us_time();
	pthread_mutex_unlock(&person->m_last_eat);
	put_philo_status(person, EAT_MSG);
	my_usleep(person->share->eating_ms_time * 1000);
	pthread_mutex_unlock(person->right_fork);
	pthread_mutex_unlock(person->left_fork);
}

static void	*run_philo_work(void *p)
{
	int			eat_count;
	t_person	*person;

	person = p;
	person->right_fork = &person->share->m_forks[person->id];
	person->left_fork
		= &person->share->m_forks[(person->id + 1) % person->share->philo_num];
	person->dead_flag = 0;
	pthread_mutex_init(&person->m_last_eat, NULL);
	person->last_eat_us_time = get_us_time();
	pthread_create(&person->die_thread, NULL, check_dead, person);
	if (person->id % 2 == 1)
		my_usleep(person->share->eating_ms_time * 1000);
	eat_count = 0;
	while (person->share->someone_dead == 0)
	{
		philo_eat(person);
		if (++eat_count == person->share->must_eat_num)
			break ;
		put_philo_status(person, SLEEP_MSG);
		my_usleep(person->share->sleeping_ms_time * 1000);
		put_philo_status(person, THINK_MSG);
	}
	pthread_detach(person->die_thread);
	pthread_mutex_destroy(&person->m_last_eat);
	return (NULL);
}

void	start_philos_thread(t_share *share, t_person *persons)
{
	int		i;

	i = -1;
	while (++i < share->philo_num)
	{
		persons[i].id = i;
		persons[i].share = share;
		pthread_create(
			&persons[i].work_thread, NULL, run_philo_work, &persons[i]);
	}
}
