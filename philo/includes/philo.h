/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/05 11:05:26 by mkamei           ###   ########.fr       */
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

typedef struct s_param
{
	int		philo_num;
	int		ms_time_until_death;
	int		eating_ms_time;
	int		sleeping_ms_time;
	int		must_eat_num;
	bool	death_flag;
	long	start_us_time;
}			t_param;

typedef struct s_resource
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_tty;
}					t_resource;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			last_eat_us_time;
	pthread_t		routine_thread;
	pthread_t		die_thread;
	t_param			*params;
	t_resource		*resources;
}					t_philo;

typedef struct s_data
{
	t_param		params;
	t_resource	resources;
	t_philo		*philos;
}				t_data;

// main
void	start_philos_thread(t_data *d);

// utils
long	get_us_time(void);
void	my_usleep(const long us_time);
void	put_errmsg(const char *err_msg);
void	put_usage(void);
void	ft_putnbr_fd(int n, int fd);
void	putnbr_with_digit(int n, int digit, int fd);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);

#endif
