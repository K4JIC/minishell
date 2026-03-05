

#include "tokenizer.h"

char	*search_envval(t_list *envlist, char *key)
{
	t_list	*curr;

	curr = envlist;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int	get_envval_key_len(char *p)
{
	int	len;

	if (!p || p[0] != '$')
		return (-1);
	len = 1;
	while ('A' <= p[len] && p[len] <= 'Z')
		len++;
	return (len);
}

char	*substitute_envval(char *p)
{

}

char	*expand_double_quote(char *p)
{
}
char	*expand_single_quote(char *p)
char	*expand_quote(char *p)
{
}
