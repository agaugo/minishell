# Makefile with colored outputs

NAME = minishell
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iincludes/ -Ilibft/ -Ift_printf/
LDFLAGS = -lreadline

SRC = \
	src/main.c \
	src/builtins/cd.c \
	src/builtins/exit.c \
	src/utils/error_handling.c \
	src/lex/lexer.c \
	src/prs/parser.c \
	src/exe/executor.c \
	src/exe/redirect.c \
	src/exe/validator.c \
	src/builtins/pwd.c \
	src/builtins/env.c \
	src/builtins/echo.c \
	src/builtins/unset.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

# Define colors for outputs
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)%.o: %.c
	@echo "$(BLUE)Creating object files...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	$(MAKE) all -C libft

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C libft

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all
