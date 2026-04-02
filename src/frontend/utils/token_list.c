/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:07:56 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/28 17:47:07 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

// specialized func
t_token	*create_token(char *str, t_token_type type)
{
	t_token	*new_token;

	if (type != TK_WORD && type != TK_OPERATOR)
		return (NULL);
	new_token = NULL;
	if (type == TK_WORD)
		new_token = ft_calloc(sizeof(t_token_word), 1);
	else if (type == TK_OPERATOR)
		new_token = ft_calloc(sizeof(t_token_operator), 1);
	if (!new_token)
		return (NULL);
	ft_bzero(new_token, sizeof(t_token));
	new_token->str = str;
	new_token->type = type;
	return (new_token);
}

// specialized func
void	add_token_last(t_token *head, t_token *new_token)
{
	t_head_list	*last_list;

	last_list = get_last_node(&head->list);
	// new_token->id = ((t_token *)last_list)->id + 1;
	add_next_node(last_list, &new_token->list);
}

void	*free_token(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	if (casted_token->str)
		free(casted_token->str);
	free(casted_token);
	return ((void *)1);
}

void	free_all_token(t_token *head)
{
	apply_func(&head->list, free_token);
}
