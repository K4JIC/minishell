/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/06 23:10:13 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_operator(t_token *head, t_operator_type del)
{
	t_token	*cur;

	cur = head;
	while (cur != NULL)
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

static t_token_lr	separate_at_token(t_token *head, t_token *op)
{
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	if (((t_head_list *)op)->prev)
		(((t_head_list *)op)->prev)->next = NULL;
	if (((t_head_list *)op)->next)
		(((t_head_list *)op)->next)->prev = NULL;
	if (op != head)
		lr.left = head;
	lr.right = (t_token *)((t_head_list *)op)->next;
	free_token(op);
	return (lr);
}

static t_token_lr	sep_token_list(t_token *head, t_operator_type del)
{
	t_token		*op;
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	op = find_operator(head, del);
	if (op == NULL)
		return (lr);
	lr = separate_at_token(head, op);
	lr.found_op = del;
	return (lr);
}

t_token_lr	sep_token_list_op(t_token *head)
{
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	lr = sep_token_list(head, OP_LIST);
	if (lr.right != NULL)
		return (lr);
	lr = sep_token_list(head, OP_PIPE);
	if (lr.right != NULL)
		return (lr);
	lr.found_op = NO_OP;
	return (lr);
}
