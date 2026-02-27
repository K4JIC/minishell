#include "operate_list.h"
#include <stdio.h>

// specialized func
void	*print_token(void *token)
{
	t_token	*casted_token;

	casted_token = (t_token *)token;
	printf("%s\n", casted_token->str);
	return (token);
}

void	print_all_token(t_token *head)
{
	apply_func(&head->list, print_token);
}
