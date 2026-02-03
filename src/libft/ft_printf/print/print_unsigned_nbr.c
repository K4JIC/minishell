/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_nbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:49:33 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:48:00 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_integer(unsigned int n, t_flags flags, int len)
{
	int		count;
	int		zero_len;
	int		padding_len;
	char	pad_char;

	count = 0;
	zero_len = 0;
	if (flags.precision > len)
		zero_len = flags.precision - len;
	padding_len = 0;
	if (flags.width > len + zero_len)
		padding_len = flags.width - (len + zero_len);
	pad_char = ' ';
	if (flags.zero && !flags.minus && !flags.dot)
		pad_char = '0';
	if (!flags.minus)
		write_check(&count, ptf_print_padding(padding_len, pad_char));
	write_check(&count, ptf_print_padding(zero_len, '0'));
	write_check(&count, ptf_putnbr_absolute(n));
	if (flags.minus)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	return (count);
}

int	print_unsigned_nbr(va_list ap, t_flags flags)
{
	int				len;
	unsigned int	n;

	n = va_arg(ap, unsigned int);
	if (flags.dot && flags.precision == 0 && n == 0)
		return (ptf_print_padding(flags.width, ' '));
	if (n == 0)
		len = 1;
	else
		len = get_decimal_len(n);
	return (print_unsigned_integer(n, flags, len));
}
