/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/07 19:15:23 by trstn4        ########   odam.nl         */
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

typedef struct data {
    char            **envp;
    char            *user_input;
    char            *executableDir;
    int             last_exit_code;
    token_t         *tokens;
    int             redirect;
    int             pipe[2];
    char            *heredoc_tmp_file;
    char            *last_path;
} data_t;

void	*allocate_memory(size_t buffer_size);

// Location: /src/main.c
void executeBuiltin(struct termios *_oldTermios, token_t *_token);
int main(int argc, char *argv[], char *envp[]);

// Location: /src/utils/
void	ms_handle_error(int _exitCode, char *_errorMessage);

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
void    resolve_command_paths(data_t *data);

// In includes/minishell.h or a similar header file
int is_builtin_command(char *command);

char *expand_quotes(data_t *data, char *token_value);
int setup_redirection(token_t *tokens, int direction);

#endif
