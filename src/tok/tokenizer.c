/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/08 00:35:10 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static token_t	*init_new_token(char *start, char *current, tokentype_t type, data_t data)
{
	token_t	*new_token;

	new_token = allocate_memory(sizeof(token_t));
	new_token->value = strndup(start, current - start);
	new_token->type = type;
	new_token->envp = data.envp;
	new_token->next = NULL;
	new_token->connect = 0;
	return (new_token);
}

void	print_commands(token_t *head)
{
	token_t	*current_token;
	int		i;

	current_token = head;
	i = 0;
	printf("----------- tokenizer debug ----------------------------------\n");
	while (current_token)
	{
		printf("Token %d: %s, Type: %d, Connect: %i\n", i, current_token->value,
			current_token->type, current_token->connect);
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

static tokentype_t parse_redirect_token(char **current)
{
    if (**current == '<')
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
	// if (**current == '$')
	// {
	// 	if (**current+1 != '\0' && **current+1 != ' '  && **current+1 != '\t')
	// 		(*current)++;
	// 	return (T_ENV_VARIABLE);
	// }
	if (**current == '~')
	{
		if (**current+1 != '\0' && **current+1 != ' '  && **current+1 != '\t')
			(*current)++;
		return (T_TILDE);
	}
	return (T_WORD); // Default return
}

// ... [rest of the existing code] ...

static tokentype_t parse_word_token(char **current)
{
    while (**current && !is_whitespace(**current) && **current != '|' && **current != '<' && **current != '>' && **current != '\'' && **current != '\"')
    {
        (*current)++;
    }

    return T_WORD;
}

token_t *ms_tokenizer(data_t data)
{
    token_t *head = NULL;
    token_t *current_token = NULL;
    char *current = data.user_input;

    while (*current != '\0')
    {
        while (is_whitespace(*current))
            current++;

        char *start = current;
        tokentype_t current_token_type = T_WORD;

        // Check for special characters and create separate tokens
        if (*current == '<' || *current == '>' || *current == '|')
        {
            if (*current == '|')
                current_token_type = parse_pipe_token(&current);
            else
                current_token_type = parse_redirect_token(&current);

            char *value = strndup(start, current - start);
            token_t *new_token = init_new_token(value, current, current_token_type, data);

            if (!head)
                head = new_token;
            else
                current_token->next = new_token;
            current_token = new_token;

            // Reset connect flag after pipe or redirection
            current_token->connect = 0;

            start = current;
        }

        // Parse other types of tokens
        if (*current == '\'' || *current == '\"')
        {
            current_token_type = parse_quote_token(&current);
        }
        else
        {
            current_token_type = parse_word_token(&current);
        }

        // Create a token for the parsed word or quote
        if (current != start)
        {
            char *value = strndup(start, current - start);
            token_t *new_token = init_new_token(value, current, current_token_type, data);

            if (!head)
                head = new_token;
            else
                current_token->next = new_token;
            current_token = new_token;

            if (is_whitespace(*current) || *current == '|' || *current == '<' || *current == '>')
                current_token->connect = 0;
            else
                current_token->connect = 1;
        }
    }

    // print_commands(head);
    return head;
}
