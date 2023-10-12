/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/29 23:12:36 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

token_t *create_token(char *value, tokentype_t type) {
	token_t *token = malloc(sizeof(token_t));
	token->value = value;
	token->type = type;
	return token;
}

int is_whitespace(char c) {
	return c == ' ' || c == '\t';
}

void print_commands(token_t *head) {
    token_t *current_token = head;

    printf("----------- lexer debug -----------------------------------------------\n");
    int i = 0;
    while (current_token) {
        printf("Token %d: %s, Type: %d\n", i, current_token->value, current_token->type);
        current_token = current_token->next;
        i++;
    }
    printf("-----------------------------------------------------------------------\n");
}

token_t *lexer(char *_userInput) {
    token_t *head = NULL, *current_token = NULL;
    char *current = _userInput;

    while (*current != '\0') {
        char *start = current;
        tokentype_t current_token_type = T_WORD; // Default token type

        if (is_whitespace(*current)) {
            while (is_whitespace(*current)) current++;
            continue;
        }
        
        else if (*current == '|') {
            if (*(current + 1) == '|') {
                current_token_type = T_LOGICAL_OR;
                current += 2;
            } else {
                current_token_type = T_PIPE;
                current++;
            }
        }
			else if (*(current + 1) != '\0' && *current == '<')
			{
				if (*(current+1) == '<')
				{
					current_token_type = T_HEREDOC;
					current += 2;
				}
				else
				{
					current_token_type = T_REDIRECT_IN;
					current++;
				}
			}
			else if (*current == '>')
			{
				if (*(current + 1) != '\0' && *(current+1) == '>')
				{
					current_token_type = T_APPEND_OUT;
					current += 2;
				}
				else
				{
					current_token_type = T_REDIRECT_OUT;
					current++;
				}
			}
			else if (*current == '\'')
			{
				current_token_type = T_SINGLE_QUOTE;
				current++;
				while (*current != '\'' && *current != '\0')
					current++;
				if (*current == '\'')
					current++;
			}
			else if (*current == '\"')
			{
				current_token_type = T_DOUBLE_QUOTE;
				current++;
				while (*current != '\"' && *current != '\0')
					current++;
				if (*current == '\"')
					current++;
			}
			else if (*current == '$')
			{
				if (*(current+1) == '?')
				{
					current_token_type = T_EXIT_STATUS;
					current += 2;
				}
				else
				{
					current_token_type = T_ENV_VARIABLE;
					current++;
					while(isalnum(*current) || *current == '_')
						current++;
				}
			}
			else if (*current == '&' && *(current+1) == '&')
			{
				current_token_type = T_LOGICAL_AND;
				current += 2;
			}
			else if (isalnum(*current) || *current == '_' || *current == '/' || *current == '.' || (*current == '-' && isalnum(*(current + 1))))
			{
				current_token_type = T_WORD;
				while(isalnum(*current) || *current == '_' || *current == '/' || *current == '.' || *current == '-')
					current++; 
			}
			else if (*current == '\n')
			{
				current_token_type = T_NEWLINE;
				current++;
			}
        else {
            while (*current != '\0' && !is_whitespace(*current) && *current != '|')
                current++;
        }
        
        if (current != start || current_token_type == T_PIPE || current_token_type == T_LOGICAL_OR) {
            char *value = strndup(start, current - start);
            token_t *new_token = malloc(sizeof(token_t));
            new_token->value = value;
            new_token->type = current_token_type;
            new_token->next = NULL;

            if (!head) {
                head = new_token;
                current_token = head;
            } else {
                current_token->next = new_token;
                current_token = new_token;
            }
        }
    }
	print_commands(head);
    return head;
}
