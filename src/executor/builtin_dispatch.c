#include "minishell.h"

bool	is_builtin(const char *name)
{
	if (!name)
		return (false);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(name, "export", 7) == 0)
		return (true);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(name, "env", 4) == 0)
		return (true);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (true);
	return (false);
}

int	dispatch_builtin(char **args, t_minishell *ms)
{
	char	*name;

	if (!args || !args[0])
		return (SUCCESS);
	name = args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_echo(args));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_cd(args, &ms->env_list));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(name, "export", 7) == 0)
		return (ft_export(args, &ms->env_list));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (ft_unset(args, &ms->env_list));
	if (ft_strncmp(name, "env", 4) == 0)
		return (ft_env(ms->env_list));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (ft_exit(args, ms));
	return (FAILURE);
}
