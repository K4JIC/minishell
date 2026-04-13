/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/13 22:32:57 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_operator(t_token *head, t_token *tail, t_operator_type del)
{
	t_token	*cur;

	cur = head;
	while (cur != NULL && cur != tail)
	{
		if (cur->type == TK_OPERATOR)
		{
			if (((t_token_operator *)cur)->op_type == del)
				return (cur);
		}
		cur = (t_token *)((t_head_list *)cur)->next;
	}
	return (NULL);
}

static t_token_lr	separate_at_token(t_token *head, t_token *tail, t_token *op)
{
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	if (op != head)
		lr.left.head = head;
	lr.left.tail = op;
	lr.right.head = (t_token *)((t_head_list *)op)->next;
	lr.right.tail = tail;
	return (lr);
}

static t_token_lr	sep_token_list(t_token *head, t_token *tail,
		t_operator_type del)
{
	t_token		*op;
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	op = find_operator(head, tail, del);
	if (op == NULL)
		return (lr);
	lr = separate_at_token(head, tail, op);
	lr.found_op = del;
	return (lr);
}

t_token_lr	sep_token_list_op(t_token *head, t_token *tail)
{
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	lr = sep_token_list(head, tail, OP_LIST);
	if (lr.right.head != NULL)
		return (lr);
	lr = sep_token_list(head, tail, OP_PIPE);
	if (lr.right.head != NULL)
		return (lr);
	lr.found_op = NO_OP;
	return (lr);
}
