/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:50:47 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/27 09:52:17 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	width;
	int	dot;
	int	precision;
}	t_flags;

int		parse_specifier(va_list ap, char specifier, t_flags flags);
void	parse_flags(const char **fmt, t_flags *flags);
void	parse_width(const char **fmt, va_list ap, t_flags *flags);
void	parse_precision(const char **fmt, va_list ap, t_flags *flags);

#endif
