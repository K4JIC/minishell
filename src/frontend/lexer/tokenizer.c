/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:31:17 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 20:59:05 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	store_one_token(t_token **head,
		char *p, unsigned int start, t_token_type_len token_len)
{
	char	*str;
	t_token	*new_token;

	if (!token_len.len)
		return (FAILURE);
	str = ft_substr(p, start, token_len.len);
	if (!str)
		return (FAILURE);
	new_token = create_token(str, token_len.type);
	if (!new_token)
	{
		free(str);
		return (FAILURE);
	}
	if (!*head)
		*head = new_token;
	else
		add_token_last(*head, new_token);
	return (SUCCESS);
}

t_token	*tokenizer(char *p)
{
	t_token				*head;
	int					i;
	t_token_type_len	tlen;

	head = NULL;
	i = 0;
	while (p[i])
	{
		while (p[i] == ' ' || p[i] == '\t')
			i++;
		if (!p[i])
			break ;
		tlen = get_one_token_len(&(p[i]));
		if (tlen.len < 0 || store_one_token(&head, p, i, tlen) == FAILURE)
		{
			if (tlen.len == NO_CLOSE_QUOTE)
				ft_putstr_fd("No end of quote\n", 2);
			free_all_token(head);
			return (NULL);
		}
		i += tlen.len;
	}
	return (head);
}
