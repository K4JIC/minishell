NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

LIBFT_DIR	=	libft
OBJS_DIR	=	objs

SRCS	= main.c\
		  lexer.c
OBJS	= $(SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT	= $(LIBFT_DIR)/libft.a

LIBS	= -lreadline -L$(LIBFT_DIR) -lft

vpath %.c frontend
vpath %.h ../include

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I ../include -I$(LIBFT_DIR) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
