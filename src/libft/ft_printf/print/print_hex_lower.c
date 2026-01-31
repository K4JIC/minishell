/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:48:50 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:42:51 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_lower(va_list ap, t_flags flags)
{
	unsigned int	n;
	int				len;

	n = va_arg(ap, unsigned int);
	if (flags.dot && flags.precision == 0 && n == 0)
		return (ptf_print_padding(flags.width, ' '));
	len = get_hex_len(n);
	return (print_hex_integer(n, flags, len, "0123456789abcdef"));
}
