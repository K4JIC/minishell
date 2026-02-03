/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:50:14 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/27 09:50:16 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_width(const char **fmt, va_list ap, t_flags *flags)
{
	if (**fmt == '*')
	{
		flags->width = va_arg(ap, int);
		(*fmt)++;
	}
	else if (ft_isdigit(**fmt))
	{
		flags->width = 0;
		while (ft_isdigit(**fmt))
		{
			flags->width = flags->width * 10 + (**fmt - '0');
			(*fmt)++;
		}
	}
}
