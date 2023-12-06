/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/06 17:37:39 by trstn4        ########   odam.nl         */
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

// void	ms_echo_command(data_t *data, token_t *token)
// {
// 	char			*str;
// 	char			*cleaned_str;
// 	char			*temp;
// 	token_t *start_token;
// 	int flag = 0;

// 	start_token = token;
// 	str = NULL;
// 	token = token->next;

// 	if (data->redirect == 2)
//     {
//         char buffer[1024];
//         while (fgets(buffer, sizeof(buffer), stdin) != NULL)
//         {
//             fputs(buffer, stdout);
//         }
//     }
//     else
// 	{
// 		while (token)
// 		{
// 			if (token->type == T_PIPE)
// 				break;
// 			if (ft_strcmp(token->value, "-n") == 0 && flag == 0)
// 			{
// 				token = token->next;
// 				continue;
// 			}
// 			else
// 				flag = 1;
// 			cleaned_str = token->value;
// 			if (!str)
// 				str = cleaned_str;
// 			else
// 			{
// 				temp = ft_strjoin(str, " ");
// 				free(str);
// 				str = ft_strjoin(temp, cleaned_str);
// 				free(temp);
// 			}
// 			token = token->next;
// 		}
// 		ms_print_echo(start_token, str);
// 		free(str);
// 	}
// 	data->last_exit_code = 0;
// }

void ms_echo_command(data_t *data, token_t *token)
{
    char *str;
    char *cleaned_str;
    token_t *start_token;
    int flag = 0;
    int stdin_backup = dup(STDIN_FILENO);   // Backup stdin
    int stdout_backup = dup(STDOUT_FILENO); // Backup stdout

    start_token = token;
    str = NULL;
    token = token->next;

    // Check if output redirection is needed
    if (setup_redirection(start_token, 1) == -1)
    {
        fprintf(stderr, "Output redirection failed\n");
        data->last_exit_code = 1;
        return;
    }

    // Find the first non-flag token
    while (token)
    {
        if (token->type == T_PIPE)
            break;
        if (ft_strcmp(token->value, "-n") == 0 && flag == 0)
        {
            token = token->next;
            continue;
        }
        else
            flag = 1;

        cleaned_str = token->value;
        str = cleaned_str;
        break; // Output only the first non-flag token
    }

    if (str)
    {
        printf("%s\n", str);
    }

    // Reset stdin and stdout to their original state
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);

    close(stdin_backup);   // Close the backup stdin file descriptor
    close(stdout_backup); // Close the backup stdout file descriptor

    data->last_exit_code = 0;
}

