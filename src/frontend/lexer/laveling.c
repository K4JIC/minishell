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
		return (PIPE);
	else
		return (WORD);
}

void	*set_one_lavel(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	casted_token->type = distinguish_type(casted_token->str);
	return ((void *)1);
}

void	set_all_lavel(t_token *head)
{
	apply_func((t_head_list *)head, set_one_lavel);
}
