/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/25 09:50:32 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define SYS_EMSG "Unexpected System Error"
# define USAGE_MSG "[Usage]\n./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef enum e_philo_status
{
	FORK	=	0,
	EAT		=	1,
	SLEEP	=	2,
	THINK	=	3,
	DIE		=	4
}			t_philo_status;

typedef struct s_sem_long
{
	sem_t			*s;
	long			val;
}					t_sem_long;

typedef struct s_share
{
	int			philo_num;
	int			ms_time_until_death;
	int			eating_ms_time;
	int			sleeping_ms_time;
	int			must_eat_num;
	long		start_us_time;
	t_sem_long	someone_dead;
	t_sem_long	ate_philo_num;
	sem_t		*s_forks;
}				t_share;

typedef struct s_person
{
	int				id;
	t_sem_long		last_eat_us_time;
	pid_t			work_pid;
	pthread_t		die_thread;
	t_share			*share;
}					t_person;

// main
void	start_philos_process(t_person *persons, t_share *share);

// utils
void	init_sem_long(t_sem_long *l, const char *name, long init_value);
long	read_sem_long(t_sem_long *l);
void	write_sem_long(t_sem_long *l, long new_value);
void	increase_sem_long(t_sem_long *l, long inc_value);
long	get_us_time(void);
void	my_usleep(const long us_time);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	exit_with_errout(const char *errmsg, int exit_status);

#endif
