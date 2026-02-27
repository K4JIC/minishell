/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:59:32 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/04 18:32:45 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * if argument is operator, returns argument
 * if not operator, returns NULL
 */

// if malloc failed in substr(), returns NULL
static char	*get_first_token(char *str_ptr)
{
	int		i;
	int		op_len;
	char	quote;

	i = 0;
	if (!str_ptr || !str_ptr[0])
		return (NULL);
	op_len = get_operator_len(str_ptr);
	if (op_len > 0)
		return (ft_substr(str_ptr, 0, op_len));
	if (str_ptr[i] == '\'' || str_ptr[i] == '\"')
	{
		quote = str_ptr[i++];
		while (str_ptr[i] && str_ptr[i] != quote)
			i++;
		if (str_ptr[i] == quote)
			i++;
	}
	else
	{
		while (str_ptr[i] && !ft_isspace(str_ptr[i]) && !ft_strchr("&|;()<>", str_ptr[i]))
			i++;
	}
	return (ft_substr(str_ptr, 0, i));
}

// if malloc failed in lstnew, returns NULL
t_list	*lexer(char *line)
{
	t_list	*token_list;
	char	*token_content;
	t_list	*new_lst;
	int		i;

	token_list = NULL;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i])
			i++;
		if (line[i] == '\0')
			break ;
		token_content = get_first_token(&line[i]);
		if (!token_content)
			return (ft_lstclear(&token_list, free), NULL);
		new_lst = ft_lstnew(token_content);
		if (!new_lst)
			return (ft_lstclear(&token_list, free), NULL);
		ft_lstadd_back(&token_list, new_lst);
		i += ft_strlen(token_content);
	}
	new_lst = ft_lstnew(NULL);
	if (!new_lst)
		return (ft_lstclear(&token_list, free), NULL);
	ft_lstadd_back(&token_list, new_lst);
	return (token_list);
}
