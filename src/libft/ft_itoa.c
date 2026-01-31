/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:59:23 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 12:59:25 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long long num)
{
	size_t		count;

	count = 0;
	if (num <= 0)
	{
		num *= -1;
		count++;
	}
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*itoa;
	size_t		len;
	long long	num;

	num = (long long)n;
	len = count_digits(num);
	itoa = malloc(sizeof(char) * (len + 1));
	if (itoa == NULL)
		return (NULL);
	itoa[len] = '\0';
	if (num == 0)
		itoa[0] = '0';
	if (num < 0)
	{
		itoa[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		len--;
		itoa[len] = (num % 10) + '0';
		num /= 10;
	}
	return (itoa);
}
