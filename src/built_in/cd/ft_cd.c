#include "minishell.h"

static char	*get_cd_path(t_cmd *cmd, t_list *env_list)
{
	t_env	*env;

	if (cmd->args[1] == NULL)
	{
		env = find_env(env_list, "HOME");
		if (!env)
			return (ft_putstr_fd("cd: HOME not set\n", 2), NULL);
		return (env->value);
	}
	if (cmd->args[1][0] == '-' && cmd->args[1][1] != '\0')
	{
		env = find_env(env_list, "OLDPWD");
		if (!env)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
		ft_putstr_fd(env->value, 1);
		write(1, "\n", 1);
		return (env->value);
	}
	return (cmd->args[1]);
}

static int	update_pwd(t_list **env_list)
{
	char	*cwd;
	t_env	*env;

	env = find_env(*env_list, "PWD");
	if (env)
		set_env(env_list, "OLDPWD", env->value);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (FAILURE);
	set_env(env_list, "PWD", cwd);
	free(cwd);
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_list **env_list)
{
	char	*path;

	path = get_cd_path(cmd, *env_list);
	if (!path)
			return (FAILURE);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (FAILURE);
	}
	return (update_pwd(env_list));
}
