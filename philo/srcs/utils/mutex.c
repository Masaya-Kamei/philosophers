/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:09:25 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 13:09:15 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_t_mutex_long(t_mutex_long *l, long init_value)
{
	pthread_mutex_init(&l->m, NULL);
	l->val = init_value;
}

long	read_t_mutex_long(t_mutex_long *l)
{
	long	tmp;

	pthread_mutex_lock(&l->m);
	tmp = l->val;
	pthread_mutex_unlock(&l->m);
	return (tmp);
}

void	write_t_mutex_long(t_mutex_long *l, long new_value)
{
	pthread_mutex_lock(&l->m);
	l->val = new_value;
	pthread_mutex_unlock(&l->m);
}

void	increase_t_mutex_long(t_mutex_long *l, long inc_value)
{
	pthread_mutex_lock(&l->m);
	l->val += inc_value;
	pthread_mutex_unlock(&l->m);
}
