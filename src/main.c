#include "minishell.h"

int	main(void)
{
	char 		*input;
	t_minishell	ms;
	t_cmd_lst	cmd;

	while (1)
	{
		input = readline("minishell$ ");//編集可能な入力を行う、文字列は　mallocされている
		if (input == NULL)
			break;
		if (*input)
			add_history(input);//入力文字列を保存する、↑でコマンドを再利用できるようにする
		ft_printf("入力値: %s\n", input);
		ft_bzero(&ms, sizeof(t_minishell));
		ft_bzero(&cmd, sizeof(t_cmd_lst));
		if (frontend(input, &ms, &cmd) == FAILURE)
			ft_printf("an error occured in frontend\n");
		free(input);
	}
	return (0);
}
