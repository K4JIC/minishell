#include "minishell.h"

static char	*get_cd_path(char **args, t_list *env_list)
{
	t_env	*env;

	if (args[1] == NULL)
	{
		env = find_env(env_list, "HOME");
		if (!env || !env->value)
			return (ft_putstr_fd("cd: HOME not set\n", 2), NULL);
		return (env->value);
	}
	if (args[1][0] == '-' && args[1][1] == '\0')
	{
		env = find_env(env_list, "OLDPWD");
		if (!env || !env->value)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
		ft_putstr_fd(env->value, 1);
		write(1, "\n", 1);
		return (env->value);
	}
	return (args[1]);
}

static int	update_pwd(t_list **env_list)
{
	char	*cwd;
	t_env	*env;

	env = find_env(*env_list, "PWD");
	if (env && env->value)
	{
		if (set_env(env_list, "OLDPWD", env->value) == FAILURE)
			return (FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (FAILURE);
	if (set_env(env_list, "PWD", cwd) == FAILURE)
		return (free(cwd), FAILURE);
	free(cwd);
	return (SUCCESS);
}

int	ft_cd(char **args, t_list **env_list)
{
	char	*path;

	path = get_cd_path(args, *env_list);
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
