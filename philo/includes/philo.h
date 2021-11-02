/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:04:23 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/02 12:54:26 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <limits.h>

typedef enum e_status
{
	SUCCESS	= 0,
	ERROR	= 1
}			t_status;

typedef struct s_philo
{
	int		philo_num;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_num;
}			t_philo;

// utils
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);

#endif
