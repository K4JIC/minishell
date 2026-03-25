/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:50:46 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 14:49:20 by tozaki           ###   ########.fr       */
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
	free(sp);
}

// concatenate path and command
char	*cat_path_cmd(char *path, char *cmd)
{
	char	last_char;
	char	*tmp;
	char	*ret;

	last_char = path[ft_strlen(path) - 1];
	if (last_char != '/')
	{
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			return (NULL);
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	else
		ret = ft_strjoin(path, cmd);
	if (!ret)
		return (NULL);
	return (ret);
}

// if pathname not executable, returns -1.
// if executable, returns PATH (envval) index.
int	isexecutable(char *cmd_name, char *env_value, char **path_name)
{
	char	**path_arr;
	int		i;

	path_arr = ft_split(env_value, ':');
	if (!path_arr)
		return (-1);
	i = 0;
	while (path_arr[i])
	{
		path_name = cat_path_cmd(path_arr[i], cmd_name);
		if (!path_name)
			break ;
		if (access(path_name, X_OK) == 0)
		{
			free_sp(path_arr);
			return (i);
		}
		free(path_name);
		i++;
	}
	free_sp(path_arr);
	return (-1);
}

// int	main(int argc, char **argv, char *envp[])
// {
// 	int		a;
// 	char	*path;
// 	char	*dir = "/home/k4jic/.local/bin:/home/k4jic/.local/bin:/home/k4jic/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files (x86)/Symantec/VIP Access Client/:/mnt/c/Program Files/dotnet/:/mnt/c/Program Files (x86)/Pulse Secure/VC142.CRT/X64/:/mnt/c/Program Files (x86)/Pulse Secure/VC142.CRT/X86/:/mnt/c/Program Files (x86)/Common Files/Pulse Secure/TNC Client Plugin/:/mnt/c/Program Files/gs/gs10.03.1/bin:/mnt/c/Program Files/mingw64/bin:/mnt/c/Program Files/nodejs/:/mnt/c/Program Files/Git/cmd:/mnt/c/Users/g2022013/AppData/Local/Pub/Cache/bin:/mnt/c/tool/Python/Scripts/:/mnt/c/tool/Python/:/mnt/c/pg/python/:/mnt/c/Users/g2022013/AppData/Local/Microsoft/WindowsApps:/mnt/c/tool/VScode/Microsoft VS Code/bin:/mnt/c/texlive/2022/bin/win32:/mnt/c/tool/php-8.1.11-nts-Win32-vs16-x64/:/mnt/c/Users/g2022013/.dotnet/tools:/mnt/c/texlive/2023/bin/windows:/mnt/c/Program Files/Vim/vim91:/mnt/c/Users/g2022013/flutter/bin:/mnt/c/Users/g2022013/AppData/Roaming/npm:/mnt/c/Users/g2022013/AppData/Local/Programs/Zed/bin";
//
// 	if (argv[0])
// 		(void)argc;
// 	path = "/usr/bin/ls";
// 	a = isaccessible(argv[1], dir);
// 	printf("access() returns %d\n", a);
// 	// print_all(envp);
// 	execve(path, argv, envp);
// 	return (0);
// }
