/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 12:15:55 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/19 13:57:50 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_commands_list(command_node_t *cmd_head) {
    printf("----------- parser debug ----------------------------------------------\n");
    
    command_node_t *cmd_node = cmd_head;
    while (cmd_node) {
        printf("Command Node: %s\n", cmd_node->value);
        
        if (cmd_node->flags_count > 0) {
            printf("  Flags: ");
            for (int j = 0; j < cmd_node->flags_count; j++) {
                printf("%s", cmd_node->flags[j]);
                if (j != cmd_node->flags_count - 1) {
                    printf(", ");
                }
            }
            printf("\n");
        } else {
            printf("  Flags: None\n");
        }

        if (cmd_node->args_count > 0) {
            printf("  Args: ");
            for (int j = 0; j < cmd_node->args_count; j++) {
                printf("%s", cmd_node->args[j]);
                if (j != cmd_node->args_count - 1) {
                    printf(", ");
                }
            }
            printf("\n");
        } else {
            printf("  Args: None\n");
        }

        cmd_node = cmd_node->next;
    }
    
    printf("-----------------------------------------------------------------------\n");
}

command_node_t *create_command_node(char *value) {
    command_node_t *node = (command_node_t *)malloc(sizeof(command_node_t));
    if (!node) {
        perror("Failed to allocate memory for command node");
        exit(EXIT_FAILURE);
    }

    node->value = strdup(value);
    node->flags = NULL;
    node->args = NULL;
    node->flags_count = 0;
    node->args_count = 0;
    node->next = NULL;

    return node;
}

static void	handle_word_flag_quote(token_t *current_token,
	command_node_t **current_cmd)
{
	char	*arg;

	if (current_token->type == T_FLAG && *current_cmd)
	{
		(*current_cmd)->flags_count++;
		(*current_cmd)->flags = realloc((*current_cmd)->flags,
			(*current_cmd)->flags_count * sizeof(char *));
		(*current_cmd)->flags[(*current_cmd)->flags_count - 1] =
			strdup(current_token->value);
	}
	else if ((current_token->type == T_WORD || current_token->type == T_DOUBLE_QUOTE ||
		current_token->type == T_SINGLE_QUOTE) && *current_cmd)
	{
		arg = (current_token->type == T_DOUBLE_QUOTE ||
			current_token->type == T_SINGLE_QUOTE) ?
			strdup(current_token->value) : strdup(current_token->value);
		if (current_token->type == T_DOUBLE_QUOTE ||
			current_token->type == T_SINGLE_QUOTE)
			arg[strlen(arg)] = '\0';
		(*current_cmd)->args_count++;
		(*current_cmd)->args = realloc((*current_cmd)->args,
			(*current_cmd)->args_count * sizeof(char *));
		(*current_cmd)->args[(*current_cmd)->args_count - 1] = arg;
	}
}

command_node_t *parse(token_t *head)
{
    command_node_t *cmd_head = NULL;
    command_node_t *current_cmd = NULL;
    token_t *current_token = head;

    while (current_token)
    {
        if (current_token->type == T_WORD)
        {
            command_node_t *new_cmd = create_command_node(current_token->value);

            if (!cmd_head)
                cmd_head = new_cmd;
            else
                current_cmd->next = new_cmd;
            
            current_cmd = new_cmd;
        }
        else if (current_token->type == T_PIPE)
        {
            if (!current_token->next || current_token->next->type != T_WORD)
            {
                fprintf(stderr, "Parsing error: unexpected pipe or missing command after pipe.\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            handle_word_flag_quote(current_token, &current_cmd);
        }

        current_token = current_token->next;
    }

    print_commands_list(cmd_head);
    return cmd_head;
}
