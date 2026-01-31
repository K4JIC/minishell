/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:52:48 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:58:53 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_flag_and_specifier(va_list ap, const char **fmt)
{
	t_flags	flags;

	init_flags(&flags);
	parse_flags(fmt, &flags);
	parse_width(fmt, ap, &flags);
	parse_precision(fmt, ap, &flags);
	return (parse_specifier(ap, **fmt, flags));
}

int	supporter_printf(const char *fmt, va_list ap)
{
	int	count;

	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			write_check(&count, parse_flag_and_specifier(ap, &fmt));
		}
		else
			write_check(&count, ptf_putchar(*fmt));
		if (count == -1)
			return (-1);
		fmt++;
	}
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	int		count;
	va_list	ap;

	if (fmt == NULL)
		return (-1);
	va_start(ap, fmt);
	count = supporter_printf(fmt, ap);
	va_end(ap);
	return (count);
}
