#include "minishell.h"

int	frontend(char *input, t_minishell *ms, t_cmd_lst *cmd)
{
	t_token		*tk_head;
	t_cmd		*cmd_head;
	int			ret;

	tk_head = convert_line_to_token(input);
	if (tk_head == NULL)
		return (FAILURE);
	set_all_op_label(tk_head);
	ft_printf("--token--\n");
	print_all_token(tk_head);
	ft_printf("--end--\n");
	ms->tokens = tk_head;
	ret = convert_token_to_cmd(ms, &cmd_head, tk_head);
	if (ret == FAILURE)
		return (FAILURE);
	ft_printf("--cmd--\n");
	print_all_cmd(cmd_head);
	ft_printf("--end--\n");
	// t_cmd 構造体を格納
	ms->cmd_list = cmd_head;
	if (ms->cmd_list->type == CMD_EXEC)
	{
		// t_cmd_lst 構造体を格納
		cmd->args = ((t_cmd_exec *)ms->cmd_list)->args;
	}
	return (SUCCESS);
}
