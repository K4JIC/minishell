/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/14 18:44:03 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *msg, t_minishell *sh)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (sh)
		sh->syntax_error = 1;
}

t_cmd_base	*create_cmd_btree_node(t_operator_type type)
{
	t_cmd_base	*ret;

	if (type == OP_PIPE)
	{
		ret = ft_calloc(sizeof(t_cmd_pipe), 1);
		if (!ret)
			return (NULL);
		ret->type = CMD_PIPE;
	}
	else if (type == OP_LIST)
	{
		ret = ft_calloc(sizeof(t_cmd_list), 1);
		if (!ret)
			return (NULL);
		ret->type = CMD_LIST;
	}
	else
		return (NULL);
	return ((t_cmd_base *)ret);
}

int	dispatch_token_conversion(t_minishell *sh, t_cmd_base **parent,
		t_token *head, t_token *tail)
{
	t_token_lr	lr;

	lr = sep_token_list_op(head, tail);
	if (lr.found_op == OP_PIPE)
		return (convert_pipe(sh, parent, lr));
	else if (lr.found_op == OP_LIST)
		return (convert_list(sh, parent, lr));
	else if (lr.found_op == OP_REDIR_IN || lr.found_op == OP_REDIR_OUT
			|| lr.found_op == OP_REDIR_APP || lr.found_op == OP_REDIR_HDOC)
		return (convert_redir(sh, parent, lr));
	else
		return (convert_exec(sh, parent, head, tail));
}

int	convert_token_to_cmd(t_minishell *sh, t_cmd_base **parent, t_token *head)
{
	int	ret;

	ret = dispatch_token_conversion(sh, parent, head, NULL);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
