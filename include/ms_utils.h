/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 23:02:08 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/06 23:11:41 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

# include "libft.h"

typedef struct s_head_list
{
	struct s_head_list	*prev;
	struct s_head_list	*next;
}	t_head_list;

typedef struct s_dynamic_str
{
	char	*str;
	int		len;
	int		capa;
}	t_dynamic_str;

# define NO_QUOTE -1
# define NO_CLOSE_QUOTE -2

// intrusive_list
void			add_next_node(t_head_list *prev_list, t_head_list *next_list);
t_head_list		*get_last_node(t_head_list *head);
int				list_len(t_head_list *head);
int				apply_func(t_head_list *head, void *(*f)(void *));
int				apply_func_ctx(t_head_list *head, void *ctx,
					void *(*f)(void *, void *));

// ms_quote
int				ismeta(char c);
int				isquote(const char c);
int				ismsspace(const char c);
int				get_quoted_string_len(char *p);

// msmalloc
void			*msmalloc(size_t bytesize);
void			msfree(void *data_ptr);

t_dynamic_str	*init_buf(void);
void			free_dynamic_str(t_dynamic_str *buf);
int				putnstr_buf(t_dynamic_str *buf, const char *str, int n);
int				putstr_buf(t_dynamic_str *buf, const char *str);

#endif
