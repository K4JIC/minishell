#include "minishell.h"

t_env	*find_env(t_list *env_list, char *key)
{
	t_list	*current;
	t_env	*env;

	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		current = current->next;
	}
	return (NULL);
}
