#include "minishell.h"

static int	exec_simple(t_cmd_exec *cmd, t_minishell *ms)
{
	if (!cmd->args || !cmd->args[0])
		return (SUCCESS);
	if (is_builtin(cmd->args[0]))
		return (dispatch_builtin(cmd->args, ms));
	return (exec_external(cmd, ms));
}

static int	exec_node(t_cmd_base *node, t_minishell *ms)
{
	if (!node)
		return (SUCCESS);
	if (node->type == CMD_EXEC)
		return (exec_simple((t_cmd_exec *)node, ms));
	ft_putstr_fd("executor: node type not implemented\n", STDERR_FILENO);
	return (FAILURE);
}

int	executor(t_cmd_base *tree, t_minishell *ms)
{
	int	status;

	if (!tree)
		return (SUCCESS);
	status = exec_node(tree, ms);
	ms->exit_status = status;
	return (status);
}
