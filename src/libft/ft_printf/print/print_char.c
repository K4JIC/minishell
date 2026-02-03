/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:48:30 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:56:50 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(va_list ap, t_flags flags)
{
	unsigned char	c;
	int				count;
	int				padding_len;

	c = (unsigned char)va_arg(ap, int);
	count = 0;
	padding_len = flags.width - 1;
	if (padding_len < 0)
		padding_len = 0;
	if (flags.minus == 0)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	if (count != -1)
		write_check(&count, ptf_putchar(c));
	if (flags.minus == 1 && count != -1)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	return (count);
}
