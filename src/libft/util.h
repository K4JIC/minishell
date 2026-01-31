/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:51:00 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/07 10:36:03 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdarg.h>
# include "libft.h"

int		ptf_putstr(char *str);
int		ptf_putchar(char c);
int		ptf_putnbr_hex(unsigned long n);
int		ptf_putnbr_hex_upper(unsigned long n);
int		ptf_putnbr(int n);
int		ptf_putnbr_unsigned(unsigned int n);
int		is_flag(int c);
int		is_specifier(int c);
int		is_flag_specifier(int c);
void	init_flags(t_flags *flags);
int		ptf_print_padding(int len, char c);
int		get_hex_len(unsigned long n);
int		get_decimal_len(long long n);
int		ptf_putnbr_absolute(unsigned int n);
int		ptf_putnbr_base(unsigned long n, const char *base);
void	write_check(int *total_count, int write_count);

#endif
