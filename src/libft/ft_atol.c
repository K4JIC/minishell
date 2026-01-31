/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:57:36 by yikebata          #+#    #+#             */
/*   Updated: 2025/12/01 17:19:11 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long long res, int digit, int sign)
{
	if (sign == 1)
	{
		if ((long)res > LONG_MAX / 10
			|| ((long)res == LONG_MAX / 10
				&& digit > LONG_MAX % 10))
			return (1);
	}
	else
	{
		if ((long)res < LONG_MIN / 10
			|| ((long)res == LONG_MIN / 10
				&& digit > 8))
			return (-1);
	}
	return (0);
}

static long	parse_digits(const char *nptr, int sign)
{
	long long	res;
	int			overflow;
	int			i;

	i = 0;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		overflow = check_overflow(res, nptr[i] - '0', sign);
		if (overflow == 1)
			return (LONG_MAX);
		if (overflow == -1)
			return (LONG_MIN);
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return ((long)(res * sign));
}

long	ft_atol(const char *str)
{
	unsigned int	i;
	int				sign;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issign(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (parse_digits(str + i, sign));
}
