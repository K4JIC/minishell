#include "minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->is_env = true;
	node->next = NULL;
	return (node);
}

static void	add_env_node(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static int set_val_and_key(char *env_str, t_env **env_list)
{
	t_env	*new_node;
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
	add_env_node(env_list, new_node);
	return (SUCCESS);
}

t_env	*envp_to_lst(char **envp)
{
	t_env	*env_list;
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
