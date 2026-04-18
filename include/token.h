/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:31:05 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/18 15:44:43 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "ms_utils.h"

typedef enum
{
	TK_WORD,
	TK_OPERATOR
}	t_token_type;

typedef enum
{
	QT_NONE,
	QT_SINGLE,
	QT_DOUBLE
}	t_quote_type;

typedef enum
{
	OP_PIPE,
	OP_LIST,
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_REDIR_APP,
	OP_REDIR_HDOC,
	OP_NOT_IMPLEMENTED,
	NO_OP
}	t_operator_type;

// parent class of word and operator
// we get token from raw strings
typedef struct s_token
{
	t_head_list		list;
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_token_word
{
	t_head_list		list;
	t_token_type	type;
	char			*str;
	t_quote_type	wd_quote;
	int				wd_assignment;
}	t_token_word;

typedef struct s_token_type_len
{
	int				len;
	t_token_type	type;
}	t_token_type_len;

typedef struct s_token_operator
{
	t_head_list		list;
	t_token_type	type;
	char			*str;
	t_operator_type	op_type;
}	t_token_operator;

typedef struct s_token_span
{
	t_token	*head;
	t_token	*tail;
}	t_token_span;

typedef struct s_token_lr
{
	t_token_span	left;
	t_token_span	right;
	t_operator_type	found_op;
}	t_token_lr;
// expand envval
char	*substitute_envval(char *p, t_list *envlist);

// token list
t_token		*create_token(char *str, t_token_type type);
void		add_token_last(t_token *head, t_token *new_token);
int			free_token(void *token);
void		free_all_token(t_token *head);

// print token
int			print_token(void *token);
void		print_all_token(t_token *head);

// find token
t_token_type_len	get_one_token_len(char *p);
t_token				*convert_line_to_token(char *p);
void				set_all_op_label(t_token *head);

#endif
