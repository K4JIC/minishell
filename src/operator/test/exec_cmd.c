#include "minishell.h"
#include "operator.h"
#include "exec_cmd.h"
#include <stdlib.h>

int	exec_cmd(t_cmd *cmd, t_env_set *env);
// int	redir_cmd(t_cmd *cmd, t_env_set *env);
// int	pipe_cmd(t_cmd *cmd, t_env_set *env);
// int	list_cmd(t_cmd *cmd, t_env_set *env);

// int	process_one_cmd(t_cmd *cmd, t_env_set *env)
// {
// 	if (cmd->type == CMD_EXEC)
// 	{
// 		exec_cmd(cmd, env);
// 	}
// 	if (cmd->type == CMD_REDIR)
// 	{
// 		redir_cmd(cmd, env);
// 	}
// 	if (cmd->type == CMD_PIPE)
// 	{
// 		pipe_cmd(cmd, env);
// 	}
// 	if (cmd->type == CMD_LIST)
// 	{
// 		list_cmd(cmd, env);
// 	}
// 	return (-1);
// }

char	*getenvvalue(t_list *env_list, char *key)
{
	t_list	*cur;
	t_env	*env;

	cur = env_list;
	while (cur)
	{
		env = (t_env *)cur->content;
		if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			return (env->value);
		cur = cur->next;
	}
	return (NULL);
}

int	exec_cmd(t_cmd *cmd, t_env_set *env)
{
	t_cmd_exec	*cmd_e;
	char		*env_path;
	char		*cmd_path;

	if (cmd->type != CMD_EXEC)
		return (-1);
	cmd_e = (t_cmd_exec *)cmd;
	env_path = getenvvalue(env->env_list, "PATH");
	cmd_path = NULL;
	if (isexecutable(cmd_e->name, env_path, &cmd_path) == -1)
	{
		free(cmd_path);
		return (-1);
	}
	execve(cmd_path, cmd_e->args, env->envp);
	return (0);
}

// test function
t_cmd_exec	*create_node(char *cmdname, char **args)
{
	t_cmd_exec	*ret;

	ret = ft_calloc(1, sizeof(t_cmd_exec));
	ret->name = cmdname;
	ret->args = args;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_exec	*cmdhead;
	t_env_set	env;
	char	*args[2] = {"-l", NULL};

	cmdhead = create_node("ls", args);
	env.env_list = envp_to_lst(envp);
	env.envp = envp;
	exec_cmd((t_cmd *)cmdhead, &env);

	(void)argc;
	(void)argv;
}
