/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:08:05 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/28 18:27:08 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operate_list.h"
#include <stdio.h>

/**
 * functions for confirm all member of the token list. use for debug.
 */

void	*print_token(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	printf("id = %2d, type = %2d, str = %s\n", casted_token->id, casted_token->type, casted_token->str);
	return (token);
}

void	print_all_token(t_token *head)
{
	apply_func(&head->list, print_token);
}
