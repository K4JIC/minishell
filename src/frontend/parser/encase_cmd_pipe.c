/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/14 18:50:35 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int validate_pipe(t_token_lr lr)
{
	if (lr.left.head == NULL || lr.right.head == NULL)
		return (FAILURE);
	if (lr.left.head == lr.left.tail)
		return (FAILURE);
	return (SUCCESS);
}

static t_cmd_base	*create_pipe_node(void)
{
	t_cmd_base	*ret;

	ret = ft_calloc(sizeof(t_cmd_pipe), 1);
	if (!ret)
		return (NULL);
	ret->type = CMD_PIPE;
	return ((t_cmd_base *)ret);
}

int	convert_pipe(t_minishell *sh, t_cmd_base **parent, t_token_lr lr)
{
	int	ret;

	if (validate_pipe(lr) == FAILURE)
		return (syntax_error("syntax error near unexpected token '|'", sh), FAILURE);
	*parent = create_pipe_node();
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
