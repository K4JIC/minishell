/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:37:24 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/18 16:16:47 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanded_token_len(char *str, t_list *envlist)
{
	char	*expanded;
	int		i;
	int		len;
	int		expanded_len;

	i = 0;
	expanded_len = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			len = get_quoted_string_len(&(str[i]));
			expanded_len += len;
		}
		else if (str[i] == '$')
		{
			len = get_envkey_len(&(str[i]));
			expanded_len += get_envval_len(&(str[i]), len, envlist);
		}
		else
		{
			len = 1;
			expanded_len++;
		}
		i += len;
	}
	return (expanded_len);
}

int	expand_envval_one(void *tk_one, void *envlist)
{
	t_token	*tk;
	char	*expanded;

	tk = (t_token *)tk_one;
	if (!tk || !tk->str)
		return (FAILURE);
	if (tk->type != TK_WORD)
		return (SUCCESS);
	expanded = substitute_envval(tk->str, (t_list *)envlist);
	if (!expanded)
		return (FAILURE);
	free(tk->str);
	tk->str = expanded;
	return (SUCCESS);
}

int	expand_envval(t_token *tk_head, t_list *envlist)
{
	return (apply_func_ctx((t_head_list *)tk_head, envlist, expand_envval_one));
}

int	expand_token(t_token *tk_head, t_list *envlist)
{
	if (!tk_head)
		return (FAILURE);
	if (expand_envval(tk_head, envlist) == FAILURE)
		return (FAILURE);
	if (expand_quote(tk_head, envlist) == FAILURE)
		return (FAILURE);
	if (delete_quote_mark(tk_head) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}