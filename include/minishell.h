#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_minishell{
	t_env	*env_list;
	t_token	*tokens;
	t_cmd	*cmd_list;
	int		exit_status;
	int		syntax_error;//for $?
	int		stdin_backup;// 
	int		stdout_backup;
}t_minishell;

typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_cmd{
	char			**args;
	t_list			*redirects;
	int				pid;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
}t_cmd;

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

typedef enum e_token_type{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}t_token_type;

typedef struct s_token{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}t_token;

#endif
