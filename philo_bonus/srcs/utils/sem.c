/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:52:22 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/26 11:23:13 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem_long(t_sem_long *l, const char *name, long init_value)
{
	l->s = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (l->s == SEM_FAILED)
		exit_with_errout(SYS_EMSG, 1);
	sem_unlink(name);
	l->val = init_value;
}

long	read_sem_long(t_sem_long *l)
{
	long	tmp;

	sem_wait(l->s);
	tmp = l->val;
	sem_post(l->s);
	return (tmp);
}

void	write_sem_long(t_sem_long *l, long new_value)
{
	sem_wait(l->s);
	l->val = new_value;
	sem_post(l->s);
}

void	increase_sem_long(t_sem_long *l, long inc_value)
{
	sem_wait(l->s);
	l->val += inc_value;
	sem_post(l->s);
}
