/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 21:00:06 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 21:00:19 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	get_operator_len(char *p)
{
	if (ft_strncmp(";;s", p, 3) == 0)
		return (3);
	if (p[0] == p[1] && ft_strchr("&|;<>", p[0]))
		return (2);
	if (ft_strncmp("|&", p, 2) == 0 || ft_strncmp(";&", p, 2) == 0)
		return (2);
	if (ft_strchr("&|;<>()=", p[0]))
		return (1);
	return (0);
}

static int	get_word_len(char *p)
{
	int	len;
	int	quote_len;

	len = 0;
	while (p[len] && !ismeta(p[len]) && !ismsspace(p[len]))
	{
		if (p[len] == '\\' && p[len + 1] != 0)
			len += 2;
		else if (isquote(p[len]))
		{
			quote_len = get_quoted_string_len(&p[len]);
			if (quote_len == NO_CLOSE_QUOTE)
				return (NO_CLOSE_QUOTE);
			len += quote_len;
		}
		else
			len++;
	}
	return (len);
}

t_token_type_len	get_one_token_len(char *p)
{
	t_token_type_len		tlen;

	ft_bzero(&tlen, sizeof(t_token_type_len));
	if (ismeta(*p))
	{
		tlen.type = TK_OPERATOR;
		tlen.len = get_operator_len(p);
	}
	else
	{
		tlen.type = TK_WORD;
		tlen.len = get_word_len(p);
	}
	return (tlen);
}
