/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:11:03 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/01 22:38:46 by trstn4        ########   odam.nl         */
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
    char *input;
    char *expanded_input;
    char temp_filename[] = "/tmp/minishell_heredoc_XXXXXX"; // Template for temp file
    int fd = mkstemp(temp_filename); // Create and open a temporary file

    if (fd == -1) {
        perror("mkstemp");
        return;
    }

    int heredoc_fd = -1;
    if (data->heredoc_tmp_file != NULL) {
        heredoc_fd = open(data->heredoc_tmp_file, O_RDONLY);
        if (heredoc_fd == -1) {
            perror("open heredoc file");
            // Handle error
        }
    }

    if (heredoc_fd != -1) {
        close(heredoc_fd);
        unlink(data->heredoc_tmp_file); // Delete the temp file
        free(data->heredoc_tmp_file);
        data->heredoc_tmp_file = NULL;
    }

    while (1)
    {
        input = readline("> ");
        if (strcmp(input, delimiter) == 0)
        {
            free(input);
            break;
        }

        expanded_input = expand_quotes(data, input);
        write(fd, expanded_input, strlen(expanded_input));
        write(fd, "\n", 1); // Write newline character

        free(expanded_input);
        free(input);
    }
    close(fd);
    // Store the filename in your data structure for later use
    data->heredoc_tmp_file = strdup(temp_filename);
}

