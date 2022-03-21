/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:09:25 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/19 16:30:43 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_safe_long(t_safe_long *l, const long init_value)
{
	pthread_mutex_init(&l->m, NULL);
	l->val = init_value;
}

long	read_safe_long(t_safe_long *l)
{
	long	tmp;

	pthread_mutex_lock(&l->m);
	tmp = l->val;
	pthread_mutex_unlock(&l->m);
	return (tmp);
}

void	write_to_safe_long(t_safe_long *l, const long new_value)
{
	pthread_mutex_lock(&l->m);
	l->val = new_value;
	pthread_mutex_unlock(&l->m);
}

long	increase_safe_long(t_safe_long *l, const long inc_value)
{
	long	tmp;

	pthread_mutex_lock(&l->m);
	l->val += inc_value;
	tmp = l->val;
	pthread_mutex_unlock(&l->m);
	return (tmp);
}
