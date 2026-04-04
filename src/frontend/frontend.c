#include "minishell.h"

int	frontend(char *input, t_minishell *ms)
{
	t_token	*tk_head;
	t_cmd	*cmd_head;
	int		ret;

	tk_head = convert_line_to_token(input);
	if (tk_head == NULL)
		return (FAILURE);
	set_all_op_lavel(tk_head);
	printf("--token--");
	print_all_token(tk_head);
	printf("--end--");
	ms->tokens = tk_head;
	ret = convert_token_to_cmd(ms, &cmd_head, tk_head);
	if (ret == FAILURE)
		return (FAILURE);
	printf("--cmd--");
	print_all_cmd(cmd_head);
	printf("--end--");
	ms->cmd_list = cmd_head;
	return (SUCCESS);
}
