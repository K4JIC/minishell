#include "minishell.h"

static int	env_list_size(t_list *env_list)
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

static t_env	**env_list_to_arr(t_list *env_list, int count)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (env_list)
	{
		arr[i] = (t_env *)env_list->content;
		env_list = env_list->next;
		i++;
	}
	return (arr);
}

static void	sort_env_arr(t_env **arr, int count)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key, ft_strlen(arr[j + 1]->key) + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_one_env(t_env *env)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
}

int	print_export(t_list *env_list)
{
	t_env **arr;
	int		count;
	int		i;

	count = env_list_size(env_list);
	if (count == 0)
		return (SUCCESS);
	arr = env_list_to_arr(env_list, count);
	if (!arr)
		return (FAILURE);
	sort_env_arr(arr, count);
	i = 0;
	while (i < count)
	{
		print_one_env(arr[i]);
		i++;
	}
	return (free(arr), SUCCESS);
}
