/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:43:55 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/21 21:21:35 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_utils.h"
#include "minishell.h"
#include "libft.h"

typedef enum
{
	WORD,
	OPERATOR
}	t_token_type;

typedef enum
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef enum
{
	OP_PIPE,
	OP_LIST,
	OP_AND,
	OP_OR,
	OP_LPAREN,
	OP_RPAREN
}	t_operator_type;

// parent class of word and operator
// we get token from raw strings
typedef struct s_token
{
	t_head_list		list;
	t_token_type	type;
}	t_token;

typedef struct s_token_word
{
	t_head_list		list;
	t_token_type	type;
	char			*str;
	t_quote_type	w_quote;
	int				w_assignment;
}	t_token_word;

typedef struct s_token_operator
{
	t_head_list		list;
	t_token_type	type;
	char			*str;
	t_operator_type	o_type;
}	t_token_operator;

typedef enum
{
	CMD_EXEC,
	CMD_REDIR,
	CMD_PIPE,
	CMD_LIST
}	t_cmd_type;

// parent class of all t_cmd_ structures
// binary tree structure
typedef struct s_cmd
{
	t_cmd_type	type;
}	t_cmd;

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
	t_cmd_type	type;
	t_cmd		*cmd_head;
	char		*filename;
	int			mode;
	int			fd;
}	t_cmd_redir;

typedef struct s_cmd_pipe
{
	t_cmd_type	type;
	int			pipenum;
	t_cmd		*cmd_head;
}	t_cmd_pipe;

typedef struct s_cmd_list
{
	t_cmd_type	type;
	t_cmd		*left;
	t_cmd		*right;
}	t_cmd_list;

typedef struct s_ms
{
	t_cmd	*cmd_head;
	t_token	*token_head;
	char	**envp;
}	t_ms;

typedef struct s_env_set
{
	t_list	*env_list;
	char	**envp;
}	t_env_set;
