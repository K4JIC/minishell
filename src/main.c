#include "minishell.h"

int	main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell$ ");//編集可能な入力を行う、文字列は　mallocされている
		if (input == NULL)
			break;
		if (*input)
			add_history(input);//入力文字列を保存する、↑でコマンドを再利用できるようにする  
		printf("入力値: %s\n", input);
		free(input);
	}
	return (0);
}
