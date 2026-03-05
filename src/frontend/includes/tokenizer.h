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

typedef enum e_token_type
{
	WORD,
	PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	OTHER_OPERATOR
}	t_token_type;

typedef struct s_token
{
	t_head_list		list;
	int				id;
	char			*str;
	t_token_type	type;
}	t_token;

#define NO_OPERATOR -3

// token list
t_token		*create_token(char *str);
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
