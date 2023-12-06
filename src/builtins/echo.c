/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/06 18:35:46 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



static void	ms_print_echo(token_t *token, char *str)
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
    char *str = NULL;
    token_t *start_token = token;
    int flag = 0;
    int stdout_backup = dup(STDOUT_FILENO); // Backup stdout

    token = token->next; // Skip the echo token

    // Check for "-n" flag and skip it
    if (token && ft_strcmp(token->value, "-n") == 0)
    {
        flag = 1; // "-n" flag found
        token = token->next; // Skip the "-n" token
    }

    // Iterate through tokens to find redirection or build the string to print
    while (token)
    {
        if (ft_strcmp(token->value, ">") == 0 || ft_strcmp(token->value, ">>") == 0)
        {
            int flags = (ft_strcmp(token->value, ">>") == 0) ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC);
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
                break; // Stop processing further tokens
            }
        }
        if (ft_strcmp(token->value, "<") == 0)
        {
            token = token->next->next; // Skip the "<" token and its following file name
            continue;
        }
        else
        {
            // Take the first token after any flags or redirections as the string to print
            if (!str)
            {
                str = token->value;
            }
            break;
        }
        token = token->next;
    }

    // Print the string if it's not NULL
    if (str)
    {
        if (flag)
            printf("%s", str); // Without newline if "-n" is present
        else
            printf("%s\n", str); // With newline
    }

    // Restore STDOUT
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    data->last_exit_code = 0;
}
