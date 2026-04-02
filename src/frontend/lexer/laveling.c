/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laveling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:04:56 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 17:01:54 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token_type	distinguish_type(char *str)
{
	if (!str)
		return (-1);
	else if (ft_strncmp(">>", str, 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp("<<", str, 2) == 0)
		return (TOKEN_HEREDOC);
	else if (str[0] == '<')
		return (TOKEN_REDIR_IN);
	else if (str[0] == '>')
		return (TOKEN_REDIR_OUT);
	else if (str[0] == '|')
		return (TK_PIPE);
	else if (str[0] == ';')
		return (TK_LIST);
	else
		return (TK_WORD);
}

void	*set_one_op_lavel(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	if (casted_token->type == TK_WORD)
		return ((void *)1);
	casted_token->type = distinguish_type(casted_token->str);
	return ((void *)1);
}

void	set_all_op_lavel(t_token *head)
{
	apply_func((t_head_list *)head, set_one_op_lavel);
}
