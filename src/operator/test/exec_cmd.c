#include "operator.h"

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

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd_exec	*cmd_e;
	char		*cmd_path;

	if (cmd->type != CMD_EXEC)
		return (-1);
	cmd_e = (t_cmd_exec *)cmd;
	if (isaccessible(cmd->name, env->envlist, cmd_path) == -1)
}
