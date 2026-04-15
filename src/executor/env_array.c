#include "minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	count_env_list(t_list *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	*env_to_str(t_env *env)
{
	char	*tmp;
	char	*result;

	if (!env->value)
		return (ft_strdup(env->key));
	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

char	**env_list_to_envp(t_list *env_list)
{
	char	**envp;
	int		count;
	int		i;

	count = count_env_list(env_list);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i] = env_to_str((t_env *)env_list->content);
		if (!envp[i])
			return (free_str_array(envp), NULL);
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
