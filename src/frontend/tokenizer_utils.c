/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:31:17 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/21 13:06:34 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	startswith(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, strlen(keyword)) == 0);
}

t_list	*tokenizer(char *p)
{
	t_list	head;
	t_list	*cur;
	int		i;

	cur = &head;
	head.next = NULL;
	i = 0;
	while (p[i])
	{
		if (isdigit(p[i]))
	}
}
