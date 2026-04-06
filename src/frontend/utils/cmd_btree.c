#include "minishell.h"
#include "cmd.h"

static void	free_cmd_exec(t_cmd_exec *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	if (cmd->name != NULL)
		free(cmd->name);
	if (cmd->args != NULL)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

static void	free_cmd_redir(t_cmd_redir *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->cmd_head != NULL)
		free_cmds(cmd->cmd_head);
	if (cmd->filename != NULL)
		free(cmd->filename);
	if (cmd->fd >= 0)
		close(cmd->fd);
	free(cmd);
}

static void	free_cmd_btree(t_cmd_btree *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->left != NULL)
		free_cmds(cmd->left);
	if (cmd->right != NULL)
		free_cmds(cmd->right);
	free(cmd);
}

void	free_cmds(t_cmd_base *cmd_head)
{
	if (cmd_head == NULL)
		return ;
	if (cmd_head->type == CMD_EXEC)
		free_cmd_exec((t_cmd_exec *)cmd_head);
	else if (cmd_head->type == CMD_REDIR)
		free_cmd_redir((t_cmd_redir *)cmd_head);
	else if (cmd_head->type == CMD_PIPE || cmd_head->type == CMD_LIST)
		free_cmd_btree((t_cmd_btree *)cmd_head);
}
