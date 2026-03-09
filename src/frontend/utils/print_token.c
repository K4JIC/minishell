/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:08:05 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 21:00:32 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// print all member of tokens. use for debug.
void	*print_token(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	ft_printf("id = %2d, type = %2d, str = %s\n",
		casted_token->id, casted_token->type, casted_token->str);
	return (token);
}

void	print_all_token(t_token *head)
{
	apply_func(&head->list, print_token);
}
