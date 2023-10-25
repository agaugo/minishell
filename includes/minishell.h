/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/10/25 11:40:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#define PROMPT "\001\033[1;31m\002[\001\033[0m\002 \001\033[1;3;31m\002MINISHELL\001\033[0m\002 \001\033[1;31m\002]\001\033[0m\002\001\033[1;36m\002$\001\033[0m\002 "
# define OPEN "\033[1;31m_______________________________________________________________________\n_/_____//_____//_____//_____//_____//_____//_____//_____//_____//_____/\n\n______  ______________   _____________________  ______________________ \n___   |/  /___  _/__  | / /___  _/_  ___/__  / / /__  ____/__  /___  / \n__  /|_/ / __  / __   |/ / __  / _____ \\__  /_/ /__  __/  __  / __  /  \n_  /  / / __/ /  _  /|  / __/ /  ____/ /_  __  / _  /___  _  /___  /___\n/_/  /_/  /___/  /_/ |_/  /___/  /____/ /_/ /_/  /_____/  /_____/_____/\n\n_______________________________________________________________________\n_/_____//_____//_____//_____//_____//_____//_____//_____//_____//_____/\n\n\033[0m"

#include "../libft/libft.h"
#include "builtins.h"
#include "lexer.h"
#include "executor.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct data {
    struct termios  orig_termios;
    char            **envp;
    char            *user_input;
    char            *executableDir;
    token_t         *tokens;
} data_t;

// Location: /src/main.c
void executeBuiltin(struct termios *_oldTermios, token_t *_token);
void exitShell(struct termios *_oldTermios);
void processInput(data_t data, char *_userInput, struct termios *_oldTermios, token_t *_token, char ***envp);
int main(int argc, char *argv[], char *envp[]);

// Location: /src/utils/
void handleError(int _exitCode, char *_errorMessage);

// Location: /src/builtins/
int restoreTerminal(struct termios *_oldTermios);

// Location: /src/builtins/env.c
void	ms_print_env_variables(data_t data);

#endif
