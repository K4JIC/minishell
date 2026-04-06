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
			$(SRCS_DIR)/frontend/parser/print_cmds.c\
			$(SRCS_DIR)/frontend/parser/separate_token.c\
			$(SRCS_DIR)/frontend/utils/find_token.c\
			$(SRCS_DIR)/frontend/utils/print_token.c\
			$(SRCS_DIR)/frontend/utils/token_list.c\
			$(SRCS_DIR)/envlst/envp_to_lst.c\
			$(SRCS_DIR)/utils/list/intrusive_list.c\
			$(SRCS_DIR)/utils/msmalloc/ms_malloc.c\
			$(SRCS_DIR)/utils/quote/ms_quote.c
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
