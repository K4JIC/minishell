/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:49:08 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:44:51 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_putptr_content(void *ptr)
{
	int	count;

	if (ptr == NULL)
		return (ptf_putstr("(nil)"));
	count = 0;
	write_check(&count, ptf_putstr("0x"));
	write_check(&count, ptf_putnbr_hex((unsigned long)ptr));
	return (count);
}

int	print_pointer(va_list ap, t_flags flags)
{
	void			*ptr;
	int				count;
	int				print_len;
	int				padding_len;

	ptr = va_arg(ap, void *);
	if (ptr == NULL)
		print_len = 5;
	else
		print_len = 2 + get_hex_len((unsigned long)ptr);
	padding_len = flags.width - print_len;
	if (padding_len < 0)
		padding_len = 0;
	count = 0;
	if (flags.minus == 0)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	write_check(&count, ptf_putptr_content(ptr));
	if (flags.minus == 1)
		write_check(&count, ptf_print_padding(padding_len, ' '));
	return (count);
}
