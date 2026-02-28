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

#include "operate_list.h"
#include "libft.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

// specialized func
t_token	*create_token(char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	bzero(new_token, sizeof(t_token));
	new_token->str = str;
	return (new_token);
}

// specialized func
void	add_token_last(t_token *head, t_token *new_token)
{
	t_head_list	*last_list;

	last_list = get_last_node(&head->list);
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

