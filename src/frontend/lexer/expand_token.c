#include "minishell.h"

char	*get_env_key(char *rawtext)
{
	char	*keytop;

	keytop = ft_strchr(rawtext, '$');
	if (!keytop)
		return (NULL);
	
}

char	*substitute_envval(char *rawtext, t_list *envlist)
{
	char	*expanded;
	char	*key;
	char	*value;

	key = get_env_key(rawtext);
	while (key)
	{
	}
}

void	*expand_envval_one(void *tk_one, void *ctx)
{
	t_token	*tk;
	char	*expanded;

	tk = (t_token *)tk_one;
	if (!tk || tk->type != TK_WORD || !tk->str)
		return ((void *)1);
	expanded = substitute_envval(tk->str, (t_list *)ctx);
	if (!expanded)
		return (NULL);
	free(tk->str);
	tk->str = expanded;
	return ((void *)1);
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