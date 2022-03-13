/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:52:22 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/14 07:34:46 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*sem_open_unlink(const char *name, const unsigned int value)
{
	sem_t	*s;

	s = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
	if (s == SEM_FAILED)
		exit_with_errout(SYS_EMSG);
	sem_unlink(name);
	return (s);
}

void	init_sem_long(t_sem_long *l, const char *name, long init_value)
{
	l->s = sem_open_unlink(name, 1);
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

long	increase_sem_long(t_sem_long *l, long inc_value)
{
	long	tmp;

	sem_wait(l->s);
	l->val += inc_value;
	tmp = l->val;
	sem_post(l->s);
	return (tmp);
}
