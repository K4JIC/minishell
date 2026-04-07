#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "token.h"
# include "cmd.h"
# include "ms_utils.h"

# define SUCCESS 0
# define FAILURE 1
# define SKIP -1

/*
 * The third argument to the main function,char **envp,
 * is managed as a structure to facilitate adding and removing elements.
*/
typedef struct s_env{
	char			*key;
	char			*value;
}t_env;

typedef enum e_redirect_type{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}t_redirect_type;

typedef struct s_redirect{
	t_redirect_type	type;
	char			*file;
	int				fd;
}t_redirect;

//The master structure that controls everything
typedef struct s_minishell{
	t_list		*env_list;
	t_token		*tokens;
	t_cmd_base	*cmd_btree;
	int			exit_status;//for $?
	int			syntax_error;// syntax_error flag
	int			stdin_backup;// for redirection and built-in commands
	int			stdout_backup;
	int			should_exit;
}t_minishell;

t_list	*envp_to_lst(char **envp);
t_env	*find_env(t_list *env_list, char *key);
int		set_env(t_list **env_list, char *key, char *value);
int		remove_env(t_list **env_list, char *key);
void	free_env_content(t_env *env);
int		print_export(t_list *env_list);
int		is_valid_identifier(char *str);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_list *env_list);
int		ft_cd(char **args, t_list **env_list);
int		ft_export(char **args, t_list **env_list);
int		ft_unset(char **args, t_list **env_list);
int		ft_exit(char **args, t_minishell *ms);

int		frontend(char *input, t_minishell *ms);
int		convert_token_to_cmd(t_minishell *sh, t_cmd_base **parent, t_token *head);
void	print_all_cmd(t_cmd_base *cmd);

#endif
