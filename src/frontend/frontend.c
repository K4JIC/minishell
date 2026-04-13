/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:11:10 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/14 04:16:40 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	frontend(char *input, t_minishell *ms)
{
	t_token		*tk_head;
	t_cmd_base	*cmd_head;
	int			ret;

	tk_head = convert_line_to_token(input);
	if (tk_head == NULL)
		return (FAILURE);
	set_all_op_label(tk_head);
	ms->tokens = tk_head;
	ret = convert_token_to_cmd(ms, &cmd_head, tk_head);
	free_all_token(ms->tokens);
	if (ret == FAILURE)
	{
		ms->tokens = NULL;
		return (FAILURE);
	}
	ms->tokens = NULL;
	ms->cmd_btree = cmd_head;
	return (SUCCESS);
}
