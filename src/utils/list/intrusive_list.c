/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intrusive_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 23:01:52 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/27 23:01:58 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// intrusive list is a kind of list structure.
void	add_next_node(t_head_list *prev_list, t_head_list *next_list)
{
	prev_list->next = next_list;
	next_list->prev = prev_list;
}

t_head_list	*get_last_node(t_head_list *head)
{
	t_head_list	*curr;

	curr = head;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

int	apply_func(t_head_list *head, void *(*f)(void *))
{
	t_head_list	*curr;
	t_head_list	*tmp;

	if (!head)
		return (FAILURE);
	curr = head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		if (!f(tmp))
			return (FAILURE);
	}
	return (SUCCESS);
}
