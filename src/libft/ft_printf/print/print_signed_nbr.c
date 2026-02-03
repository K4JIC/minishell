/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:49:15 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:49:44 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_integer(long long n, t_flags flags, int len)
{
	int	count;
	int	zero_len;
	int	padding_len;

	count = 0;
	zero_len = 0;
	if (flags.precision > (len - (n < 0)))
		zero_len = flags.precision - (len - (n < 0));
	padding_len = 0;
	if (flags.width > len + zero_len)
		padding_len = flags.width - (len + zero_len);
	if (!flags.minus && !flags.zero)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	if (n < 0)
		write_check(&count, ptf_putchar('-'));
	if (!flags.minus && flags.zero)
		write_check(&count, ptf_print_padding(padding_len, '0'));
	write_check(&count, ptf_print_padding(zero_len, '0'));
	if (n < 0)
		write_check(&count, ptf_putnbr_absolute(-n));
	else
		write_check(&count, ptf_putnbr_absolute(n));
	if (flags.minus)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	return (count);
}

int	print_signed_nbr(va_list ap, t_flags flags)
{
	int			len;
	long long	n;

	n = va_arg(ap, int);
	if (flags.dot && flags.precision == 0 && n == 0)
		return (ptf_print_padding(flags.width, ' '));
	if (n == 0)
		len = 1;
	else
		len = get_decimal_len(n);
	return (print_integer(n, flags, len));
}
