/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:15:51 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/23 01:17:59 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_expand(char p, t_dynamic_str *buf)
{
	if (putnstr_buf(buf, &p, 1) == FAILURE)
		return (-1);
	return (1);
}

static int	dispatch_expand_one_str(char *p, t_dynamic_str *buf, t_list *env_list, int exit_status)
{
	int			i;
	int			len;

	i = 0;
	while (p[i])
	{
	if (p[i] == '$')
			len = expand_dollar_mark(&p[i], buf, env_list, exit_status);
		else if (isquote(p[i]))
			len = expand_quote(&p[i], buf, env_list, exit_status);
		else
			len = no_expand(p[i], buf);
		if (len == -1)
			return (FAILURE);
		i += len;
	}
	return (SUCCESS);
}

static void	*expand_one_token(void *raw_token, void *raw_minishell)
{
	t_token		*token;
	t_minishell	*ms;
	t_dynamic_str	*buf;
	int			ret;

	token = (t_token *)raw_token;
	ms = (t_minishell *)raw_minishell;
	buf = init_buf();
	if (!buf)
		return (NULL);
	ret = dispatch_expand_one_str(token->str, buf, ms->env_list, ms->exit_status);
	if (ret == FAILURE)
		return (free_dynamic_str(buf), NULL);
	free(token->str);
	token->str = buf->str;
	free(buf);
	return ((void *)1);
}

int	expand_token(t_token *tk_head, t_minishell *ms)
{
	return (apply_func_ctx((t_head_list *)tk_head, ms, expand_one_token));
}
