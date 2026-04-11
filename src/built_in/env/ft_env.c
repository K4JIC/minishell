#include "minishell.h"

int	ft_env(t_list *env_list)
{
	t_list	*current;
	t_env	*env;

	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (!env->value)
		{
			current = current->next;
			continue;
		}
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
	return (SUCCESS);
}
