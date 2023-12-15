NAME = minishell
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes/ -Ilibft/ -Ift_printf/
LDFLAGS = -lreadline
OBJS_DIR = objs/

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

SRC = \
	src/builtins/cd.c			\
	src/builtins/echo.c			\
	src/builtins/env.c			\
	src/builtins/exit.c			\
	src/builtins/export.c		\
	src/builtins/export_extra.c	\
	src/builtins/pwd.c			\
	src/builtins/unset.c		\
	src/exe/executor.c			\
	src/exe/exe_heredoc.c		\
	src/exe/exe_resolve_paths.c	\
	src/exe/exe_builtins.c		\
	src/exe/exe_utils.c			\
	src/exe/exe_redirects.c		\
	src/exe/exe_syntax.c		\
	src/exe/exe_pid.c			\
	src/exp/expander.c			\
	src/exp/exp_quotes.c		\
	src/exp/exp_expand.c		\
	src/exp/exp_token_utils.c	\
	src/exp/exp_merge.c			\
	src/main/env.c				\
	src/main/env2.c				\
	src/main/main.c				\
	src/main/main_utils.c		\
	src/main/signal.c			\
	src/tok/tokenizer.c			\
	src/tok/tok_create_link.c	\
	src/tok/tok_parse_tokens.c	\
	src/tok/tok_utils.c			\
	src/utils/error.c			\
	src/utils/memory.c			\
	src/utils/stdlib.c			\
	src/utils/path.c			\
	src/main/term.c				\
	src/test/test.c				\
	src/utils/memory2.c

OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)%.o: %.c
	@echo "$(BLUE)Creating $(NAME) object files...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) all -C libft

clean:
	@echo "$(RED)Cleaning $(NAME) object files...$(RESET)"
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C libft

fclean: clean
	@echo "$(RED)Removing $(NAME) executable...$(RESET)"
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all
