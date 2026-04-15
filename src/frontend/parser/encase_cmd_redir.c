/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/14 22:52:12 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_redir(t_token_lr lr)
{
	if (lr.right.head == NULL)
		return (FAILURE);
	if (lr.right.head == lr.right.tail)
		return (FAILURE);
	if (lr.right.head->type != TK_WORD) 
		return (FAILURE);
	return (SUCCESS);
}

static void	free_recreated_tokens(t_token_span *span)
{
	if (!span)
		return ;
	if (span->head)
		free_all_token(span->head);
	free(span);
}

static t_token	*duplicate_token(t_token *src)
{
	t_token	*dup;
	char	*dup_str;

	dup_str = ft_strdup(src->str);
	if (!dup_str)
		return (NULL);
	dup = create_token(dup_str, src->type);
	if (!dup)
	{
		free(dup_str);
		return (NULL);
	}
	if (src->type == TK_OPERATOR)
		((t_token_operator *)dup)->op_type = ((t_token_operator *)src)->op_type;
	else
	{
		((t_token_word *)dup)->wd_quote = ((t_token_word *)src)->wd_quote;
		((t_token_word *)dup)->wd_assignment = ((t_token_word *)src)->wd_assignment;
	}
	return (dup);
}

static int	append_token_copy(t_token_span *span, t_token *src)
{
	t_token	*dup;

	dup = duplicate_token(src);
	if (!dup)
		return (FAILURE);
	if (!span->head)
		span->head = dup;
	else
		add_token_last(span->head, dup);
	return (SUCCESS);
}

static t_token_span	*recreate_new_token_list(t_token_lr lr)
{
	t_token_span	*new_span;
	t_token			*cur;

	new_span = ft_calloc(sizeof(t_token_span), 1);
	if (!new_span)
		return (NULL);
	cur = lr.left.head;
	while (cur != NULL && cur != lr.left.tail)
	{
		if (append_token_copy(new_span, cur) == FAILURE)
			return (free_recreated_tokens(new_span), NULL);
		cur = (t_token *)((t_head_list *)cur)->next;
	}
	cur = (t_token *)((t_head_list *)lr.right.head)->next;
	while (cur != NULL && cur != lr.right.tail)
	{
		if (append_token_copy(new_span, cur) == FAILURE)
			return (free_recreated_tokens(new_span), NULL);
		cur = (t_token *)((t_head_list *)cur)->next;
	}
	new_span->tail = NULL;
	return (new_span);
}

int	convert_redir(t_minishell *sh, t_cmd_base **parent, t_token_lr lr)
{
	t_cmd_redir		*cmd_r;
	t_token_span	*newtoken;
	int				ret;

	if (validate_redir(lr) == FAILURE)
		return (syntax_error("syntax error near unexpected token \"newline\"\n", sh), FAILURE);
	*parent = ft_calloc(sizeof(t_cmd_redir), 1);
	if (!*parent)
		return (FAILURE);
	(*parent)->type = CMD_REDIR;
	cmd_r = (t_cmd_redir *)*parent;
	cmd_r->mode = lr.found_op;
	cmd_r->fd = -1;
	cmd_r->filename = ft_strdup(lr.right.head->str);
	if (!cmd_r->filename)
		return (free_cmds(*parent), FAILURE);
	newtoken = recreate_new_token_list(lr);
	if (!newtoken)
		return (free_cmds(*parent), FAILURE);
	ret = dispatch_token_conversion(sh, &cmd_r->cmd_head,
		newtoken->head, newtoken->tail);
	if (ret == FAILURE)
		return (free_recreated_tokens(newtoken), free_cmds(*parent), FAILURE);
	free_recreated_tokens(newtoken);
	return (SUCCESS);
}
