#include "operate_list.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

// specialized func
t_token	*create_token(char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	bzero(new_token, sizeof(t_token));
	new_token->str = str;
	return (new_token);
}

// specialized func
void	add_token_last(t_token *head, t_token *new_token)
{
	t_head_list	*last_list;

	last_list = get_last_node(&head->list);
	add_next_node(last_list, &new_token->list);
}

void	*free_token(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	free(casted_token);
	return ((void *)1);
}

void	free_all_token(t_token *head)
{
	apply_func(&head->list, free_token);
}

#ifdef DEBUG
int	main(void)
{
	t_token	*fir;
	t_token	*sec;
	t_token	*thi;

	fir = create_token("fir");
	sec = create_token("sec");
	thi = create_token("thi");
	add_token_last(fir, sec);
	add_token_last(fir, thi);
	print_all_token(fir);
	free_all_token(fir);
	return (0);
}
#endif
