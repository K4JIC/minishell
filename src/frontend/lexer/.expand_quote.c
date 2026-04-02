
#include "minishell.h"
#include "tokenizer.h"

char	*getenvvalue(t_list *env_list, char *key)
{
	t_list	*cur;
	t_env	*env;

	cur = env_list;
	while (cur)
	{
		env = (t_env *)cur->content;
		if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			return (env->value);
		cur = cur->next;
	}
	return (NULL);
}

int	get_envval_key_len(char *p)
{
	int	len;

	if (!p || p[0] != '$')
		return (-1);
	len = 1;
	while (ft_isalpha(p[len]) || ft_isdigit(p[len]) || p[len] == '_')
		len++;
	return (len);
}

char	*join_value(char *form_val, char *val, char *latt_val)
{
	char	*js1;
	char	*js2;

	if (!val)
		js1 = form_val;
	if (!form_val)
		js1
	js1 = ft_strjoin(s1, s2);
	if (!js1)
		return (NULL);
}

char	*substitute_envval_helper(char *p, char *env_start,
	char *env_end, t_list *envlist)
{
	char	*former;
	char	*latter;
	char	*key;
	char	*value;
	char	*joined_str;

	former = ft_substr(p, 0, env_start - p);
	if (!former)
		return (NULL);
	latter = ft_substr(p, env_end - p + 1, ft_strlen(p) - (env_end - p));
	if (!latter)
		return (free(former), NULL);
	key = ft_substr(p, env_start - p, env_end - env_start);
	if (!key)
		return (free(former), free(latter), NULL);
	value = getenvvalue(envlist, key);
	joined_str = ft_strjoin3(former, value, latter);
}

char	*substitute_envval(char *p, t_list *envlist)
{
	char	*env_start;
	char	*env_end;
	char	*joined_str;

	env_start = ft_strchr(p, '$');
	env_end = env_start + get_envval_key_len(env_start);
	joined_str = substitute_envval_helper(p, env_start, env_end, envlist);
	if (!joined_str)
		return (NULL);
	return (joined_str);
}

char	*expand_double_quote(char *p)
{
}
char	*expand_single_quote(char *p)
char	*expand_quote(char *p)
{
}
