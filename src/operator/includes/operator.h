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
#include <threads.h>
#include <unistd.h>
#include "libft.h"

// typedef struct s_cmd{
// 	char			*name;
// 	char			**args;
// 	t_list			*redirects;
// 	int				pid;
// 	struct s_cmd	*next;
// 	int				fd_in;
// 	int				fd_out;
// }t_cmd;

typedef enum error
{
	E_ARG=-1,
	E_MALLOC=-2,
	E_PIPE=-3,
	E_FORK=-4
}	t_error;

// execute_command
int	isaccessible(char *cmd_name, char menv_value, char *path_name);


// t_list	*envp_to_lst(char **envp);

#endif
