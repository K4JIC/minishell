#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_list **env_list)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env(env_list, cmd->args[i]);
		i++;
	}
	return (SUCCESS);
}
