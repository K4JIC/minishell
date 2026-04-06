#include "minishell.h"

static t_token_lr	sep_token_list(t_token *head, t_operator_type del)
{
	t_token		*cur;
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	cur = head;
	while (cur != NULL)
	{
		if (cur->type == TK_OPERATOR)
		{
			if (((t_token_operator *)cur)->op_type == del)
				break ;
		}
		cur = (t_token *)((t_head_list *)cur)->next;
	}
	if (cur == NULL)
		return (lr);
	(((t_head_list *)cur)->prev)->next = NULL;
	(((t_head_list *)cur)->next)->prev = NULL;
	lr.left = head;
	lr.right = (t_token *)((t_head_list *)cur)->next;
	return (lr);
}

t_token_lr	sep_token_list_op(t_token *head)
{
	t_token_lr	lr;

	ft_bzero(&lr, sizeof(lr));
	lr = sep_token_list(head, OP_LIST);
	if (lr.right != NULL)
	{
		lr.found_op = OP_LIST;
		return (lr);
	}
	lr = sep_token_list(head, OP_PIPE);
	if (lr.right != NULL)
	{
		lr.found_op = OP_PIPE;
		return (lr);
	}
	lr.found_op = NO_OP;
	return (lr);
}

void	syntax_error(char *msg, t_minishell *sh)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (sh)
		sh->syntax_error = 1;
}

t_cmd_base	*convert_token_to_cmd_exec(t_token *head)
{
	t_cmd_exec	*cmd_e;
	t_head_list	*curr;
	int			listlen;
	int			i;

	cmd_e = ft_calloc(sizeof(t_cmd_exec), 1);
	if (!cmd_e)
		return (NULL);
	cmd_e->type = CMD_EXEC;
	cmd_e->name = head->str;
	curr = ((t_head_list *)head);
	listlen = list_len(curr);
	i = 0;
	cmd_e->args = ft_calloc(sizeof(char *), listlen + 1);
	if (!cmd_e->args)
		return (free(cmd_e), NULL);
	while (curr != NULL)
	{
		cmd_e->args[i] = ((t_token *)curr)->str;
		curr = curr->next;
		i++;
	}
	cmd_e->args[i] = NULL;
	return ((t_cmd_base *)cmd_e);
}

t_cmd_base	*create_cmd_btree_node(t_operator_type type)
{
	t_cmd_base	*ret;

	if (type == OP_PIPE)
	{
		ret = ft_calloc(sizeof(t_cmd_pipe), 1);
		if (!ret)
			return (NULL);
		ret->type = CMD_PIPE;
	}
	else if (type == OP_LIST)
	{
		ret = ft_calloc(sizeof(t_cmd_list), 1);
		if (!ret)
			return (NULL);
		ret->type = CMD_LIST;
	}
	else
		return (NULL);
	return ((t_cmd_base *)ret);
}

int	convert_token_to_cmd(t_minishell *sh, t_cmd_base **parent, t_token *head)
{
	t_token_lr	lr;
	int			ret;

	lr = sep_token_list_op(head);
	if (lr.found_op == OP_PIPE && lr.left == NULL)
		return (syntax_error("syntax error near unexpected token '|'", sh), FAILURE);
	if (lr.found_op == OP_PIPE && lr.right == NULL)
		return (syntax_error("syntax error near unexpected token '|'", sh), FAILURE);
	// if (lr.found_op == OP_REDIR_IN)
	if (lr.found_op == OP_PIPE || lr.found_op == OP_LIST)
	{
		*parent = create_cmd_btree_node(lr.found_op);
		if (!*parent)
			return (FAILURE);
		ret = convert_token_to_cmd(sh, &((t_cmd_btree *)*parent)->left, lr.left);
		if (ret == FAILURE)
			return (free(*parent), FAILURE);
		ret = convert_token_to_cmd(sh, &((t_cmd_btree *)*parent)->right, lr.right);
		if (ret == FAILURE)
			return (free(*parent), FAILURE);
	}
	if (lr.found_op == NO_OP)
	{
		*parent = convert_token_to_cmd_exec(head);
		if (!*parent)
			return (FAILURE);
	}
	return (SUCCESS);
}
