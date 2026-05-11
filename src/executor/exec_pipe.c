/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:04:28 by tozaki            #+#    #+#             */
/*   Updated: 2026/05/11 19:45:55 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static int	count_commands(t_cmd_base *node, int count)
{
	if (!node)
		return (count);
	if (node->type == CMD_EXEC)
		return (count + 1);
	count = count_commands(node->left, count);
	count = count_commands(node->right, count);
	return (count);
}

static t_pipe_info	*init_pipeinfo(int count)
{
	t_pipe_info	*pinfo;

	if (!count)
		return (NULL);
	pinfo = ft_calloc(1, sizeof(t_pipe_info));
	if (!pinfo)
		return (NULL);
	pinfo->pids = ft_calloc(count, sizeof(pid_t));
	if (!pinfo->pids)
		return (free(pinfo), NULL);
	ft_memset(pinfo->fd, -1, 2 * sizeof(int));
	ft_memset(pinfo->pids, -1, count * sizeof(pid_t));
	return (pinfo);
}

static int	do_left(t_cmd_base *node, t_minishell *ms)
{
	dup2(ms->pipe_info->fd[1], STDOUT_FILENO);
	close(ms->pipe_info->fd[0]);
	dup2(ms->pipe_info->prev_in, STDIN_FILENO);
	close(ms->pipe_info->prev_in);
	exit(exec_node(node->left, ms));
}

static int	do_last_cmd(t_cmd_base *node, t_minishell *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(ms->pipe_info->prev_in, STDIN_FILENO);
		close(ms->pipe_info->prev_in);
		exit(exec_node(node->right, ms));
	}
	else
		ms->pipe_info->pids[ms->pipe_info->pid_idx] = pid;
	return (SUCCESS);
}

static int	do_right(t_cmd_base *node, t_minishell *ms)
{
	if (ms->pipe_info->pid_idx == ms->pipe_info->cmds_count)
		return (do_last_cmd(node, ms));
	ms->pipe_info->prev_in = ms->pipe_info->fd[0];
	close(ms->pipe_info->fd[1]);
	return (exec_node(node->right, ms));
}

static int	fork_and_dup(t_cmd_base *node, t_minishell *ms)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid == 0)
		ret = do_left(node, ms);
	else
	{
		ms->pipe_info->pids[ms->pipe_info->pid_idx++] = pid;
		ret = do_right(node, ms);
	}
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	pipe_and_fork(t_cmd_base *node, t_minishell *ms)
{
	int	ret;

	ret = pipe(ms->pipe_info->fd);
	if (ret == -1)
		return (FAILURE);
	ret = fork_and_dup(node, ms);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	wait_all(t_minishell *ms)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < ms->pipe_info->cmds_count)
	{
		waitpid(ms->pipe_info->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus) != true)
			ms->pipe_info->err_pid = ms->pipe_info->pids[i];
		i++;
	}
}

int	exec_pipe(t_cmd_pipe *node, t_minishell *ms)
{
	int	count;

	if (ms->pipe_info == NULL)
	{
		count = count_commands((t_cmd_base *)node, 0);
		ms->pipe_info = init_pipeinfo(count);
		ms->pipe_info->is_owner = true;
		if (!ms->pipe_info)
			return (FAILURE);
	}
	else
		ms->pipe_info->is_owner = false;
	if (pipe_and_fork((t_cmd_base *)node, ms) == FAILURE)
		return (FAILURE);
	if (ms->pipe_info->is_owner == true)
		wait_all(ms);
	return (SUCCESS);
}
