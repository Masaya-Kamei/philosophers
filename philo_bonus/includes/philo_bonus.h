/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/15 10:11:26 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define SYS_EMSG "Unexpected System Error"
# define USAGE_MSG "[Usage]\n./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define DEBUG_FLAG 0

# define EXIT_DEAD 1
# define EXIT_EATEN 2

typedef enum e_status
{
	SUCCESS	=	0,
	ERROR	=	1
}			t_status;

typedef enum e_philo_status
{
	FORK	= 0,
	EAT		= 1,
	SLEEP	= 2,
	THINK	= 3,
	DIE		= 4
}			t_philo_status;

typedef struct s_sem_long
{
	sem_t	*s;
	long	val;
}			t_sem_long;

typedef struct s_share
{
	int			philo_num;
	int			death_ms_time;
	int			eat_ms_time;
	int			sleep_ms_time;
	int			must_eat_num;
	long		start_us_time;
	sem_t		*s_forks;
	sem_t		*s_forks_access;
	sem_t		*s_continue;
	pid_t		someone_dead_monitor_pid;
	sem_t		*s_dead_philo_count;
	pid_t		everyone_eaten_monitor_pid;
	sem_t		*s_eaten_philo_count;
}				t_share;

typedef struct s_philo
{
	int			id;
	int			eat_num;
	t_sem_long	last_eat_us_time;
	pid_t		routine_pid;
	pthread_t	dead_monitor_thread;
	t_share		*share;
}				t_philo;

// main
void	read_args_with_check(const int argc, char **argv, t_share *share);
void	fork_processes(t_philo *philos, t_share *share);
void	wait_child_processes(t_philo *philos, t_share *share);
void	someone_dead_monitor(t_share *share);
void	everyone_eaten_monitor(t_share *share);
void	loop_philo_routine(t_philo *philo, t_share *share);
void	philo_eat(t_philo *philo, t_share *share);
void	philo_sleep(t_philo *philo, t_share *share);
void	philo_think(t_philo *philo, t_share *share);
void	put_philo_status(
			t_philo *philo, t_share *share, const t_philo_status status);

// utils
sem_t	*sem_open_unlink(const char *name, const unsigned int value);
void	init_sem_long(t_sem_long *l, const char *name, long init_value);
long	read_sem_long(t_sem_long *l);
void	write_sem_long(t_sem_long *l, const long new_value);
long	increase_sem_long(t_sem_long *l, long inc_value);
long	get_us_time(void);
void	my_msleep(const long ms_time);
char	*create_str_with_id(const char *str, const int id);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	exit_with_errout(const char *errmsg);

#endif
