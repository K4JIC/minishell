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

typedef struct s_cmd
{
	t_head_list	list;
	char		*cmd_name;
	char		**args;
	char		**envp;
}	t_cmd;

int	do_parent(int id_cmd, int num_cmds, int prev_in, int fd[2], int wstatus)
{
	close(prev_in);
	close(fd[1]);
	recursive_pipe(id_cmd++, num_cmds, fd[0]);
	waitpid(pid, &wstatus, 0);
}

int	recursive_pipe(int id_cmd, int num_cmds, int prev_in)
{
	int	fd[2];
	int	pid;
	int	wstatus;

	if (id_cmd == num_cmds)
		return (0);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid != 0)
		do_parent(id_cmd, num_cmds, prev_in, fd, wstatus);
	if (pid == 0)
	{
		dup2(prev_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(prev_in);
		close(fd[0]);
		close(fd[1]);
	}
	return (pid);
}

int	list_len(t_head_list *head)
{
	t_head_list	*curr;
	int			i;

	curr = head;
	i = 0;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

int	build_pipe_and_exec(t_cmd *head)
{
	int	pid;

	pid = recursive_pipe(0, list_len((t_head_list *)head), 0);
	if (pid == 0)
	{
		execve(head->name, head->args, head->envp);
	}
}
#include <stdlib.h>

t_cmd	*create_node(char *name, char **args, char **envp)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	ft_bzero(ret, sizeof(t_cmd));
	ret->name = name;
	ret->args = args;
	ret->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*head;
	t_cmd	*sec;
	t_cmd	*thi;
	char	**head_args = {"-l", NULL};
	char	**sec_args = {"-l", NULL};
	char	**thi_args = {"-l", NULL};

	head = create_node("/usr/bin/ls", head_args, envp);
	sec = create_node("/usr/bin/ls", sec_args, envp);
	thi = create_node("/usr/bin/ls", thi_args, envp);
	((t_head_list *)head)->next = (t_head_list *)sec;
	((t_head_list *)sec)->next = (t_head_list *)thi;

	build_pipe_and_exec(head);
	(void)argc;
	(void)argv;
}

// pid_t	build_first_pipe(int *prev_in)
// {
	// int		fd[2];
	// pid_t	pid;
//
	// if (pipe(fd) == -1)
		// return (-1);
	// pid = fork();
	// if (pid != 0)
	// {
		// close(fd[1]);
		// *prev_in = fd[0];
	// }
	// else
	// {
		// close(fd[0]);
		// dup2(fd[1], STDOUT_FILENO);
		// close(fd[1]);
	// }
	// return (pid);
// }
//
// pid_t	build_middle_pipe(int *prev_in)
// {
	// int		fd[2];
	// pid_t	pid;
//
	// if (pipe(fd) == -1)
		// return (-1);
	// pid = fork();
	// if (pid != 0)
	// {
		// close(fd[1]);
		// close(*prev_in);
		// *prev_in = fd[0];
	// }
	// else
	// {
		// dup2(*prev_in, STDIN_FILENO);
		// dup2(fd[1], STDOUT_FILENO);
		// close(*prev_in);
		// close(fd[0]);
		// close(fd[1]);
	// }
	// return (pid);
// }
//
// pid_t	build_last_pipe(int *prev_in)
// {
	// pid_t	pid;
//
	// pid = fork();
	// if (pid != 0)
	// {
		// close(*prev_in);
		// *prev_in = -1;
	// }
	// else
	// {
		// dup2(*prev_in, STDIN_FILENO);
		// close(*prev_in);
	// }
	// return (pid);
// }
//
// int	build_pipes(t_cmd *head)
// {
	// int	nr_cmds;
	// int	i;
	// int	*pids;
	// int	prev_in;
//
	// if (nr_cmds == 1)
		// return (-1);
	// pids = (int *)malloc(sizeof(int) * nr_cmds);
	// if (!pids)
		// return (-1);
	// prev_in = 0;
	// pids[0] = build_first_pipe(&prev_in);
	// i = 1;
	// while (i < nr_cmds)
	// {
		// pids[i] = build_middle_pipe(&prev_in);
//
	// }
// }

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
