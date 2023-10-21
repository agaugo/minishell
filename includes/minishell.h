/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/10/19 14:08:59 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "\033[1;31m[\033[0m \033[1;3;31mMINISHELL\033[0m \033[1;31m]\033[0m\033[1;36m$\033[0m "
# define OPEN "\033[1;31m_______________________________________________________________________\n_/_____//_____//_____//_____//_____//_____//_____//_____//_____//_____/\n\n______  ______________   _____________________  ______________________ \n___   |/  /___  _/__  | / /___  _/_  ___/__  / / /__  ____/__  /___  / \n__  /|_/ / __  / __   |/ / __  / _____ \\__  /_/ /__  __/  __  / __  /  \n_  /  / / __/ /  _  /|  / __/ /  ____/ /_  __  / _  /___  _  /___  /___\n/_/  /_/  /___/  /_/ |_/  /___/  /____/ /_/ /_/  /_____/  /_____/_____/\n\n_______________________________________________________________________\n_/_____//_____//_____//_____//_____//_____//_____//_____//_____//_____/\n\n\033[0m"

# include "../libft/libft.h"
#include "colors.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <ctype.h>


//structs
typedef struct s_terminal
{
	int	x;
} t_terminal;

//used for converting env from char ** to linked list to dynamically add and remove variables.
//typedef struct s_envLinkedList
//{
//    char *_envVariable;
//    struct s_envLinkedList *_next;
//} t_envLinkedList;

//functions
// Location: /src/main.c
void handleSigInt(int _signalNumber);
void handleSigQuit(int _signalNumber);
void executeBuiltin(struct termios *_oldTermios, token_t *_token);
int  initSignals(void);
int  initTerminal(struct termios *_oldTermios);
void exitShell(struct termios *_oldTermios);
void processInput(char *_userInput, struct termios *_oldTermios, token_t *_token);
int main(int argc, char *argv[], char *envp[]);

// Location: /src/utils/
void handleError(int _exitCode, char *_errorMessage);

// Location: /src/builtins/
int restoreTerminal(struct termios *_oldTermios);
void exitShell(struct termios *_oldTermios);
void cdCommand(token_t *_token);
char *getCurrentWorkingDirectory(void);
void printENV(token_t *_token);
void echoCommand(token_t *_token);
void unsetCommand(token_t *_token);

// Location: /src/lex/
token_t *lexer(char *_userInput, char *envp[]);

// Location: /src/prs/
command_node_t *parse(token_t *head);

#endif
