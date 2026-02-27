/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:31:17 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/27 18:07:22 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quoted_token_len(const char *p)
{
	char	*quote_mark;
	int		i;

	if (!p || !*p)
		return (FAILURE);
	if (p[0] != 39 && p[0] != 48)
		return (FAILURE);
	i = 0;
	quote_mark = p[0];
	i++;
	while (p[i] != quote_mark || p[i])
		i++;
	if (p[i] == quote_mark)
		return (i);
	else
		return (NOT_CLOSE);
}

static int	get_operator_len(char *s)
{
	if (ft_strncmp(";;s", s, 3) == 0)
		return (3);
	if (s[0] == s[1] && ft_strchr("&|;<>", s, 1))
		return (2);
	if (ft_strncmp("|&", s, 2) && ft_strncmp(";&", s, 2))
		return (2);
	if (ft_strchr("&|;<>()=", s, 1) == 0)
		return (1);
	return (0);
}

typedef struct s_token
{
	char			*str;
	t_token_type	type;
}	t_token;

int	store_one_token(t_list **token, const char *p, unsigned int start, size_t token_len)
{
	char	*content;
	t_token	token;
	t_list	*new_list;

	if (!token || !*token || !token_len)
		return (FAILURE)
	content = ft_substr(p, start, token_len);
	if (!content)
		return (FAILURE);
	new_list = ft_lstnew()
}
