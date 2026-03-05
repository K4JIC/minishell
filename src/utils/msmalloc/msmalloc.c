/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msmalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:05:29 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/04 23:06:57 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_utils.h"
#include <stdlib.h>

void	free_all_heap(t_head_list *sentinel)
{
	t_head_list	*curr;
	t_head_list	*tmp;

	if (!sentinel)
		return ;
	curr = sentinel->next;
	while (curr == sentinel)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void	*msmalloc(size_t bytesize)
{
	static t_head_list	sentinel = {NULL, NULL};
	t_head_list			*new_node;

	if (!sentinel.next)
	{
		sentinel.next = &sentinel;
		sentinel.prev = &sentinel;
	}
	new_node = malloc(sizeof(t_head_list) + bytesize);
	if (!new_node)
	{
		free_all_heap(&sentinel);
		exit(1);
	}
	ft_bzero(new_node, sizeof(t_head_list) + bytesize);
	new_node->next = &sentinel;
	new_node->prev = sentinel.prev;
	sentinel.prev->next = new_node;
	sentinel.prev = new_node;
	return (new_node + 1);
}

void	msfree(void *data_ptr)
{
	t_head_list	*node_ptr;

	node_ptr = (t_head_list *)data_ptr - 1;
	node_ptr->prev->next = node_ptr->next;
	node_ptr->next->prev = node_ptr->prev;
	free(node_ptr);
}
