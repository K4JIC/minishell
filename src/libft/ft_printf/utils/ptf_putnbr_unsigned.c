/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_putnbr_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:48:10 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:56:16 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		write_check(&count, ptf_putnbr_unsigned(n / 10));
	write_check(&count, ptf_putchar((n % 10) + '0'));
	return (count);
}
