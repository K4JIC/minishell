/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_putnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:47:12 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:53:51 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptf_putnbr_base(unsigned long n, const char *base)
{
	int				count;
	unsigned int	base_len;

	base_len = ft_strlen(base);
	count = 0;
	if (n >= base_len)
		write_check(&count, ptf_putnbr_base(n / base_len, base));
	write_check(&count, ptf_putchar(base[n % base_len]));
	return (count);
}
