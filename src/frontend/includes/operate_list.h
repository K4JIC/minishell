/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 23:02:08 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/27 23:02:11 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_head_list
{
	struct s_head_list	*prev;
	struct s_head_list	*next;
}	t_head_list;

typedef enum e_token_type
{
	WORD,
	PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_head_list		list;
	int				id;
	char			*str;
	t_token_type	type;
}	t_token;

#define SUCCESS 0
#define FAILURE 1

// list
void		add_next_node(t_head_list *prev_list, t_head_list *next_list);
t_head_list	*get_last_node(t_head_list *head);
int			apply_func(t_head_list *head, void *(*f)(void *));

// token
t_token		*create_token(char *str);
void		add_token_last(t_token *head, t_token *new_token);
void		*free_token(void *token);
void		free_all_token(t_token *head);

// for debug
void		*print_token(void *token);
void		print_all_token(t_token *head);
