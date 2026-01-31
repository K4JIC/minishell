/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:48:38 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:59:20 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_integer(unsigned int n, t_flags flags, int len, char *base)
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
	write_check(&count, ptf_putnbr_base(n, base));
	if (flags.minus)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	return (count);
}
