/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:48:52 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/09 14:29:52 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

// int	execute_one_simple_cmd(t_cmd cmd, char **envp)
// {
// 	int	path_index;

// 	cmd.pid = build_first_pipe(cmd);
// 	if (cmd.pid == 0)
// 	{
// 	}
// 	else
// 	{
// 		if (path_index = isaccessible(pathname, env_path))
// 		{
// 			pathname = cat_path_cmd("", cmd.name);
// 			if (!pathname)
// 				return (-1);
// 			execve(pathname, cmd.args, envp);
// 		}
// 	}
// 	return (0);
// }

#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"

pid_t	fork_and_close_fd(int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
	{
		close(fd_out);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		close(fd_in);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (pid);
}

int	do_parent(int fd[2], int *prev_in)
{
	if (fd[1])
		close(fd[1]);
	*prev_in = fd[0];
	return (0);
}

int	do_child(int fd[2], int prev_in, t_cmd *cmd, char **envp)
{
	int		envnum;
	char	*pathname;

	dup2(prev_in, 0);
	close(prev_in);
	dup2(fd[1], 1);
	close(fd[1]);
	if (envnum = isaccessible(cmd->name, ))
	{
		pathname = cat_path_cmd();
		execve();
	}
	free();
	return (0);
}

int	*exec_pipe_processes(int pipenum, t_cmd cmd)
{
	int	fd[2];
	int	prev_in;
	int	*pids;
	int	i;

	pids = (int *)malloc(sizeof(int) * (pipenum + 1));
	if (!pids)
		return (NULL);
	ft_bzero(fd, 2);
	i = 0;
	while (i < pipenum)
	{
		if (pipe(fd) == -1)
			return (NULL);
		pids[i] = fork();
		if (pids[i] != 0)
			do_parent();
		else
			do_child();
		i++;
	}
	return (pids);
}

// int	execute_one_cmd(int pipenum, char **argv, char **envp)
// {
// 	char	**args = {NULL};
// 	int		pid;
// 	char	*cmd;

// 	pid = -1;
// 	if (pipenum)
// 		pid = build_pipe();
// 	if (pid == 0)
// 		execute_one_cmd(pipenum - 1, argv, envp);
// 	cmd = ft_strjoin("/usr/bin/", argv[pipenum + 1]);
// 	execve(cmd, args, envp);
// 	free(cmd);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	int		waitstatus;
	int		pipenum;

	pipenum = argc - 2;
	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, &waitstatus, 0);
		printf("waitstatus = %d\n", waitstatus);
	}
	else
		execute_one_cmd(pipenum, argv, envp);
	return (0);
}
