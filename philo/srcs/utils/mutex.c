/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:09:25 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/10 16:07:59 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex_long(t_mutex_long *l, const long init_value)
{
	pthread_mutex_init(&l->m, NULL);
	l->val = init_value;
}

long	read_mutex_long(t_mutex_long *l)
{
	long	tmp;

	pthread_mutex_lock(&l->m);
	tmp = l->val;
	pthread_mutex_unlock(&l->m);
	return (tmp);
}

void	write_mutex_long(t_mutex_long *l, const long new_value)
{
	pthread_mutex_lock(&l->m);
	l->val = new_value;
	pthread_mutex_unlock(&l->m);
}

long	increase_mutex_long(t_mutex_long *l, const long inc_value)
{
	long	tmp;

	pthread_mutex_lock(&l->m);
	l->val += inc_value;
	tmp = l->val;
	pthread_mutex_unlock(&l->m);
	return (tmp);
}
