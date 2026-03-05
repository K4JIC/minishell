/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 23:02:08 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/28 18:14:24 by tozaki           ###   ########.fr       */
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

#define SUCCESS 0
#define FAILURE 1

#define NO_QUOTE -1
#define NO_CLOSE_QUOTE -2

// intrusive_list
void		add_next_node(t_head_list *prev_list, t_head_list *next_list);
t_head_list	*get_last_node(t_head_list *head);
int			apply_func(t_head_list *head, void *(*f)(void *));

// ms_quote
int		ismeta(char c);
int		isquote(const char c);
int		ismsspace(const char c);
int		get_quoted_string_len(char *p);

// msmalloc
void	*msmalloc(size_t bytesize);
void	msfree(void *data_ptr);

// alart error
int		print_error_msg(char *msg);

#endif
