/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/06 09:30:18 by mkamei           ###   ########.fr       */
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

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "is died"

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

typedef struct s_share
{
	int				philo_num;
	int				ms_time_until_death;
	int				eating_ms_time;
	int				sleeping_ms_time;
	int				must_eat_num;
	long			start_us_time;
	bool			someone_dead;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	*m_forks;
}					t_share;

typedef struct s_person
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	bool			dead_flag;
	long			last_eat_us_time;
	pthread_mutex_t	m_last_eat;
	pthread_t		work_thread;
	pthread_t		die_thread;
	t_share			*share;
}					t_person;

// main
void	start_philos_thread(t_share *share, t_person *persons);

// utils
long	get_us_time(void);
void	my_usleep(const long us_time);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);

#endif
