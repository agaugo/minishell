/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/13 14:06:01 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "\001\033[1;31m\002[\001\033[0m\002 \001\033[1;3;31m\002MINISHELL\001\033[0m\002 \001\033[1;31m\002]\001\033[0m\002\001\033[1;36m\002$\001\033[0m\002 "
# define OPEN "\033[1;31m_______________________________________________________________________\n_/_____//_____//_____//_____//_____//_____//_____//_____//_____//_____/\n\n______  ______________   _____________________  ______________________ \n___   |/  /___  _/__  | / /___  _/_  ___/__  / / /__  ____/__  /___  / \n__  /|_/ / __  / __   |/ / __  / _____ \\__  /_/ /__  __/  __  / __  /  \n_  /  / / __/ /  _  /|  / __/ /  ____/ /_  __  / _  /___  _  /___  /___\n/_/  /_/  /___/  /_/ |_/  /___/  /____/ /_/ /_/  /_____/  /_____/_____/\n\n_______________________________________________________________________\n_/_____//_____//_____//_____//_____//_____//_____//_____//_____//_____/\n\n\033[0m"

#include "../libft/libft.h"
#include "tokenizer.h"

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

extern int g_print_new_prompt;

typedef struct data {
    char            **envp;
    char            *user_input;
    int             last_exit_code;
    token_t         *tokens;
    int             redirect;
    int             pipe[2];
    char            *heredoc_tmp_file;
    char            *last_path;
    struct termios	*original_termios;
} data_t;

struct termios enable_noncanonical_mode(void);

// Main
void	ms_make_data_struct(data_t *data, char **envp);
void	ms_check_redirect(data_t *data);

// Tokenizer
void	test_tok(token_t *head);
token_t	*ms_tokenizer(data_t data);
void	parse_special_tokens(char **current, token_t **head, token_t **current_token);
void	parse_regular_tokens(char **current, token_t **head, token_t **current_token);
tokentype_t	parse_pipe_token(char **current);
tokentype_t	parse_redirect_token(char **current);
tokentype_t	parse_redirect_token2(char **current);
tokentype_t	parse_quote_token(char **current);
tokentype_t	parse_word_token(char **current);
int	ms_is_whitespace(char c);
token_t	*init_new_token(char *start, char *current, tokentype_t type);


// Expander
typedef struct s_quote_vars
{
	size_t	*i;
	size_t	*j;
	int		*in_single_quote;
	int		*in_double_quote;
	char	*cleaned_str;
}				t_quote_vars;

char *ms_clean_quotes(t_quote_vars *vars, const char *str);

// Executor
typedef struct exec_data {
    pid_t pid;
    token_t *current;
    token_t *next_command;
    char **args;
    int fds[2];
    int in_fd;
    int is_pipe;
    int is_redirect;
    int br;
    int br2;
    token_t *first_command_token;
} exec_data_t;

void	ms_run_builtin(data_t *data, char **args, token_t *current);
int	ms_is_builtin_command(char *command);
void	ms_resolve_command_paths(data_t *data);
int ms_is_directory(const char *path);
int	ms_set_command_path(char **allpath, token_t *current);
char	**ms_get_full_args(token_t *start_token, token_t *end_token);
token_t *ms_handle_heredoc(data_t *data, token_t *temp, token_t *first_command_token, int *br2);
token_t *ms_check_redirects(data_t *data, exec_data_t *cmd_data, token_t *next_command);
int ms_setup_redirection(token_t *tokens);
void	ms_throw_error(data_t *data, token_t *current);


// Expander
typedef struct exp_data {
	int		i;
	int		j;
    int		k;
	int		do_free;
} exp_data_t;

char *ms_expand_tilde(data_t *data, char *token_value);
char *ms_expand_dollarsign(data_t *data, char *token_value);
void ms_expand_variable(data_t *data, token_t *current_token);
void ms_expand_tokens(data_t *data, token_t *current_token);
void update_token_type(token_t *current_token);
void remove_token(token_t **head, token_t *prev_token, token_t *current_token);
void remove_empty_token(data_t *data, token_t **prev_token, token_t **current_token);
void remove_next_token(token_t *current);
char *merge_token_values(token_t *current, token_t *next);
void merge_connected_tokens(data_t *data);
char *ms_call_expand(data_t *data, char *token_value);
char *ms_expand_exit_code(data_t *data, char *token_value, int *do_free, int i);

void	print_env(data_t *data);
void	update_env(data_t *data, char *key, char *new_assignment);

void	*allocate_memory(size_t buffer_size);
char *ft_strcpy(char *dest, const char *src);
char *ft_strchr(const char *str, int character);
char *ft_strcat(char *dest, const char *src);
char *ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strndup(const char *str, size_t n);
void debug(char *output);
void	*memory_realloc(void* ptr, size_t new_size);

int	ms_get_env_size(char **envp);
void	ms_add_to_env(data_t *data, char *key);

// Location: /src/main.c
void executeBuiltin(struct termios *_oldTermios, token_t *_token);
int main(int argc, char *argv[], char *envp[]);

// Location: /src/utils/
void	ms_handle_error(int exit_code, char *message);

// Location: /src/builtins/
int		restoreTerminal(struct termios *_oldTermios);

/******** /src/builtins ********/
// Location: /src/builtins/env.c
void	ms_print_env_variables(data_t *data);
// Location: /src/builtins/cd.c
void	ms_cd_command(data_t *data, token_t *token);
// Location: /src/builtins/echo.c
void	ms_echo_command(data_t *data, token_t *token);
// Location: /src/builtins/exit.c
void    ms_exit_shell(data_t *data, token_t *token);
// Location: /src/builtins/export.c
void	ms_export_command(data_t *data, token_t *token);
// Location: /src/builtins/pwd.c
void	ms_pwd_command(data_t *data);
// Location: /src/builtins/unset.c
void	ms_unset_command(data_t *data, token_t *token);
/*******************************/

// Location: /src/main/init.c
int ms_set_terminal_settings(data_t *data);
char **ms_clone_envp(char **envp);

// Location: /src/main/signal.c
void ms_handle_ctrl_c(int _signalNumber);
void ms_handle_ctrl_d(data_t *data);
void ms_handle_ctrl_backspace(int _signalNumber);
int ms_init_signals(void);
int	ms_find_env_index(char **envp, const char *key);

char	*read_file_content(const char *filename);

void remove_intermediate_input_redirections(data_t *data);

token_t	*ms_tokenizer(data_t data);
void	ms_expander(data_t *data);

void ms_redirect(data_t *data);
void  ms_redirect_out_append(data_t *data);

void	ms_identify_command(data_t *data);
void	ms_execute_command(data_t *data, char **_array);

void ms_heredoc(data_t *data, token_t *token);

char	*ms_get_current_working_dir(void);

// ** src/exe/redirect.c

int		ms_load_fd(token_t *_token, tokentype_t _direction);
void	ms_handle_redirect(token_t *_token, tokentype_t _direction);

// ** src/exe/validator.c

void	ms_free_2d_array(char **_array);
char    *ft_getenv(char **envp, char *key);
void ms_check_pipe(data_t *data);

void    ms_execute_commands(data_t *data);

int setup_redirection(token_t *tokens);
void free_token_list(token_t *head);
void wipe_data_struct(data_t *data);
void	free_memory(void *buffer);

#endif
