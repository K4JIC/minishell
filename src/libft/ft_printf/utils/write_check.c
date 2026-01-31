/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:34:58 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:35:18 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_check(int *total_count, int write_count)
{
	if (*total_count == -1)
		return ;
	if (write_count == -1)
		*total_count = -1;
	else
		*total_count += write_count;
}
