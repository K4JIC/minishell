/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:50:53 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/27 09:50:55 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <stdarg.h>
# include "libft.h"
# include "util.h"

int	print_char(va_list ap, t_flags flags);
int	print_str(va_list ap, t_flags flags);
int	print_pointer(va_list ap, t_flags flags);
int	print_signed_nbr(va_list ap, t_flags flags);
int	print_unsigned_nbr(va_list ap, t_flags flags);
int	print_hex_lower(va_list ap, t_flags flags);
int	print_hex_upper(va_list ap, t_flags flags);
int	print_hex_integer(unsigned int n, t_flags flags, int len, char *base);

#endif
