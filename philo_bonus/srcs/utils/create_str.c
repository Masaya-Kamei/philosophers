/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:56:14 by mkamei            #+#    #+#             */
/*   Updated: 2022/03/02 10:12:18 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
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

static char	*ft_itoa(int n)
{
	const int	digit_num = get_digit_num(n);
	const int	minus_flag = (n < 0);
	const int	sign = 1 - (minus_flag * 2);
	char		*str;
	int			i;

	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc((digit_num + minus_flag + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = digit_num + minus_flag;
	while (n != 0)
	{
		str[--i] = (n % 10) * sign + '0';
		n /= 10;
	}
	if (minus_flag)
		str[0] = '-';
	str[digit_num + minus_flag] = '\0';
	return (str);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	pre_len;
	size_t	suf_len;
	char	*join;

	pre_len = ft_strlen(s1);
	suf_len = ft_strlen(s2);
	join = (char *)malloc((pre_len + suf_len + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, pre_len + 1);
	ft_strlcpy(join + pre_len, s2, suf_len + 1);
	return (join);
}

char	*create_str_with_id(const char *str, int id)
{
	char	*id_str;
	char	*join;

	id_str = ft_itoa(id);
	if (id_str == NULL)
		exit_with_errout(SYS_EMSG);
	join = ft_strjoin(str, id_str);
	if (join == NULL)
		exit_with_errout(SYS_EMSG);
	free(id_str);
	return (join);
}
