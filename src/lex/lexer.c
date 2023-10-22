/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/22 19:21:00 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static token_t	*init_new_token(char *start, char *current, tokentype_t type,
								char *envp[])
{
	token_t	*new_token;

	new_token = malloc(sizeof(token_t));
	if (!new_token)
		return (NULL);
	new_token->value = strndup(start, current - start);
	new_token->type = type;
	new_token->envp = envp;
	new_token->next = NULL;
	return (new_token);
}

void			print_commands(token_t *head)
{
	token_t	*current_token;
	int		i;

	current_token = head;
	i = 0;
	printf("----------- lexer debug --------------------------------------\n");
	while (current_token)
	{
		printf("Token %d: %s, Type: %d Validity: %d\n", i,
				current_token->value, current_token->type,
				validateToken(current_token));
		current_token = current_token->next;
		i++;
	}
	printf("--------------------------------------------------------------\n");
}

static tokentype_t	parse_pipe_token(char **current)
{
	if (**current == '|')
	{
		(*current)++;
		return (T_PIPE);
	}
	return (T_WORD); // Default return
}

static tokentype_t	parse_redirect_token(char **current)
{
	if (*(*current + 1) != '\0' && **current == '<') 
	{
		if (*(*current + 1) == '<')
		{
			*current += 2;
			return (T_HEREDOC);
		}
		else
		{
			(*current)++;
			return (T_REDIRECT_IN);
		}
	}
	else if (**current == '>')
	{
		if (*(*current + 1) != '\0' && *(*current + 1) == '>')
		{
			*current += 2;
			return (T_APPEND_OUT);
		}
		else
		{
			(*current)++;
			return (T_REDIRECT_OUT);
		}
	}
	return (T_WORD); // Default return
}

static tokentype_t	parse_quote_token(char **current)
{
	if (**current == '\'')
	{
		(*current)++;
		while (**current != '\'' && **current != '\0')
			(*current)++;
		if (**current == '\'')
			(*current)++;
		return (T_SINGLE_QUOTE);
	}
	else if (**current == '\"')
	{
		(*current)++;
		while (**current != '\"' && **current != '\0')
			(*current)++;
		if (**current == '\"')
			(*current)++;
		return (T_DOUBLE_QUOTE);
	}
	return (T_WORD); // Default return
}

static tokentype_t	parse_special_token(char **current)
{
	if (**current == '$')
	{
		if (*(*current + 1) == '?')
		{
			*current += 2;
			return (T_EXIT_STATUS);
		}
		else
		{
			(*current)++;
			while (isalnum(**current) || **current == '_')
				(*current)++;
			return (T_ENV_VARIABLE);
		}
	}
	return (T_WORD); // Default return
}

static tokentype_t	parse_word_token(char **current)
{
	while (isalnum(**current) || **current == '_' || **current == '/'
		|| **current == '.' || **current == '-')
		(*current)++;
	return (T_WORD);
}

token_t	*lexer(char *_userInput, char *envp[])
{
	token_t		*head;
	token_t		*current_token;
	char		*current;
	tokentype_t	current_token_type;

	head = NULL;
	current_token = NULL;
	current = _userInput;
	while (*current != '\0')
	{
		char *start = current;
		if (is_whitespace(*current))
		{
			while (is_whitespace(*current))
				current++;
			continue;
		}
		current_token_type = parse_pipe_token(&current);
		if (current_token_type == T_WORD)
			current_token_type = parse_redirect_token(&current);
		if (current_token_type == T_WORD)
			current_token_type = parse_quote_token(&current);
		if (current_token_type == T_WORD)
			current_token_type = parse_special_token(&current);
		if (current_token_type == T_WORD)
			current_token_type = parse_word_token(&current);

		// Create new token
		if (current != start)
		{
			token_t *new_token = init_new_token(start, current,
												current_token_type, envp);
			if (!head)
			{
				head = new_token;
				current_token = head;
			}
			else
			{
				current_token->next = new_token;
				current_token = new_token;
			}
		}
	}
	print_commands(head);
	return (head);
}