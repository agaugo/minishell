/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:11:03 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 11:33:36 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_list2(token_t *head)
{
    token_t    *current_token;
    int        i;

    current_token = head;
    i = 0;
    printf("----------- expander debug -----------------------------------\n");
    while (current_token)
    {
        printf("Token %d: %s, Type: %d\n", i, current_token->value,
            current_token->type);
        current_token = current_token->next;
        i++;
    }
    printf("--------------------------------------------------------------\n");
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
