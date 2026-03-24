#include "operator.h"
#include <stdlib.h>

int	exec_cmd(t_cmd *cmd, t_env *env);
int	redir_cmd(t_cmd *cmd, t_env *env);
int	pipe_cmd(t_cmd *cmd, t_env *env);
int	list_cmd(t_cmd *cmd, t_env *env);

int	process_one_cmd(t_cmd *cmd, t_env *env)
{
	if (cmd->type == CMD_EXEC)
	{
		exec_cmd(cmd, env);
	}
	if (cmd->type == CMD_REDIR)
	{
		redir_cmd(cmd, env);
	}
	if (cmd->type == CMD_PIPE)
	{
		pipe_cmd(cmd, env);
	}
	if (cmd->type == CMD_LIST)
	{
		list_cmd(cmd, env);
	}
}

char	*getenvvalue(t_list *env, char *key)
{
	t_list	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd_exec	*cmd_e;
	char		*env_path;
	char		*cmd_path;

	if (cmd->type != CMD_EXEC)
		return (-1);
	cmd_e = (t_cmd_exec *)cmd;
	env_path = getenvvalue(env->envlist, "PATH");
	if (isexecutable(cmd->name, env_path, cmd_path) == -1)
	{
		free(cmd_path);
		return (-1);
	}
	execve(cmd_path, cmd->args, env->envp);
}

// test function
t_cmd	*create_node(char *cmdname, char **args)
{
	t_cmd	*ret;

	ret = ft_calloc(1, sizeof(t_cmd));
	ret->cmd_name = cmdname;
	ret->args = args;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmdhead;
	char	*args[2] = {"-l", NULL};

	cmdhead = create_node("ls", args);

	(void)argc;
	(void)argv;
}
