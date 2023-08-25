NAME = minishell
LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes/
LDFLAGS = -lreadline

SRC = \
		src/main.c \
		src/builtins/cd.c \

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) all -C libft

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all
