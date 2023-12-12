/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:11:03 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 23:25:21 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

token_t *ms_handle_heredoc(data_t *data, token_t *temp, token_t *first_command_token, int *br2)
{
    while (temp != NULL) {
        if (temp->type == T_PIPE)
            first_command_token = temp->next;

        if (temp->type == T_HEREDOC) {
            if (temp->next == NULL || (temp->next && temp->next->type != T_WORD))
            {
                char    *val = NULL;
                if (temp->next == NULL)
                    val = "\\n";
                else
                    val = temp->next->value;
                fprintf(stderr, "syntax error near unexpected token '%s'\n", val);
                data->last_exit_code = 258;
                *br2 = 1;
                break;
            }
            else
            {
                ms_heredoc(data, temp);
                    
                temp->type = T_REDIRECT_IN;
                free_memory(temp->value);
                temp->value = ft_strdup("<");

                if (temp->next)
                {
                    temp->next->type = T_WORD;
                    free_memory(temp->next->value);
                    temp->next->value = ft_strdup(data->heredoc_tmp_file);

                    if (first_command_token && first_command_token->type != T_WORD)
                    {
                        token_t	*new_token;

                        new_token = allocate_memory(sizeof(token_t));
                        new_token->value = ft_strdup("|");
                        new_token->type = T_PIPE;
                        new_token->next = temp->next->next;
                        new_token->connect = 0;

                        temp->next->next = new_token;

                        ms_resolve_command_paths(data);
                    }
                }     
                    
                remove_intermediate_input_redirections(data);
                free_memory(data->heredoc_tmp_file);
                data->heredoc_tmp_file = NULL;  
            }
        }
        temp = temp->next;
    }
    return (first_command_token);
}

void ms_heredoc(data_t *data, token_t *token)
{
    char *delimiter = token->next->value;
    char temp_filename[] = "/tmp/minishell_heredoc";

    if (access(temp_filename, F_OK) == 0) {
        if (unlink(temp_filename) == -1) {
            perror("unlink");
            return;
        }
    }

    int fd = open(temp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("open");
        return;
    }

    char *input;
    char *expanded_input;

    while (1)
    {
        input = readline("> ");
        if (strcmp(input, delimiter) == 0)
        {
            free_memory(input);
            break;
        }

        expanded_input = expand_quotes(data, input);
        write(fd, expanded_input, strlen(expanded_input));
        write(fd, "\n", 1); // Write newline character

        free_memory(expanded_input);
        free_memory(input);
    }

    close(fd);

    // Store the filename in your data structure for later use
    data->heredoc_tmp_file = strdup(temp_filename);
}
