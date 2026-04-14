#include "minishell.h"

int	main(void)
{
	char 		*input;
	t_minishell	ms;

	while (1)
	{
		input = readline("minishell$ ");//編集可能な入力を行う、文字列は　mallocされている
		if (input == NULL)
			break;
		if (*input)
			add_history(input);//入力文字列を保存する、↑でコマンドを再利用できるようにする
		ft_bzero(&ms, sizeof(t_minishell));
		if (frontend(input, &ms) == FAILURE)
			ft_printf("an error occured in frontend\n");
		free(input);
		free_cmds(ms.cmd_btree);
	}
	return (0);
}
