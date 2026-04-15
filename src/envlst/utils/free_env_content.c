#include "minishell.h"

void	free_env_content(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	del_env(void *content)
{
	free_env_content((t_env *)content);
}
