# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/28 00:08:14 by tozaki            #+#    #+#              #
#    Updated: 2026/03/05 00:00:00 by tozaki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
AR      := ar rcs
CFLAGS  := -Wall -Wextra -Werror -MMD -MP
INCLUDES	:=	-Iincludes -I../libft

LIB     := libutils.a
SRCDIRS := quote\
           list\
           msmalloc\
           error

SRC     := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJDIR  := objs
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

DEPS    := $(OBJS:.o=.d)

.PHONY: all clean fclean re msmalloc quote list

all: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(dir $(OBJS))
	$(AR) $@ $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

-include $(DEPS)

TEST_SRC := test/main.c
TEST_BIN := test_run

msmalloc: $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) -DMSMALLOC $(OBJS) $(TEST_SRC) -L../libft -lft -o $(TEST_BIN)
	./$(TEST_BIN)
	@rm -f $(TEST_BIN)

quote: $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) -DQUOTE $(OBJS) $(TEST_SRC) -L../libft -lft -o $(TEST_BIN)
	./$(TEST_BIN)
	@rm -f $(TEST_BIN)

list: $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) -DLIST $(OBJS) $(TEST_SRC) -L../libft -lft -o $(TEST_BIN)
	./$(TEST_BIN)
	@rm -f $(TEST_BIN)

clean:
	rm -rf $(OBJDIR)
	rm -f $(DEPS)

fclean: clean
	rm -f $(LIB)

re: fclean all
