/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:50:46 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/04 12:41:49 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	print_all(char *arr[])
{
	int	i = 0;

	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	return (0);
}

void	free_sp(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i++;
	}
}

// if pathname not executable, returns -1.
// if executable, returns PATH (envval) index.
int	isexecutable(char *cmd_name, char *env_value)
{
	char	**path_arr;
	char	*path_name;
	int		i;

	path_arr = ft_split(env_value, ':');
	if (!path_arr)
		return (-1);
	i = 0;
	while (path_arr[i])
	{
		path_name = ft_strjoin(path_arr[i], cmd_name);
		if (access(path_arr[i], X_OK) == 0)
		{
			free(path_name);
			free_sp(path_arr);
			return (i);
		}
		free(path_name);
		i++;
	}
	free_sp(path_arr);
	return (-1);
}

int	main(int argc, char **argv, char *envp[])
{
	int		a;
	char	*path;

	path = "/usr/bin/ls";
	a = is
	printf("access() returns %d\n", a);
	print_all(envp);
	execve(path, NULL, NULL);
	return (0);
}
