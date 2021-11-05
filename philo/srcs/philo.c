/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:59:26 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/05 11:58:21 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_philo_status(t_philo *philo, const char *status_msg)
{
	const int	elapsed_ms_time
		= (get_us_time() - philo->params->start_us_time) / 1000;

	pthread_mutex_lock(&philo->resources->output_tty);
	if (philo->params->death_flag == 0)
	{
		// if (status_msg[0] == 'd')
		// 	philo->params->death_flag = 1;
		// putnbr_with_digit(elapsed_ms_time, 6, STDOUT_FILENO);
		// write(STDOUT_FILENO, "ms ", 3);
		// putnbr_with_digit(philo->id + 1, 4, STDOUT_FILENO);
		// write(STDOUT_FILENO, " ", 1);
		// write(STDOUT_FILENO, status_msg, ft_strlen(status_msg));
		// write(STDOUT_FILENO, "\n", 1);
		printf("%6d ms %4d %s\n", elapsed_ms_time, philo->id + 1, status_msg);
	}
	pthread_mutex_unlock(&philo->resources->output_tty);
}

static void	*death_timer(void *p)
{
	t_philo	*philo;
	long	timelimit;

	philo = p;
	while (1)
	{
		timelimit = philo->params->ms_time_until_death * 1000
			- (get_us_time() - philo->last_eat_us_time);
		if (timelimit < 0)
		{
			put_philo_status(philo, "died");
			philo->params->death_flag = 1;
			break ;
		}
		my_usleep(timelimit);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	put_philo_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	put_philo_status(philo, "has taken a fork");
	philo->last_eat_us_time = get_us_time();
	put_philo_status(philo, "is eating");
	my_usleep(philo->params->eating_ms_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	*run_philo_routine(void *p)
{
	int		eat_count;
	t_philo	*philo;

	philo = p;
	philo->right_fork = &philo->resources->forks[philo->id];
	philo->left_fork
		= &philo->resources->forks[(philo->id + 1) % philo->params->philo_num];
	philo->last_eat_us_time = get_us_time();
	pthread_create(&philo->die_thread, NULL, death_timer, philo);
	if (philo->id % 2 == 1)
		my_usleep(philo->params->eating_ms_time * 1000);
	eat_count = 0;
	while (philo->params->death_flag == 0)
	{
		philo_eat(philo);
		if (++eat_count == philo->params->must_eat_num)
			break ;
		put_philo_status(philo, "is sleeping");
		my_usleep(philo->params->sleeping_ms_time * 1000);
		put_philo_status(philo, "is thinking");
	}
	pthread_detach(philo->die_thread);
	return (NULL);
}

void	start_philos_thread(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->params.philo_num)
	{
		d->philos[i].id = i;
		d->philos[i].params = &d->params;
		d->philos[i].resources = &d->resources;
		pthread_create(&d->philos[i].routine_thread,
			NULL, run_philo_routine, &d->philos[i]);
	}
}
