#include "operator.h"

#include <stdio.h>

int	do_child_process();

int	do_parent_process();

typedef struct s_cmds
{
	t_head_list	list;
	char		*cmd_name;
	char		**args;
}	t_cmds;

typedef struct s_redir
{
	int	in;
	int	out;
}	t_redir;

int	count_list(t_head_list *head)
{
	t_head_list	curr;
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

int	build_middle_pipe(int *prev_in, t_cmds *cmds)
{
	int			*fd[2];
	int			pid;

	if (!*prev_in)
		return (FAILURE);
	if (pipe(fd[2]) == -1)
		return (FAILURE);
	pid = fork();
	if (pipe != 0)
	{
		close(*prev_in);
		*prev_in = fd[0];
		close(fd[1]);
	}
	if (pipe == 0)
	{
		dup2(*prev_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(*prev_in);
	}
	return (pid);
}

int	build_first_pipe(int *prev_in, t_cmds *cmds)
{
	int			*fd[2];
	int			pid;

	if (pipe(fd[2]) == -1)
		return (FAILURE);
	pid = fork();
	if (pipe != 0)
	{
		*prev_in = fd[0];
		close(fd[1]);
	}
	if (pipe == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return (pid);
}

int	build_last_pipe(int *prev_in, t_cmds *cmds)
{
	int			pid;

	pid = fork();
	if (pipe != 0)
		close(*prev_in);
	if (pipe == 0)
	{
		dup2(prev_in, STDIN_FILENO);
		close(*prev_in);
	}
	return (pid);
}
