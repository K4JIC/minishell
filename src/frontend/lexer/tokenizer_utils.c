/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:31:17 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/28 17:17:35 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "operate_list.h"
#include "libft.h"
#include <stddef.h>

int	get_quoted_token_len(char *p)
{
	char		quote_mark;
	int			len;

	if (!p || !*p)
		return (-1);
	if (p[0] != 34 && p[0] != 39)
		return (-1);
	len = 0;
	quote_mark = p[0];
	len++;
	while (p[len] != quote_mark || p[len])
		len++;
	if (p[len] == quote_mark)
		return (len);
	else
		return (-2);
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
	return (-1);
}

char	*ismeta(char c)
{
	return (ft_strchr("&|;<>()=", (int)c));
}

int	isquote(const char c)
{
	return (c == 34 || c == 39);
}

int	get_one_token_len(char *p)
{
	int		len;

	if (!*p)
		return (0);
	else if (ismeta(*p))
		len = get_operator_len(p);
	else if (isquote(*p))
		len = get_quoted_token_len(p);
	else
	{
		len = 0;
		while (p[len] && !ismeta(p[len]) && !isquote(p[len]) && p[len] != ' ' && p[len] != '\t')
			len++;
	}
	return (len);
}

int	store_one_token(t_token *head, char *p, unsigned int start, size_t token_len)
{
	char	*str;
	t_token	*new_token;

	if (!head || !token_len)
		return (FAILURE);
	str = ft_substr(p, start, token_len);
	if (!str)
		return (FAILURE);
	new_token = create_token(str);
	if (!new_token)
	{
		free(str);
		return (FAILURE);
	}
	add_token_last(head, new_token);
	return (SUCCESS);
}

t_token	*tokenizer(char *p)
{
	t_token	*head;
	int		i;
	int		len;

	head = create_token("");
	i = 0;
	while (p[i])
	{
		while (p[i] == ' ' || p[i] == '\t')
			i++;
		if (!p[i])
			break ;
		printf("i = %d, p[i] = %c\n", i, p[i]);
		len = get_one_token_len(&(p[i]));
		store_one_token(head, p, i, len);
		i += len;
	}
	return (head);
}

