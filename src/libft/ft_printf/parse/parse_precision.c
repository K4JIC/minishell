/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:49:58 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/27 09:49:59 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_precision(const char **fmt, va_list ap, t_flags *flags)
{
	if (**fmt != '.')
		return ;
	flags->dot = 1;
	(*fmt)++;
	if (**fmt == '*')
	{
		flags->precision = va_arg(ap, int);
		(*fmt)++;
	}
	else if (ft_isdigit(**fmt))
	{
		flags->precision = 0;
		while (ft_isdigit(**fmt))
		{
			flags->precision = flags->precision * 10 + (**fmt - '0');
			(*fmt)++;
		}
	}
}
