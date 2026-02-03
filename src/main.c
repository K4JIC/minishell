#include "libft.h"
#include "minishell.h"

void	printlst(t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr->next)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}

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
		t_list	*lst;
		lst = lexer(input);
		ft_lstadd_back(&lst, NULL);
		printf("入力値: %s\n", input);
		free(input);
	}
	return (0);
}
