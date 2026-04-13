/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/13 22:32:57 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	convert_pipe(t_minishell *sh, t_cmd_base **parent, t_token_lr lr)
{
	int	ret;

	if (lr.left.head == NULL || lr.right.head == NULL)
		return (syntax_error("syntax error near unexpected token '|'", sh), FAILURE);
	*parent = create_cmd_btree_node(OP_PIPE);
	if (!*parent)
		return (FAILURE);
	ret = dispatch_token_conversion(sh, &((t_cmd_btree *)*parent)->left,
			lr.left.head, lr.left.tail);
	if (ret == FAILURE)
		return (free(*parent), FAILURE);
	ret = dispatch_token_conversion(sh, &((t_cmd_btree *)*parent)->right,
			lr.right.head, lr.right.tail);
	if (ret == FAILURE)
	{
		free_cmds(((t_cmd_btree *)*parent)->left);
		return (free(*parent), FAILURE);
	}
	return (SUCCESS);
}
