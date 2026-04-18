/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:04:56 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/18 15:19:23 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator_type	distinguish_op_type(char *str)
{
	if (!str)
		return (-1);
	else if (ft_strncmp(">>", str, 2) == 0)
		return (OP_REDIR_APP);
	else if (ft_strncmp("<<", str, 2) == 0)
		return (OP_REDIR_HDOC);
	else if (str[0] == '<' && str[1] == 0)
		return (OP_REDIR_IN);
	else if (str[0] == '>' && str[1] == 0)
		return (OP_REDIR_OUT);
	else if (str[0] == '|' && str[1] == 0)
		return (OP_PIPE);
	else if (str[0] == ';' && str[1] == 0)
		return (OP_LIST);
	else
		return (OP_NOT_IMPLEMENTED);
}

static int	set_one_op_label(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	if (casted_token->type == TK_WORD)
		return (SUCCESS);
	((t_token_operator *)casted_token)->op_type = distinguish_op_type(casted_token->str);
	return (SUCCESS);
}

void	set_all_op_label(t_token *head)
{
	apply_func((t_head_list *)head, set_one_op_label);
}
