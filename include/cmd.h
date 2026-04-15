/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:43:55 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/06 23:11:26 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "libft.h"
# include "token.h"

typedef enum
{
	CMD_EXEC,
	CMD_REDIR,
	CMD_PIPE,
	CMD_LIST
}	t_cmd_type;

// parent class of all t_cmd_ structures
// binary tree structure
typedef struct s_cmd_base
{
	t_cmd_type	type;
}	t_cmd_base;

typedef struct s_cmd_exec
{
	t_cmd_type		type;
	pid_t			pid;
	int				exit_status;
	char			*name;
	char			**args;
	char			**envp;
}	t_cmd_exec;

typedef struct s_cmd_redir
{
	t_cmd_type				type;
	t_cmd_base				*cmd_head;
	char					*filename;
	t_operator_type			mode;
	int						fd;
}	t_cmd_redir;

typedef struct s_cmd_btree
{
	t_cmd_type	type;
	t_cmd_base	*left;
	t_cmd_base	*right;
}	t_cmd_btree;

typedef struct s_cmd_pipe
{
	t_cmd_type	type;
	t_cmd_base	*left;
	t_cmd_base	*right;
	int			pipenum;
}	t_cmd_pipe;

typedef struct s_cmd_list
{
	t_cmd_type	type;
	t_cmd_base	*left;
	t_cmd_base	*right;
}	t_cmd_list;

typedef struct s_env_set
{
	t_list	*env_list;
	char	**envp;
}	t_env_set;

void	free_cmds(t_cmd_base *cmd_head);

#endif
