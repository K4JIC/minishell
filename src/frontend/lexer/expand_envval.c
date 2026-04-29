/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 01:59:08 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/23 01:59:10 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_as_dollar_mark(t_dynamic_str *buf)
{
	int	len;

	len = 1;
	if (putstr_buf(buf, "$") == FAILURE)
		return (-1);
	return (len);
}

static int	expand_as_envval(char *dollar, t_dynamic_str *buf, t_list *env_list)
{
	int		keylen;
	char	*key;
	t_env	*env;

	keylen = 1;
	while (ft_isalnum(dollar[keylen]) || dollar[keylen] == '_')
		keylen++;
	key = ft_substr(dollar, 1, keylen - 1);
	if (!key)
		return (-1);
	env = find_env(env_list, key);
	free(key);
	if (!env)
		return (keylen);
	if (putstr_buf(buf, env->value) == FAILURE)
		return (-1);
	return (keylen);
}

static int	expand_as_exit_status(t_dynamic_str *buf, int exit_status)
{
	int		len;
	char	*str_exit_status;

	len = 2;
	str_exit_status = ft_itoa(exit_status);
	if (!str_exit_status)
		return (-1);
	if (putstr_buf(buf, str_exit_status) == FAILURE)
		return (free(str_exit_status), -1);
	free(str_exit_status);
	return (len);
}

// returns length of strings starts with $
int	expand_dollar_mark(char *dollar, t_dynamic_str *buf, t_list *env_list, int exit_status)
{
	int	len;

	if (ft_isalpha(dollar[1]) || dollar[1] == '_')
		len = expand_as_envval(dollar, buf, env_list);
	else if (dollar[1] == '?')
		len = expand_as_exit_status(buf, exit_status);
	else
		len = expand_as_dollar_mark(buf);
	if (len == -1)
		return (-1);
	return (len);
}
