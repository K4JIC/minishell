#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	ms;

	(void)ac;
	(void)av;
	ft_bzero(&ms, sizeof(t_minishell));
	ms.env_list = envp_to_lst(envp);
	while (!ms.should_exit)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		ms.cmd_btree = NULL;
		if (frontend(input, &ms) == SUCCESS && ms.cmd_btree)
			executor(ms.cmd_btree, &ms);
		free(input);
		free_cmds(ms.cmd_btree);
	}
	ft_lstclear(&ms.env_list, del_env);
	rl_clear_history();
	return (ms.exit_status);
}
