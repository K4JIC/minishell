/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:48:52 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 16:01:15 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

// int	execute_one_simple_cmd(t_cmd cmd, char **envp)
// {
	// int	path_index;

	// cmd.pid = build_first_pipe(cmd);
	// if (cmd.pid == 0)
	// {
	// }
	// else
	// {
		// if (path_index = isaccessible(pathname, env_path))
		// {
			// pathname = cat_path_cmd("", cmd.name);
			// if (!pathname)
				// return (-1);
			// execve(pathname, cmd.args, envp);
		// }
	// }
	// return (0);
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

int	*build_pipe(int pipenum)
{
	int	i;
	int	*fd;

	i = 0;
	while (i < pipenum)
	{
		pipe();
	}
}

int	execute_one_cmd(int pipenum, char **argv, char **envp)
{
	char	**args = {NULL};
	int		pid;
	char	*cmd;

	pid = -1;
	if (pipenum)
		pid = build_pipe();
	if (pid == 0)
		execute_one_cmd(pipenum - 1, argv, envp);
	cmd = ft_strjoin("/usr/bin/", argv[pipenum + 1]);
	execve(cmd, args, envp);
	free(cmd);
	return (0);
}

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
