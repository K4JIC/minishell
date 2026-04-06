#include "minishell.h"
#include "cmd.h"

void	print_all_cmd_helper(t_cmd_base *cmd, int depth, int is_last)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	while (i < depth - 1)
	{
		printf("│   ");
		i++;
	}
	if (depth > 0)
	{
		if (is_last)
			printf("└── ");
		else
			printf("├── ");
	}
	if (cmd->type == CMD_EXEC)
	{
		printf("[EXEC] %s\n", ((t_cmd_exec *)cmd)->name);
		i = 0;
		while (((t_cmd_exec *)cmd)->args[i])
		{
			int j = 0;
			while (j < depth)
			{
				printf("│   ");
				j++;
			}
			printf("arg[%d] = %s\n", i, ((t_cmd_exec *)cmd)->args[i]);
			i++;
		}
	}
	else if (cmd->type == CMD_PIPE)
	{
		printf("[PIPE]\n");
		print_all_cmd_helper(((t_cmd_btree *)cmd)->left, depth + 1, 0);
		print_all_cmd_helper(((t_cmd_btree *)cmd)->right, depth + 1, 1);
	}
	else if (cmd->type == CMD_LIST)
	{
		printf("[LIST]\n");
		print_all_cmd_helper(((t_cmd_btree *)cmd)->left, depth + 1, 0);
		print_all_cmd_helper(((t_cmd_btree *)cmd)->right, depth + 1, 1);
	}
}

void	print_all_cmd(t_cmd_base *cmd)
{
	if (cmd == NULL)
		return ;
	print_all_cmd_helper(cmd, 0, 0);
}
