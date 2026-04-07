#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_one(char *arg, t_list **env_list)
{
	char	*equal;
	char	*key;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (FAILURE);
	}
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (!find_env(*env_list, arg))
			return (set_env(env_list, arg, NULL));
		return (SUCCESS);
	}
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (FAILURE);
	if (set_env(env_list, key, equal + 1) == FAILURE)
		return (free(key), FAILURE);
	free(key);
	return (SUCCESS);
}

int	ft_export(t_cmd *cmd, t_list **env_list)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (print_export(*env_list));
	ret = SUCCESS;
	i = 1;
	while(cmd->args[i])
	{
		if (export_one(cmd->args[i], env_list) == FAILURE)
			ret = FAILURE;
		i++;
	}
	return (ret);
}
