#include "minishell.h"

static char	*join_path(const char *dir, const char *name)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, name);
	free(tmp);
	return (full);
}

static char	*search_in_paths(char **paths, const char *name)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], name);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(const char *name, t_list *env_list)
{
	t_env	*path_env;
	char	**paths;
	char	*result;

	if (!name || !*name)
		return (NULL);
	if (ft_strchr(name, '/'))
	{
		if (access(name, X_OK) == 0)
			return (ft_strdup(name));
		return (NULL);
	}
	path_env = find_env(env_list, "PATH");
	if (!path_env || !path_env->value)
		return (NULL);
	paths = ft_split(path_env->value, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, name);
	free_str_array(paths);
	return (result);
}
