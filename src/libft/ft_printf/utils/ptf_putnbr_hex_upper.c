/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_putnbr_hex_upper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:48:01 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:55:39 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_putnbr_hex_upper(unsigned long n)
{
	char	*hex;
	int		count;

	hex = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
		write_check(&count, ptf_putnbr_hex_upper(n / 16));
	write_check(&count, ptf_putchar(hex[n % 16]));
	return (count);
}
