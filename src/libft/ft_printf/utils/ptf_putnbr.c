/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:47:20 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:54:36 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_putnbr(int n)
{
	long	ln;
	int		count;

	ln = n;
	count = 0;
	if (ln == 0)
		return (ptf_putchar('0'));
	if (ln < 0)
	{
		write_check(&count, ptf_putchar('-'));
		ln = -ln;
	}
	if (ln > 9)
		write_check(&count, ptf_putnbr(ln / 10));
	write_check(&count, ptf_putchar((ln % 10) + '0'));
	return (count);
}
