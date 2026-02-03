/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:59:58 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 12:59:59 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		del(current->content);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*lst = NULL;
}
