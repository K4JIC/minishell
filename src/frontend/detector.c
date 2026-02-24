/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:14:15 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/18 21:24:24 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum
{
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	IN_SHELL_PARAM,

t_list	*tokenize(char *p)
{
	t_list	head;
	t_list	*cur;
	int		i;

	head.next = NULL;
	cur = &head;
	i = 0;
	while (p[i])
	{
		if (ft_isspace(p[i]))
		{
			i++;
			continue;
		}
		if (isquote(p[i]))
		{
			in_quote = 1;
