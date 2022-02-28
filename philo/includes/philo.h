/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/01 08:44:46 by mkamei           ###   ########.fr       */
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

# define FORK_MSG	"has taken a fork"
# define EAT_MSG	"is eating"
# define SLEEP_MSG	"is sleeping"
# define THINK_MSG	"is thinking"
# define DIE_MSG	"is died"

typedef enum e_status
{
	SUCCESS	=	0,
	ERROR	=	1
}			t_status;

typedef struct s_mutex_long
{
	pthread_mutex_t	m;
	long			val;
}					t_mutex_long;

typedef struct s_share
{
	int				philo_num;
	int				death_ms_time;
	int				eat_ms_time;
	int				sleep_ms_time;
	int				must_eat_num;
	long			start_us_time;
	t_mutex_long	continue_flag;
	t_mutex_long	ate_philo_num;
	t_mutex_long	*m_forks;
}					t_share;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_mutex_long	last_eat_us_time;
	int				eat_num;
	pthread_t		work_thread;
	pthread_t		dead_thread;
	t_share			*share;
}					t_philo;

// main
void	start_philos_thread(t_philo *philos, const int philo_num);
void	wait_philos_thread(t_philo *philos, const int philo_num);
void	*run_philo_work(void *p);
void	*monitor_if_dead(void *p);
void	count_eat_num(t_philo *philo, t_share *share);

// utils
void	init_mutex_long(t_mutex_long *l, long init_value);
long	read_mutex_long(t_mutex_long *l);
void	write_mutex_long(t_mutex_long *l, long new_value);
void	increase_mutex_long(t_mutex_long *l, long inc_value);
long	get_us_time(void);
void	my_usleep(const long us_time);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);

#endif
