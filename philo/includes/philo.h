/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/21 11:55:29 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define MALLOC_EMSG "Malloc Error"
# define USAGE_MSG "[Usage]\n./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define DEBUG_FLAG 0
# define PASSED_TM_FLAG 1

typedef enum e_status
{
	SUCCESS	=	0,
	ERROR	=	1
}			t_status;

typedef enum e_philo_status
{
	FORK	=	0,
	EAT		=	1,
	SLEEP	=	2,
	THINK	=	3,
	DIE		=	4
}			t_philo_status;

typedef struct s_safe_long
{
	pthread_mutex_t	m;
	long			val;
}					t_safe_long;

typedef struct s_fork
{
	t_safe_long		last_user_id;
	pthread_mutex_t	real;
}					t_fork;

typedef struct s_share
{
	int				philo_num;
	int				death_ms_time;
	int				eat_ms_time;
	int				sleep_ms_time;
	int				must_eat_num;
	long			start_us_time;
	t_safe_long		eaten_philo_num;
	t_safe_long		continue_flag;
	t_fork			*forks;
}					t_share;

typedef struct s_philo
{
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_safe_long		last_eat_us_time;
	int				eat_num;
	pthread_t		routine_thread;
	pthread_t		dead_monitor_thread;
	t_share			*share;
}					t_philo;

// main
t_status	read_args_with_check(const int argc, char **argv, t_share *share);
void		start_philos_thread(t_philo *philos, t_share *share);
void		wait_philos_thread(t_philo *philos, t_share *share);
void		*loop_philo_routine(void *p);
void		philo_eat(t_philo *philo, t_share *share);
void		philo_sleep(t_philo *philo, t_share *share);
void		philo_think(t_philo *philo, t_share *share);
void		put_philo_status(
				t_philo *philo, t_share *share, const t_philo_status status);

// utils
void		init_safe_long(t_safe_long *l, const long init_value);
long		read_safe_long(t_safe_long *l);
void		write_to_safe_long(t_safe_long *l, const long new_value);
long		increase_safe_long(t_safe_long *l, const long inc_value);
long		get_us_time(void);
void		my_msleep(const long ms_time);
void		ft_putendl_fd(char *s, int fd);

#endif
