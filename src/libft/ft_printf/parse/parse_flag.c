/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:49:49 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/27 09:49:50 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		if (**fmt == '-')
			flags->minus = 1;
		else if (**fmt == '0')
			flags->zero = 1;
		(*fmt)++;
	}
}
