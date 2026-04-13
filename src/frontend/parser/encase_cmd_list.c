/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/06 23:10:13 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	convert_list(t_minishell *sh, t_cmd_base **parent, t_token_lr lr)
{
	int	ret;

	if (lr.left == NULL || lr.right == NULL)
		return (syntax_error("syntax error near unexpected token ';'", sh), FAILURE);
	*parent = create_cmd_btree_node(OP_LIST);
	if (!*parent)
		return (FAILURE);
	ret = convert_token_to_cmd(sh, &((t_cmd_btree *)*parent)->left, lr.left);
	if (ret == FAILURE)
		return (free(*parent), FAILURE);
	ret = convert_token_to_cmd(sh, &((t_cmd_btree *)*parent)->right, lr.right);
	if (ret == FAILURE)
	{
		free_cmds(((t_cmd_btree *)*parent)->left);
		return (free(*parent), FAILURE);
	}
	return (SUCCESS);
}
