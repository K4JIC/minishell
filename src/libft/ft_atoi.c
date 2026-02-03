/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:57:43 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/29 16:36:08 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_overflow(long long result, int digit, int sign)
{
	if (sign == 1)
	{
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10
				&& digit > INT_MAX % 10))
			return (1);
	}
	else
	{
		if (result > -(long long)INT_MIN / 10
			|| (result == -(long long)INT_MIN / 10
				&& digit > -(long long)INT_MIN % 10))
			return (-1);
	}
	return (0);
}

static int	parse_digits(const char *nptr, int sign)
{
	long long	result;
	int			overflow;
	int			i;

	result = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		overflow = is_overflow(result, nptr[i] - '0', sign);
		if (overflow == 1)
			return ((int)LONG_MAX);
		if (overflow == -1)
			return ((int)LONG_MIN);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				sign;

	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	return (parse_digits(nptr + i, sign));
}
