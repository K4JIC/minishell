/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:15:51 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/22 23:39:48 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_dynamic_str
{
	char	*str;
	int		len;
	int		capa;
}	t_dynamic_str;

static int	ensure_buf_capacity(t_dynamic_str *buf, int add_len)
{
	int		newcapa;
	int		need;
	char	*newstr;
	size_t	copied;

	if (!buf || !buf->str || add_len < 0)
		return (FAILURE);
	need = buf->len + add_len + 1;
	if (need <= buf->capa)
		return (SUCCESS);
	newcapa = buf->capa;
	while (newcapa < need)
		newcapa *= 2;
	newstr = ft_calloc(newcapa, 1);
	if (!newstr)
		return (FAILURE);
	copied = ft_strlcpy(newstr, buf->str, newcapa);
	if (copied >= (size_t)newcapa)
		return (free(newstr), FAILURE);
	free(buf->str);
	buf->str = newstr;
	buf->capa = newcapa;
	return (SUCCESS);
}

t_dynamic_str	*init_buf(void)
{
	t_dynamic_str	*buf;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_calloc(1, sizeof(t_dynamic_str));
	if (!buf)
		return (NULL);
	buf->str = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buf->str)
		return (free(buf), NULL);
	buf->capa = BUFFER_SIZE;
	return (buf);
}

void	free_str_len(t_dynamic_str *buf)
{
	if (!buf)
		return ;
	if (buf->str)
		free(buf->str);
	free(buf);
}

int	putnstr_buf(t_dynamic_str *buf, const char *str, int n)
{
	if (!buf || !buf->str || !str)
		return (FAILURE);
	if (ensure_buf_capacity(buf, n) == FAILURE)
		return (FAILURE);
	ft_memcpy(buf->str + buf->len, str, n);
	buf->len += n;
	buf->str[buf->len] = '\0';
	return (SUCCESS);
}

int	putstr_buf(t_dynamic_str *buf, const char *str)
{
	int	len;

	len = ft_strlen(str);
	return (putnstr_buf(buf, str, len));
}

int	expand_as_dollar_mark(t_dynamic_str *buf)
{
	int	len;

	len = 1;
	if (putstr_buf(buf, "$") == FAILURE)
		return (-1);
	return (len);
}

int	expand_as_envval(char *dollar, t_dynamic_str *buf, t_list *env_list)
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

int	expand_as_exit_status(t_dynamic_str *buf, int exit_status)
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

int	expand_single_quote(char *p, t_dynamic_str *buf)
{
	int	len;

	len = 0;
	if (!p || p[0] != '\'')
		return (-1);
	len++;
	while (p[len] && p[len] != '\'')
		len++;
	if (len <= 1)
		return (len);
	if (putnstr_buf(buf, &p[1], len - 1) == FAILURE)
		return (-1);
	return (len + 1);
}

int	expand_double_quote(char *p, t_dynamic_str *buf, t_list *env_list, int exit_status)
{
	int			total_len;
	int			len;

	total_len = 0;
	if (!p || p[0] != '\"')
		return (-1);
	total_len++;
	while (p[total_len] && p[total_len] != '\"')
	{
		if (p[total_len] == '$')
			len = expand_dollar_mark(&p[total_len], buf, env_list, exit_status);
		else
			len = no_expand(p[total_len], buf);
		if (len == -1)
			return (-1);
		total_len += len;
	}
	return (total_len + 1);
}

int	expand_quote(char *p, t_dynamic_str *buf, t_list *env_list, int exit_status)
{
	if (!p || (*p != '\'' && *p != '\"'))
		return (-1);
	if (*p == '\'')
		return (expand_single_quote(p, buf));
	if (*p == '\"')
		return (expand_double_quote(p, buf, env_list, exit_status));
	return (-1);
}

int	no_expand(char p, t_dynamic_str *buf)
{
	if (putnstr_buf(buf, &p, 1) == FAILURE)
		return (-1);
	return (1);
}

int	dispatch_expand_one_str(char *p, t_dynamic_str *buf, t_list *env_list, int exit_status)
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

void	*expand_one_token(void *raw_token, void *raw_minishell)
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
		return (free_str_len(buf), NULL);
	free(token->str);
	token->str = buf->str;
	free(buf);
	return ((void *)1);
}

int	expand_token(t_token *tk_head, t_minishell *ms)
{
	return (apply_func_ctx((t_head_list *)tk_head, ms, expand_one_token));
}

// int	expand_token(t_token *tk_head, t_list *envlist)
// {
	// if (!tk_head)
		// return (FAILURE);
	// if (expand_envval(tk_head, envlist) == FAILURE)
		// return (FAILURE);
	// if (expand_quotes(tk_head, envlist) == FAILURE)
		// return (FAILURE);
	// if (delete_quote_mark(tk_head) == FAILURE)
		// return (FAILURE);
	// return (SUCCESS);
// }