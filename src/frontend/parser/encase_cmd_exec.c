/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/14 19:55:04 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args, int i)
{
	if (!args)
		return ;
	while (i--)
		free(args[i]);
	free(args);
}

static int	token_len(t_token *head, t_token *tail)
{
	t_head_list	*curr;
	int			tklen;

	tklen = 0;
	curr = (t_head_list *)head;
	while (curr && curr != (t_head_list *)tail)
	{
		tklen++;
		curr = curr->next;
	}
	return (tklen);
}


int	copy_args(char ***args, t_token *head, t_token *tail)
{
	t_head_list	*curr;
	int			listlen;
	int			i;

	listlen = token_len(head, tail);
	*args = ft_calloc(sizeof(char *), listlen + 1);
	if (!*args)
		return (FAILURE);
	curr = ((t_head_list *)head);
	i = 0;
	while (curr != NULL && (t_token *)curr != tail)
	{
		(*args)[i] = ft_strdup(((t_token *)curr)->str);
		if (!(*args)[i])
		{
			free_args(*args, i);
			return (FAILURE);
		}
		curr = curr->next;
		i++;
	}
	(*args)[i] = NULL;
	return (SUCCESS);
}

t_cmd_base	*convert_token_to_cmd_exec(t_token *head, t_token *tail)
{
	t_cmd_exec	*cmd_e;

	cmd_e = ft_calloc(sizeof(t_cmd_exec), 1);
	if (!cmd_e)
		return (NULL);
	cmd_e->type = CMD_EXEC;
	if (copy_args(&cmd_e->args, head, tail) == FAILURE)
		return (free(cmd_e), NULL);
	cmd_e->name = cmd_e->args[0];
	return ((t_cmd_base *)cmd_e);
}

int	convert_exec(t_minishell *sh, t_cmd_base **parent,
		t_token *head, t_token *tail)
{
	(void)sh;
	*parent = convert_token_to_cmd_exec(head, tail);
	if (!*parent)
		return (FAILURE);
	return (SUCCESS);
}
