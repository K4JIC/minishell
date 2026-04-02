/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:31:05 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/05 17:01:31 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ms_utils.h"
# include "libft.h"

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

typedef struct s_token_operator
{
	t_head_list		list;
	t_token_type	type;
	char			*str;
	t_operator_type	op_type;
}	t_token_operator;
// typedef enum e_token_type
// {
	// TK_WORD,
	// TK_PIPE,
	// TK_LIST,
	// TOKEN_REDIR_IN,
	// TOKEN_REDIR_OUT,
	// TOKEN_APPEND,
	// TOKEN_HEREDOC,
	// TK_NONE=-1,
// }	t_token_type;
//
// typedef struct s_token
// {
	// t_head_list		list;
	// int				id;
	// char			*str;
	// t_token_type	type;
// }	t_token;

#define NO_OPERATOR -3

// token list
t_token		*create_token(char *str, t_token_type type);
void		add_token_last(t_token *head, t_token *new_token);
void		*free_token(void *token);
void		free_all_token(t_token *head);

// print token
void		*print_token(void *token);
void		print_all_token(t_token *head);

// find token
int		get_one_token_len(char *p);
t_token	*tokenizer(char *p);
void	set_all_lavel(t_token *head);

#endif
