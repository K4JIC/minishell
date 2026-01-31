/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_print_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:46:45 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:52:50 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_print_padding(int len, char c)
{
	int	count;

	count = 0;
	while (len > 0)
	{
		write_check(&count, ptf_putchar(c));
		len--;
	}
	return (count);
}
