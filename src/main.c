#include "libft.h"
#include "minishell.h"
#include "frontend.h"

void	printlst(t_list *lst)
{
	t_list	*curr;
	int		i;

	curr = lst;
	i = 0;
	while (curr->next)
	{
		ft_printf("%d : %s\n", i, (char *)curr->content);
		curr = curr->next;
		i++;
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
		printlst(lst);
		printf("入力値: %s\n", input);
		free(input);
	}
	return (0);
}
