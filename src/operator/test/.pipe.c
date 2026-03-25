/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 19:01:45 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/09 11:13:05 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"
#include "ms_utils.h"

#include <stdio.h>
#include <sys/wait.h>

typedef enum
{
	PIPE_RUNNING,
	PIPE_STOPPED,
	PIPE_COMPLETED
}	t_pipe_state;

typedef struct s_cmd
{
	t_head_list		list;
	pid_t			pid;
	t_pipe_state	state;
	int				exit_status;
	char			*cmd_name;
	char			**args;
}	t_cmd;

typedef struct s_redirect
{
	char	*redir_in_filename;
	char	*redir_out_filename;
}	t_redirect;

int	dup_redirect(int redirect[2])
{
	dup2(redirect[0], STDIN_FILENO);
	dup2(redirect[0], STDOUT_FILENO);
}

int	build_child_pipeline(int pfd[2], int prev_in, int id_cmd, int cmd_cnt)
{
	if (id_cmd == 0 && id_cmd + 1 != cmd_cnt)
		dup2(pfd[1], STDOUT_FILENO);
	else if (id_cmd != 0 && id_cmd + 1 != cmd_cnt)
	{
		dup2(prev_in, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(prev_in);
	}
	else if (id_cmd != 0 && id_cmd + 1 == cmd_cnt)
	{
		dup2(prev_in, STDIN_FILENO);
		close(prev_in);
	}
	close(pfd[0]);
	close(pfd[1]);
	return (1);
}

t_cmd	*build_pipeline(t_cmd *cmdhead)
{
	int		cmd_cnt;
	t_cmd	*cur_cmd;
	int		i;
	int		pfd[2];
	int		prev_in;

	cmd_cnt = list_len((t_head_list *)cmdhead);
	cur_cmd = cmdhead;
	i = 0;
	prev_in = -1;
	while (i < cmd_cnt)
	{
		pipe(pfd);
		cur_cmd->pid = fork();
		if (cur_cmd->pid == 0)
		{
			build_child_pipeline(pfd, prev_in, i, cmd_cnt);
			break;
		}
		if (prev_in != -1)
			close(prev_in);
		prev_in = pfd[0];
		close(pfd[1]);
		cur_cmd = (t_cmd *)((t_head_list *)cur_cmd)->next;
		i++;
	}
	close(prev_in);
	return (cur_cmd);
}

int	execute_command(t_cmd *cmd, char *envp)
{
	char	*cmd_path;

	if (isaccessible(cmd->name, env_path))
	{
		cmd_path = cat_path_cmd(env_path[6], cmd_name);
		execve(cmd_path, cmd->args, envp);
	}
}

int	build_pipeline_and_exec(t_cmd *cmdhead, char **env_path, int redirect[2])
{
	t_cmd	*cur_cmd;
	int		ret;

	ret = dup_redirect(redirect);
	cur_cmd = build_pipeline(cmdhead);
	if (cur_cmd->pid == 0)
	 	execute_command(cur_cmd, env_path);
	// else
	// 	wait_child_process(cmdhead);
	(void)envp;
	(void)redirect;
	return (1);
}

// test function
#include <stdlib.h>

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
	t_cmd	*sec;
	t_cmd	*thi;
	char	*args[2] = {"-l", NULL};

	cmdhead = create_node("/usr/bin/ls", args);
	sec = create_node("/usr/bin/ls", args);
	thi = create_node("/usr/bin/ls", args);
	((t_head_list *)cmdhead)->next = (t_head_list *)sec;
	((t_head_list *)sec)->next = (t_head_list *)thi;

	build_pipeline_and_exec(cmdhead, envp, NULL);
	(void)argc;
	(void)argv;
}
