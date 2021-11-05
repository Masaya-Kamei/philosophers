/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:02:09 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/05 10:18:04 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_errmsg(const char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
}

void	put_usage(void)
{
	write(STDERR_FILENO, "[Usage]\n", 8);
	write(STDERR_FILENO, "./philo ", 8);
	write(STDERR_FILENO, "number_of_philosophers ", 23);
	write(STDERR_FILENO, "time_to_die ", 12);
	write(STDERR_FILENO, "time_to_eat ", 12);
	write(STDERR_FILENO, "time_to_sleep ", 14);
	write(STDERR_FILENO, "[number_of_times_each_philosopher_must_eat]\n", 44);
}

static int	get_digit_num(int n)
{
	int		digit_num;

	if (n == 0)
		return (1);
	digit_num = 0;
	while (n != 0 && ++digit_num)
		n /= 10;
	return (digit_num);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		un = -1 * n;
	}
	else
		un = n;
	if (un >= 10)
		ft_putnbr_fd(un / 10, fd);
	c = un % 10 + '0';
	write(fd, &c, 1);
}

void	putnbr_with_digit(int n, int digit, int fd)
{
	const int	digit_num = get_digit_num(n);

	while (--digit >= digit_num)
		write(fd, " ", 1);
	ft_putnbr_fd(n, fd);
}
