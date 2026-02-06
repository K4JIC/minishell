#include "minishell.h"

static bool	option_check(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	bool	nl_flag;

	i = 1;
	nl_flag = true;

	while (cmd->args[i] && option_check(cmd->args[i]))
	{
		nl_flag = false;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (nl_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
