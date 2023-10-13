/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 18:26:52 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/29 22:57:40 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** tokentype_t:
** Represents different types of tokens available in the shell.
**
** T_WORD: Generic word or command name.
** T_PIPE: The '|' character, representing a pipe between commands.
** T_REDIRECT_IN: The '<' character, representing input redirection.
** T_REDIRECT_OUT: The '>' character, representing output redirection.
** T_APPEND_OUT: The '>>' characters, representing appending output redirection.
** T_HEREDOC: The '<<' characters, representing here documents.
** T_SINGLE_QUOTE: The '\'' character, representing single quotes.
** T_DOUBLE_QUOTE: The '\"' character, representing double quotes.
** T_ENV_VARIABLE: The '$' character, representing environment variables.
** T_EXIT_STATUS: The '$?' characters, representing the exit status of the last command.
** T_NEWLINE: The '\n' character, representing the end of a command.
** T_WHITESPACE: Represents spaces or tabs, which are used to separate tokens.
** T_BUILTIN: Represents built-in commands like echo, cd, pwd, etc.
** T_LOGICAL_AND: The '&&' characters, representing logical AND.
** T_LOGICAL_OR: The '||' characters, representing logical OR.
*/
typedef enum e_tokentype {
    T_WORD,
    T_PIPE,
    T_REDIRECT_IN,
    T_REDIRECT_OUT,
    T_APPEND_OUT,
    T_HEREDOC,
    T_SINGLE_QUOTE,
    T_DOUBLE_QUOTE,
    T_ENV_VARIABLE,
    T_EXIT_STATUS,
    T_NEWLINE,
    T_WHITESPACE,
    T_BUILTIN,
    T_LOGICAL_AND,
    T_LOGICAL_OR
} tokentype_t;

typedef struct token {
    char            *value;
    tokentype_t     type;
    struct token    *next;
    char            **envp;
    char            *executableDir;
    int             *_pipe;
} token_t;

#endif
