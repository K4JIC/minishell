#include "minishell.h"
#include <sys/wait.h>

static int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (FAILURE);
}

static int	fork_and_exec(char *path, char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILURE);
	if (pid == 0)
	{
		execve(path, args, envp);
		perror(path);
		exit(126);
	}
	return (wait_child(pid));
}

int	exec_external(t_cmd_exec *cmd, t_minishell *ms)
{
	char	*path;
	char	**envp;
	int		status;

	path = find_cmd_path(cmd->args[0], ms->env_list);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	envp = env_list_to_envp(ms->env_list);
	if (!envp)
		return (free(path), FAILURE);
	status = fork_and_exec(path, cmd->args, envp);
	free(path);
	free_str_array(envp);
	return (status);
}
