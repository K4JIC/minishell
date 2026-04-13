#include "minishell.h"

static t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	if (!env->key || (value && !env->value))
	{
		free_env_content(env);
		return (NULL);
	}
	return (env);
}

static int	add_env(t_list **env_list, char *key, char *value)
{
	t_env	*env;
	t_list	*node;

	env = create_env(key, value);
	if (!env)
		return (FAILURE);
	node = ft_lstnew(env);
	if (!node)
	{
		free_env_content(env);
		return (FAILURE);
	}
	ft_lstadd_back(env_list, node);
	return (SUCCESS);
}

int	set_env(t_list **env_list, char *key, char *value)
{
	t_env	*env;
	char	*new_value;

	env = find_env(*env_list, key);
	if (env)
	{
		if (value)
			new_value = ft_strdup(value);
		else
			new_value = NULL;
		if (value && !new_value)
			return (FAILURE);
		free(env->value);
		env->value = new_value;
		return (SUCCESS);
	}
	return (add_env(env_list, key, value));
}
