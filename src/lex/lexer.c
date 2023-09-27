/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/27 12:53:11 by trstn4        ########   odam.nl         */
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

void print_commands(command_t *head) {
	command_t *current_command = head;

	printf("----------- lexer debug -----------------------------------------------\n");
	while (current_command)
	{
		printf("Command: \n");
		int i = 0;
		while (current_command->tokens && current_command->tokens[i])
		{
			printf("Token %d: %s, Type: %d\n", i, current_command->tokens[i]->value, current_command->tokens[i]->type);
			i++;
		}
		current_command = current_command->next;
	}
	printf("-----------------------------------------------------------------------\n");
}

void lexer(char *_userInput) {
    command_t *head = NULL, *current_command = NULL;
    
    char *start_command = _userInput;
    char *current = _userInput;
    
    while (*current != '\0')
    {
        while (*current != '\0')
        {
            if (*current == '|')
            {
                if (*(current + 1) == '|')
                {
                    current += 2; // Skip over logical OR
                    continue;
                }
                else
                {
                    *current = '\0'; // split commands on single pipe
                    current++;
                    break;
                }
            }
            current++;
        }
        
        char *command_substring = strndup(start_command, current - start_command);
        char *trimmed_command = ft_strtrim(command_substring, " \t\n");
        free(command_substring); 
        
        int j = 0;
        token_t **tokens = NULL;
        char *command_current = trimmed_command;
        tokentype_t current_token_type;

		while(*command_current != '\0')
		{
			char *start = command_current;
			
			if (is_whitespace(*command_current))
			{
				while (is_whitespace(*command_current))
					command_current++;
				continue;
			}
			else if (*command_current == '|')
			{
				if (*(command_current + 1) != '\0' && *(command_current+1) == '|')
				{
					current_token_type = T_LOGICAL_OR; 
					command_current += 2;
				}
				else
				{
					current_token_type = T_PIPE;
					command_current++;
				}
			}
			else if (*(command_current + 1) != '\0' && *command_current == '<')
			{
				if (*(command_current+1) == '<')
				{
					current_token_type = T_HEREDOC;
					command_current += 2;
				}
				else
				{
					current_token_type = T_REDIRECT_IN;
					command_current++;
				}
			}
			else if (*command_current == '>')
			{
				if (*(command_current + 1) != '\0' && *(command_current+1) == '>')
				{
					current_token_type = T_APPEND_OUT;
					command_current += 2;
				}
				else
				{
					current_token_type = T_REDIRECT_OUT;
					command_current++;
				}
			}
			else if (*command_current == '\'')
			{
				current_token_type = T_SINGLE_QUOTE;
				command_current++;
				while (*command_current != '\'' && *command_current != '\0')
					command_current++;
				if (*command_current == '\'')
					command_current++;
			}
			else if (*command_current == '\"')
			{
				current_token_type = T_DOUBLE_QUOTE;
				command_current++;
				while (*command_current != '\"' && *command_current != '\0')
					command_current++;
				if (*command_current == '\"')
					command_current++;
			}
			else if (*command_current == '$')
			{
				if (*(command_current+1) == '?')
				{
					current_token_type = T_EXIT_STATUS;
					command_current += 2;
				}
				else
				{
					current_token_type = T_ENV_VARIABLE;
					command_current++;
					while(isalnum(*command_current) || *command_current == '_')
						command_current++;
				}
			}
			else if (*command_current == '&' && *(command_current+1) == '&')
			{
				current_token_type = T_WORD;
				command_current += 2;
			}
			else if (isalnum(*command_current) || *command_current == '_' || *command_current == '/' || *command_current == '.' || (*command_current == '-' && isalnum(*(command_current + 1))))
			{
				current_token_type = T_WORD;
				while(isalnum(*command_current) || *command_current == '_' || *command_current == '/' || *command_current == '.' || *command_current == '-')
					command_current++; 
			}
			else if (*command_current == '\n')
			{
				current_token_type = T_NEWLINE;
				command_current++;
			}
			else
			{
				command_current++;
			}

			int len = command_current - start;
			if(len > 0)
			{
				char *value = strndup(start, len);
				tokens = realloc(tokens, (j + 2) * sizeof(token_t *));
				tokens[j] = create_token(value, current_token_type);
				tokens[j + 1] = NULL;
				j++;
			}
		}

		if (tokens) tokens = realloc(tokens, (j + 1) * sizeof(token_t *));
		tokens[j] = NULL;
        command_t *command = malloc(sizeof(command_t));
        command->tokens = tokens;
        command->next = NULL;
        
        if (!head)
        {
            head = command;
            current_command = head;
        }
        else
        {
            current_command->next = command;
            current_command = command;
        }
        
        free(trimmed_command);
        
        start_command = current; // start new command after single pipe
    }
    
    print_commands(head);
}
