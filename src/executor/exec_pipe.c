/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:04:28 by tozaki            #+#    #+#             */
/*   Updated: 2026/05/01 21:23:43 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipe_state
{
	bool	is_owner;
	pid_t	*pids;
	pid_t	error_cmd;
}	t_pipe_state;

typedef struct s_cmd_ctx
{
	t_pipe_state	*pipe_state;
}	t_cmd_ctx;

t_pipe_state	*init_pipe_state(void)
{
	t_pipe_state	*new;

	new = ft_calloc(1, sizeof(t_pipe_state));
	if (!new)
		return (NULL);
	new->pids = ft_calloc();
}

int	exec_pipe(t_cmd_pipe *pipe, t_minishell *ms, t_cmd_ctx *ctx)
{
	if (ctx->pipe_state == NULL)
	{
		ctx->pipe_state = init_pipe_state();
		if (!ctx->pipe_state)
			return (FAILURE);
		ctx->pipe_state->is_owner = 1;
	}
}
