/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 18:26:52 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 21:40:25 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

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
*/
typedef enum e_tokentype
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND_OUT,
	T_HEREDOC,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_ENV_VARIABLE,
	T_TILDE
}					tokentype_t;

/*
** token_t:
** Represents a single token parsed from a shell command.
**
** value: A string representation of the token's value. This could be the actual word,
	flag,
**        or any other parsed element from the command.
**
** type: Specifies the type of the token. It is an enum value which tells whether the token
**       is a word, flag, pipe, redirection, etc.
**
** next: A pointer to the next token in the linked list of tokens. This allows for the sequential
**       processing of each token in a command.
**
** envp: An array of environment variables. This is typically used to reference any environment
**       variables that might be invoked during command execution.
**
** executableDir: A string representation of the directory path where the executable corresponding
**                to this token is located. Useful for commands that require path resolution.
**
** _pipe: Represents an array that can be used for creating pipes between commands. This allows
**        for commands to communicate by sending and receiving data from one another.
*/
typedef struct token
{
	char			*value;
	tokentype_t		type;
	struct token	*next;
	int				fd;
	int				status;
	int				connect;
}					token_t;

#endif
