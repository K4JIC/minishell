/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_putnbr_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:47:36 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:55:07 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_putnbr_hex(unsigned long n)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		write_check(&count, ptf_putnbr_hex(n / 16));
	write_check(&count, ptf_putchar(hex[n % 16]));
	return (count);
}
