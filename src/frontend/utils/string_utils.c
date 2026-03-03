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

#include "libft.h"
#include "operate_list.h"
#include "frontend_utils.h"

char*ismeta(char c)
{
	return (ft_strchr("&|;<>()=", (int)c));
}

int	isquote(const char c)
{
	return (c == 34 || c == 39);
}

/**
 * use for get length of token or filepath.
 */

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
		return (NO_CLOSE);
}

static int	get_operator_len(char *s)
{
	if (ft_strncmp(";;s", s, 3) == 0)
		return (3);
	if (s[0] == s[1] && ft_strchr("&|;<>", s[0]))
		return (2);
	if (ft_strncmp("|&", s, 2) == 0 || ft_strncmp(";&", s, 2) == 0)
		return (2);
	if (ft_strchr("&|;<>()=", s[0]))
		return (1);
	return (NO_OPERATOR);
}

int	get_one_token_len(char *p)
{
	int		len;

	if (!*p)
		return (0);
	else if (ismeta(*p))
		len = get_operator_len(p);
	else if (isquote(*p))
		len = get_quoted_string_len(p);
	else
	{
		len = 0;
		while (p[len] && !ismeta(p[len]) && !isquote(p[len]) && p[len] != ' ' && p[len] != '\t')
			len++;
	}
	return (len);
}
