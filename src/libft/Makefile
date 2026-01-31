CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror -I./ft_printf/header -I./GNL -I./

AR	:= ar
ARFLAGS	:= rsc

INCLUDES	:= ./libft.h

NAME	:= libft.a

SRC_PART1 := \
			 ./ft_memset.c  \
			 ./ft_bzero.c   \
			 ./ft_memcpy.c	\
			 ./ft_memmove.c	\
			 ./ft_memchr.c	\
			 ./ft_memcmp.c	\
			 ./ft_calloc.c	\
			 ./ft_strlen.c	\
			 ./ft_strlcpy.c	\
			 ./ft_strlcat.c	\
			 ./ft_strchr.c	\
			 ./ft_strrchr.c	\
			 ./ft_strncmp.c	\
			 ./ft_strnstr.c	\
			 ./ft_strdup.c	\
			 ./ft_isdigit.c	\
			 ./ft_issign.c  \
			 ./ft_atoi.c	\
			 ./ft_atol.c    \
			 ./ft_isalpha.c	\
			 ./ft_isalnum.c	\
			 ./ft_isascii.c	\
			 ./ft_isprint.c	\
			 ./ft_toupper.c	\
			 ./ft_tolower.c \
			 ./ft_isspace.c

SRC_PART2	:= \
			   ./ft_substr.c		\
			   ./ft_strjoin.c		\
			   ./ft_strtrim.c		\
			   ./ft_split.c			\
			   ./ft_itoa.c			\
			   ./ft_strmapi.c		\
			   ./ft_striteri.c		\
			   ./ft_putchar_fd.c	\
			   ./ft_putstr_fd.c		\
			   ./ft_putendl_fd.c	\
			   ./ft_putnbr_fd.c

SRC_BONUS	:= \
			   ./ft_lstnew.c			\
			   ./ft_lstadd_front.c		\
			   ./ft_lstsize.c			\
			   ./ft_lstlast.c			\
			   ./ft_lstadd_back.c		\
			   ./ft_lstdelone.c			\
			   ./ft_lstclear.c			\
			   ./ft_lstiter.c			\
			   ./ft_lstmap.c

SRC_PRINTF	:= \
				./ft_printf/ft_printf.c                  \
				./ft_printf/parse/parse_flag.c           \
				./ft_printf/parse/parse_precision.c      \
				./ft_printf/parse/parse_specifier.c      \
				./ft_printf/parse/parse_width.c          \
				./ft_printf/print/print_char.c           \
				./ft_printf/print/print_hex_integer.c    \
				./ft_printf/print/print_hex_lower.c      \
				./ft_printf/print/print_hex_upper.c      \
				./ft_printf/print/print_pointer.c        \
				./ft_printf/print/print_signed_nbr.c     \
				./ft_printf/print/print_str.c            \
				./ft_printf/print/print_unsigned_nbr.c   \
				./ft_printf/utils/get_decimal_len.c      \
				./ft_printf/utils/get_hex_len.c          \
				./ft_printf/utils/init_flags.c           \
				./ft_printf/utils/is_flag_specifier.c    \
				./ft_printf/utils/ptf_print_padding.c    \
				./ft_printf/utils/ptf_putchar.c          \
				./ft_printf/utils/ptf_putnbr.c           \
				./ft_printf/utils/ptf_putnbr_absolute.c  \
				./ft_printf/utils/ptf_putnbr_base.c      \
				./ft_printf/utils/ptf_putnbr_hex.c       \
				./ft_printf/utils/ptf_putnbr_hex_upper.c \
				./ft_printf/utils/ptf_putnbr_unsigned.c  \
				./ft_printf/utils/ptf_putstr.c           \
				./ft_printf/utils/write_check.c

SRC_GNL	:= \
			./GNL/get_next_line.c \
			./GNL/get_next_line_utils.c

SRCS	:= $(SRC_PART1) $(SRC_PART2) $(SRC_BONUS) $(SRC_PRINTF) $(SRC_GNL)
OBJ	:= $(SRCS:.c=.o)

#OBJ_BONUS	:= $(SRC_BONUS:.c=.o)


all: $(NAME)

#bonus: $(OBJ) $(OBJ_BONUS)
#	$(AR) $(ARFLAGS) $(NAME) $^

$(NAME): $(OBJ)
	@printf "\r\033[K\033[32mCompiling Done!!\033[0m"
	@echo "\n\033[32mCreating archive $(NAME)...\033[0m"
	@$(AR) $(ARFLAGS) $@ $^
	@echo "\033[32mCreating libft.a Done!!\033[0m"

%.o: %.c $(INCLUDES)
	@printf "\r\033[K\033[32mCompiling $<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[33mCleaning object files...\033[0m"
	@rm -f $(OBJ)
	@echo "\033[33mCleaning Done!!\033[0m"

fclean: clean
	@echo "\033[31mRemoving binary...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31mRemoving Done!!\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
