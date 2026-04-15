#include "minishell.h"

int	ft_unset(char **args, t_list **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env(env_list, args[i]);
		i++;
	}
	return (SUCCESS);
}
