/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/08 13:03:11 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

static void ms_print_echo(token_t *token, char *str)
{
    if (!token->next || !token->next->value)
        printf("\n");
    else if (ft_strcmp(token->next->value, "-n") == 0)
    {
        if (token->next->next && token->next->next->value)
        {
            printf("%s", str);
        }
    }
    else
        printf("%s\n", str);
}

void ms_echo_command(data_t *data, token_t *token)
{
    int flag_n = 0;
    int first_word = 1;
    int stdout_backup = dup(STDOUT_FILENO); // Backup stdout
    int word_printed = 0;
    int after_output_redirect = 0; // Flag for output redirection

    token = token->next; // Skip the echo token

    // Iterate through tokens
    while (token)
    {
        if (token->type == T_PIPE)
            break;

        // Check for "-n" flag at the beginning
        if (first_word && ft_strcmp(token->value, "-n") == 0)
        {
            flag_n = 1;
            token = token->next;
            continue;
        }
        first_word = 0;

        // Handle output redirection
        if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
        {
            int flags = (token->type == T_APPEND_OUT) ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC);
            token = token->next; // Skip the redirection token
            if (token && token->value)
            {
                int fd = open(token->value, flags, 0666);
                if (fd < 0)
                {
                    perror("open");
                    data->last_exit_code = 1;
                    return;
                }
                dup2(fd, STDOUT_FILENO); // Redirect STDOUT to the file
                close(fd);
                token = token->next; // Move past the file name
                after_output_redirect = 1; // Set the flag since we are after output redirection
                continue; // Continue processing further tokens
            }
        }

        // Skip input redirection ("<") and its associated file name
        if (token->type == T_REDIRECT_IN)
        {
            token = token->next ? token->next->next : NULL;
            continue;
        }

        // Print tokens of type T_WORD
        if (token && token->type == T_WORD)
        {
            if (word_printed > 0 || after_output_redirect)
            {
                printf(" "); // Add a space if this is not the first word or after output redirection
            }

            printf("%s", token->value);
            word_printed++;

            after_output_redirect = 0; // Reset the output redirect flag
        }

        token = token->next;
    }
	
    // Print newline if "-n" flag is not present
    if (!flag_n)
    {
        printf("\n");
    }

    // Restore STDOUT
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    data->last_exit_code = 0;
}
