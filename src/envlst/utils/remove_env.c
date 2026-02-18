#include "minishell.h"

static void	unlink_and_free(t_list **env_list, t_list *prev, t_list *current)
{
	if (prev)
		prev->next = current->next;
	else
		*env_list = current->next;
	free_env_content((t_env *)current->content);
	free(current);
}

int	remove_env(t_list **env_list, char *key)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env;

	prev = NULL;
	current = *env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			unlink_and_free(env_list, prev, current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}
