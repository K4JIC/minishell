/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:04:28 by tozaki            #+#    #+#             */
/*   Updated: 2026/05/07 15:13:33 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

// one-pass structure
// allocate memory and execute command at once.

t_pipe_state	*init_pipe_state(void)
{
	t_pipe_state	*new;

	new = ft_calloc(1, sizeof(t_pipe_state));
	if (!new)
		return (NULL);
	new->pids = ft_calloc(BUFFER_SIZE, sizeof(pid_t));
	if (!new->pids)
	{
		free(new);
		return (NULL);
	}
	new->error_cmd = -1;
	return (new);
}

static void	add_pid(t_pipe_state *state, pid_t pid)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE - 1 && state->pids[i] != 0)
		i++;
	state->pids[i] = pid;
}

static int	wait_all(t_pipe_state *state, pid_t last_pid)
{
	int		i;
	int		status;
	int		last_status;

	i = 0;
	last_status = 0;
	while (state->pids[i] != 0)
	{
		if (waitpid(state->pids[i], &status, 0) != -1)
		{
			if (state->pids[i] == last_pid)
			{
				if (WIFEXITED(status))
					last_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					last_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	return (last_status);
}

int	exec_pipe(t_cmd_pipe *pipe_node, t_minishell *ms, t_cmd_ctx *ctx)
{
	int		fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (ctx->pipe_state == NULL)
	{
		ctx->pipe_state = init_pipe_state();
		if (!ctx->pipe_state)
			return (FAILURE);
		ctx->pipe_state->is_owner = 1;
	}
	if (pipe(fds) == -1)
		return (FAILURE);
	pid_left = fork();
	if (pid_left == -1)
		return (FAILURE);
	if (pid_left == 0)
	{
		ctx->pipe_state->is_owner = 0;
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		exit(exec_node(pipe_node->left, ms, ctx));
	}
	add_pid(ctx->pipe_state, pid_left);
	pid_right = fork();
	if (pid_right == -1)
		return (FAILURE);
	if (pid_right == 0)
	{
		ctx->pipe_state->is_owner = 0;
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		exit(exec_node(pipe_node->right, ms, ctx));
	}
	add_pid(ctx->pipe_state, pid_right);
	close(fds[0]);
	close(fds[1]);
	if (ctx->pipe_state->is_owner)
	{
		int res = wait_all(ctx->pipe_state, pid_right);
		free(ctx->pipe_state->pids);
		free(ctx->pipe_state);
		ctx->pipe_state = NULL;
		return (res);
	}
	return (SUCCESS);
}
