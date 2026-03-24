#include "minishell.h"

static t_env	*create_env_content(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (!env->key)
	{
		free(env);
		return (NULL);
	}
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	return (env);
}

static t_list	*create_env_node(char *key, char *value)
{
	t_env	*env;
	t_list	*node;

	env = create_env_content(key, value);
	if (!env)
		return (NULL);
	node = ft_lstnew(env);
	if (!node)
	{
		free(env->value);
		free(env->key);
		free(env);
		return (NULL);
	}
	return (node);
}

static int	set_val_and_key(char *env_str, t_list **env_list)
{
	t_list	*new_node;
	char	*key;
	char	*value;

	value = ft_strchr(env_str, '=');
	if (!value)
		return (SKIP);
	key = ft_substr(env_str, 0, value - env_str);
	if (!key)
		return (SKIP);
	new_node = create_env_node(key, value + 1);
	free(key);
	if (!new_node)
		return (FAILURE);
	// TODO: Maybe there aren't enough NULL checks.
	ft_lstadd_back(env_list, new_node);
	return (SUCCESS);
}

t_list	*envp_to_lst(char **envp)
{
	t_list	*env_list;
	int		ret;
	int		i;

	if (!envp)
		return (NULL);
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		ret = set_val_and_key(envp[i], &env_list);
        // TODO: consider handling SKIP case if needed
		if (ret == FAILURE)
			return (NULL);
		i++;
	}
	return (env_list);
}
