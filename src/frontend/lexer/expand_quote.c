#include "minishell.h"

static int	expand_single_quote(char *p, t_dynamic_str *buf)
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

static int	expand_double_quote(char *p, t_dynamic_str *buf, t_list *env_list, int exit_status)
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
