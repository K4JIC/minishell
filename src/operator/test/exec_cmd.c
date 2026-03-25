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

	(void)env;
	if (cmd->type != CMD_EXEC)
		return (-1);
	cmd_e = (t_cmd_exec *)cmd;
	if (!cmd_e->name || !cmd_e->args || !cmd_e->args[0])
		return (-1);
	execvp(cmd_e->name, cmd_e->args);
	return (-1);
}

// test function
t_cmd_exec	*create_node(char *cmdname, char **args)
{
	t_cmd_exec	*ret;

	ret = ft_calloc(1, sizeof(t_cmd_exec));
	ret->type = CMD_EXEC;
	ret->name = cmdname;
	ret->args = args;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_exec	*cmdhead;
	t_env_set	env;
	char	*args[3] = {"ls", "-l", NULL};

	cmdhead = create_node("ls", args);
	env.env_list = envp_to_lst(envp);
	env.envp = envp;
	exec_cmd((t_cmd *)cmdhead, &env);

	(void)argc;
	(void)argv;
}
