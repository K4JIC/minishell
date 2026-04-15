/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/14 19:33:53 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validate_list(t_token_lr lr)
{
	if (lr.left.head == NULL || lr.right.head == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static t_cmd_base	*create_list_node(void)
{
	t_cmd_base	*ret;

	ret = ft_calloc(sizeof(t_cmd_list), 1);
	if (!ret)
		return (NULL);
	ret->type = CMD_LIST;
	return ((t_cmd_base *)ret);
}

int convert_list(t_minishell *sh, t_cmd_base **parent, t_token_lr lr)
{
	int ret;

	if (validate_list(lr) == FAILURE)
		return (syntax_error("syntax error near unexpected token ';'", sh), FAILURE);
	*parent = create_list_node();
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
