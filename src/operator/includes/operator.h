/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:45:56 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 15:24:13 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

#include <sys/types.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_cmd{
	char			*name;
	char			**args;
	t_list			*redirects;
	int				pid;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
}t_cmd;

// execute_command
int	isaccessible(char *cmd_name, char *env_value);

pid_t	build_first_pipe(void);
pid_t	build_pipe(void);

// t_list	*envp_to_lst(char **envp);

#endif
