/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:48:58 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/27 09:49:00 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_upper(va_list ap, t_flags flags)
{
	unsigned int	n;
	int				len;

	n = va_arg(ap, unsigned int);
	if (flags.dot && flags.precision == 0 && n == 0)
		return (ptf_print_padding(flags.width, ' '));
	len = get_hex_len(n);
	return (print_hex_integer(n, flags, len, "0123456789ABCDEF"));
}
