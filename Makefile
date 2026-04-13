NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS_DIR	= src
OBJS_DIR	= obj
INC_DIR		= include
LIBFT_DIR	= src/libft

SRCS	=	$(SRCS_DIR)/main.c\
			$(SRCS_DIR)/frontend/frontend.c\
			$(SRCS_DIR)/frontend/lexer/label_token.c\
			$(SRCS_DIR)/frontend/lexer/tokenizer.c\
			$(SRCS_DIR)/frontend/parser/encase_cmd_exec.c\
			$(SRCS_DIR)/frontend/parser/encase_cmd_list.c\
			$(SRCS_DIR)/frontend/parser/encase_cmd_pipe.c\
			$(SRCS_DIR)/frontend/parser/encase_cmd_redir.c\
			$(SRCS_DIR)/frontend/parser/separate_token.c\
			$(SRCS_DIR)/frontend/parser/token_to_cmd.c\
			$(SRCS_DIR)/frontend/utils/find_token.c\
			$(SRCS_DIR)/frontend/utils/cmd_btree.c\
			$(SRCS_DIR)/frontend/utils/token_list.c\
			$(SRCS_DIR)/built_in/cd/ft_cd.c\
			$(SRCS_DIR)/built_in/echo/ft_echo.c\
			$(SRCS_DIR)/built_in/env/ft_env.c\
			$(SRCS_DIR)/built_in/exit/ft_exit.c\
			$(SRCS_DIR)/built_in/export/ft_export.c\
			$(SRCS_DIR)/built_in/export/print_export.c\
			$(SRCS_DIR)/built_in/pwd/ft_pwd.c\
			$(SRCS_DIR)/built_in/unset/ft_unset.c\
			$(SRCS_DIR)/envlst/envp_to_lst.c\
			$(SRCS_DIR)/envlst/utils/find_env.c\
			$(SRCS_DIR)/envlst/utils/free_env_content.c\
			$(SRCS_DIR)/envlst/utils/remove_env.c\
			$(SRCS_DIR)/envlst/utils/set_env.c\
			$(SRCS_DIR)/utils/list/intrusive_list.c\
			$(SRCS_DIR)/utils/msmalloc/ms_malloc.c\
			$(SRCS_DIR)/utils/quote/ms_quote.c

DEBUG_SRCS	=	$(SRCS_DIR)/test/frontend_test.c\
				$(SRCS_DIR)/test/print_cmds.c\
				$(SRCS_DIR)/test/print_token.c

OBJS	= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
LIBFT	= $(LIBFT_DIR)/libft.a

LIBS	= -lreadline -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
