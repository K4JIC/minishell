/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:31:17 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/03 19:22:59 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operate_list.h"
#include "frontend_utils.h"
#include "libft.h"
#include <stddef.h>

/**
 *
 */
int	store_one_token(t_token **head, char *p, unsigned int start, size_t token_len)
{
	char	*str;
	t_token	*new_token;

	if (!token_len)
		return (FAILURE);
	str = ft_substr(p, start, token_len);
	if (!str)
		return (FAILURE);
	new_token = create_token(str);
	if (!new_token)
	{
		free(str);
		return (FAILURE);
	}
	if (!*head)
		*head = new_token;
	else
		add_token_last(*head, new_token);
	return (SUCCESS);
}

t_token	*tokenizer(char *p)
{
	t_token	*head;
	int		i;
	int		len;

	head = NULL;
	i = 0;
	while (p[i])
	{
		while (p[i] == ' ' || p[i] == '\t')
			i++;
		if (!p[i])
			break ;
		len = get_one_token_len(&(p[i]));
		if (len < 0 || store_one_token(&head, p, i, len) == FAILURE)
		{
			if (len == NO_CLOSE)
				print_error_msg("No end of quote\n");
			free_all_token(head);
			return (NULL);
		}
		i += len;
	}
	return (head);
}
