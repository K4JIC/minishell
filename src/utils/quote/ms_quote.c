/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:37:16 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/03 19:21:01 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_utils.h"

int	ismeta(char c)
{
	if (ft_strchr("&|;<>()=", (int)c))
		return (1);
	return (0);
}

int	isquote(const char c)
{
	return (c == 34 || c == 39);
}

int	ismsspace(const char c)
{
	return (c == ' ' || c == '\t');
}

// use for tokenizer, parse_envval and get_filepath.
int	get_quoted_string_len(char *p)
{
	char		quote_mark;
	int			len;

	if (!p || !*p)
		return (-1);
	if (p[0] != 34 && p[0] != 39)
		return (NO_QUOTE);
	len = 0;
	quote_mark = p[0];
	len++;
	while (p[len] != quote_mark && p[len])
		len++;
	if (p[len] == quote_mark)
		return (len + 1);
	else
		return (NO_CLOSE_QUOTE);
}
