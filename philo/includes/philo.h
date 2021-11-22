/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/22 14:25:00 by mkamei           ###   ########.fr       */
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

typedef struct e_mutex_long
{
	pthread_mutex_t	m;
	long			val;
}					t_mutex_long;

typedef struct s_share
{
	int				philo_num;
	int				ms_time_until_death;
	int				eating_ms_time;
	int				sleeping_ms_time;
	int				must_eat_num;
	long			start_us_time;
	t_mutex_long	someone_dead;
	t_mutex_long	ate_philo_num;
	pthread_mutex_t	*m_forks;
}					t_share;

typedef struct s_person
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_mutex_long	last_eat_us_time;
	pthread_t		work_thread;
	pthread_t		die_thread;
	t_share			*share;
}					t_person;

// main
void	start_philos_thread(t_person *persons, t_share *share);

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
