# Makefile with colored outputs

NAME = minishell
LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes/
LDFLAGS = -lreadline

SRC = \
	src/main.c \
	src/builtins/cd.c \
	src/builtins/exit.c \

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
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
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
