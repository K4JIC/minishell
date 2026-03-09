/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 19:01:45 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 14:53:22 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

pid_t	build_first_pipe(void)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid != 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	return (pid);
}

pid_t	build_pipe(void)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid != 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	return (pid);
}

// int	execute_one_cmd(char *cmd[], int pipe_num)
// {
// 	if (pipe_num == 0)
// 	{
// 		char	*dir = "/home/k4jic/local/bin";
// 		char	*path;
//
// 		path = malloc(strlen(dir) + strlen(cmd[pipe_num]));
//
// 		execve(path, NULL, NULL);
// 	}
// 	pid_t	pid;
//
// 	pid = build_pipe(cmd);
// 	if (pid ==
//
//
//
// int	execute_cmd(char *cmd[], int pipe_num)
// {
// 	pid_t	pid;
//
// 	pid = build_first_pipe(cmd);
// 	if (pid == 0)
// 	{
// 	}
// 	else
// 	{
// 		execute_one_cmd(cmd, pipe_num);
// 	}
// }
